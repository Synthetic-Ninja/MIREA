#include "rational.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

	int a, b, choise, target1, target2;
	int obj_count;
	bool flag = true;
	cout << "Введите количество элементов для массива:" << endl;
	cin >> obj_count;

	Rational **rationalmas = new Rational*[obj_count];

	for (int i = 0; i <  obj_count; ++i)
	{
		cout << "Введите a,b для " << i + 1 << "-ой дроби через пробел\n: ";
		cin >> a >> b;
		rationalmas[i] = new Rational(a, b);
	}

	
	while(flag)
	{
		cout << "Введите номер функци\n0.Выход\n1.Set\n2.Show\n3.+\n4.-\n5.++\n6.==\n7.<\n8.>\n9.=\n\n: ";

		cin >> choise;

		switch (choise)
		{
			case 0:
				flag = false;
				break;

			case 1:
				cout << "Введите номер дроби\n: ";
				cin >> target1;
				target1 -= 1;

				if (target1 < 0 || target1 >= obj_count)
				{
					cout << "Неверный номер дроби";
					break;
				}
				cout << "Введите a,b для " << target1 + 1 << "-ой дроби через пробел\n: ";
				cin >> a >> b;
				rationalmas[target1] -> set(a, b);
				cout << "Успех!";
				break;

			case 2:
				cout << "Введите номер дроби\n: ";
				cin >> target1;
				target1 -= 1;

				if (target1 < 0 || target1 >= obj_count)
				{
					cout << "Неверный номер дроби";
					break;
				}

				cout << "Дробь [" << target1 + 1 << "]: ";
				rationalmas[target1] -> show();
				break;

			case 3:
				cout << "Введите номера дробей через пробел\n: ";
				cin >> target1 >> target2;
				target1 -= 1;
				target2 -= 1;
				if ((target1 < 0 || target1 >= obj_count) || (target2 < 0 || target2 >= obj_count))
				{
					cout << "Неверный номер дробей";
					break;
				}

				cout << "\n\n";
				rationalmas[target1] -> show();
				cout << " + ";
				rationalmas[target2] -> show();
				cout << " = ";
				(*rationalmas[target1] + *rationalmas[target2]).show();
				break;

			case 4:
				cout << "Введите номера дробей через пробел\n: ";
				cin >> target1 >> target2;
				target1 -= 1;
				target2 -= 1;
				if ((target1 < 0 || target1 >= obj_count) || (target2 < 0 || target2 >= obj_count))
				{
					cout << "Неверный номер дробей";
					break;
				}
				cout << "\n\n";
				rationalmas[target1] -> show();
				cout << " - ";
				rationalmas[target2] -> show();
				cout << " = ";
				(*rationalmas[target1] - *rationalmas[target2]).show();
				break;

			case 5:
				cout << "Введите номер дроби\n: ";
				cin >> target1;
				target1 -= 1;

				if (target1 < 0 || target1 >= obj_count)
				{
					cout << "Неверный номер дроби";
					break;
				}
				(*rationalmas[target1])++;
				rationalmas[target1] -> show();
				break;


			case 6:
				cout << "Введите номера дробей через пробел\n: ";
				cin >> target1 >> target2;
				target1 -= 1;
				target2 -= 1;
				if ((target1 < 0 || target1 >= obj_count) || (target2 < 0 || target2 >= obj_count))
				{
					cout << "Неверный номер дробей";
					break;
				}

				rationalmas[target1] -> show();
				cout << " и ";
				rationalmas[target2] -> show();
				cout << " " << (*rationalmas[target1] == *rationalmas[target2]? "Равны" : "Не равны");
				break;

			case 7:
				cout << "Введите номера дробей через пробел\n: ";
				cin >> target1 >> target2;
				target1 -= 1;
				target2 -= 1;
				if ((target1 < 0 || target1 >= obj_count) || (target2 < 0 || target2 >= obj_count))
				{
					cout << "Неверный номер дробей";
					break;
				}

				rationalmas[target1] -> show();
				cout << " < ";
				rationalmas[target2] -> show();
				cout << " " << (*rationalmas[target1] < *rationalmas[target2]? "Да" : "Нет");
				break;

			case 8:
				cout << "Введите номера дробей через пробел\n: ";
				cin >> target1 >> target2;
				target1 -= 1;
				target2 -= 1;
				if ((target1 < 0 || target1 >= obj_count) || (target2 < 0 || target2 >= obj_count))
				{
					cout << "Неверный номер дробей";
					break;
				}

				rationalmas[target1] -> show();
				cout << " > ";
				rationalmas[target2] -> show();
				cout << " " << (*rationalmas[target1] > *rationalmas[target2]? "Да" : "Нет");
				break;

			case 9:
				cout << "Введите номера дробей через пробел\n: ";
				cin >> target1 >> target2;
				target1 -= 1;
				target2 -= 1;
				if ((target1 < 0 || target1 >= obj_count) || (target2 < 0 || target2 >= obj_count))
				{
					cout << "Неверный номер дробей";
					break;
				}

				*rationalmas[target1] = *rationalmas[target2];
				cout << "Успех!";
				break;


		}

		cout << "\n\n";
	}


	// Очистка объектов массива
	for (int i = 0; i < obj_count; i++)
	{
		delete rationalmas[i];
	}

	
	// Очистка массива
	delete [] rationalmas;


	cout << "Программа завершена" << endl;

	return 0;
}