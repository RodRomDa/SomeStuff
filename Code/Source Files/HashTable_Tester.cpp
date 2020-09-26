#include <fstream>
#include <chrono>
#include <iomanip>
#include "HashTable_Tester.h"

using std::string;
using std::setw;
using std::setprecision;
using namespace std::chrono;

HashTable_Tester::HashTable_Tester(string file_name) {
	Open(file_name);
}

HashTable_Tester::~HashTable_Tester() {
	delete[] Key_Dataset;
}

bool HashTable_Tester::Open(string file_name) {
	std::ifstream file(file_name);
	if (!file.is_open()) return false;

	file >> data_size;
	delete[] Key_Dataset;
	Key_Dataset = new string[data_size];
	std::getline(file, Key_Dataset[0]);
	for (int i = 0; i < data_size; i++) {
		std::getline(file, Key_Dataset[i]);
	}
	file.close();
	return true;
}

void HashTable_Tester::Test(HashTable_Interface& table, size_t factors_count, const double factors[], std::ostream& output) {
	//Установка seed'а для rand
	srand(steady_clock::now().time_since_epoch().count());

	//Сохраняем состояние потока
	//перед изменением
	std::ios output_state(nullptr);
	output_state.copyfmt(output);
	setlocale(LC_ALL, "Rus");
	output << "Степень   |     Кол. поисков      |             Среднее число проб               |   Среднее затраченное время (ms)  |\n";
	output << "заполнения|   Удачи   |  Неудачи  | При добавлении |   При удаче  | При неудаче  | На одно добаление | На один поиск |\n";
	output << std::fixed;

	for (int i = 0; i < factors_count; i++) {
		size_t portion_size = (size_t)table.GetSize() * (factors[i] - table.LoadFactor());
		string* buffer = new string[2 * portion_size];
		_MakePortion(portion_size, buffer);

		//Вставка
		long long int LoadProbeCount = 0;
		//Начало счётчика
		high_resolution_clock::time_point Start = high_resolution_clock::now();
		for (int i = 0; i < portion_size; i++) {
			table.insert(buffer[i], "Some value");
			LoadProbeCount += table.LoadProbe();
		}
		//Конец счётчика
		high_resolution_clock::time_point End = high_resolution_clock::now();
		double dur_insert = duration_cast<microseconds>(End - Start).count() / (double)portion_size / 1000;

		//Поиск
		long long int GoodProbeCount = 0, BadProbeCount = 0;
		int bad_iter = portion_size;
		//Начало счётчика
		Start = high_resolution_clock::now();
		for (int i = 0; i < 2 * portion_size; i++) {
			if (i % 2) {
				table.lookup(buffer[rand() % portion_size]);
				GoodProbeCount += table.SearchProbe();
			}
			else {
				table.lookup(buffer[bad_iter++]);
				BadProbeCount += table.SearchProbe();
			}
		}
		//Конец счётчика
		End = high_resolution_clock::now();
		double dur_lookup = duration_cast<microseconds>(End - Start).count() / (double)portion_size / 1000;

		output << setprecision(1);
		output << setw(9) << factors[i] * 100 << "%|";
		output << setw(11) << portion_size << "|" << setw(11) << portion_size << '|';
		output << setprecision(3);
		output << setw(16) << LoadProbeCount / (double)portion_size << '|';
		output << setw(14) << GoodProbeCount / (double)portion_size << '|';
		output << setw(14) << BadProbeCount / (double)portion_size << '|';
		output << setw(19) << dur_insert << '|' << setw(15) << dur_lookup << '|' << '\n';

		delete[] buffer;
	}

	//Восстанавливаем состояние потока
	output.copyfmt(output_state);
}

void HashTable_Tester::_MakePortion(size_t portion_size, string portion[]) {
	for (int i = 0; i < portion_size; i++) {
		portion[i] = _TakeValue();
	}
	for (int i = portion_size; i < 2 * portion_size; i++) {
		portion[i] = _GetValue();
	}
}

string HashTable_Tester::_TakeValue() {
	int i = rand() % data_size;
	while (!Key_Dataset[i].length()) {
		i = (i + 1) % data_size;
	}
	string temp = Key_Dataset[i];
	Key_Dataset[i] = "";
	return temp;
}

string HashTable_Tester::_GetValue() const {
	int i = rand() % data_size;
	while (!Key_Dataset[i].length()) {
		i = (i + 1) % data_size;
	}
	return Key_Dataset[i];
}