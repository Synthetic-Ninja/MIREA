#include <iostream>
#include "bay.h"
#include "sea.h"
#include "ocean.h"

using namespace std;

int main(int argc, char const *argv[])
{

	Ocean ocean;
	cin >> ocean;
	cout << ocean;

	Bay bay;
	cin >> bay;
	cout << bay;
	bay.add_parent(ocean);

	Sea sea;
	cin >> sea;
	cout << sea;
	sea.add_parent(ocean);
	sea.add_child(bay);



	return 0;
}