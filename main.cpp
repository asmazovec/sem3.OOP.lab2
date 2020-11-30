#include "matrix.hpp"
#include "vector.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>


using namespace linear;
int main() {
    try {
        std::cout << std::setprecision(4);
        
        matrix M {{1.12456, 3, 5}, {3, 3, 2}, {4, 5, 5}, {2, 3, 4}};
        std::cout << M << std::endl;

        std::cout << M[1] << std::endl; 
        std::cout << M[1][1] << std::endl; 

        matrix A1 {{1, 2}, {3, 4}};
        M *= M;
        matrix B1 {{5, 6}, {7, 8}};

        A1 *= B1;
        std::cout << (A1 *= B1) << std::endl;

        std::cout << A1 * 2 << std::endl;
        std::cout << 2 * A1 << std::endl;

        M = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
        std::cout << M << std::endl;
    }
    catch (std::exception &exception) {
        std::cerr << "Standard exception: \x1B[1;31m" << exception.what() << "\x1B[0m" << std::endl;
    } catch (...) {
		std::cerr << "\x1B[1;31m" << "Undetermined exception" << "\x1B[31m" << std::endl;
    }
    return 0;
}

