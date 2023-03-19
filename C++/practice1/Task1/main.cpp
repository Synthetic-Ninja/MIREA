#include <iostream>
#include "triangle.h"

using namespace std;

int main(int arcg, char *argv[])
{
	Triangle *triangle_mas;
	triangle_mas = new Triangle[3];
	double a, b, c;
	for (int i = 0; i < 3; i++)
	{
		cout << "Введите стороны (a,b,c) через пробел для " << i + 1 << " треугольника" << endl << ": ";
		while (true)
		{
			cin >> a >> b >> c;
			triangle_mas[i].set(a, b, c);
			if (triangle_mas[i].exst_tr()) break;
			cout << "Треугольник с такими сторонами не может существовать, попробуйте еще раз" << endl << ": ";
		}

	}

	for (int i = 0; i < 3; i++){
		cout << "Треугольник № " << i + 1 << endl;
		cout << endl;
		cout << "Стороны треугольника : ";
		triangle_mas[i].show();
		cout << "Периметр для треугольника равен " << triangle_mas[i].perimetr() << endl;
		cout << "Площадь для треугольника равна " << triangle_mas[i].square() << endl;
		cout << endl;
	}

	delete []triangle_mas;
	
	return 0;
}
