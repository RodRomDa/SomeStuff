#pragma once
#include <string>

/*
	Интерфейс для различных вариантов хеш-таблиц
*/
class HashTable_Interface {
public:
	//Добавление записи
	virtual bool insert(const std::string& key, const std::string& value) = 0;

	//Проверка наличия записи
	virtual bool lookup(const std::string& key) = 0;

	//Получение записи
	virtual std::string& get(const std::string& key) = 0;

	//Удаление записи
	virtual void remove(const std::string& key) = 0;

	//Степень заполненности
	virtual double LoadFactor() const = 0;

	//Получение размера таблицы
	virtual size_t GetSize() const = 0;

	//Сбор статистики

	//Кол. проб при поиске
	virtual int SearchProbe() const = 0;
	//Кол. проб при вставке
	virtual int LoadProbe() const = 0;

	virtual ~HashTable_Interface() = default;
};