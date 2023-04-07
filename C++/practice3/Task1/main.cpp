#include <iostream>
#include "cone.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//Конус без параметров
	Cone cone1;
	cone1.show();

	cout << "\n" << endl;	

	//Конус с высотой и радиусом
	Cone cone2(2, 5.2);
	cone2.show();

	cout << "\n" << endl;

	//Произвольный конус
	Cone cone3(2, 5.2, 1, 2, 3);
	cone3.show();


	//Массив из count динамических конусов
	
	int count = 3;

	double h, r, x, y, z;

	char answer;

	Cone* conemas[count];

	cout << "\n" << endl;
	

	//Заполнение конусов
	for (int i = 0; i < count; i++)
	{
		while (true)
		{
			cout << "Хотите заполнить " << i + 1 << "-й конус  \ny/n\n" << endl;

			cin >> answer;
				if (answer == 'y' || answer == 'n')
				{
					break;
				}
			cout << "Неправильный параметр \n" << endl;
		} 


		if (answer == 'n')
		{
			conemas[i] = new Cone();
			continue;
		}

		while(true)
		{
			cout << "Выберите вариат заполнения: \n1.Только h, r;\n2.h, r, x, y, z;\n: ";
			cin >> answer;

			if (answer == '1' || answer == '2')
			{
				break;
			}
			cout << "Неправильный параметр.\n\n";
		}

		switch (answer)
		{
			case '1':
				cout << "Ввведите h, r для " << i + 1 << "-го конуса через пробел" << endl;
				cin >> h >> r;

				conemas[i] = new Cone(h, r); 
				break;

			case '2':
				cout << "Ввведите h, r, x, y, z для " << i + 1 << "-го конуса через пробел" << endl;
				cin >> h >> r >> x >> y >> z;

				conemas[i] = new Cone(h, r, x, y, z);
				break;
		}	
	}

	//Работа с конусами

	int target;

	while(true)
	{
		cout << "Введите номер конуса или 0 для выхода.\n: ";
		cin >> target;
		target -= 1;

		if (target < -1 or target > count - 1)
		{
			cout << "Неправильный аргумент.";
			continue;
		}

		if (target == -1)
		{
			break;
		}

		bool flag = true;
		while (flag)
		{
			cout << "Ввведите номер функции\n0.Выход\n1.Set\n2.Show\n3.Get_area\n4.Get_valume\n: ";
			cin >> answer;

			switch (answer)
			{
				case '0':
					flag = false;
					break;

				case '1':
					while(true)
					{
						cout << "Выберите вариат заполнения: \n1.Только h, r;\n2.h, r, x, y, z;\n: ";
						cin >> answer;

						if (answer == '1' || answer == '2')
						{
							break;
						}
						cout << "Неправильный параметр.\n\n";
					}

					switch (answer)
					{
						case '1':
							cout << "Ввведите h, r для " << target << "-го конуса через пробел" << endl;
							cin >> h >> r;

							conemas[target] -> set(h, r); 
							break;

						case '2':
							cout << "Ввведите h, r, x, y, z для " << target << "-го конуса через пробел" << endl;
							cin >> h >> r >> x >> y >> z;

							conemas[target] -> set(h, r, x, y, z);
							break;
					}
					cout << "Успех!";
					break;

				case '2':
					conemas[target] -> show();
					break;

				case '3':
					cout << "Площадь: " << conemas[target] -> get_area() << endl;
					break;

				case '4':
					cout << "Объем: " << conemas[target] -> get_volume();
					break;
			}
			cout << "\n" << endl;
		}

	}


	// Очистка памяти
	for (int i = 0; i < count; i++)
	{
		delete conemas[i];
	}

	cout << "Программа завершена" << endl;


	return 0;
}