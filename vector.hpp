#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"
#include <iostream>
#include <initializer_list>


namespace linear {
    class vector {
        private:
            double* m_data;
            explicit vector (double*, long unsigned int width);

        protected:
            long unsigned int m_width;

        public:
            explicit vector (long unsigned int width = 1);
            explicit vector (long unsigned int width, double def);
            vector (const vector&); // копирование
            vector (vector&&); // перемещение
            vector (const std::initializer_list<double> &list);
            ~vector();
            
            // вспомогательные
            long unsigned int get_width() const;
            bool is_proport (const vector&) const;
            double abs() const;
            vector& get_normalize() const;
            vector& to_normalize();

            // индексирование
            double& operator[] (long unsigned int index);
            double operator[] (long unsigned int index) const;

            // унарные + и -
            vector& operator+ ();
            vector& operator- ();

            // присваивание
            vector& operator= (const vector&); // оператор копирования
            vector& operator= (vector&&); // оператор перемещения
            vector& operator= (double);

            vector& operator+= (const vector&);
            vector& operator-= (const vector&);

            vector& operator*= (double); // произведение со скаляром

            // внешние функции
            friend bool is_proport (const vector&, const vector&);
            friend vector operator+ (const vector&, const vector&);
            friend vector operator- (const vector&, const vector&);
            friend vector operator* (const vector&, double); // произведение со скаляром
            friend vector operator* (double, const vector&); // 

            // стейтмент вывода
            friend std::ostream& operator<< (std::ostream&, const vector&);

            //
            friend vector& matrix::operator[] (long unsigned int row);
            friend vector matrix::operator[] (long unsigned int row) const;
    };
}

#endif /* VECTOR_HPP */
