#pragma once
#include "HashTable_Interface.h"

/*
	������ ���-������� ���������� ��������
	������������ ���� ��� �������/������/��������.
	������ ������� �������� �������� 2.
*/
struct QuadraticHashTable : HashTable_Interface {

public:

	QuadraticHashTable(size_t size);

	~QuadraticHashTable();

	//����������� ������������� �������� (2 �������� ����)
	//������������ �������� ���������
	uint16_t hash_int(uint16_t x);

	//����������� ������
	//������������� � ����������� �������
	uint16_t hash_str(const std::string& key);

	//���������� ������
	bool insert(const std::string& key, const std::string& value) override;

	//�������� ������� ������
	bool lookup(const std::string& key) override;

	//��������� ������
	std::string& get(const std::string& key) override;

	//�������� ������
	void remove(const std::string& key) override;

	//������� �������������
	double LoadFactor() const override;

	//��������� ������� �������
	size_t GetSize() const override;

	//���� ����������

	//���. ���� ��� ������
	int SearchProbe() const override;
	//���. ���� ��� �������
	int LoadProbe() const override;

private:
	//��������� ����� ������ �������
	struct Data {
		std::string key;
		size_t state = 0;//0 - ������, 1 - �����������, 2 - ��������
		std::string value;
	};

	Data* table;
	//���������� ����������
	size_t load = 0;
	//�������� ������� �������
	size_t size_log = 1;
	//������ �������
	size_t table_size = 1;

	//���� ����������

	//���������� ���� ��� �������
	size_t load_probe = 0;
	//���������� ���� ��� ������
	size_t search_probe = 0;

	//��������� ������� � ������� �� ����� 
	//���������� -1, ���� ����� � ������� ���
	int _GetIndex(const std::string& key);
};
