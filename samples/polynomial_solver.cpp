#include <iostream>
#include <vector>
#include <string>
#include "polynomial.h"

using namespace std;

vector<polynomial> polynomials;

void print_error(const std::string& input, const syntax_error& err)
{
    cout << "Error occured: " << err.message << endl;
    int left_bound = std::max(0, (int)err.pos - 10);
    cout << "..." << input.substr(left_bound, 20) << "..." << endl;
    cout << string(err.pos - left_bound + 3, ' ') << '^' << endl;
    cout << "At position: " << err.pos << endl;
}

polynomial get_polynomial()
{
    string str;
    do
    {
        cout << "Enter a polynomial from w, x, y, z or some of them. You can use ^ to specify degrees if you want, you cannot use * to multiply.\nEnter \"mem\" if you want to use polynomial from memory.\n";
        getline(cin >> ws, str);

        if (str == "mem")
        {
            if (polynomials.size() == 0)
            {
                cout << "No polynomials in memory yet...\n";
                continue;
            }

            for (size_t i = 0; i < polynomials.size(); ++i)
            {
                cout << i + 1 << ") " << polynomials[i] << '\n';
            }

            size_t ind;
            cout << "Enter index: ";
            cin >> ind;
            if (ind == 0 || ind > polynomials.size())
            {
                cout << "Incorrect index!\n";
                continue;
            }

            return polynomials[ind - 1];
        }

        auto p = polynomial::from_string(str);
        if (p.index())
        {
            print_error(str, std::get<syntax_error>(p));
            continue;
        }

        return std::get<polynomial>(p);
    } while (1);
}

int main()
{

    while (true)
    {
        cout << "Menu:\n";
        cout << "1) Add polynomials\n";
        cout << "2) Subtract polynomials\n";
        cout << "3) Multiply by scalar\n";
        cout << "4) Get derivative by W\n";
        cout << "5) Get derivative by X\n";
        cout << "6) Get derivative by Y\n";
        cout << "7) Get derivative by Z\n";
        cout << "8) Calculate in point\n";
        cout << "9) Show memory\n";
        cout << "10) Exit\n";
        cout << "Your choice (1-10): ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter first polynomial:\n";
            polynomial p1 = get_polynomial();
            cout << "Enter second polynomial:\n";
            polynomial p2 = get_polynomial();
            polynomials.push_back(p1 + p2);
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 2)
        {
            cout << "Enter first polynomial:\n";
            polynomial p1 = get_polynomial();
            cout << "Enter second polynomial:\n";
            polynomial p2 = get_polynomial();
            polynomials.push_back(p1 - p2);
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 3)
        {
            cout << "Enter polynomial:\n";
            polynomial p1 = get_polynomial();
            cout << "Enter multiplier:\n";
            double s;
            cin >> s;
            polynomials.push_back(s * p1);
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 4)
        {
            cout << "Enter polynomial:\n";
            polynomial p1 = get_polynomial();
            polynomials.push_back(p1.derivative_w());
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 5)
        {
            cout << "Enter polynomial:\n";
            polynomial p1 = get_polynomial();
            polynomials.push_back(p1.derivative_x());
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 6)
        {
            cout << "Enter polynomial:\n";
            polynomial p1 = get_polynomial();
            polynomials.push_back(p1.derivative_y());
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 7)
        {
            cout << "Enter polynomial:\n";
            polynomial p1 = get_polynomial();
            polynomials.push_back(p1.derivative_z());
            cout << "Result: " << polynomials.back() << '\n';
        }
        else if (choice == 8)
        {
            cout << "Enter polynomial:\n";
            polynomial p1 = get_polynomial();
            double w, x, y, z;
            cout << "Enter w: "; cin >> w;
            cout << "Enter x: "; cin >> x;
            cout << "Enter y: "; cin >> y;
            cout << "Enter z: "; cin >> z;
            cout << "Result: " << p1.evaluate(w, x, y, z) << '\n';
        }
        else if (choice == 9)
        {
            if (polynomials.size() == 0)
            {
                cout << "Memory is empty.\n";
            }

            for (size_t i = 0; i < polynomials.size(); ++i)
            {
                cout << i + 1 << ") " << polynomials[i] << '\n';
            }
        }
        else
        {
            cout << "Have a nice day! Bye\n";
            return 0;
        }
    }
}