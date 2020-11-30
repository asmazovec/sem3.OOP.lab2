#ifndef VECTOR_CPP
#define VECTOR_CPP


#include "vector.hpp"
#include <stdexcept>
#include <iomanip>
#include <cmath>


#ifdef DEBUG

#if defined (__linux) || defined (__gnu_linux__) || defined (linux) || defined (__linux__)

#define NCOL "\x1b[0m"  // normal color
#define GCOL "\x1B[32m" // green color

#else  /* OPERATING SYSTEM */

#define NCOL "" 
#define GCOL ""

#endif /* OPERATING SYSTEM */

#endif /* DEBUG */


namespace linear {
    vector::vector (long unsigned int width)
    : m_width (width) {

#ifdef DEBUG
        std::cout << GCOL
                  << "vector constructor "
                  << NCOL
                  << std::endl;
#endif

        if (width < 1)
            throw std::invalid_argument ("Invalid vector size ");
        m_data = new double[m_width];
    }

    vector::vector (long unsigned int width, double def)
    : m_width (width) {

#ifdef DEBUG
        std::cout << GCOL
                  << "vector constructor with default " 
                  << NCOL
                  << std::endl;
#endif

        if (width < 1)
            throw std::invalid_argument ("Invalid vector size ");
        m_data = new double[m_width];
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] = def;
    }

    vector::vector (const vector& refer)
    : m_width (refer.m_width) {

#ifdef DEBUG
        std::cout << GCOL
                  << "vector constructor copy \x1B[0m" 
                  << NCOL
                  << std::endl;
#endif

        m_data = new double[m_width];
        for (long unsigned int i = 0; i < m_width; i++)
            m_data[i] = refer.m_data[i];
    }

    vector::vector (vector&& refer)
    : m_data (refer.m_data), m_width (refer.m_width) {

#ifdef DEBUG
        std::cout << GCOL 
                  << "vector constructor move " 
                  << NCOL
                  << std::endl;
#endif

        refer.m_width = 0;
        refer.m_data = nullptr;
    }

    vector::vector (const std::initializer_list<double> &list)
    : m_width (list.size()) {

#ifdef DEBUG
        std::cout << GCOL 
                  << "vector constructor initializer list \x1B[0m" 
                  << NCOL
                  << std::endl;
#endif

        if (m_width < 1)
            throw std::length_error ("Invalid initialiser list ");
        m_data = new double[m_width];
        int count = 0;
        for (auto &element : list) 
			m_data[count++] = element;
    }

    vector::vector (double* list, long unsigned int width)
    : m_data (list), m_width (width) {

#ifdef DEBUG
        std::cout << GCOL
                  << "vector constructor pointer \x1B[0m" 
                  << NCOL
                  << std::endl;
#endif

        if (width < 1)
            throw std::invalid_argument ("Invalid vector size ");
    }

    vector::~vector() {

#ifdef DEBUG
        std::cout << GCOL 
                  << "vector destructor \x1B[0m" 
                  << NCOL
                  << std::endl;
#endif

        delete[] m_data; 
    }


    // вспомогательные
    long unsigned int vector::get_width() const {
        return m_width;
    }

    bool vector::is_proport (const vector& V) const {
        return m_width == V.m_width;
    }

    double vector::abs() const {
        int abs = 0;
        for (long unsigned int i = 0; i < m_width; i++)
            abs += m_data[i] * m_data[i];
        return sqrt(abs);
    }

    vector& vector::get_normalize() const {
        double len = abs();
        vector* tmp = new vector (m_width);
        for (long unsigned int i = 0; i < m_width; i++) 
            (*tmp)[i] = m_data[i] / len;
        return *tmp;
    }

    vector& vector::to_normalize() {
        double len = abs();
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] = m_data[i] / len;
        return *this;
    }


    // индексирование
    double& vector::operator[] (long unsigned int index) {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }

    double vector::operator[] (long unsigned int index) const {
        if (index < 0)
            throw std::invalid_argument ("Invalid index ");
        if (index >= m_width) 
            throw std::out_of_range ("Index is out of range ");
        return m_data[index];
    }


    // унарные + и -
    vector& vector::operator+ () { 
        return *this;
    }

    vector& vector::operator- () {
        *this *= -1;
        return *this;
    }


    // присваивания
    vector& vector::operator= (const vector& refer) {

#ifdef DEBUG
        std::cout << GCOL
                  << "vector operator= copy " 
                  << NCOL
                  << std::endl;
#endif

        delete m_data;
        m_width = refer.m_width;
        m_data = new double[m_width];
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] = refer.m_data[i];
        return *this;
    }

    vector& vector::operator= (vector&& refer) {

#ifdef DEBUG
        std::cout << GCOL 
                  << "vector operator= move " 
                  << NCOL
                  << std::endl;
#endif

        if (&refer == this)
            return *this;
        delete m_data;
        m_width = refer.m_width;
        m_data = refer.m_data;
        refer.m_width = 0;
        refer.m_data = nullptr;
        return *this;
    }

    vector& vector::operator= (double def) {
        for (long unsigned int i = 0; i < m_width; i++)
            m_data[i] = def;
        return *this;
    }

    vector& vector::operator+= (const vector& B) {
        if (!is_proport (B)) 
            throw std::length_error ("Vectors are not proportionate ");
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] += B.m_data[i];
        return *this;
    }

    vector& vector::operator-= (const vector& B) { 
        if (!is_proport (B)) 
            throw std::length_error ("Vectors are not proportionate ");
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] -= B.m_data[i];
        return *this;
    }

    vector& vector::operator*= (double B) {
        for (long unsigned int i = 0; i < m_width; i++) 
            m_data[i] *= B;
        return *this;
    }


    // внешние функции
    bool is_proport (const vector& A, const vector& B) {
        return A.m_width == B.m_width; 
    }

    vector operator+ (const vector& A, const vector& B) {
        return vector (A) += B;
    }
  
    vector operator- (const vector& A, const vector& B) {
        return vector (A) -= B;
    }

    vector operator* (const vector& A, double B) {
        return vector (A) *= B;
    }

    vector operator* (double A, const vector& B) {
        return vector (B) *= A;
    }


    // стейтмент вывода
    std::ostream& operator<< (std::ostream& out, const vector& V) {
        std::ios state (nullptr);
        state.copyfmt(std::cout);
        out << "(";
        for (long unsigned int i = 0; i < V.m_width; i++) {
            out.copyfmt (state);
            out << V.m_data[i]
                << ((i == V.m_width - 1)?")":", ");
        }
        return out;
    }
}

#endif /* VECTOR_CPP */
