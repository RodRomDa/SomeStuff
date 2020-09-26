#pragma once
#include "HashTable_Interface.h"

/*
	Данная хеш-таблица использует алгоритм
	квадратичных проб для вставки/поиска/удаления.
	Размер таблицы является степенью 2.
*/
struct QuadraticHashTable : HashTable_Interface {

public:

	QuadraticHashTable(size_t size);

	~QuadraticHashTable();

	//Хеширование целочисленных значений (2 байтовых слов)
	//Используется алгоритм умножения
	uint16_t hash_int(uint16_t x);

	//Хеширование строки
	//Перемешивание с циклическим сдвигом
	uint16_t hash_str(const std::string& key);

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
	//Логарифм размера таблицы
	size_t size_log = 1;
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
