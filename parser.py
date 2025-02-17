from string import digits
import json
from concurrent.futures import  as_completed, ThreadPoolExecutor
import re
import requests
import mwparserfromhell


SESSION = requests.Session()
API_URL = "https://royalquest.info/api.php"

BASE_TRANSLATION_MAP = {
    "Атака": "attack",
    "ЦенаМодификации1": "modificationPrice1",
    "Создаётся": "created",
    "З1": "green1",
    "С1": "blue1",
    "Ф1": "violet1",
    "О1": "orange1",
    "Уровень": "level",
    "Ограничение":"limitation",
    "Особенность":"peculiarity",
    "Особенность1":"peculiarity1",
    "Перезарядка": "reloading",
    "Ограничения": "restrictions",
    "СоздаётсяШт": "createdPieaces",
    "Особое свойство": "specialProperties",
    "Воздействие": "impact",
    "Предмет1":"item1",
    "Знаки": "signs",
    "Слот1":"slot1",
    "Бонус": "bonus",
    "Бонус1": "stat1",
    "Модификация1":"modification1",
    "Класс1": "heroClass1",
    "НаградаИвента":"eventReward",
    "Устаревший":"outdated",
    "Пол":"sex",
    "Дроп1":"drop1",
    "Описание":"description",
    "Ивент":"event",
    "Рецепт1": "recipe1",
    "КлассПредмета": "itemClass",
    "МинУровень": "minLevel",
    "Скорость атаки": "attackSpeed",
    "Слоты": "slots",
    "Тип": "type",
    "Урон в секунду": "damagePerSecond",
    "ФактУровень": "level",
    "Защита": "defence",
    "Цена":"price"
}

def get_items_by_category(category: str):
    all_items = []
    cmcontinue = None

    while True:
        params = {
            "action": "query",
            "list": "categorymembers",
            "cmtitle": f"Категория:{category}",
            "cmlimit": "500",
            "format": "json"
        }
        if cmcontinue:
            params["cmcontinue"] = cmcontinue

        response = requests.get(API_URL, params=params)
        data = response.json()

        all_items.extend(data["query"]["categorymembers"])

        if "continue" in data:
            cmcontinue = data["continue"]["cmcontinue"]
        else:
            break

    return [item["title"] for item in all_items]

def translate(item: dict):
    for k in list(item):
        if not k.isdigit() and k in BASE_TRANSLATION_MAP:
            if k[-1] in digits:
                key_without_digit = re.sub(r"[0-9]+", "", k)
                i = 1
                while True:
                    if key_without_digit+str(i)not in item:
                        break
                    item[BASE_TRANSLATION_MAP[k][:-1]+str(i)] = item[key_without_digit+str(i)]
                    del item[key_without_digit+str(i)]
                    i += 1
            else:
                item[BASE_TRANSLATION_MAP[k]] = item[k]
                del item[k]

def convert_to_array(item: dict):
    keys = list(item)
    to_change = []

    for k in keys:
        if k[-1] in digits:
            to_change.append(re.sub(r"[0-9]+", "", k))

    for k in list(set(to_change)):
        i = 1
        array = []
        while True:
            if f"{k}{i}" not in item:
                break

            array.append(item[f"{k}{i}"])
            del item[f"{k}{i}"]
            i+=1

        item[k+'s'] = array


def get_item_data(name: str):
    params = {
        "action": "query",
        "titles": name,
        "prop": "revisions",
        "rvprop": "content",
        "formatversion": "2",
        "format": "json"
    }
    response = SESSION.get(API_URL, params=params)
    data = response.json()
    page = data["query"]["pages"][0]

    if "revisions" in page:
        raw_content = page["revisions"][0]["content"]
        wikicode = mwparserfromhell.parse(raw_content)
        templates = wikicode.filter_templates()

        for template in templates:
            item_data = {param.name.strip(): param.value.strip() for param in template.params}

        translate(item_data)
        convert_to_array(item_data)

    return {f"{name}":item_data}


def fetch_category_items_multithreaded(category, max_threads=10):
    """ Получает данные всех предметов в категории в несколько потоков """
    items = get_items_by_category(category)
    results = {}

    with ThreadPoolExecutor(max_threads) as executor:
        future_to_item = {executor.submit(get_item_data, item): item for item in items}

        for future in as_completed(future_to_item):
            item_name = future_to_item[future]
            try:
                data = future.result()
                results.update(data)
            except Exception as exc:
                print(f"Ошибка при обработке {item_name}: {exc}")

    return results

def save_to_json(data, filename):
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

def main():
    categories = {
        "Оружие": "weapons.json",
        "Экипировка": "equipment.json",
        "Карты": "cards.json",
        "Магические_печати": "seals.json"
    }

    for category, filename in categories.items():
        print(f"⏳ Парсим категорию: {category}")
        items_data = fetch_category_items_multithreaded(category, max_threads=10)
        print(f"✅ Сохранено {len(items_data)} предметов в {filename}")
        save_to_json(items_data, filename)

if __name__ == "__main__":
    main()
