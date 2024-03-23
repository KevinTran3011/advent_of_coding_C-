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

bool isSymbol(int i, int j, const vector<string> &lines, int n, int m)
{
    if (!(0 <= i && i < n && 0 <= j && j < m))
    {
        return false;
    }
    return lines[i][j] != '.' && !isdigit(lines[i][j]);
}

int checkGearTotal(const string &inputFileName)
{
    ifstream file(inputFileName);
    string line;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    int n = lines.size();
    int m = lines[0].size();

    int total = 0;
    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        while (j < m)
        {
            int start = j;
            string num = "";
            while (j < m && isdigit(lines[i][j]))
            {
                num += lines[i][j];
                ++j;
            }
            if (num.empty())
            {
                ++j;
                continue;
            }
            int numInt = stoi(num);
            if (isSymbol(i, start - 1, lines, n, m) || isSymbol(i, j, lines, n, m))
            {
                total += numInt;
                continue;
            }
            for (int k = start - 1; k < j + 1; ++k)
            {
                if (isSymbol(i - 1, k, lines, n, m) || isSymbol(i + 1, k, lines, n, m))
                {
                    total += numInt;
                    break;
                }
            }
        }
    }
    return total;
}

int main()
{
    cout << checkGearTotal("input.txt") << endl;
    return 0;
}