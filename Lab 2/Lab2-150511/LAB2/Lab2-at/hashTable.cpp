#include <assert.h>
#include <iomanip>
#include <fstream>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{
    hTable = new Item*[size];

    //can be written as a clear function
    for (int i=0; i<size; i++)
    {
        hTable[i] = NULL;
    }
}


//destructor
// IMPLEMENT
HashTable::~HashTable() {
    delete hTable;
}


//Return the load factor of the table
double HashTable::loadFactor() const {
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const {

    //hash value
    int hashVal = h(key, size);

    while(hTable[hashVal] != NULL) {

        if(hTable[hashVal]->key == key) {
            return hTable[hashVal]->value;
        }
        hashVal = (hashVal + 1) % size;
    }

    return NOT_FOUND;
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v) {

    int hashVal = h(key, size); //get hash code

    nItems++; //note that list is expanded

    while(hTable[hashVal] != NULL && hTable[hashVal] != Deleted_Item::get_Item() ) {
        hashVal = (hashVal + 1) % size;
    }

    //new item
    hTable[hashVal] = new Item(key,v);

    //rehash if table to big
    if(loadFactor() > MAX_LOAD_FACTOR) {
        reHash();
    }
}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key) {

    int hashVal = h(key, size);

    while(hTable[hashVal] != NULL) {

        if(hTable[hashVal]->key == key) {

            this->hTable[hashVal] = Deleted_Item::get_Item();

            nItems--;
            return true;
        }
        hashVal = (hashVal + 1) % size;
    }

    return false;
}


void HashTable::display(ostream& os) {
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i) {
        os << setw(6) << i << ": ";

        if (!hTable[i]) {
            os << "null" << endl;
        } else {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }
    os << endl;
}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T) {

    //if table empty, break
    if (!T.hTable) return os;

    ofstream myfile;
    myfile.open("TestOut.txt");

    os << "Number of words in the file = " << T.totItems << endl;
    os << "Number of unique words in the file = " << T.nItems << endl;

    os << endl << "Frequency table ..." << endl << endl;

    myfile << "Number of words in the file = " << T.totItems << endl;
    myfile << "Number of unique words in the file = " << T.nItems << endl;

    myfile << endl << "Frequency table ..." << endl << endl;


    for (int i = 0, j = 0; i < T.size && j < T.nItems; ++i) {

        //only write item if it's NOT empty and NOT a deleted item
        if (T.hTable[i] && T.hTable[i] != Deleted_Item::get_Item()) {

            Item *temp = T.hTable[i];

            //write key and value
            os << left << setw(3) << j+1 << ": key = " << setw(15) << left << temp->key << "value = " << temp->value << endl;
            myfile << left << setw(3) << j+1 << ": key = " << setw(15) << left << temp->key << "value = " << temp->value << endl;

            ++j;
        }
    }
    myfile.close();
    return os;
}

//subscript operator
int &HashTable::operator[](string key) {

    pair<int, int> pos = findPosition(key);

    if (pos.first == NOT_FOUND) {

        Item *temp = new Item(key);

        tryInsert(temp, pos.second);

        //rehash if to much space used
        if (loadFactor() > MAX_LOAD_FACTOR)
            reHash();

        pos = findPosition(key);
    }

    return hTable[pos.first]->value;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash() {
    HashTable newTable(size*2, h);

    newTable.nItems = 0; //reset counter. It will get right number since we count when we insert

    //loop through old table and store items in new table
    for(int i=0; i<size; ++i) {
        Item* temp = hTable[i]; //temp variable

        if(temp != NULL) { //check that element isn't empty
            newTable.insert(temp->key, temp->value);
        }
    }

    //make the new table the "current" table
    delete [] hTable;
    hTable = newTable.hTable;

    size = newTable.size;
}

// private function to insert new item at "best" position
void HashTable::tryInsert(Item *i, int pos) {
    if (pos > size)
        tryInsert(i, 0);

    if (!hTable[pos] || hTable[pos] == Deleted_Item::get_Item()) {
        nItems++;
        hTable[pos] = i;
    } else {
        tryInsert(i, pos + 1);
    }
}

pair<int, int> HashTable::findPosition(string key) const {

    pair<int, int> response(NOT_FOUND, NOT_FOUND);
    bool flipped = false;

    for (int i = h(key, size); i < size; ++i) {

        if (!hTable[i]) {
            // position is empty, return not found
            response.second = i;
            break;
        }

        else if (hTable[i] == Deleted_Item::get_Item()) {
            // position holds a deleted item
            response.second = i;
        }

        else if (hTable[i] && hTable[i]->key == key) {
            // key found!
            response.first = response.second = i;
            break;
        }

        // are we at the end of our array? start from the beginning!
        if (i == size - 1 && !flipped) {
            i = -1;
            flipped = true;
        }
    }

    return response;
}
