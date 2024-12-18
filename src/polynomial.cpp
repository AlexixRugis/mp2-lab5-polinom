#include "polynomial.h"
#include <cmath>

polynomial polynomial::operator+(const polynomial& other) const
{
    polynomial result;

    auto it1 = mMonomials.begin();
    auto it2 = other.mMonomials.begin();
    
    while (it1 != mMonomials.end() && it2 != other.mMonomials.end())
    {
        uint32_t deg1 = (*it1).degree();
        uint32_t deg2 = (*it2).degree();

        if (deg1 > deg2)
        {
            result.mMonomials.push_back(*it1);
            ++it1;
        }
        else if (deg2 > deg1)
        {
            result.mMonomials.push_back(*it2);
            ++it2;
        }
        else
        {
            double coefficient = (*it1).coefficient() + (*it2).coefficient();
            if (coefficient != 0.0)
            {
                result.mMonomials.push_back(monomial(coefficient, (*it1).w(), (*it1).x(), (*it1).y(), (*it1).z()));
            }
            ++it1;
            ++it2;
        }
    }

    while (it1 != mMonomials.end())
    {
        result.mMonomials.push_back(*it1);
        ++it1;
    }

    while (it2 != other.mMonomials.end())
    {
        result.mMonomials.push_back(*it2);
        ++it2;
    }

    return result;
}

polynomial polynomial::operator*(double coefficient) const
{
    polynomial result;

    if (coefficient == 0.0) return result;

    for (auto it = mMonomials.begin(); it != mMonomials.end(); ++it)
    {
        result.mMonomials.push_back(monomial(coefficient * (*it).coefficient(), (*it).w(), (*it).x(), (*it).y(), (*it).z()));
    }

    return result;
}

polynomial operator*(double coefficient, const polynomial& p)
{
    return p * coefficient;
}

polynomial polynomial::operator-() const
{
    return (*this) * -1.0;
}

polynomial polynomial::operator-(const polynomial& other) const
{
    return (*this) + (-other);
}

polynomial& polynomial::operator+=(const polynomial& other)
{
    *this = *this + other;
    return *this;
}

polynomial& polynomial::operator-=(const polynomial& other)
{
    *this = *this - other;
    return *this;
}

polynomial& polynomial::operator*=(double coefficient)
{
    *this = *this * coefficient;
    return *this;
}

double polynomial::evaluate(double w, double x, double y, double z) const
{
    double res = 0.0;

    for (auto it = mMonomials.begin(); it != mMonomials.end(); ++it)
    {
        res += (*it).coefficient() * (
            pow(w, static_cast<double>((*it).w())) +
            pow(x, static_cast<double>((*it).x())) +
            pow(y, static_cast<double>((*it).y())) +
            pow(z, static_cast<double>((*it).z()))
            );
    }

    return res;
}

polynomial polynomial::derivative_w() const
{
    polynomial res;

    for (auto it = mMonomials.begin(); it != mMonomials.end(); ++it)
    {
        uint8_t degree = (*it).w();
        if (degree > 0)
        {
            res.mMonomials.push_back(
                monomial(static_cast<double>(degree) * (*it).coefficient(), (*it).w() - 1, (*it).x(), (*it).y(), (*it).z())
            );
        }
    }

    return res;
}

polynomial polynomial::derivative_x() const
{
    polynomial res;

    for (auto it = mMonomials.begin(); it != mMonomials.end(); ++it)
    {
        uint8_t degree = (*it).x();
        if (degree > 0)
        {
            res.mMonomials.push_back(
                monomial(static_cast<double>(degree) * (*it).coefficient(), (*it).w(), (*it).x() - 1, (*it).y(), (*it).z())
            );
        }
    }

    return res;
}

polynomial polynomial::derivative_y() const
{
    polynomial res;

    for (auto it = mMonomials.begin(); it != mMonomials.end(); ++it)
    {
        uint8_t degree = (*it).y();
        if (degree > 0)
        {
            res.mMonomials.push_back(
                monomial(static_cast<double>(degree) * (*it).coefficient(), (*it).w(), (*it).x(), (*it).y() - 1, (*it).z())
            );
        }
    }

    return res;
}

polynomial polynomial::derivative_z() const
{
    polynomial res;

    for (auto it = mMonomials.begin(); it != mMonomials.end(); ++it)
    {
        uint8_t degree = (*it).z();
        if (degree > 0)
        {
            res.mMonomials.push_back(
                monomial(static_cast<double>(degree) * (*it).coefficient(), (*it).w(), (*it).x(), (*it).y(), (*it).z() - 1)
            );
        }
    }

    return res;
}

std::variant<polynomial::monomial, std::string> polynomial::parse_monomial(const std::string& str, size_t& offset)
{
    double coefficient = std::stod(str, &offset);

    // TODO: parsing

    return std::variant<monomial, std::string>();
}

std::variant<polynomial, std::string> polynomial::parse_polynomial(const std::string& str)
{
    polynomial p;
    size_t offset = 0;
    
    while (offset < str.size())
    {
        auto res = parse_monomial(str, offset);
        if (res.index()) return std::get<std::string>(res);
        p.mMonomials.push_back(std::get<monomial>(res));
    }

    return p;
}