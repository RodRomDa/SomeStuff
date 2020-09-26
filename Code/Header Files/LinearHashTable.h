#pragma once
#include "HashTable_Interface.h"

struct LinearHashTable : HashTable_Interface {

public:

	LinearHashTable(size_t size);

	~LinearHashTable();


	//Хеширование строки
	//Алогритм деления
	uint32_t hash_str(const std::string& key);

	//Добавление записи
	bool insert(const std::string& key, const std::string& value) override;

	//Проверка наличия записи
	bool lookup(const std::string& key) override;

	//Получение записи
	std::string& get(const std::string& key) override;

	//Удаление записи
	void remove(const std::string& key) override;

	//Степень заполненности
	double LoadFactor() const override;

	//Получение размера таблицы
	size_t GetSize() const override;

	//Сбор статистики

	//Кол. проб при поиске
	int SearchProbe() const override;
	//Кол. проб при вставке
	int LoadProbe() const override;

private:
	//Структура одной записи таблицы
	struct Data {
		std::string key;
		size_t state = 0;//0 - пустая, 1 - заполненная, 2 - удалённая
		std::string value;
	};

	Data* table;
	//Количество заполнения
	size_t load = 0;
	//Размер таблицы
	size_t table_size = 1;

	//Сбор статистики

	//Количество проб при вставке
	size_t load_probe = 0;
	//Количество проб при поиске
	size_t search_probe = 0;

	//Получение индекса в таблице по ключу 
	//Возвращает -1, если ключа в таблице нет
	int _GetIndex(const std::string& key);
};