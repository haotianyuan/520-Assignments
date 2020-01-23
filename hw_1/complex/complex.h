#ifndef COPMLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Fraction object and method definitions
 *
 *  A fraction object is a struct with a numerator, denoted num, and
 *  a denominator, denoted den. Varions Methods that take fractions and return 
 *  fractions do arithmetical operations on them.
 */
typedef struct {
    double real;
    double im;
} Complex;


Complex add ( Complex a, Complex b );
Complex negate ( Complex a, Complex b );
Complex multiply ( Complex a,Complex b);
double magnitude( Complex a);


#endif