#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "hashTable.h"

using namespace std;

//Hash function from the book.
unsigned my_hash(string s, int tableSize) {
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++) {
        hashVal += s[i];
    }
    hashVal %= tableSize;

    return hashVal;
}

//Kollar om det �r punkt eller "'" och returnerar bool enligt det.
bool is_ok_char(char &c) {
    return ispunct(c) && c != '\'';
}

//G�r till gemener.
void to_lower(char &c) {
    c = tolower(c);
}

void clean_punct(string& s) {
    for_each(s.begin(), s.end(), to_lower);                        //g�r till lower f�r orden.
    s.erase(remove_if(s.begin(), s.end(), is_ok_char), s.end());  //tar bort "'" och ".".
}


int main() {
    const int TABLE_SIZE = 7;
    HashTable table(TABLE_SIZE, my_hash);

    string filename = "test_file2.txt", word = "";

    ifstream readFile;
    readFile.open(filename);

    if(!readFile.is_open()){
        cout << "Could not read the file '" << filename << "'!";
        return -1;
    }

    table.totItems = 0;

    while (readFile >> word){
        clean_punct(word);

        //insert the word in the hash table
        table[word]++;

        //count words in file
        table.totItems ++;
    }

    cout << table;

    return 0;
}
