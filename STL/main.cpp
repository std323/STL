#include<iostream>
#include<array>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter   "\n----------------------------------\n"

#define STL_ARRAY

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl;

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива
	const int N = 5;
	std::array<int, N> arr = {3,5,8};
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif STL_ARRAY

}