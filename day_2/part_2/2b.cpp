#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

string removeExtraSpaces(const string &str)
{
    string result;
    unique_copy(str.begin(), str.end(), back_inserter(result), [](char a, char b)
                { return isspace(a) && isspace(b); });
    return result;
}

int maxTotal(const string &inputFileName)
{
    ifstream file(inputFileName);
    string line;
    int totalPower = 0;

    while (getline(file, line))
    {
        line = removeExtraSpaces(line);
        istringstream game(line);
        string gameId, gameCombination;
        getline(game, gameId, ':');
        getline(game, gameCombination);
        int gamePower = 1;
        istringstream combinations(gameCombination);
        string subsets;
        map<string, int> colorCount = {{"red", 0}, {"green", 0}, {"blue", 0}};

        while (getline(combinations, subsets, ';'))
        {
            istringstream cubeQuantity(subsets);
            string cube;

            while (getline(cubeQuantity, cube, ','))
            {
                stringstream ss(cube);
                string quantity, color;
                ss >> quantity >> color;

                if (colorCount.find(color) != colorCount.end())
                {
                    colorCount[color] = max(stoi(quantity), colorCount[color]);
                }
            }
        }

        cout << gameId << " : ";
        for (const auto &[color, quantity] : colorCount)
        {
            cout << "color: " << color << ", quantity: " << quantity << "; ";
            gamePower *= quantity;
        }
        cout << endl;

        totalPower += gamePower;
    }

    return totalPower;
}

int main()
{
    cout << maxTotal("input.txt") << endl;
    return 0;
}