#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

class Complex
{
private:
	double real;
	double imag;
public:
	Complex(double r = 0.0, double i = 0.0);

	Complex operator*(double scalar) const;
	Complex operator+(const Complex& other) const;
	Complex operator-(const Complex& other) const;
	double abs() const;
		

	void print() const;
	double GetReal() const;
	double GetImag() const;

};

#endif // COMPLEX_H
