#pragma once
#include <string>
#include <iostream>
#include "HashTable_Interface.h"

class ConsoleDialog {
public:
	//Начало диалога
	void Run();

private:
	//Структура настроек диалога
	struct Settings{
		int table_size = 2000;
		std::string source = "Names.txt";
		std::string output = "";
		static const int commands_count = 5;
		static const int tables_count = 3;
		static const int points_count = 8;
		const double points[points_count] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.75, 0.9, 0.99 };
	} settings;
	
	//ID для команд
	enum CommandID {
		exit = 0,
		info,
		set,
		test,
		null_command
	};

	//Структура одной команды
	const struct Command {
		CommandID id;
		std::string name;
		std::string description;
		std::string more;
	} //Список команд
	command_list[Settings::commands_count] = {
		{
			exit, 
			"exit", 
			"выход из программы\n",
			"exit - Завершить работу\n"
		},
		{
			info,
			"info", 
			"получить информацию и команде/хеш-таблице/настройках\n\
    info [command] - для информации о команде\n\
    info tables - для информации о хеш-таблицах\n\
    info settings - для информции о настройках\n",
			"Получить информацию и команде/хеш-таблице/настройках\n\
info [command] - для информации о команде\n\
info tables - для информации о хеш-таблицах\n\
info settings - для информции о настройках\n"
		},
		{
			set,
			"set",
			"задать параметр настроек\n",
			"set [парамер] - задать параметр настроек\n\
параметр = FileSourceData имя_файла - задать ресурс тестирования хеш-таблиц\n\
параметр = FileOutputData имя_файла - задать имя файла выдачи отчета\n\
(по умолчанию в консоль)\n\
параметр = TableSize число - задать размер хеш-таблиц\n"
		},
		{
			test,
			"test",
			"запустить тестирование хеш-таблиц\n",
			"test [хеш-таблица] - Создаёт отчёт о работе хеш таблицы и выводит его на экран\n\
Чтобы узнать о параметре [хеш-таблица] введите info tables\n", 
		},
		{null_command, "", "", ""}
	};

	//ID варианта хеш-таблицы
	enum TableID {
		Robin = 0,
		Quad,
		Linear
	};

	//Структура информации о хеш-таблице
	const struct TableInfo {
		std::string name;
		TableID id;
		std::string description;
	}
	tables[Settings::tables_count] = {
		{"RobinHashTable", Robin,
		"Разрешение коллизий в этой хеш-таблице\n\
основано на алгоритме Robin Hood.\n\
Для хеширования строковых ключей используется\n\
алгоритм FNV с хешированием умножением (4 байтовое) в конце.\n"},
		{"QuadraticHashTable", Quad,
		"Для разрешения коллизий в этой хеш-таблице\n\
применяются квадратичные пробы.\n\
Для хеширования строковых ключей используется\n\
хеширование перемешиванием с циклическим сдвигом,\n\
в конце производится хеширование умножением (2 байтовое)\n"},
		{"LinearHashTable", Linear,
		"Для разрешения коллизий в этой хеш-таблице\n\
применяются квадратичные пробы.\n\
Для хеширования строковых ключей используется\n\
сложение по модулю простого числа\n"}
	};
	//Получить команду по строковому представлению
	Command _GetCommand(std::string command);

	//Получить ID комманды по строковому представлению
	CommandID _GetCommandID(std::string command);

	//Получить индекс варианта таблици
	int _GetTableIndex(std::string name);

	//Получить указатель на созданную таблицу
	//по заданному id
	HashTable_Interface* _GetTable(TableID id);

	//Вывести список команд
	void _PrintCommands();

	//Вывести описание варианта хеш-таблицы
	void _PrintDes(int i, std::ostream& out = std::cout);

	//Вывести описание всех вариантов хеш-таблицы
	void _PrintAllDes();
};