#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction
{
public:
    Fraction();

    Fraction(int num, int den);
    Fraction(unsigned int num, unsigned int den, bool neg = false);

    // Getters
    unsigned int Num() const;
    unsigned int Den() const;
    bool Neg() const;

    // Setters
    void Num(const unsigned int& i);
    void Den(const unsigned int& i);

    void Num(const int& i);
    void Den(const int& i);

    void Neg(const bool& b);

    // Finds and divides numerator and denominator by largest common divisor
    void Simplify();

    Fraction operator+(const Fraction& f) const;
    Fraction operator-(const Fraction& f) const;

    Fraction operator*(const int& i) const;
    Fraction operator/(const int& i) const;

    Fraction operator*(const Fraction& f) const;
    Fraction operator/(const Fraction& f) const;

    bool operator==(const Fraction& f) const;
    bool operator!=(const Fraction& f) const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
    friend std::istream& operator>>(std::istream& is, Fraction& frac);

private:

    // Returns copy with flipped positive/negative sign
    Fraction FlippedSign() const;

    unsigned int m_Num;
    unsigned int m_Den;

    bool m_Neg;
};

unsigned int LargestDivisor(unsigned int a, unsigned int b);

#endif // FRACTION_H