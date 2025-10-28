#pragma once
namespace EasySDL
{
    struct Complex
    {
        float re;
        float im;

        Complex mult(const Complex &otherComplex) const
        {
            float reMult = (this->re * otherComplex.re) - (this->im * otherComplex.im);
            float imMult = (this->re * otherComplex.im) + (this->im * otherComplex.re);
            Complex result{reMult, imMult};
            return result;
        }
        void add(const Complex &otherComplex)
        {
            this->re += otherComplex.re;
            this->im += otherComplex.im;
        }
        void average(int N)
        {
            this->re = this->re / N;
            this->im = this->im / N;
        }
    };
}
