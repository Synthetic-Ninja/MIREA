class eq2
{
private:
	double a, b, c, d;


public:
	eq2(double in_a, double in_b, double in_c);
	void set(double in_a, double in_b, double in_c);
	double find_x();
	double find_y(double x1);
	friend eq2 operator + (eq2& obj1, eq2& obj2);

};

//Переопределение оператора +
eq2 operator + (eq2& obj1, eq2& obj2);
