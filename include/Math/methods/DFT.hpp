#pragma once
#include <vector>
#include <cmath>
#include "../types/FourierData.hpp"
#include "../types/Complex.hpp"

namespace EasySDL
{
    class DFT
    {
    public:
        static std::vector<FourierData> dft(const std::vector<Complex> &data)
        {
            std::vector<FourierData> fourierInfo;
            int N = data.size();

            for (size_t k = 0; k < N; k++)
            {
                Complex sum{0, 0};
                for (size_t n = 0; n < N; n++)
                {
                    float angle = (2 * M_PI * k * n) / N;
                    float real = cos(angle);
                    float imaginary = -sin(angle);

                    Complex eulerTerms{real, imaginary};
                    Complex result = data[n].mult(eulerTerms);
                    sum.add(result);
                }
                sum.average(N);
                float frecuency = k;
                float amplitude = sqrt((sum.re * sum.re) + (sum.im * sum.im));
                float phase = atan2(sum.im, sum.re);

                FourierData fourierElement{sum, frecuency, amplitude, phase};
                fourierInfo.push_back(fourierElement);
            }
            return fourierInfo;
        }
    };
}