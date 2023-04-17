#include "set.h"

using namespace std;

int main()
{

    Set<int> my_Int(2);
    for (int i = 0; i < 2; i++)
    {
        my_Int[i] = 1;
    }
    my_Int.Add(1);
    my_Int.Add(2);
    my_Int.Add(3);
    my_Int.Get(2);
    if (my_Int.Is_Empty())
    {
        cout << "my_Int size: 0 "  << endl;
    }
    if (my_Int.Is_Full())
    {
        cout << "my_Int size: > 0 " << endl;
    }
    if (my_Int.In_Set(1))
    {
        cout << "1 is in the my_Int." << endl;
    }
    if (!(my_Int.In_Set(2)))
    {
        cout << "2 is not in the my_Int." << endl;
    }
    my_Int = my_Int + 6;
    cout << "my_Int size: " << my_Int.Size() << endl;
    for (int i = 0; i < my_Int.Size(); i++)
    {
        cout << my_Int[i] << " ";
    }
    cout << endl << endl;

    Set <string> my_String(3);
    my_String[0] = "Васин";
    my_String[1] = "Джудаев";
    my_String[2] = "Керзев";
    my_String.Add("Астапов");
    my_String.Get("Костильо");
    if (my_String.Is_Empty())
    {
        cout << "my_String size: 0 " << endl;
    }
    if (my_String.Is_Full())
    {
        cout << "my_String size: > 0 " << endl;
    }
    if (my_String.In_Set("Антонов"))
    {
        cout << "Антонов is in the my_String." << endl;
    }
    if (!(my_String.In_Set("Иванов")))
    {
        cout << "Иванов is not in the my_String." << endl;
    }
    my_String = my_String + "Жмыев";
    cout << "my_String size: " << my_String.Size() << endl;
    for (int i = 0; i < my_String.Size(); i++)
    {
        cout << my_String[i] << " ";
    }
    cout << endl << endl;

    Set <Point> my_Point(3);
    Point P1(2, 3);
    Point P2(1, 2);
    Point P3(3, 2);
    my_Point[0] = P1;
    my_Point[1] = P2;
    my_Point[2] = P3;
    Point P4(7, 7);
    my_Point.Add(P4);
    my_Point.Get(P2);
    if (my_Point.Is_Empty())
    {
        cout << "my_Point size: 0 " << endl;
    }
    if (my_Point.Is_Full())
    {
        cout << "my_Point size: > 0 " << endl;
    }
    if (my_Point.In_Set(P1))
    {
        cout << "(2,3) is in the my_Point." << endl;
    }
    if (!(my_Point.In_Set(P2)))
    {
        cout << "(1,2) is not in the my_Point." << endl;
    }
    Point P5(9, 9);
    my_Point = my_Point + P5;
    cout << "my_Point size: " << my_Point.Size() << endl;
    for (int i = 0; i < my_Point.Size(); i++)
    {
        cout << my_Point[i] << " ";
    }
    cout << endl << endl;
}
