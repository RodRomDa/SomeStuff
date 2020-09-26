#include "QuadraticHashTable.h"
using std::string;

QuadraticHashTable::QuadraticHashTable(size_t size) {
	while (size >>= 1) {
		size_log++;
	}
	table_size <<= size_log;
	table = new Data[table_size];
}

QuadraticHashTable::~QuadraticHashTable() {
	delete[] table;
}

uint16_t QuadraticHashTable::hash_int(uint16_t x) {
	//Заменили mod и div на сдвиг.
	return (uint16_t)(x * UINT16_C(40503)) >> (16 - size_log);
}

uint16_t QuadraticHashTable::hash_str(const string& key) {
	uint16_t temp = 0;
	const uint16_t* ptr = (const uint16_t*)key.c_str();
	while (*ptr) {
		temp ^= *ptr;
		//циклический сдвиг на один разряд влево
		temp & 0x8000 ? (temp <<= 1)++ : temp <<= 1;
		ptr++;
	}
	return hash_int(temp);
}

bool QuadraticHashTable::insert(const string& key, const string& value) {
	size_t i = hash_str(key), d = 1;
	//Для подсчёта среднего числа проб
	load_probe = 1;
	while (table[i].state & 1) {
		i += d;
		d += 2;
		if (i >= table_size)
			i -= table_size;
		//Если шаг наращения стал слишком большим - останавливаем вставку
		if (i >= table_size) {
			return false;
		}
		load_probe++;
	}

	table[i].state = 1;
	table[i].key = key;
	table[i].value = value;

	load++;
	return true;
}

bool QuadraticHashTable::lookup(const string& key) {
	return _GetIndex(key) != -1;
}

string& QuadraticHashTable::get(const string& key) {
	return table[_GetIndex(key)].value;
};

void QuadraticHashTable::remove(const string& key) {
	int i = _GetIndex(key);
	if (i != -1) {
		//Запись удалена
		table[i].state = 2;
		load--;
	}
}

int QuadraticHashTable::_GetIndex(const string& key) {
	size_t i = hash_str(key), d = 1;
	//Для подсчёта среднего числа проб
	search_probe = 1;
	//Ищем запись методом квадратичных проб, пропускаем удалённые
	while (table[i].state && ((table[i].state == 2) || (key != table[i].key))) {
		i += d;
		d += 2;
		if (i >= table_size)
			i -= table_size;
		//Если шаг наращения стал слишком большим - останавливаем поиск
		if (i >= table_size) {
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

double QuadraticHashTable::LoadFactor() const {
	return load / (double)table_size;
}

size_t QuadraticHashTable::GetSize() const {
	return table_size;
};

int QuadraticHashTable::SearchProbe() const {
	return search_probe;
}

int QuadraticHashTable::LoadProbe() const {
	return load_probe;
}
