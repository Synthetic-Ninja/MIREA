#include <iostream>
#include "figure.h"

using namespace std;

int main(int argc, char *argv[])
{
	Figure figure = Figure(1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1);
	cout << figure.is_prug() << endl;
	return 0;
}