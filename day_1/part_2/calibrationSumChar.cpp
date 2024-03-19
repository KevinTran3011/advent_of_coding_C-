#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

int main(){
    ifstream file("input.txt");
    string line;
    int total = 0;
    while(getline(file, line)){
        vector<int> numbers;
        vector<string> numbersCharacter = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};        int firstDigit = -1;
        int lastDigit = -1;
        int sumLine = 0;

        for(int i =0; i < line.size(); i++){
            if(isdigit(line[i])){
                numbers.push_back(line[i] - '0');
            }
            else{
                for(int j = 0; j < numbersCharacter.size(); j++){
                    if(line.substr(i, numbersCharacter[j].size()) == numbersCharacter[j]){
                        numbers.push_back(j+1);
                    }

                }
                
            }
        }
        if(!numbers.empty()){
            firstDigit = numbers[0];
            lastDigit = numbers[numbers.size()-1];
            sumLine = firstDigit*10 + lastDigit;
            total += sumLine;

        }

    }

    cout << "Total: " << total << endl;
    return 0;
}