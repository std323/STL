#include<iostream>
using namespace std;


void main()
{
	setlocale(LC_ALL, "");
	try
	{
		throw "My exception";
		throw 1;
	}
	catch (int e)
	{
		std::cerr << "Error #"  << e << endl;
	}
	catch (const char* e)
	{
		std::cerr << "Error: " << e << endl;
	}
	int a=2;
	//cout << a << endl;

	int b = 0;
	cout << "¬ведите два числа: "; cin >> a >> b;
	try
	{
		cout << a / b << endl;
	}
	catch (int e)
	{
		std::cerr << "Error #" << e << endl;
	}
	catch (...)
	{
		std::cerr << "Something happened" << endl;
	}
}