#include <iostream>
#include "figure.h"

using namespace std;

int main(int argc, char *argv[])
{
	Figure* figure_mas[3];
	double x1, x2, x3, x4, y1, y2, y3, y4;
	int target;
	int func_num;
	double result;

	for (int i = 0; i < 3; i++)
	{
		cout << "Введите x1, x2, x3, x4, y1, y2, y3, y4 " << i + 1 << "-й фигуры через пробел." << endl << ": ";
		cin >> x1 >> x2 >> x3 >> x4 >> y1 >> y2 >> y3 >> y4;
		figure_mas[i] = new Figure(x1, x2, x3, x4, y1, y2, y3, y4);
	}

	while (true)
	{
		cout << "Введите номер созданной фигуры от 1 до 3 или 0 для выхода." << endl << ": ";
		cin >> target;

		if (target - 1 < 0) break;
			if (target - 1 > 2)
			{
				cout << "Некорректный номер Фигуры, попробуйте еще раз!" << endl;
				continue;
			}
			cout << "Вы выбрали фигуру № " << target << " ." << endl;

		while(true)
		{
			cout <<
			"Выберите номер функции" << endl<<
			"0 - Exit" << endl <<
			"1 - show" << endl <<
			"2 - is_prug" << endl <<
			"3 - is_square" << endl <<
			"4 - is_romb" << endl <<
			"5 - is_in_circle" << endl <<
			"6 - is_out_circle" << endl <<
			": ";
			cin >> func_num;

			if (func_num == 0) break;

			switch (func_num)
			{
				case 1:
					figure_mas[target - 1] -> show();
					break;

				case 2:
					cout << "Результат: ";
					figure_mas[target - 1] -> is_prug() ? cout << "Прямоугольник" : "Не прямоугольник";
					cout << endl;
					break;

				case 3:
					cout << "Результат: ";
					figure_mas[target - 1] -> is_square() ? cout << "Квадрат" : "Не квадрат";
					cout << endl;
					break;

				case 4:
					cout << "Результат: ";
					figure_mas[target - 1] -> is_romb() ? cout << "Ромб" : "Не ромб";
					cout << endl;
					break;

				case 5:
					cout << "Результат: ";
					figure_mas[target - 1] -> is_in_circle() ? cout << "Можно" : "Нельзя";
					cout << endl;
					break;

				case 6:
					cout << "Результат: ";
					figure_mas[target - 1] -> is_out_circle() ? cout << "Можно" : "Нельзя";
					cout << endl;
					break;

				default:
					cout << "Некорректный номер функции, попробуйте снова!" << endl;
					break;
			
			}
		cout << endl << endl << endl;
		}

	}


	// Removing figures in figure_mas
	for (int i = 0; i < 3; i++)
	{
		delete figure_mas[i];
	}

	cout << "Программа завершена" << endl;



	return 0;
}

// Figure figure = Figure(8, 10, 2, 0, 0, 8, 10, 2);
	