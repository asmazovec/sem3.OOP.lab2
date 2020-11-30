#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <iostream>
#include <initializer_list>


namespace linear {
    class vector;

    class matrix { 
        private:
            double* m_data;

        protected:
            long unsigned int m_width;
            long unsigned int m_height;

        public:
            explicit matrix (long unsigned int size = 1); // квадратная матрица
            explicit matrix (long unsigned int size, double def); // квадратная матрица со стандартным
            explicit matrix (long unsigned int width, long unsigned int height); // прямоугольная матрица
            explicit matrix (long unsigned int width, long unsigned int height, double def); // прямоугольная матрица со стандартным
            matrix (const matrix&); // копирование
            matrix (matrix&&);  // перемещение
            matrix (const std::initializer_list<std::initializer_list<double>> &list);
            ~matrix();

            // вспомогательные 
            long unsigned int get_width() const;
            long unsigned int get_height() const;
            bool is_isomeric (const matrix&) const; // согласованность
            bool is_proport (const matrix&) const;  // соразмерность
            double max() const;
            double min() const;

            // индексирование
            vector& operator[] (long unsigned int row);
            vector operator[] (long unsigned int row) const;

            // унарные + и -
            matrix& operator+ ();
            matrix& operator- ();

            // присваивание
            matrix& operator= (const matrix&);
            matrix& operator= (matrix&&);
            matrix& operator= (const std::initializer_list<std::initializer_list<double>> &list);
            matrix& operator= (double);

            matrix& operator+= (const matrix&);
            matrix& operator-= (const matrix&);

            matrix& operator*= (const matrix&);
            matrix& operator*= (double);

            // внешние функции
            friend bool is_proport (const matrix&, const matrix&);
            friend bool is_isomeric (const matrix&, const matrix&);
            friend matrix operator+ (const matrix&, const matrix&);
            friend matrix operator- (const matrix&, const matrix&);
            friend matrix operator* (const matrix&, const matrix&);
            friend matrix operator* (const matrix&, double);
            friend matrix operator* (double, const matrix&);

            // стейтмент вывода
            friend std::ostream& operator<< (std::ostream&, const matrix&);
    };
}

#endif /* MATRIX_HPP */
