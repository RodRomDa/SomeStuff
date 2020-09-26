#include "LinearHashTable.h"
using std::string;

LinearHashTable::LinearHashTable(size_t size) {
	table_size = size;
	table = new Data[table_size];
}

LinearHashTable::~LinearHashTable() {
	delete[] table;
}

uint32_t LinearHashTable::hash_str(const string& key) {
	const char* ptr = key.c_str();
	uint32_t hash = 4294967279u;
	while (*ptr) {
		hash = (hash + *ptr) % 4294967291u;
		ptr++;
	}
	return hash % table_size;
}

bool LinearHashTable::insert(const string& key, const string& value) {
	size_t i0 = hash_str(key);
	size_t i = i0;
	//Для подсчёта среднего числа проб
	load_probe = 1;
	while (table[i].state & 1) {
		i++;
		if (i >= table_size) {
			i = 0;
		}
		if (i == i0) {
			return false;
		}
		load_probe++;
	}
	table[i].key = key;
	table[i].state = 1;
	table[i].value = value;
	load++;
	return true;
}

bool LinearHashTable::lookup(const string& key) {
	return (_GetIndex(key) != -1);
}

string& LinearHashTable::get(const string& key) {
	return (table[_GetIndex(key)].value);
}

void LinearHashTable::remove(const string& key) {
	int i = _GetIndex(key);
	if (i != -1) {
		//Запись удалена
		table[i].state = 2;
		load--;
	}
}

int LinearHashTable::_GetIndex(const string& key) {
	size_t i0 = hash_str(key);
	size_t i = i0;
	//Для подсчёта среднего числа проб
	search_probe = 1;
	//Ищем запись методом линейных проб, пропускаем удалённые
	while (table[i].state&&((table[i].state == 2)||(table[i].key != key))) {
		i++;
		if (i >= table_size) {
			i = 0;
		}
		if (i == i0) {
			return -1;
		}
		search_probe++;
	}
	//Если ячейка заполнена - то нашли
	if (table[i].state == 1) {
		return i;
	}
	else {
		return -1;
	}
}

double LinearHashTable::LoadFactor() const {
	return load / (double)table_size;
}

size_t LinearHashTable::GetSize() const {
	return table_size;
};

int LinearHashTable::SearchProbe() const {
	return search_probe;
}

int LinearHashTable::LoadProbe() const {
	return load_probe;
}