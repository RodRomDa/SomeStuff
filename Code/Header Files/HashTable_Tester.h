#pragma once
#include <iosfwd>
#include "HashTable_Interface.h"

/*
	����� ������������ ���-������ �� ���������� ������ ������
*/
class HashTable_Tester {
public:
	HashTable_Tester() = default;

	//������ ������, �������� ������� �� file_name 
	HashTable_Tester(std::string file_name);

	~HashTable_Tester();

	/*
		��������� ������� �� ����� file_name 
		���� ��� ������������ ������ ������������ �����
		������������������ �����, ������ �� ������� ���������������� ���
		���� ��� ������� � ���-�������.
		������ ������ ������ ��������� ����� ���������� �����
	*/
	bool Open(std::string file_name);

	/*
		��������� ������� �� ������ � ��������� ��������� � output
		������� ������:
		table - ������� ��� ������������
		factors_count - ���������� �������� ������� ����������
		factors - ������������ ������� ���������� �������, �� �������
		��������� ������
		output - ����� ������ ����������
	*/
	void Test(HashTable_Interface& table, 
			  size_t factors_count,
			  const double factors[], 
			  std::ostream& output);

private:
	//��������� �� ������� ������
	std::string* Key_Dataset = nullptr;
	//��������� �� ������� ������
	size_t data_size = 0;

	/* 
		�������� ������ ������ ��� �������
		��������� portion_size ������ �� �������
		������ portion[] ������ ����� ������ 2*portion_size
		� ������ �������� ��������� ����� ��� �������
		�� ������ - ����� ��� ���������� ������
	*/
	void _MakePortion(size_t portion_size, std::string portion[]);

	//���������� �� ������� ��������� ����
	std::string _TakeValue();

	//���������� ��������� ����
	//�� �������� ���
	std::string _GetValue() const;
};