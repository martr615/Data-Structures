/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

bool isNotAlnum(char &c){
    return ispunct(c) && c != '\'';
}

void to_lower(char &c){
    c = tolower(c);
}

void clean_punct(string& s){
    for_each(s.begin(), s.end(), to_lower);
    s.erase(remove_if(s.begin(), s.end(), isNotAlnum), s.end());
}


/*******************************
* 2. Main function             *
********************************/


int main()
{
    MAP table;

    string name;
    string s = "";
    int aCounter = 0;
    int uniqueCounter = 0;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    ifstream textFile;
    name = "mesg1.txt";
    textFile.open(name);

    if(!textFile){
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }
    cout << "Loading the words from " << name << " ...\n\n";

    textFile >> s;
    clean_punct(s);
    ELEMENT e(s,1);
    table.insert(e);

    aCounter++;
    uniqueCounter++;

    //Läser in ord och läser in de i tabellen
    while (textFile >> s){
        clean_punct(s);
        if (!s.size()) continue;
        table[s].second++;  //Sätter in ordet

        if (table[s].second == 1){ //om ordet redans finns så + med ett.
                uniqueCounter++;
        }
        aCounter++;
    }

    textFile.close();

    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    cout << "TEST PHASE 1" << endl << endl;

    //ADD CODE
    cout << "Number of words in the file = " << aCounter << endl
         << "Number unique words in the file = " << uniqueCounter << endl;

    cout << endl << endl << endl
         << "Frequency table sorted alphabetically..." << endl << endl;

    BiIterator it = table.begin();

    cout << "  \tKEY" << "\tCOUNTER" << endl;
    cout << "==============================\n";

    for(; it != table.end(); it++){
        cout << setw(15) << it->first
             << setw(12) << it->second << endl;
    }


    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    cout<< endl << "TEST PHASE 3" << endl << endl;

    //ADD CODE
     vector<string> to_remove;
    BiIterator it_remove = table.begin();

    for( ; it_remove != table.end(); it_remove++){
        if(it_remove->second == 1){
            to_remove.push_back(it_remove->first);
        }
    }

    for(int i = 0; i < to_remove.size(); i++){

        table.remove(to_remove.at(i));  //varje ord i vektorn to_remove ska tas bort för de uppstår bara 1 gång i texten.
        aCounter--;
        uniqueCounter--;
    }

    cout << endl << "Number of words after remove: " << table.size();
    cout << endl << endl << endl
         << "Frequency table sorted alphabetically..." << endl << endl;

    BiIterator it_new = table.begin();

    cout << "  \tKEY" << "\tCOUNTER" << endl;
    cout << "==============================\n";

    for(; it_new != table.end(); it_new++){
        cout << setw(15) << it_new->first
             << setw(12) << it_new->second << endl;
    }

    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

    //ADD CODE
    cout<< endl << "TEST PHASE 4" << endl << endl;

    string w1, w2;

    //Check för fel input, om inte ordet finns och om det är fel ordning på orden.
    while(true){
        cout << "Enter a starting word: ";
        cin >> w1;
        if(table.find(w1) == table.end()){
            cout << "It does not exist." << endl;
            continue;
        }
        cout << endl << "Enter a end word: ";
        cin >> w2;
        if(table.find(w2) == table.end()){
            cout << "It does not exist." << endl;
            continue;
        }
        if(w1 < w2){            ////Loopen avslutas om det är korrekt input.
            break;
        }
        else{
            cout << "Enter the words in the correct order." << endl;
        }
    }

    cout << endl << endl << endl
         << "Frequency table in [" << w1 << "," << w2 << "]" << endl << endl;

    BiIterator interval = table.find(w2);

    cout << "  \tKEY" << "\tCOUNTER" << endl;
    cout << "==============================\n";
    for(; interval != --table.find(w1); --interval){
        cout << setw(15) << interval->first
             << setw(12) << interval->second << endl;
    }
    return 0;
}

