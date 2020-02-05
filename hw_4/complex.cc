#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::real() const{
    return re;
}

double Complex::imaginary() const{
    return im;
}

Complex Complex::operator*(const Complex& other) const {
    Complex x(0,0);
    x.re=re*other.re - im*other.im;
    x.im=re*other.im + im*other.re;
    return x;
}

Complex Complex::operator+(const Complex& other) const {
    Complex x(0,0);
    x.re=other.re+re;
    x.im=other.im+im;
    return x;
}

bool Complex::operator==(const Complex& other) const {
    if(re == other.re && im==other.im){
        return true;
    }
    return false;
}

Complex Complex::conjugate() const{
    Complex res(re,-im);
    return res;
}



