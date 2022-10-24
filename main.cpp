# BilalCisProject

#include <iostream>
#include <string>
#include "QuadraticProbing.h"
#include "SpellChecker.h"
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
    SpellChecker spellcheck;
    spellcheck.fillHashTable(atoi(argv[1]), string(argv[2]));
    spellcheck.readFile(string(argv[3]));
    spellcheck.writeCorrections();
    spellcheck.writeCerr();
}
