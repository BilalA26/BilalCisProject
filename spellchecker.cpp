# BilalCisProject

#include <iostream>
#include <stdio.h>
#include "SpellChecker.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//default constructor
SpellChecker::SpellChecker() {}

void SpellChecker::writeCorrections() {
    for (int i = 0; i < incorrectWords.size(); ++i) {
        cout << incorrectWords[i].first << ": ";//
        if (incorrectWords[i].second.size() > 0) {
            for (int j = 0; j < incorrectWords[i].second.size(); ++j) {
                cout << incorrectWords[i].second[j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void SpellChecker::readFile(string inputFilename) {
    int count = 0;
    string line;
    input.open(inputFilename);
    stringstream buffer;
    string tempWord;
    while (getline(input, line)) {
        for (int i = 0; i < line.length(); i++)//basic punctuation clean
        {
            if (!isalpha(line[i]))
                line[i] = ' ';
        }
        count++;
        stringstream buffer(line);
        while (buffer >> tempWord) {
            if (!dictionary.contains(tempWord)) {//check if present
                string tempWordLowerCase = tempWord;
                for (int i = 0; i < tempWord.length(); ++i) {//convert to lowercase
                    tempWordLowerCase[i] = tolower(tempWordLowerCase[i]);
                }
                if (!dictionary.contains(tempWordLowerCase)) {//check if present again
                    incorrectWords.push_back(make_pair(Word(tempWord, count), spellCheck(tempWord)));
                }
            }
        }
    }
    input.close();
}

vector<string> SpellChecker::spellCheck(string word) {
    vector<string> permutations;
    //erase letter from each position
    for (int i = 0; i < word.length(); ++i) {
        string temp = word.substr(0, i) + word.substr(i + 1);
        if (dictionary.contains(temp)) {
            permutations.push_back(temp);
        }
    }
    //swap adjacent letters
    for (int i = 1; i < word.length(); ++i) {
        string temp = word;
        swap(temp[i - 1], temp[i]);
        if (dictionary.contains(temp)) {
            permutations.push_back(temp);
        }
    }
    //insert random letter in each position
    for (int i = 0; i < word.length() + 1; ++i) {
        for (char j = 'a'; j != 'z'; ++j) {
            string temp = word;
            temp = word.substr(0, i) + j + word.substr(i);
            if (dictionary.contains(temp)) {
                permutations.push_back(temp);
            }
        }
    }
    //replace random letter in each position
    for (int i = 0; i < word.length(); ++i) {
        for (char j = 'a'; j != 'z'; ++j) {
            string temp = word;
            temp[i] = j;
            if (dictionary.contains(temp)) {
                permutations.push_back(temp);
            }
        }
    }
    return permutations;
}

void SpellChecker::fillHashTable(int numWords, string dictionaryFilename) {
    dictionary = HashTable<string>(numWords * 2);
    string line;
    input.open(dictionaryFilename);
    while (input >> line) {
        dictionary.insert(line);
    }
    input.close();
}
void SpellChecker::writeCerr() {
    cerr << "Number of words: " << dictionary.getNumberOfObjectsInTable() << ", Table Size: " << dictionary.getArraySize() << ", Load Factor: " << setprecision(6) << dictionary.getLoadFactor() << endl;
    cerr << "Collisions: " << dictionary.getTotalCollisions() << ", Average Chain Length: " << setprecision(6) << dictionary.getCollisionLengthAverage() << ", Longest Chain Length: " << dictionary.getLongestCollision() << endl;
}
