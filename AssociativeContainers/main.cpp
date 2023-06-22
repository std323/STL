#include<iostream>
#include<set>
#include<map>
#include<vector>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter   "\n--------------------------------------\n"
//#define STL_SET
//#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_SET
	std::multiset<int> set = { 50, 25, 75, 16, 32, 64, 80, 50, 16, 16, 16, 16, 18, 32, 33 };
	for (std::set<int>::const_iterator it = set.begin(); it != set.end(); ++it)
		cout << *it << tab;
	cout << endl;

#endif // STL_SET

#ifdef STL_MAP

	std::map<int, std::string > week =
	{
        std::pair<int, std::string> (0, "Sunday"),
        std::pair<int, std::string> (1, "Monday"),
        std::pair<int, std::string> (2, "Tuesday"),
        std::pair<int, std::string> (3, "Wednesday"),
		{4, "Thursday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{5, "Friday"},
		{6, "Saturday"},
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
	cout << endl;

	cout << delimiter << endl;
	for(std::pair<int, std::string> i:week)cout << i.first << tab << i.second << endl;
#endif // STL_MAP

	std::map<std::string, std::vector<std::string>> dictionary =
	{
		std::pair<std::string, std::vector<std::string>>("declaration", {"декларация", "обьявление", "заявление"}),
		std::pair<std::string, std::vector<std::string>>("definition", {"определение", "формулировка", "формулирование"}),
		std::pair<std::string, std::vector<std::string>>("space", {"пробел", "пространство", "космос"}),
		{"solely", {"единственно", "исключительно", "самостоятельно"}},
		{"fire", {"огоь", "костер", "сжигать"}},
	};
	for (std::map < std::string, std::vector<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		//cout << typeid(it->first + ":").name() << endl;
		cout.width(15);
		cout << left;
		cout << it->first + ":";
		
		for (std::vector<std::string>::iterator v_it = it->second.begin(); v_it != it->second.end(); ++v_it)
		{
			cout << *v_it << ", ";
		}
		cout << "\b\b;\n";
	}
}