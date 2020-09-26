#pragma once
#include "HashTable_Interface.h"

/*
	Данная хеш-таблица основана на алгоритме RobinHood
	(используется в операции вставки/поиска/удаления).
	Размер таблицы является степенью 2.
*/
class RobinHashTable : public HashTable_Interface {
public:

	RobinHashTable(size_t size);

	~RobinHashTable();

	//Хеширование целочисленных значений (4 байтовых слов)
	//Используется алгоритм умножения c фибоначчиевой константой
	uint32_t hash_int(uint32_t x) const;

	//Хеширование строки (алгоритм FNV)
	uint32_t hash_str(const std::string& key) const;

	//Добавление записи
	bool insert(const std::string& key, const std::string& value) override;

	//Поиск по ключу
	bool lookup(const std::string& key) override;

	//Получение данных записи
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
		size_t probe_length; //Cмешение от точки хеширования
		std::string value;

		Data() : key(""), probe_length(0) {};
		Data(std::string key, std::string value) : key(key), probe_length(0), value(value) {};

		Data& operator=(const Data& other) = default;
		//Замена одной записи на другую
		void swap(Data& other);
	};

	Data* table;
	//Количество заполнения
	size_t load = 0;
	//Логарифм размера таблицы
	size_t size_log = 1;
	//Размер таблицы
	size_t table_size = 1;

	//Для сбора статистики

	//Количество проб при вставке
	size_t load_probe = 0;
	//Количество проб при поиске
	size_t search_probe = 0;

	//Получение индекса в таблице по ключу 
	//Возвращает -1, если ключа в таблице нет
	int _GetIndex(const std::string& key);
};