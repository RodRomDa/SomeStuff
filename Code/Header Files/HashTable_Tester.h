#pragma once
#include <iosfwd>
#include "HashTable_Interface.h"

/*
	Класс тестирования хеш-таблиц на конкретном наборе данных
*/
class HashTable_Tester {
public:
	HashTable_Tester() = default;

	//Создаёт объект, заполняя данными из file_name 
	HashTable_Tester(std::string file_name);

	~HashTable_Tester();

	/*
		Заполняет данными из файла file_name 
		Файл для тестирования должен представлять собой
		последоватьльность строк, каждая из которых интерпретируется как
		ключ для вставки в хеш-таблицу.
		Первая строка должна содержать общее количество строк
	*/
	bool Open(std::string file_name);

	/*
		Тестирует таблицу на данных и сохраняет результат в output
		Входные данные:
		table - таблица для тестирования
		factors_count - количество значений степени заполнения
		factors - интересующие степени заполнения таблицы, на которых
		замерятся работа
		output - поток вывода результата
	*/
	void Test(HashTable_Interface& table, 
			  size_t factors_count,
			  const double factors[], 
			  std::ostream& output);

private:
	//Указатель на таблицу ключей
	std::string* Key_Dataset = nullptr;
	//Указатель на таблицу ключей
	size_t data_size = 0;

	/* 
		Создание порции данных для вставки
		Извлекает portion_size ключей из таблицы
		Массив portion[] должен иметь размер 2*portion_size
		в первой половине находятся ключи для вставки
		во второй - ключи для неудачного поиска
	*/
	void _MakePortion(size_t portion_size, std::string portion[]);

	//Извелекает из таблицы случайный ключ
	std::string _TakeValue();

	//Возвращает случайный ключ
	//не извлекая его
	std::string _GetValue() const;
};