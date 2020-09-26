#include "RobinHashTable.h"
using std::string;

RobinHashTable::RobinHashTable(size_t size) {
	while (size >>= 1) {
		size_log++;
	}
	table_size <<= size_log;
	table = new Data[table_size];
}

RobinHashTable::~RobinHashTable(){
	delete[] table;
}


uint32_t RobinHashTable::hash_int(uint32_t x) const{
	//Заменили mod и div на сдвиг.
	return (uint32_t)(x * 2654435769u) >> (32 - size_log);
}

uint32_t RobinHashTable::hash_str(const string& key) const{
	uint32_t temp = 2166136261;
	const char* str = key.c_str();
	while (*str) {
		temp ^= (uint32_t)*str++;
		temp *= 16777619;
	}
	return hash_int(temp);
}

bool RobinHashTable::insert(const string& key, const string& value) {
	Data entry(key, value);
	load_probe = 1;
	size_t i0 = hash_str(key);
	if (!table[i0].key.length()) {
		table[i0] = entry;
	}
	else {
		size_t i = i0;
		do {
			while (entry.probe_length <= table[i].probe_length) {
				load_probe++;
				entry.probe_length++;
				i++;
				if (i == table_size) {
					i = 0; //возвращаемся в начало таблицы
				}
				if (i == i0) {
					return false; //не нашли свободное место
				}
			}
			table[i].swap(entry);
		} while (entry.key.length());
	}
	load++;
	return true;
}

bool RobinHashTable::lookup(const string& key) {
	return _GetIndex(key) != -1;
}

string& RobinHashTable::get(const string& key) {
	return table[_GetIndex(key)].value;
}

void RobinHashTable::remove(const string& key) {
	int i = _GetIndex(key);
	if (i != -1) {
		while (table[i + 1].probe_length) {
			table[i] = table[i + 1];
			table[i].probe_length--;
			i++;
		}
		load--;
		table[i].key = "";
		table[i].probe_length = 0;
	}
}

double RobinHashTable::LoadFactor() const {
	return load / (double)table_size;
}

size_t RobinHashTable::GetSize() const {
	return table_size;
}

int RobinHashTable::SearchProbe() const {
	return search_probe;
}

int RobinHashTable::LoadProbe() const {
	return load_probe;
}

int RobinHashTable::_GetIndex(const string& key) {
	size_t i = hash_str(key);
	size_t offset = 0;
	search_probe = 1;
	while ((table[i].key != key) && (offset <= table[i].probe_length)) {
		search_probe++;
		i++;
		if (i == table_size) {
			i = 0; //Возвращаемся в начало таблицы
		}
		offset++;
	}
	if (table[i].key == key) {
		return i;
	}
	else return -1;
}

void RobinHashTable::Data::swap(Data& other) {
	key.swap(other.key);
	value.swap(other.value);

	size_t temp = probe_length;
	probe_length = other.probe_length;
	other.probe_length = temp;
}