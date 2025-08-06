#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <random>


namespace EasySDL
{   
    template <typename T = float>
    class Matrix
    {
    public:
        int rows;
        int cols;
        std::vector<std::vector<T>> m;
        
        Matrix() = default;

        Matrix(int rows, int cols) : m(rows, std::vector<T>(cols))
        {
            this->rows = rows;
            this->cols = cols;
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] = 0;
                }
            }
        }

        Matrix(std::initializer_list<std::initializer_list<T>> list)
            : rows(list.size()), cols(list.begin()->size()), m(list.size())
        {
            size_t i = 0;
            for (const auto &row : list)
            {
                if (row.size() != cols)
                {
                    throw std::runtime_error("All rows must have the same number of columns.");
                }
                m[i++] = std::vector<T>(row);
            }
        }

        Matrix<T> operator+(const T &scalar) const
        {
            Matrix<T> result(this->rows, this->cols);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    result.m[i][j] = this->m[i][j] + scalar;
                }
            }
            return result;
        }

        void operator+=(const T &scalar)
        {
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] += scalar;
                }
            }
        }

        Matrix<T> operator-(const T &scalar) const
        {
            Matrix<T> result(this->rows, this->cols);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    result.m[i][j] = this->m[i][j] - scalar;
                }
            }
            return result;
        }

        void operator-=(const T &scalar)
        {
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] -= scalar;
                }
            }
        }


        Matrix<T> operator+(const Matrix<T> &otherMatrix) const
        {
            if (this->rows != otherMatrix.rows || this->cols != otherMatrix.cols)
            {
                throw std::runtime_error("Matrix dimensions must match for addition.");
            }
            Matrix<T> result(this->rows, this->cols);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    result.m[i][j] = this->m[i][j] + otherMatrix.m[i][j];
                }
            }
            return result;
        }

        void operator+=(const Matrix<T> &otherMatrix)
        {
            if (this->rows != otherMatrix.rows || this->cols != otherMatrix.cols)
            {
                throw std::runtime_error("Matrix dimensions must match for addition.");
            }
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] += otherMatrix.m[i][j];
                }
            }
        }

        Matrix<T> operator-(const Matrix<T> &otherMatrix) const
        {
            if (this->rows != otherMatrix.rows || this->cols != otherMatrix.cols)
            {
                throw std::runtime_error("Matrix dimensions must match for subtraction.");
            }
            Matrix<T> result(this->rows, this->cols);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    result.m[i][j] = this->m[i][j] - otherMatrix.m[i][j];
                }
            }
            return result;
        }

        void operator-=(const Matrix<T> &otherMatrix) 
        {
            if (this->rows != otherMatrix.rows || this->cols != otherMatrix.cols)
            {
                throw std::runtime_error("Matrix dimensions must match for subtraction.");
            }
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] -= otherMatrix.m[i][j];
                }
            }
        }

        Matrix<T> operator*(const T &scalar) const
        {
            Matrix<T> result(this->rows, this->cols);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    result.m[i][j] = this->m[i][j] * scalar;
                }
            }
            return result;
        }

        void operator*=(const T &scalar)
        {
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] *= scalar;
                }
            }
        }

        Matrix<T> operator*(const Matrix<T> &otherMatrix) const
        {
            if (this->cols != otherMatrix.rows)
            {
                throw std::runtime_error("Matrix dimensions must match rows = cols");
            }
            Matrix<T> result(this->rows, otherMatrix.cols);

            for (size_t i = 0; i < result.rows; i++)
            {
                for (size_t j = 0; j < result.cols; j++)
                {
                    T operation = 0;
                    for (size_t k = 0; k < this->cols; k++)
                    {
                        operation += this->m[i][k] * otherMatrix.m[k][j];
                    }

                    result.m[i][j] = operation;
                }
            }

            return result;
        }

        std::vector<T> &operator[](size_t row)
        {
            return m[row];
        }
        const std::vector<T> &operator[](size_t row) const
        {
            return m[row];
        }

        Matrix<T> t() const
        {
            Matrix<T> result(this->cols, this->rows);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    result.m[j][i] = this->m[i][j];
                }
            }
            return result;
        }

        void randomize()
        {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::uniform_real_distribution<T> distribution(-1.0, 1.0);
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] = distribution(generator);
                }
            }
        }

        void print() const
        {
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {   
                    if(j == 0){
                        if(this->m[i][j] < 0)  std::cout << "   N"<< std::setw(3) << std::left << i+1 << " |" + std::to_string(this->m[i][j]) + "|";
                        else                   std::cout << "   N"<< std::setw(3) << std::left << i+1 <<  " | " + std::to_string(this->m[i][j]) + "|";
                        continue;
                    }  
                    if(this->m[i][j] < 0) std::cout << "" + std::to_string(this->m[i][j]) + "|";
                    else                  std::cout << " " + std::to_string(this->m[i][j]) + "|";

                    
                }
                std::cout << std::endl;
            }
        }

        void applyFuntion(T (*f)(T))
        {
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] = f(this->m[i][j]);
                }
            }
        }

        void pow(const T n){
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] = std::pow(this->m[i][j],n);
                }
            }
        }

        static T mean(const Matrix<T> &m) {
            if (m.cols > 1)
            {
                throw std::runtime_error("Matrix dimensions mismatch: expected 1 column.");
            }
            T result;
            for (size_t i = 0; i < m.rows; i++)
            {
                result += m[i][0];   
            }
            return result / m.rows;
        }

        static T sum(const Matrix<T> &m) {
            if (m.cols > 1)
            {
                throw std::runtime_error("Matrix dimensions mismatch: expected 1 column.");
            }
            T result;
            for (size_t i = 0; i < m.rows; i++)
            {
                result += m[i][0];   
            }
            return result;
        }

        void hadamardProduct(const Matrix<T> & otherMatrix){
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    this->m[i][j] *= otherMatrix.m[i][j];
                }
            }
        }

        Matrix<T> getRow(size_t i) const {
            if (i >= this->rows) throw std::out_of_range("Row index out of range");
            
            Matrix<T> rowMatrix(1, this->cols);
            rowMatrix.m[0] = this->m[i];  
            return rowMatrix;
        }

    };
}
