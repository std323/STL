#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<map>
#include<ctime>
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n------------------------------------------\n"
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
	std::string licence_plate;//номерно знак
	int id; //правонарушение (статья)
	tm datetime; //время нарушения
	std::string place; //место нарушения
public:
	const std::string& get_licence_plate()const
	{
		return licence_plate;
	}
	int get_id()const
	{
		return id;
	}
	const char* get_time()const
	{  
		char* datetime= asctime(&this->datetime);
		datetime[strlen(datetime) - 1] = 0;//убираем перенос на новую строку
		return datetime;
	}
	const std::string& get_place()const
	{
		return place;
	}
	void set_licence_plate(const std::string& licence_plate)
	{
		this->licence_plate = licence_plate;
	}
	void set_id(int id)
	{
		/*if (violation.find(id) != violation.end())
			this->id = id;
		else this->id = 0;*/
		this->id = violation.find(id) == violation.end() ? 0 : id;
	}
	tm* init_datetime()
	{
		const time_t datetime = mktime(&this->datetime);
		return localtime(&datetime);
	}
	void set_datetime(int year, int month, int day, int hour, int minute)
	{
		this->datetime = tm{};
		datetime.tm_year = year-1900;
		datetime.tm_mon = month-1;
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
		strcpy(buffer, datetime.c_str());
		int part[5] = {};
		const char delimiters[] = ". /:";
		int n = 0;
		for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			part[n++] = std::stoi(pch);
		this->datetime.tm_year = part[0]-1900;
		this->datetime.tm_mon = part[1]-1;
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

	Crime(const std::string& licence_plate, int id, const std::string& datetime, const std::string& place)
	{
		set_licence_plate(licence_plate);
		set_id(id);
		set_datetime(datetime);
		set_place(place);

	}
	~Crime() {}
	};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_licence_plate() << " " 
		<< obj.get_id() << " " 
		<< obj.get_time() << " " 
		<< obj.get_place();

}

void main()
{
	setlocale(LC_ALL, "");

	/*"2023.05.05 12:21";
	"2023/05/05 12:21";*/
	Crime crime("aa777bb", 1, "2023.06.21 12:05", "ул.Ленина");
	cout << crime << endl;

	

}