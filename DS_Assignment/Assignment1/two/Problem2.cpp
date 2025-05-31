// #include "Polynomial.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Polynomial
{
private:
    int order;

public:
    int *coefficients;
    Polynomial();
    Polynomial(int order);
    ~Polynomial();

    // Function declarations
    void display() const;
    Polynomial add(const Polynomial &p);
    Polynomial subtract(const Polynomial &p);
};

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(int order)
{
    this->order = order;
    coefficients = new int[order + 1];
    for (int i = 0; i <= order; ++i)
        coefficients[i] = 0;
}

Polynomial::~Polynomial()
{
    delete[] coefficients;
}


void Polynomial::display() const
{
    bool firstTerm = true;
    for (int i = 0; i <= order; ++i)
    {
        int power = order - i;
        if (coefficients[i] != 0)
        {
            if (!firstTerm && coefficients[i] > 0)
                cout << " + ";
            if (coefficients[i] < 0)
                cout << " - ";

            cout << abs(coefficients[i]);
            if (power > 0)
                cout << "x^" << power;

            firstTerm = false;
        }
    }
    cout << " = 0" << endl;
}

Polynomial Polynomial::add(const Polynomial &p)
{
    int maxOrder = max(order, p.order);
    Polynomial result(maxOrder);

    for (int i = 0; i <= maxOrder; ++i)
    {
        int a = (i <= order) ? coefficients[i] : 0;
        int b = (i <= p.order) ? p.coefficients[i] : 0;
        result.coefficients[i] = a + b;
    }

    return result;
}

Polynomial Polynomial::subtract(const Polynomial &p)
{
    int maxOrder = max(order, p.order);
    Polynomial result(maxOrder);

    for (int i = 0; i <= maxOrder; ++i)
    {
        int a = (i <= order) ? coefficients[i] : 0;
        int b = (i <= p.order) ? p.coefficients[i] : 0;
        result.coefficients[i] = a - b;
    }

    return result;
}

int main()
{
    ifstream inputFile("polynomials.txt"); // hardcoded filename
    if (!inputFile)
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int order1, order2;

    // Read first polynomial
    inputFile >> order1;
    Polynomial poly1(order1);
    for (int i = 0; i <= order1; ++i)
    {
        inputFile >> poly1.coefficients[i];
    }

    // Read second polynomial
    inputFile >> order2;
    Polynomial poly2(order2);
    for (int i = 0; i <= order2; ++i)
    {
        inputFile >> poly2.coefficients[i];
    }

    inputFile.close();

    // Display polynomials
    cout << "First polynomial: ";
    poly1.display();

    cout << "Second polynomial: ";
    poly2.display();

    Polynomial sum = poly1.add(poly2);
    cout << "Sum of polynomials: ";
    sum.display();

    Polynomial difference = poly2.subtract(poly1);
    cout << "Difference of polynomials: ";
    difference.display();

    return 0;
}