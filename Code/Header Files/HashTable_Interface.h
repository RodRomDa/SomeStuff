#pragma once
#include <string>

/*
	��������� ��� ��������� ��������� ���-������
*/
class HashTable_Interface {
public:
	//���������� ������
	virtual bool insert(const std::string& key, const std::string& value) = 0;

	//�������� ������� ������
	virtual bool lookup(const std::string& key) = 0;

	//��������� ������
	virtual std::string& get(const std::string& key) = 0;

	//�������� ������
	virtual void remove(const std::string& key) = 0;

	//������� �������������
	virtual double LoadFactor() const = 0;

	//��������� ������� �������
	virtual size_t GetSize() const = 0;

	//���� ����������

	//���. ���� ��� ������
	virtual int SearchProbe() const = 0;
	//���. ���� ��� �������
	virtual int LoadProbe() const = 0;

	virtual ~HashTable_Interface() = default;
};