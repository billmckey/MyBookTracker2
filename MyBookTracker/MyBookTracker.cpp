#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <string>
using namespace std;
const int max_books = 1000;
struct BOOKS
{
	char date[11];
	char name[40];
	char author[40];
	float grade;
};

BOOKS books[max_books];
int bookkolvo = 0;

void loadBooks(const char* filename)
{
	ifstream fin(filename);
	if (!fin)
		return;
	bookkolvo = 0;
	string date_str, name_str, author_str, grade_str;
	while (getline(fin, date_str, '|') &&
		getline(fin, name_str, '|') &&
		getline(fin, author_str, '|') &&
		getline(fin, grade_str))
	{
		if (date_str.length() < 11)
			date_str.copy(books[bookkolvo].date, date_str.length());
		books[bookkolvo].date[date_str.length()] = '\0';
		if (author_str.length() < 40)
			author_str.copy(books[bookkolvo].author, author_str.length());
		books[bookkolvo].author[author_str.length()] = '\0';
		if (name_str.length() < 40)
			name_str.copy(books[bookkolvo].name, name_str.length());
		books[bookkolvo].name[name_str.length()] = '\0';

		books[bookkolvo].grade = stof(grade_str);
		bookkolvo++;
	}
	fin.close();
}
void saveBOOKSToFIle(const char* filename)
{
	ofstream fout(filename);
	if (!fout)
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	for (int i = 0; i < bookkolvo; i++)
	{
		fout << books[i].date << "|" << books[i].name << "|" << books[i].author << "|" << books[i].grade << endl;
	}
	fout.close();
}
void addBook()
{
	if (bookkolvo >= max_books)
	{
		cout << "хватит" << endl;
		return;
	}
	BOOKS e;

	cout << "дата (гггг.дд.мм) ";
	cin >> e.date;

	cout << "Автор (И.О.Фамилия) ";
	cin >> e.author;

	cout << "введите название ";
	cin.ignore();
	cin.getline(e.name, 40);

	cout << "понравилось? ";
	cin >> e.grade;

	books[bookkolvo++] = e;
	saveBOOKSToFIle("books.txt");
	cout << "новая книга\n";
}
void showallbooks()
{
	if (bookkolvo == 0)
	{
		cout << "нет данных\n";
		return;
	}

	cout << "\n ---ВСЕ КНИГИ---\n";
	cout << left << setw(15) << "дата"
		<< setw(25) << "название "
		<< setw(30) << "автор "
		<< "оценка\n";
	cout << "========================================================================================\n";
	for (int i = 0; i < bookkolvo; i++)
	{
		cout << left << setw(15) << books[i].date
			<< setw(25) << books[i].name
			<< setw(30) << books[i].author
			<< books[i].grade << " баллов\n";
	}
}
void showgrades()
{
	if (bookkolvo == 0)
	{
		cout << "нет данных\n";
		return;
	}
	float total = 0;
	float max = books[0].grade;
	for (int i = 0; i < bookkolvo; i++)
	{
		total += books[i].grade;
		if (books[i].grade > max)
		{
			max = books[i].grade;
		}
	}
	float avg = total / bookkolvo;
	cout << "\n----  статистика ----\n";
	cout << "Всего книг " << bookkolvo << " шт.\n";
	cout << "Средняя оценка " << avg << " баллов\n";
	cout << "Максимальная оценка " << max << " баллов\n";
}
void showMenu()
{
	cout << "\n---- Трекер книг ----\n";
	cout << "1) Добавить книгу\n";
	cout << "2) Показать все книги\n";
	cout << "3) Показать всю статистику\n";
	cout << "4) Выйти\n";
	cout << "Выберети пункт: ";
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");
	loadBooks("books.txt");
	int choice;

	do
	{
		showMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			addBook();
			break;
		case 2:
			showallbooks();
			break;
		case 3:
			showgrades();
			break;
		case 4:
			cout << "выход\n";
			break;
		default:
			cout << "неверно\n";
		}
	} while (choice != 4);
	return 0;
}
