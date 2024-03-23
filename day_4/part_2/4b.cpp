#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
using namespace std;

pair<int, int> totalCards(const string &inputFileName)
{
    ifstream file(inputFileName);
    string lines;
    int total = 0;
    map<int, int> N;
    int i = 0;

    while (getline(file, lines))
    {
        i++;
        N[i]++;

        if (lines.empty())
            continue;

        vector<int> luckyNumbers;
        vector<int> numbers;
        string cardId, combinations;
        istringstream line(lines);

        getline(line, cardId, ':');
        getline(line, combinations);
        if (cardId.empty() || combinations.empty())
            continue;
        string luckySets, numberSets;
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
            for (int j = 0; j < count; j++)
            {
                N[i + 1 + j] += N[i];
            }
                }
    }

    int sumN = 0;
    for (auto const &pair : N)
    {
        sumN += pair.second;
        cout << pair.first << " " << pair.second << endl;
    }

    return {total, sumN};
}

int main()
{
    pair<int, int> result = totalCards("input.txt");
    cout << "Total cards: " << result.first << ", Sum: " << result.second << endl;
    return 0;
}