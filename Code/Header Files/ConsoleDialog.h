#pragma once
#include <string>
#include <iostream>
#include "HashTable_Interface.h"

class ConsoleDialog {
public:
	//������ �������
	void Run();

private:
	//��������� �������� �������
	struct Settings{
		int table_size = 2000;
		std::string source = "Names.txt";
		std::string output = "";
		static const int commands_count = 5;
		static const int tables_count = 3;
		static const int points_count = 8;
		const double points[points_count] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.75, 0.9, 0.99 };
	} settings;
	
	//ID ��� ������
	enum CommandID {
		exit = 0,
		info,
		set,
		test,
		null_command
	};

	//��������� ����� �������
	const struct Command {
		CommandID id;
		std::string name;
		std::string description;
		std::string more;
	} //������ ������
	command_list[Settings::commands_count] = {
		{
			exit, 
			"exit", 
			"����� �� ���������\n",
			"exit - ��������� ������\n"
		},
		{
			info,
			"info", 
			"�������� ���������� � �������/���-�������/����������\n\
    info [command] - ��� ���������� � �������\n\
    info tables - ��� ���������� � ���-��������\n\
    info settings - ��� ��������� � ����������\n",
			"�������� ���������� � �������/���-�������/����������\n\
info [command] - ��� ���������� � �������\n\
info tables - ��� ���������� � ���-��������\n\
info settings - ��� ��������� � ����������\n"
		},
		{
			set,
			"set",
			"������ �������� ��������\n",
			"set [�������] - ������ �������� ��������\n\
�������� = FileSourceData ���_����� - ������ ������ ������������ ���-������\n\
�������� = FileOutputData ���_����� - ������ ��� ����� ������ ������\n\
(�� ��������� � �������)\n\
�������� = TableSize ����� - ������ ������ ���-������\n"
		},
		{
			test,
			"test",
			"��������� ������������ ���-������\n",
			"test [���-�������] - ������ ����� � ������ ��� ������� � ������� ��� �� �����\n\
����� ������ � ��������� [���-�������] ������� info tables\n", 
		},
		{null_command, "", "", ""}
	};

	//ID �������� ���-�������
	enum TableID {
		Robin = 0,
		Quad,
		Linear
	};

	//��������� ���������� � ���-�������
	const struct TableInfo {
		std::string name;
		TableID id;
		std::string description;
	}
	tables[Settings::tables_count] = {
		{"RobinHashTable", Robin,
		"���������� �������� � ���� ���-�������\n\
�������� �� ��������� Robin Hood.\n\
��� ����������� ��������� ������ ������������\n\
�������� FNV � ������������ ���������� (4 ��������) � �����.\n"},
		{"QuadraticHashTable", Quad,
		"��� ���������� �������� � ���� ���-�������\n\
����������� ������������ �����.\n\
��� ����������� ��������� ������ ������������\n\
����������� �������������� � ����������� �������,\n\
� ����� ������������ ����������� ���������� (2 ��������)\n"},
		{"LinearHashTable", Linear,
		"��� ���������� �������� � ���� ���-�������\n\
����������� ������������ �����.\n\
��� ����������� ��������� ������ ������������\n\
�������� �� ������ �������� �����\n"}
	};
	//�������� ������� �� ���������� �������������
	Command _GetCommand(std::string command);

	//�������� ID �������� �� ���������� �������������
	CommandID _GetCommandID(std::string command);

	//�������� ������ �������� �������
	int _GetTableIndex(std::string name);

	//�������� ��������� �� ��������� �������
	//�� ��������� id
	HashTable_Interface* _GetTable(TableID id);

	//������� ������ ������
	void _PrintCommands();

	//������� �������� �������� ���-�������
	void _PrintDes(int i, std::ostream& out = std::cout);

	//������� �������� ���� ��������� ���-�������
	void _PrintAllDes();
};