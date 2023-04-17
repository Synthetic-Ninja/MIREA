#include "myclass.h"

using namespace std;

int main()
{	
	int x = 1;
	int y = 2;
	cout << "Перед обменом (int)" << endl;
	OutXY(x, y);
	Swap(x, y);
	cout << "После обмена (int)" << endl;
	OutXY(x, y);

	float x1 = 1.5;
	float y1 = 5.9;
	cout << "Перед обменом (float)" << endl;
	OutXY(x1, y1);
	Swap(x1, y1);
	cout << "После обмена (float)" << endl;
	OutXY(x1, y1);

	My_class t1(1, 1.5), t2(2, 9.9);
	cout << "Перед обменом (class)" << endl;
	t1.Out();
	t2.Out();
	Swap(t1, t2);
	cout << "После обмена (class)" << endl;
	t1.Out();
	t2.Out();
}
