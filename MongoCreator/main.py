import os
import random
import json
from datetime import datetime as DT
from datetime import timedelta

import pymongo
from dotenv import load_dotenv


def get_collection(host: str, port: int, base_name: str, collection_name: str) -> pymongo.collection.Collection:
	client = pymongo.MongoClient(host, port)
	db = client[base_name]
	collection = db[collection_name]
	
	return collection


def insert_in_collection(collection: pymongo.collection.Collection, data: dict | list) -> None:
	if isinstance(data, dict):
		collection.insert_one(data)
	elif isinstance(data, list):
		collection.insert_many(data)
	else:
		raise TypeError('Invalid data type. Need "dict or "list" types.')


def get_json_data(path_to_json: str) -> dict:
	with open(path_to_json, 'r') as json_file:
		json_data = json.load(json_file)
		
		return json_data


def get_random_date(start_date: str, end_date: str) -> str:
	START_DATE = DT.strptime(start_date, '%d.%m.%Y')
	END_DATE = DT.strptime(end_date, '%d.%m.%Y')
	delta = END_DATE - START_DATE
	date = START_DATE + timedelta(random.randint(0, delta.days))
	
	return date.strftime('%d.%m.%Y')

 
def get_data(json_data: dict) -> dict:
	START_DATE = '01.01.2017'
	END_DATE = '01.01.2023'

	data = {
		 		"Общая информация":
		 		{
			 		"Модель": random.choice(json_data['phone_models']),
			 		"Дисплей": random.choice(json_data['screen_models']),
			 		"Размеры": [
			 					random.uniform(100.0, 250.0),
			 					random.uniform(50.0, 150.0),
			 					random.uniform(5.0, 15.0)
			 					],
			 		"Вес": random.randint(100, 300),
			 		"Цвет": random.choice(json_data['phone_colors'])
		 		},
				 
				 "Оценки":[
				 			{
							  "Дата": get_random_date(START_DATE, END_DATE),
							  "Оценка": f"{random.randint(1, 11)}"
							} 
				 		    for _ in range(random.randint(10, 30))
				 		   ],

		 		"Магазин": random.choice(json_data['shops']),

		 		"товар_id": f"{random.randint(100000000, 999999999)}"
			}

	return data


def main() -> None:
	
	JSON_FILE = 'data.json'
	COUNT_OF_DOCUMENTS = 1
	
	# MongoDB params

	HOST = os.getenv('HOST')
	PORT = int(os.getenv('PORT'))
	BASE_NAME = os.getenv('BASE_NAME')
	COLLECTION_NAME = os.getenv('COLLECTION_NAME')

	collection = get_collection(host=HOST, port=PORT, base_name=BASE_NAME, collection_name=COLLECTION_NAME)
	json_data = get_json_data(JSON_FILE)
	generated_data = [get_data(json_data) for x in range(COUNT_OF_DOCUMENTS)]
	insert_in_collection(collection=collection, data=generated_data)


if __name__ == '__main__':
	load_dotenv()
	main()