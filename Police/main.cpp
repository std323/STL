#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<map>
#include<ctime>
#include<list>
#include<Windows.h>
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n---------------------------------------------------\n"
#define tab "\t"

const std::map<int, std::string> violation =
{
	{0, "Другие правонарушения"},
	{1, "Превышение скорости"},
	{2, "Езда в нетрезвом состоянии"},
	{3, "Проезд на красный"},
	{4, "Пересечение сплошной"},
	{5, "Выезд на встречную полосу"},
	{6, "Проезд в запрещенном месте"},
	{7, "Парковка в неположенном месте"},
	{8, "Ремень безопасности"},
	{9, "Отсутствие документов"},
	{10, "Дрифт на перекрестке"},
	{11, "Оскорбление офицера"},
};

#define CRIME_TAKE_PARAMETERS int year, int month, int day, int hour, int minute
#define CRIME_GIVE_PARAMETERS year, month, day, hour, minute

class Crime
{
	//std::string licence_plate;//номерной знак
	int id; //правонарушение (статья)
	tm datetime; //время нарушения
	std::string place; //место нарушения
public:
	/*const std::string& get_licence_plate()const
	{
		return licence_plate;
	}*/
	int get_id()const
	{
		return id;
	}
	const char* get_time()const
	{
		char* datetime = asctime(&this->datetime);
		datetime[strlen(datetime) - 1] = 0;//убираем перенос на новую строку
		return datetime;
	}
	time_t get_timestamp()const
	{
		tm datetime = this->datetime;
		return mktime(&datetime);
	}
	const std::string& get_place()const
	{
		return place;

	}
	/*void set_licence_plate(const std::string& licence_plate)
	{
		this->licence_plate = licence_plate;
	}*/
	void set_id(int id)
	{
		/*if (violation.find(id) != violation.end())
			this->id = id;
		else this->id = 0;*/
		this->id = violation.find(id) == violation.end() ? 0 : id;
	}
	void set_timestamp(time_t time)
	{
		datetime = *localtime(&time);
	}
	tm* init_datetime()
	{
		const time_t datetime = mktime(&this->datetime);
		return localtime(&datetime);
	}
	void set_datetime(int year, int month, int day, int hour, int minute)
	{
		this->datetime = tm{};
		datetime.tm_year = year - 1900;
		datetime.tm_mon = month - 1;
		datetime.tm_mday = day;
		datetime.tm_hour = hour;
		datetime.tm_min = minute;
		this->datetime = *init_datetime();
	}
	void set_datetime(const std::string& datetime)
	{
		this->datetime = tm{};
		const int SIZE = 32;
		char buffer[SIZE]{};
		strcpy(buffer, datetime.c_str());//метод const char* c_str()const возвращает RAW строку, которую обворачивает обьект класса 'std::string'
		int part[5] = {};
		const char delimiters[] = ". /:";
		int n = 0;
		for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			part[n++] = std::stoi(pch);
		this->datetime.tm_year = part[0] - 1900;
		this->datetime.tm_mon = part[1] - 1;
		this->datetime.tm_mday = part[2];
		this->datetime.tm_hour = part[3];
		this->datetime.tm_min = part[4];
		this->datetime = *init_datetime();
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	//           Constructors:

	Crime(int id, const std::string& datetime, const std::string& place)
	{
		set_id(id);
		set_datetime(datetime);
		set_place(place);

	}
	~Crime() {}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{

	os << obj.get_time() << " | ";
	os.width(25);
	os << std::left;
	os << obj.get_place() << " | ";
	os << violation.at(obj.get_id());
	return os;

}
std::ofstream& operator <<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_timestamp() << " ";
	ofs << obj.get_id() << " ";
	ofs << obj.get_place();
	return ofs;
}
std::istream& operator>>(std::istream& is, Crime& obj)
{
	int id;
	std::string date;
	std::string time;
	std::string place;
	cout << "Введите нарушение: "; is >> id;

	cout << R"(

		0 - Ввести время вручную;\n
        1 - Использовать текущее время;
		 
			)";
	bool current_time;
	cin >> current_time;
	if (current_time)
	{
		obj.set_timestamp(std::time(NULL));
		is.ignore();
	}
	else
	{
		is.ignore();
		std::getline(is, date, ' ');
		std::getline(is, time, ' ');
		obj.set_datetime(date + " " + time);
	}
	cout << "Введите место происшествия: ";
	SetConsoleCP(1251);
	std::getline(is, place);
	SetConsoleCP(866);

