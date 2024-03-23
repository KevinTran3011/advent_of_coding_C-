#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool isSymbol(int i, int j, int num, const vector<string> &lines, vector<vector<vector<int>>> &gears, int n, int m)
{
    if (!(0 <= i && i < n && 0 <= j && j < m))
    {
        return false;
    }
    if (lines[i][j] == '*')
    {
        gears[i][j].push_back(num);
    }
    return lines[i][j] != '.' && !isdigit(lines[i][j]);
}

int checkParttNum(const string &input)
{
    ifstream file(input);
    string line;
    vector<string> lines;
    int finalResult = 0;
    int gearTotal = 0;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    int n = lines.size();
    int m = lines[0].size();
    vector<vector<vector<int>>> gears(n, vector<vector<int>>(m));

    for (int i = 0; i < n; ++i)
    {
        int j = 0;
        while (j < m)
        {
            int start = j;
            string numStr = "";
            while (j < m && isdigit(lines[i][j]))
            {
                numStr += lines[i][j];
                ++j;
            }
            if (numStr.empty())
            {
                ++j;
                continue;
            }
            int num = stoi(numStr);
            isSymbol(i, start - 1, num, lines, gears, n, m) || isSymbol(i, j, num, lines, gears, n, m);
            for (int k = start - 1; k < j + 1; ++k)
            {
                isSymbol(i - 1, k, num, lines, gears, n, m) || isSymbol(i + 1, k, num, lines, gears, n, m);
            }
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (lines[i][j] == '*' && gears[i][j].size() == 2)
            {
                gearTotal = gears[i][j][0] * gears[i][j][1];

                finalResult += gearTotal;
            }
        }
    }
    return finalResult;
}

int main()
{
    cout << checkParttNum("input.txt") << endl;
    return 0;
}