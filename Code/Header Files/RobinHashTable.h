#pragma once
#include "HashTable_Interface.h"

/*
	������ ���-������� �������� �� ��������� RobinHood
	(������������ � �������� �������/������/��������).
	������ ������� �������� �������� 2.
*/
class RobinHashTable : public HashTable_Interface {
public:

	RobinHashTable(size_t size);

	~RobinHashTable();

	//����������� ������������� �������� (4 �������� ����)
	//������������ �������� ��������� c ������������� ����������
	uint32_t hash_int(uint32_t x) const;

	//����������� ������ (�������� FNV)
	uint32_t hash_str(const std::string& key) const;

	//���������� ������
	bool insert(const std::string& key, const std::string& value) override;

	//����� �� �����
	bool lookup(const std::string& key) override;

	//��������� ������ ������
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
		size_t probe_length; //C������� �� ����� �����������
		std::string value;

		Data() : key(""), probe_length(0) {};
		Data(std::string key, std::string value) : key(key), probe_length(0), value(value) {};

		Data& operator=(const Data& other) = default;
		//������ ����� ������ �� ������
		void swap(Data& other);
	};

	Data* table;
	//���������� ����������
	size_t load = 0;
	//�������� ������� �������
	size_t size_log = 1;
	//������ �������
	size_t table_size = 1;

	//��� ����� ����������

	//���������� ���� ��� �������
	size_t load_probe = 0;
	//���������� ���� ��� ������
	size_t search_probe = 0;

	//��������� ������� � ������� �� ����� 
	//���������� -1, ���� ����� � ������� ���
	int _GetIndex(const std::string& key);
};