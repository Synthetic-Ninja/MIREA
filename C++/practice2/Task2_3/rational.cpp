#include "rational.h"
#include <iostream>


Rational::Rational(int a1, int b1)
{
	set(a1, b1);
}

void Rational::set(int a1, int b1)
{
	a = a1;
	b = b1 != 0? b1 : 1; // Заменяем знаменатель на 1, если он 0
	if (a > b) a %= b;
	reduce();
}

void Rational::reduce()
{
	int nod = gcd(a, b);
	a /= nod;
	b /= nod;
}

int Rational::gcd(int a1, int b1)
{
	if (b1 == 0) return a1;
	return gcd(b1, a1 % b1);
}


void Rational::show()
{
	std::cout << a << '/' << b;
}


Rational Rational::operator + (Rational& src)
{

	return Rational(a + src.a, b + src.b);
}

Rational& Rational::operator ++ ()
{
	set(a + 1, b);
	return *this;
}

Rational& Rational::operator ++ (int d)
{
	set(a + 1, b);
	return *this;
}

bool Rational::operator == (Rational& src)
{
	return a == src.a && b == src.b;
}

bool Rational::operator < (Rational& src)
{
	return a * src.b < src.a * b;
}

bool Rational::operator > (Rational& src)
{
	return src < *this;
}

Rational& Rational::operator = (Rational& src)
{
	a = src.a;
	b = src.b;
	return *this;
}


Rational operator - (Rational& src1, Rational& src2)
{
	return Rational(src1.a - src2.a, src1.b - src2.b);
}