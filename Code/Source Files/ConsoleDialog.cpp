#include <sstream>
#include <fstream>
#include <iostream>
#include "ConsoleDialog.h"
#include "HashTable_Tester.h"
#include "RobinHashTable.h"
#include "QuadraticHashTable.h"
#include "LinearHashTable.h"

using std::string;
using std::cout;
using std::cin;
using std::ostream;
using std::ofstream;

HashTable_Interface* ConsoleDialog::_GetTable(TableID id) {
	switch (id) {
		case Robin:
		return new RobinHashTable(settings.table_size);
		break;
		case Quad:
		return new QuadraticHashTable(settings.table_size);
		break;
		case Linear:
		return new LinearHashTable(settings.table_size);
		break;
	}
	return nullptr;
}

ConsoleDialog::Command ConsoleDialog::_GetCommand(string command) {
	int i = 0;
	while ((command_list[i].id != null_command) && (command_list[i].name != command)) {
		i++;
	}
	return command_list[i];
}

ConsoleDialog::CommandID ConsoleDialog::_GetCommandID(string command) {
	Command element = _GetCommand(command);
	if (element.id == null_command) throw 1;
	else return element.id;
}

int ConsoleDialog::_GetTableIndex(std::string name) {
	int i = 0;
	while ((i < Settings::tables_count)&&(name != tables[i].name)) {
		i++;
	}
	if (i == Settings::tables_count) throw 1;
	else return i;
}

void ConsoleDialog::_PrintCommands() {
	cout << "Доступные команды:\n";
	int i = 0;
	while (command_list[i].name.length()) {
		cout << command_list[i].name << " - ";
		cout << command_list[i].description;
		i++;
	}
	cout << '\n';
}

void ConsoleDialog::_PrintDes(int i, ostream& out) {
	out << "    " << tables[i].name << " - ";
	out << tables[i].description;
}

void ConsoleDialog::_PrintAllDes() {
	cout << "Варианты хеш-таблиц:\n";
	for (int i = 0; i < settings.tables_count; i++) {
		_PrintDes(i);
		cout << '\n';
	}
}

void ConsoleDialog::Run() {
	setlocale(LC_ALL, "Rus");
	cout << "Лабораторная работа №4\n";
	cout << "По курсу Структуры и алгоритмы обработки данных\n";
	cout << "Выполнил студент группы КТбо2-6\n";
	cout << "Давиденко Родион Романович\n\n";

	_PrintCommands();
	string command;
	HashTable_Tester tester(settings.source);
	//Консольный цикл
	while (true) {
		std::stringstream command_line;
		cin >> command;
		try {
			switch (_GetCommandID(command)) {
				case info:
					std::getline(cin, command);
					if (command.length()) {
						command_line << command;
						command_line >> command;
						Command elem = _GetCommand(command);
						if (elem.id == null_command) {
							if (command == "tables") {
								_PrintAllDes();
							} else if (command == "settings") {
								cout << "Установленные настройки:\n";
								cout << "Размер хеш-таблиц \n\
    TableSize = " << settings.table_size << '\n';
								cout << "Источник данных для тестирования \n\
    FileSourceData = " << settings.source << '\n';
								cout << "Файл, куда выводится отчёт \n\
    FileOutputData = " << ((settings.output.length()) ? settings.output : "CONSOLE") << '\n';
							} else throw 1;
						}
						else {
							cout << elem.more;
						}
					}
					else {
						_PrintCommands();
					}
					break;
				case set:
					std::getline(cin, command);
					if (command.length()) {
						command_line << command;
						command_line >> command;
						if (command == "FileSourceData") {
							command_line >> settings.source;
						}
						else if (command == "FileOutputData") {
							command_line >> settings.output;
						}
						else if (command == "TableSize") {
							command_line >> settings.table_size;
						}
						else throw 1;
					}
					else {
						cout << command_list[static_cast<int>(set)].more;
					}
				break;
				case test:
					std::getline(cin, command);
					if (command.length()) {
						command_line << command;
						command_line >> command;
						int i = _GetTableIndex(command);
						HashTable_Interface* table = _GetTable(tables[i].id);
						tester.Open(settings.source);
						if (settings.output.length()) {
							ofstream file(settings.output, std::ios_base::app);
							_PrintDes(i, file);
							tester.Test(*table, Settings::points_count, settings.points, file);
							file << "\n";
						}
						else {
							_PrintDes(i);
							tester.Test(*table, Settings::points_count, settings.points, cout);
							cout << "\n";
						}
						delete table;
					}
					else {
						cout << command_list[static_cast<int>(test)].more;
					}
				break;
				case exit:
					return;
				break;
			}
		}
		catch (int error) {
			switch (error) {
				case 1:
					cout << "Неверный синтаксис введённой команды\n";
				break;
			}
		}
	}
}