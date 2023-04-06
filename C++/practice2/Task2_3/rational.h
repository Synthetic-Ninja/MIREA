class Rational
{
private:
	int a, b;
	void reduce();
	int gcd(int a1, int b1);

public:
	Rational(int a1, int b1);
	void set(int a1, int b1);
	void show();
	Rational operator + (Rational& src);
	Rational& operator ++ ();
	Rational& operator ++ (int d);
	bool operator == (Rational& src);
	bool operator < (Rational& src);
	bool operator > (Rational& src);
	Rational& operator = (Rational& src);
	friend Rational operator - (Rational& src1, Rational& src2);
	
};



Rational operator - (Rational& src1, Rational& src2);