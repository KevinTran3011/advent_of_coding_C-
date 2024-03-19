#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

string removeExtraSpaces(const string& str) {
    string result;
    unique_copy(str.begin(), str.end(), back_inserter(result), [](char a,char b){ return isspace(a) && isspace(b);});
    return result;
}

int checkGame(const string& inputFileName){
    ifstream file(inputFileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << inputFileName << endl;
        return -1;
    }

    string line;
    int total = 0;

    map<string, int> colorMap = {
            {"red", 12},
            {"green", 13},
            {"blue", 14}
    };

    while(getline(file, line)){
        line = removeExtraSpaces(line);
        string quantity, color;

        istringstream game(line);
        string gameId, gameCombination;
        getline(game, gameId, ':');
        getline(game, gameCombination);
        istringstream combination(gameCombination);
        string subsets;
        bool isGameValid = true;

        map<string, int> colorCount = {
                {"red", 0},
                {"green", 0},
                {"blue", 0}
        };

        int id = stoi(gameId.substr(gameId.find(" ") + 1)); 

        while (getline(combination, subsets, ';')) {
            istringstream cubeQuantity(subsets);
            string cube;

            while (getline(cubeQuantity, cube, ',')) {
                stringstream ss(cube);
                ss >> quantity >> color;

                if(colorCount.find(color) != colorCount.end()) {
                    colorCount[color] = max(stoi(quantity),     colorCount[color]);
                } else {
                    cerr << "Invalid color: " << color << endl;
                    return -1;
                }

                for(auto const& pair: colorCount) {
                    if(pair.second > colorMap[pair.first]) {
                        isGameValid = false;
                        break;
                    }
                }
            } 
        }

        if(isGameValid) {
            for(auto const& pair: colorCount) {
                cout << "Game:" << id << " Color: " << pair.first << ", Quantity: " << pair.second << endl;
            }

            total += id;
        }
    }

    return total;
}


int main(){
    cout << checkGame("input.txt") << endl;
    return 0;
}