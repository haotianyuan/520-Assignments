#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {//im here
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce(Fraction a){
  if(a.num==0){
    return (Fraction) { 0, a.den};
  }
  bool num=true;//positive
  bool den=true;

  if(a.num<0){
    a.num=-a.num;
    num=false;
  }
  if(a.den<0){
    a.den=-a.den;
    den=false;
  }

  int i,gcd;
  for(i=1; i<= a.num && i <= a.den; i++){
    if(a.num%i==0 && a.den%i==0)
        gcd = i;
  }

  if(num==false && den==false){//both negative
    return (Fraction) { a.num/gcd, a.den/gcd };
  }

  if(num==false){//num negative
    return (Fraction) { -a.num/gcd, a.den/gcd };
  }

  if(den==false){//den negative
    return (Fraction) { a.num/gcd, -a.den/gcd };
  }
  return (Fraction) { a.num/gcd, a.den/gcd };
}