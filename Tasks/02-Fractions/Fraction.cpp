#include "Fraction.h"

Fraction::Fraction():
    m_Num(0), m_Den(0), m_Neg(false)
{ }

Fraction::Fraction(int num, int den)
{
    if (num < 0 ^ den < 0)
        m_Neg = true;
    
    else
        m_Neg = false;

    m_Den = abs(den);
    m_Num = abs(num);
}

Fraction::Fraction(unsigned int num, unsigned int den, bool neg):
    m_Num(num), m_Den(den), m_Neg(neg)
{ }

unsigned int Fraction::Num() const
{
    return m_Num;
}

unsigned int Fraction::Den() const
{
    return m_Den;
}

bool Fraction::Neg() const
{
    return m_Neg;
}

void Fraction::Num(const unsigned int& i)
{
    m_Num = i;
}

void Fraction::Den(const unsigned int& i)
{
    m_Den = i;
}

void Fraction::Num(const int& i)
{
    if (i < 0)
        m_Neg = !m_Neg;

    m_Num = i;
}

void Fraction::Den(const int& i)
{
    if (i < 0)
        m_Neg = true;
    
    else
        m_Neg = false;
    
    m_Den = i;
}

void Fraction::Neg(const bool& b)
{
    m_Neg = b;
}

Fraction Fraction::operator*(const int& i) const
{
    return Fraction(m_Num * i, m_Den, i < 0 ? !m_Neg : m_Neg);
}

Fraction Fraction::operator/(const int& i) const
{
    return Fraction(m_Num, m_Den * i, i < 0 ? !m_Neg : m_Neg);
}

Fraction Fraction::operator*(const Fraction& f) const
{
    return Fraction(m_Num * f.m_Num, m_Den * f.m_Den, m_Neg ^ m_Neg);
}

Fraction Fraction::operator/(const Fraction& f) const
{
    return Fraction(m_Num * f.m_Den, m_Den * f.m_Num, m_Neg ^ m_Neg);
}

bool Fraction::operator==(const Fraction& f) const
{
    return m_Neg == f.m_Neg && m_Num == f.m_Num && m_Den == f.m_Den;
}

bool Fraction::operator!=(const Fraction& f) const
{
    return m_Neg != f.m_Neg || m_Num != f.m_Num && m_Den == f.m_Den;
}

Fraction Fraction::operator+(const Fraction& f) const
{
    // a + -b = a - b
    if (m_Neg && !f.m_Neg)
        return f - FlippedSign();
    
    // Likewise -a + b = b - a
    else if (f.m_Neg && !m_Neg)
        return f.FlippedSign() - *this;
    
    return Fraction((m_Num * f.m_Den) + (f.m_Num * m_Den), m_Den * f.m_Den, m_Neg);
}

Fraction Fraction::operator-(const Fraction& f) const
{
    // a - -b = a + b
    // -a - b = -(a + b)
    // Therefore on XOR just flip the sign of b then add
    if (m_Neg ^ f.m_Neg)
        f.FlippedSign() + *this;

    const unsigned int numMult = m_Num * f.m_Den;
    const unsigned int fNumMult = f.m_Num * m_Den;

    // Avoid overflow from subtracting larger from smaller
    if (numMult < fNumMult)
        return Fraction(fNumMult - numMult, m_Den * f.m_Den, !m_Neg);
    
    return Fraction(numMult - fNumMult, m_Den * f.m_Den, m_Neg);
}

void Fraction::Simplify()
{
    const unsigned int d = LargestDivisor(m_Num, m_Den);
    m_Num /= d;
    m_Den /= d;
}

Fraction Fraction::FlippedSign() const
{
    return Fraction(m_Num, m_Den, !m_Neg);
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac)
{
    os << (frac.m_Neg ? "-" : "") << frac.m_Num << '/' << frac.m_Den;
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& frac)
{
    int num, den;
    is >> num >> den;
    frac = Fraction(num, den);
    return is;
}

unsigned int LargestDivisor(unsigned int a, unsigned int b)
{
    if (a == b)
        return a;
    
    const unsigned int min = a < b ? a : b;
    const unsigned int max = b > a ? b : a;

    if (min == 0)
        return 1;
    
    // Largest divisor is equal to remainder of max / min
    // If remaineder is 0 min is largest divisor
    const unsigned int mod = max % min;
    return mod ? mod : min;
}