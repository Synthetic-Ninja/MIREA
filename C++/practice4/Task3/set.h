#include <iostream>

using namespace std;

template <class Atype> class Set
{
    Atype* a; 
    int len; 

public:
    Set(int size)
    {
        len = size;

        a = new Atype[size];


    }

    ~Set()
    {
        delete[]a;
    }

    bool In_Set(Atype T)
    {
        for (int i = 0; i < len; i++)
        {
            if (a[i] == T)
            {
                return true;
            }
        }
        return false;
    }

    bool Add(Atype T)
    {
        if (!In_Set(T))
        {
            Atype* tmp = new Atype[len + 1];
            for (int i = 0; i < len; i++)
            {
                tmp[i] = a[i];
            }
            tmp[len++] = T;
            delete[] a;
            a = tmp;
            return true;
        }
        return false;
    }

    bool Get(Atype T)
    {
        if (In_Set(T))
        {
            Atype* tmp = new Atype[len - 1];
            int j = 0;
            for (int i = 0; i < len; i++)
            {
                if (a[i] != T)
                {
                    tmp[j++] = a[i];
                }
            }
            delete[]a;
            a = tmp;
            len--;
            return true;
        }
        return false;
    }

    bool Is_Full()
    {
        if (len > 0)
        {
            return true;
        }
        return false;
    }

    bool Is_Empty()
    {
        if(len == 0)
        {
            return true;
        }
        return false;
    }

    
    Set& operator+(Atype T)
    {
        Add(T);
        return *this;
    }

    Atype& operator[](int n)
    {
        if (n < 0 || n > len - 1)
        {
            cout << "IndexError";
            exit(1);
        }
        return a[n];
    }

    int Size() const
    {
        return len;
    }
};

class Point
{
    int x, y;
public:
    Point(int x1, int y1)
    {   
        this->x = x1;
        this->y = y1;
    }
    Point()
    {
        x = 0;
        y = 0;
    }

    friend ostream& operator<<(ostream& mass, Point& mass1)
    {
        mass << mass1.x << "," << mass1.y;
        return mass;
    }
    Point& operator=(Point& my_Point1)
    {
        this->x = my_Point1.x;
        this->y = my_Point1.y;
        return *this;
    }
    
    bool operator==(Point const& my_Point1)
    {
        return (this->x == my_Point1.x && my_Point1.y == this->y);
    }

    bool operator!=(Point const& my_Point1)
    {
        return (this->x != my_Point1.x || my_Point1.y != this->y);
    }
};