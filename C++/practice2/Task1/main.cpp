#include "eq2.h"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
	
	eq2* eq2mas[2];
	double a,b,c, x1;

	for (int i; i < 2; i++)
	{
		cout << "Введите a, b ,c " << i + 1 << "-го уравнения через пробел." << endl;
		cin >> a >> b >> c;
		eq2mas[i] = new eq2(a, b, c);
	}

	for (int i; i < 2; i++)
	{
		cout << "Введите X1 " << i + 1 << "-го уравнения." << endl;
		cin >> x1;
		
		cout << "X: " << i + 1 << "-го уравнения: " << eq2mas[i] -> find_x() << endl;
		cout << "Y: " << i + 1 << "-го уравнения: " << eq2mas[i] -> find_y(x1) << endl;

	}

	eq2 sumeq2 = *eq2mas[0] + *eq2mas[1];
	cout << "Введите X1 для суммы уравнений." << endl;
	cout << "X: Суммы уравнений: " << sumeq2.find_x() << endl;
	cout << "Y: Суммы уравнений: " << sumeq2.find_y(x1) << endl;

	for (int i = 0; i < 2; i++)
	{
		delete eq2mas[i];
	}

	cout << "Программа завершена" << endl;

	return 0;
}