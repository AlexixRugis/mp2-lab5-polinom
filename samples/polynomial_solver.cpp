#include <iostream>
#include "polynomial.h"

using namespace std;

void print_error(const std::string& input, const syntax_error& err)
{
    cout << "Error occured: " << err.message << endl;
    int left_bound = std::max(0, (int)err.pos - 10);
    cout << "..." << input.substr(left_bound, 20) << "..." << endl;
    cout << string(err.pos - left_bound + 3, ' ') << '^' << endl;
    cout << "At position: " << err.pos << endl;
}

int main()
{
    std::string p;
    getline(std::cin, p);

    auto poly = polynomial::from_string(p);
    if (poly.index())
    {
        syntax_error err = std::get<syntax_error>(poly);
        print_error(p, err);
    }
    else
    {
        cout << std::get<polynomial>(poly) << endl;
    }

    return 0;
}