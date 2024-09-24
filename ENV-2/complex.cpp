#include "complex.h"

#include <iostream>
// конструктор
Complex::Complex(double r, double i): real(r), imag(i){}

//Операция сложения 
Complex Complex::operator+(const Complex& other) const
{
	return Complex(real + other.real, imag + other.imag);
}

// операция вычитания 
Complex Complex::operator-(const Complex& other) const
{
	return Complex(real - other.real, imag - other.imag);
}

// умножение на сколяр
Complex Complex::operator*(double scalar) const
{
	return Complex(scalar * real, scalar * imag);
}

// Модуль комплексного чило
// sqrt(a^2 + b^2);
double Complex::abs() const
{
	return std::sqrt(real * real + imag * imag);
}

double Complex::GetReal() const
{
	return real;
}

double Complex::GetImag() const
{
	return imag;
}

void Complex::print() const
{
	std::cout << "(" << real << ", " << imag << "i)" << std::endl;

}




