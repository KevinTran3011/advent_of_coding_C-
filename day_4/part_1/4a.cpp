#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;

int totalPoints(const string &inputFileName)
{
    ifstream file(inputFileName);
    string lines;

    int total = 0;

    while (getline(file, lines))
    {
        if (lines.find(':') == string::npos || lines.find('|') == string::npos)
            continue;

        vector<int> luckyNumbers;
        vector<int> numbers;
        string cardId, combinations;
        istringstream line(lines);
        getline(line, cardId, ':');
        getline(line, combinations);
        string luckySets;
        string numberSets;
        istringstream combination(combinations);
        getline(combination, luckySets, '|');
        getline(combination, numberSets);

        istringstream luckySetStream(luckySets);
        int luckyNumber;
        while (luckySetStream >> luckyNumber)
        {
            luckyNumbers.push_back(luckyNumber);
        }

        istringstream numberSetStream(numberSets);
        int number;
        while (numberSetStream >> number)
        {
            numbers.push_back(number);
        }

        set<int> luckySet(luckyNumbers.begin(), luckyNumbers.end());
        set<int> numberSet(numbers.begin(), numbers.end());

        vector<int> intersection;
        set_intersection(luckySet.begin(), luckySet.end(), numberSet.begin(), numberSet.end(), back_inserter(intersection));

        int count = intersection.size();
        if (count > 0)
        {
            total += pow(2, count - 1);
        }
    }

    return total;
}

int main()
{
    cout << totalPoints("input.txt") << endl;
    return 0;
}