#include <iostream>
#include "circle.h"

using namespace std;


int main(int argc, char *argv[])
{
	Circle* сircle_mas[3];
	double r, x, y;
	double a, b, c;
	int target;
	int func_num;
	double result;
	
	for (int i = 0; i < 3; i++)
	{
		cout << "Введите r, x, y " << i + 1 << "-й Окружности через пробел." << endl << ": ";
		cin >> r >> x >> y;
		сircle_mas[i] = new Circle(r , x , y);
	}

	
	while (true)
	{
		cout << "Введите номер созданной окружности от 1 до 3 или 0 для выхода." << endl << ": ";
		cin >> target;
		if (target - 1 < 0) break;
		if (target - 1 > 2)
		{
			cout << "Некорректный номер окружности, попробуйте еще раз!" << endl;
			continue;
		}
		cout << "Вы выбрали окружность № " << target << " ." << endl;
		while(true)
		{
			cout <<
			"Выберите номер функции" << endl<<
			"0 - Exit" << endl <<
			"1 - set_circle" << endl <<
			"2 - square" << endl <<
			"3 - triangle_around" << endl <<
			"4 - triangle_in" << endl <<
			"5 - check_circle" << endl <<
			": ";
			cin >> func_num;

			if (func_num == 0) break;

			switch (func_num)
			{
				case 1:
					cout << "Введите r, x, y окружности через пробел." << endl << ": ";
					cin >> r >> x >> y;
					сircle_mas[target - 1] -> set_circle(r, x, y);
					cout << "Данные изменены" << endl;
					break;
				
				case 2:
					cout << "Радиус окружности равен: " << сircle_mas[target - 1] -> square() << endl;
					break;

				
				case 3:
					cout << "Введите a, b, c треугольника через пробел." << endl << ": ";
					cin >> a >> b >> c;
					result = сircle_mas[target - 1] -> triangle_around(a, b, c);
					cout << "Результат: " << (result ?  "Можно " : "Нельзя") << endl;
					break;
				
				case 4:
					cout << "Введите a, b, c треугольника через пробел." << endl << ": ";
					cin >> a >> b >> c;
					result = сircle_mas[target - 1] -> triangle_in(a, b, c);
					cout << "Результат: " << (result ?  "Можно " : "Нельзя") << endl;
					break;
				
				case 5:
					cout << "Введите r, x, y  окружности через пробел." << endl << ": ";
					cin >> r >> x >> y;
					result = сircle_mas[target - 1] -> check_circle(r, x, y);
					cout << "Результат: " << (result ?  "Можно " : "Нельзя") << endl;
					break;

				default:
					cout << "Некорректный номер функции, попробуйте снова!";
					break;
			}

		cout << endl << endl << endl;

		}


	}

	
	// Removing circles in circle_mas
	for (int i = 0; i < 3; i++)
	{
		delete сircle_mas[i];
	}

	cout << "Программа завершена" << endl;

}
