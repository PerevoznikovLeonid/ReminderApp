#include <iostream>
#include <vector>
#include <string>

using namespace std;


// ЗАПИСЫВАЕТ НАПОМИНАНИЕ
string bookmark()
{
	string reminder;
	cout << "Введите напоминание: ";
	getline(cin, reminder);
	return reminder;
}
// ЗАПИСЫВАЕТ ДАТУ
string dates()
{
	string date;
	cout << "Введите когда вам напомнить: ";
	getline(cin, date);
	cout << "Дата запомнена." << endl;
	return date;
}

// ВЫВОДИТ СПИСОК НАПОМИНАНИЙ
void print_list(vector<string> bookmarks, vector<string> dates) {
	for (int i = 0; i < bookmarks.size(); i++)
	{
		cout << i <<": ( Напоминание: " << bookmarks[i] << "; Дата: " << dates[i] << " )" << endl;
	}
}

//УДАЛЯЕТ ЯЧЕЙКИ
void delete_reminder(vector<string>& bookmarks, vector<string>& dates)
{
	string delete_index;
	cout << "Введите номер напоминания: ";
	getline(cin, delete_index);

	//TODO: Обработчик ошибок на случай некорректного индекса

	bookmarks.erase(bookmarks.begin() + stoi(delete_index));
	dates.erase(dates.begin() + stoi(delete_index));
}


int main()
{
	system("chcp 1251");

	string reminder;
	string date;
	string request;
	vector<string> list_reminder;
	vector<string> list_date;

	while (request != "0")
	{
		cout << "Хотите добавить напоминание? |1-да|0-нет|2-посмотреть список напоминаний|3-удалить напоминание" << endl;
		getline(cin, request);
		if (request == "1")
		{
			reminder = bookmark();
			date = dates();

			list_reminder.push_back(reminder);
			list_date.push_back(date);

		}
		else if (request == "2") {

			print_list(list_reminder, list_date);
		}
		else if (request == "3") {
			delete_reminder(list_reminder, list_date);
		}
	}
}
