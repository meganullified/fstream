#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<vector>

void show() {
	std::string name;
	std::vector<std::string> name_list;
	std::string quantity;
	std::vector<std::string> quantity_list;
	std::string cost;
	std::vector<std::string> cost_list;
	std::ifstream read;
	read.open("name.txt");
	unsigned int i = 0, j = 0, l = 0;
	while (std::getline(read, name, '\n')) { name_list.push_back(name); i++; }
	read.close();
	read.open("quantity.txt");
	while (std::getline(read, quantity, '\n')) { quantity_list.push_back(quantity); j++; if (j > i) i++; }
	read.close();
	read.open("cost.txt");
	while (std::getline(read, cost, '\n')) { cost_list.push_back(cost); l++; if (l > i) i++; }
	read.close();

	std::cout << std::setfill('.') << std::left << std::setw(20)
		<< "Наименование" << std::left << std::setw(10)
		<< "Кол-во" << "Цена" << '\n';
	for (unsigned int k = 0; k < i; k++) {
		name_list.push_back(""); // Костыль, чтобы игнорировать возможное остутствие элементов
		quantity_list.push_back("");
		cost_list.push_back("");
		std::cout << std::setfill('.') << std::left << std::setw(20)
			<< name_list[k] << std::left << std::setw(10)
			<< quantity_list[k] << cost_list[k] << '\n';
	}
}

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	char cmd;
	std::cout << "Доступные команды:\n"
		"\tn - редактировать названия\n"
		"\tq - редактировать количество\n"
		"\tc - редактировать стоимость\n"
		"\ts - отобразить информацию\n"
		"\tx - закрыть программу\n";
	while (true) {
		std::cout << ">> ";
		std::cin >> cmd;
		std::string filename;
		if (cmd == 'n') { filename = "name.txt"; }
		else if (cmd == 'q') { filename = "quantity.txt"; }
		else if (cmd == 'c') { filename = "cost.txt"; }
		else if (cmd == 's') { show(); continue; }
		else if (cmd == 'x') { break; }
		else { continue; }
		std::ofstream out;
		char to_truncate;
		std::cout << "Перезаписать информацию? (y/n) ";
		std::cin >> to_truncate;
		if (to_truncate == 'y' || to_truncate == 'Y') { out.open(filename, std::ios::out | std::ios::trunc); }
		else { out.open(filename, std::ios::app); }
		if (out.is_open()) {
			std::cout << "Вводите значения через новую строку\nДля завершения введите тильду (~)\nи нажмите Enter\n\n";
			std::string data;
			std::getline(std::cin, data, '~');
			out << data.erase(0, 1);
			out.close();
		}
		else {
			std::cout << "Произошла ошибка: невозможно открыть файл для записи.\n";
			continue;
		}
	}

	return 0;
}