#include <chrono>
#include <ctime>
#include <iostream>
using namespace std;


// ЗАПИСЫВАЕТ НАПОМИНАНИЕ

string bookmark()
{
	string reminder;
	cout << "Введите напоминание: "; cin >> reminder;
	return reminder;
}
// ЗАПИСЫВАЕТ ДАТУ
string dates()
{
	string date;
	cout << "Введите когда вам напомнить: "; cin >> date;
	cout << "Дата запомнина." << endl;
	return date;
}

// ДОЛЖНО ЗАПИСЫВАТЬ ЯЧЕЙКУ ЕСЛИ ОНА СОДЕРЖИТ ПУСТУЮ СТРОКУ
void recording(string arr[], int size, string info) {

	for (int i = 0; i < size; i++) {
		if (arr[i] != "") {
			arr[i] = info;
			break;
		}

	}
		
}
// СОЗДОЁТ СПИСОК СОСТО ЯЩИЙ ИЗ ПУСТЫХ СТРОК
void fill_array(string arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = "";
	}
}
// НЕ РОБОТОЕТ ПОЧИНИТЬ | ДОЛЖЕН ВЫВОДИТЬ СПИСОК ЕСЛИ ЯЧЕЙКА НЕ ПУСТАЯ.
void print_list(string arr1[], string arr2[]) {


	for (int i = 0; arr1[i] != ""; i++) {

		cout << "Ячейка "<< i <<"  "<< arr1[i] <<"--"<< arr2[i] << endl;
	}

}


int main()
{
	system("chcp 1251");

	string reminder;
	string date;
	int request;
	const int limit = 500;
	string list_reminder[limit];
	string list_date[limit];

	fill_array(list_reminder, limit);
	fill_array(list_date,limit);
	do
	{


		cout << "Хотите добавить напоминание? |1-да|0-нет|2-посмотреть список напоминаний|" << endl;cin >>request;
		if (request == 1)
		{
			reminder = bookmark();
			date = dates();


			recording(list_reminder, limit, reminder);
			recording(list_date, limit, date);

		}else if(request == 2) {

			print_list(list_date, list_reminder);
		}



	} while (request != 0);

}




