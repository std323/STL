#include<iostream>
#include<array>
#include<stack>
#include<vector>
#include<deque>
#include<list>
#include<forward_list>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter   "\n--------------------------------------\n"

template<typename T>void vector_properties(const std::vector<T>& vec);

//#define STL_ARRAY
//#define STL_STACK
//#define STL_VECTOR
//#define STL_QUEE
//#define STL_DEQUEE
#define STL_LIST
//#define STL_FORWARD_LIST

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl;

#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива
	const int N = 5;
	std::array<int, N> arr = { 3,5,8 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
#endif STL_ARRAY
#ifdef STL_STACK
	std::stack<int> stack;
	stack.push(3);
	stack.push(5);
	stack.push(8);
	stack.push(13);
	stack.push(21);
	while (!stack.empty())
	{
		cout << stack.top() << endl;
		stack.pop();
	}
#endif // STL_STACK
#ifdef STL_VECTOR
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	try
	{
		for (int i = 0; i < vec.size() * 2; i++)
		{
			//cout << vec[](i) << tab;
			//cout << vec[i] << tab;
			cout << vec.at(i) << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	vector_properties(vec);
	vec.push_back(55);
	vector_properties(vec);
	//vec.reserve(25);    //Резервирует дополнительную вместительность
	//vec.shrink_to_fit();  //Урезает вместительность до фактического размера вектора
	vec.resize(8);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_properties(vec);

	cout << delimiter << endl;
	cout << std::vector<int>().max_size() << endl;
	cout << std::vector<double>().max_size() << endl;

	/*int index;
	int value;
	do
	{
		cout << "Введите индекс добавляемого элемента: "; cin >> index;
		cout << "Введите значение добавляемого элемента: "; cin >> value;
		if (index > vec.size())cout << "Очень большой индекс" << endl;
	} while (index>vec.size());
	vec.insert(vec.begin() + index, 3, value);
	for (int i : vec)cout << i << tab; cout << endl;*/
	vec.insert(vec.begin() + 3, { 104, 2048, 3072 });
	for (int i : vec)cout << i << tab; cout << endl;

	vec.erase(vec.begin()+3, vec.begin() + 6);
	for (int i : vec)cout << i << tab; cout << endl;
	cout << vec.front() << endl;
	cout << vec.back() << endl;
	//cout << vec.data() << endl;

#endif // STL_VECTOR
#ifdef STL_QUEE
	std::deque<int> deque = { 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < deque.size(); i++)
	{
		cout << deque[i] << tab;
	}
	cout << endl;

	deque.push_back(55);
	deque.push_back(45);
	deque.push_back(38);

	deque.pop_front();
	deque.pop_front();

	for (std::deque<int>::iterator it = deque.begin(); it != deque.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

#endif // STL_QUEE
#ifdef STL_DEQUEE

	std::deque<int> deque = { 3, 5, 8, 13, 21, };
	for (int i = 0; i < deque.size(); i++)
	{
		cout << deque[i] << tab;
	}
	cout << endl;
	deque.push_back(34);
	deque.push_back(55);
	deque.push_back(89);
	deque.push_front(2);
	deque.push_front(1);
	deque.push_front(1);
	deque.push_front(0);
	for (int i : deque)cout << i << tab; cout << endl;

#endif // STL_DEQUEE
#ifdef STL_LIST
	std::list<int> list = { 3, 5, 8, 13, 21 };
	/*for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << tab;
		
	}
	cout << endl;*/

	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	int index;
	int value;
	
	do
	{
		cout << "Введите индекс добавляемого элемента: "; cin >> index;
		if (index > list.size())cout << "Error: out of range" << endl;
	} while (index>list.size());
		cout << "Введите значение добавляемого элемента: "; cin >> value;

			std::list<int>::iterator position = list.begin();
			//for (int i = 0; i < index; i++)position++;
			std::advance(position, index);
			list.insert(position, value);
			for (int i : list)cout << i << tab; cout << endl;
		
	list.assign({ 1024, 2048, 3072, 4096 });
	list.push_front(512);
	list.push_back(5120);
	for (int i : list)cout << i << tab; cout << endl;
	
#endif // STL_LIST
#ifdef STL_FORWARD_LIST
	std::forward_list<int> f_list = { 3, 5, 8, 13, 21 };
	
	for (int i : f_list)cout << i << tab; cout << endl;
	f_list.push_front(2);
	for (int i : f_list)cout << i << tab; cout << endl;
	int index;
	int value;
	
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	std::forward_list<int>::iterator position = f_list.before_begin();
	std::advance(position, index);
	f_list.insert_after(position, value);
	for (int i : f_list)cout << i << tab; cout << endl;

#endif // STL_FORWARD_LIST

}



template<typename T>void vector_properties(const std::vector<T>& vec)
{
	cout << "Size: " << vec.size() << endl;
	cout << "Max size:" << vec.max_size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << delimiter << endl;
}