#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

long long closestLocation(const string &inputFileName)
{
    ifstream file(inputFileName);
    vector<long long> locationNums;
    if (file.is_open())
    {
        string line;
        string conversionMap;
        while (getline(file, line))
        {
            conversionMap += line + "\n";
        }
        file.close();

        vector<string> segments;
        size_t pos = 0;
        while ((pos = conversionMap.find("\n\n")) != string::npos)
        {
            segments.push_back(conversionMap.substr(0, pos));
            conversionMap.erase(0, pos + 2);
        }
        segments.push_back(conversionMap);

        string seeds = segments[0];
        regex numRegex("\\d+");
        sregex_iterator currentSeed(seeds.begin(), seeds.end(), numRegex);
        sregex_iterator finalSeed;

        while (currentSeed != finalSeed)
        {
            long long num = stoll((*currentSeed).str());
            for (size_t i = 1; i < segments.size(); ++i)
            {
                regex matchMap("(\\d+) (\\d+) (\\d+)");
                sregex_iterator currentMatch(segments[i].begin(), segments[i].end(), matchMap);
                sregex_iterator endSegment;
                while (currentMatch != endSegment)
                {
                    smatch match = *currentMatch;
                    long long destination = stoll(match[1].str());
                    long long start = stoll(match[2].str());
                    long long delta = stoll(match[3].str());
                    if (num >= start && num < start + delta)
                    {
                        num += destination - start;
                        break;
                    }
                    ++currentMatch;
                }
            }
            locationNums.push_back(num);
            ++currentSeed;
        }
    }
    return *min_element(locationNums.begin(), locationNums.end());
}

int main()
{
    cout << closestLocation("input.txt") << endl;
    return 0;
}
