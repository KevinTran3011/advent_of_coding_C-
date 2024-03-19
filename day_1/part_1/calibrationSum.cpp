#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // Include this to use isdigit
#include <vector> // Include this to use vectors
using namespace std;

int main()
{
    ifstream file("input.txt");
    string line;
    int total = 0; // Initialize total to 0
    while (getline(file, line))
    {
        vector<int> digits;
        for (int i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
            {
                digits.push_back(line[i] - '0');
            }
        }
        int firstDigit = -1;
        int lastDigit = -1;
        int sumTotal = 0;
        if (!digits.empty())
        {
            firstDigit = digits[0];
            lastDigit = digits[digits.size() - 1];
            sumTotal += firstDigit * 10 + lastDigit;
        }
        total += sumTotal;
    }
    cout << "Total: " << total << endl;
    return 0;
}