	obj.set_id(id);
	obj.set_place(place);
	return is;
}
std::ifstream& operator>>(std::ifstream& ifs, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	ifs >> id >> timestamp;
	std::getline(ifs, place, ',');
	obj.set_id(id);
	obj.set_timestamp(timestamp);
	return ifs;
}
void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename);

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, NULL);
	setlocale(LC_ALL, "");

	/*Crime crime("aa777bb", 1, "2023.06.21 12:05", "ул.Ленина");
	cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base /*=
	{
		{"aa777bb", std::list <Crime>
			{
			Crime(1, "2023.06.21 12:05", "ул.Ленина"),
			Crime(2, "2023.06.21 12:05", "ул.Ленина"),
			Crime(11, "2023.06.21 12:05", "ул.Ленина")}
			},
		{"aa123bb",  std::list <Crime>
			{
			Crime(5, "2023.06.21 18:05", "ул.Октябрьская"),
			Crime(6, "2023.06.21 18:05", "ул.Октябрьская")
			}
		},
		{"mm111ab", std::list <Crime>
			{
			Crime(2, "2023.06.21 18:30", "ул.Парижской коммуны"),
			}
		},
		{"ab344ab",  std::list <Crime>
			{
			Crime(7, "2023.06.22 11:22", "ул.Ворошилова"),
			Crime(8, "2023.06.22 11:22", "ул.Ворошилова")
			}
		},
	}*/;

	char key;
	do
	{
		system("CLS");
		cout << "1. Распечатка базы данных;" << endl;
		cout << "2. Распечатка данных по заданному номеру;" << endl;
		cout << "3. Распечатка данных по диапазону номеров;" << endl;
		cout << "4. Сохранение базы в файл;" << endl;
		cout << "5. Загрузка базы из файла;" << endl;
		cout << "6. Добавление записи в базу;" << endl;
		cout << "0. Выход из программы;" << endl;
		key = _getch();
		switch (key)
		{
		case '1': print(base); break;
		case '4': save(base, "base.txt"); break;
		case '5': load(base, "base.txt"); break;
		case '6':
			for (std::pair<int, std::string> i : violation)cout << "\t" << i.first << "\t" << i.second << endl;
			std::string licence_plate;
			Crime crime(0, "2000.01.01 00:00", "Somewere");
			cout << "Введите номер автомобиля: "; cin >> licence_plate;
			cout << "Введите правонарушение: "; cin >> crime;
			base[licence_plate].push_back(crime);
			break;
		}
	} while (key != 27 && key != '0');
	
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout.width(8);
		cout << it->first + ":\n";

		for (std::list<Crime>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); ++l_it)
		{
			cout.width(8);
			cout << " ";
			cout << " | " << *l_it << endl;
		}
		cout << delimiter << endl;
	}
	system("PAUSE");
}

void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{

		fout << it->first + ":\t";

		for (std::list<Crime>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); ++l_it)
		{

			fout << *l_it << ", ";
		}
		fout << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}

void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		//TODO: read file
		while (!fin.eof())
		{
			std::string licence_plate;
			std::string all_crimes;
			std::getline(fin, licence_plate, ':');
			fin.ignore(); //пропускаем двоеточие

			std::getline(fin, all_crimes);
			int all_crimes_size = all_crimes.size() + 1;
			char* sz_all_crimes = new char[all_crimes_size] {};
			std::strcpy(sz_all_crimes, all_crimes.c_str());
			Crime crime(0, "2000.01.01 00:00", "");
			for (char* pch = strtok(sz_all_crimes, ","); pch; pch = strtok(NULL, ","))
			{
				//elements[n++] = pch;
				if (strcmp(pch, " ") == 0)continue;
				time_t timestamp = std::stoi(pch);
				while (pch[0] == ' ')for (int i = 0; pch[i]; i++)pch[i] = pch[i + 1];
				pch = strchr(pch, ' ') + 1;
				int id = std::stoi(pch);
				pch = strchr(pch, ' ') + 1;
				crime.set_id(id);
				crime.set_timestamp(timestamp);
				crime.set_place(pch);
				base[licence_plate].push_back(crime);
			}
			delete[] sz_all_crimes;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	cout << "База загружена" << endl;
	system("PAUSE");
}






