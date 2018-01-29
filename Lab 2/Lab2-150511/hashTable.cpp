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
    //table is an array of pointers to Items
    hTable = new Item*[table_size];
    //Skapa table som pekar på null
    for(int i = 0; i < table_size; i++){
        hTable[i] = nullptr;
    }
}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    for(int i = 0; i < size; i++){
        if(hTable[i] != Deleted_Item::get_Item()){
            delete hTable[i];
        }
    }
    delete[] hTable;
}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{
    int hashVal = h(key, size); //beräknar ett index med modulusgrejen.
    int counter = 0;

    while(hTable[hashVal] != NULL && counter < size){                 //Vi startar på indexet ordet borde vara på.
        if(hTable[hashVal]->key == key){            //Går vidare i while:n för ibland finns kluster.
            return hTable[hashVal]->value;          //While:n tar slut när vi nått slutet i klustret och det är NULL där.
        }
        hashVal = (hashVal + 1) % size;             //itererar
        counter++;
    }
    return NOT_FOUND;
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{
    int hashVal = h(key, size); //index

    //hTable slot får inte vara tom/null, och inte samma värde på key.
    while(hTable[hashVal] != NULL && hTable[hashVal] != Deleted_Item::get_Item()){
        hashVal = (hashVal + 1) % size; //Ändra nåt för att få koll på hur långt vi går, ej längre än size
    //If key already exists in the table then change the associated value to v
        if(hTable[hashVal]->key == key){
            hTable[hashVal]->value = v;
            return;
        }
    }
    //lägger in ordet och value;
    hTable[hashVal] = new Item(key, v); //insert
    nItems++;


    //Re-hash if the table becomes 50% full
    if( loadFactor() > MAX_LOAD_FACTOR){
        cout << "Rehashing..." << endl;
        reHash();
    }
}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    //Remove Item with key
    int hashVal = h(key, size);
    int counter = 0;

    while(hTable[hashVal] != NULL && counter < size){
        if(hTable[hashVal]->key == key){
            //Tar bort value och key.
            delete this->hTable[hashVal];
            this->hTable[hashVal] = Deleted_Item::get_Item();

            nItems--;
            return true;
        }
        hashVal = (hashVal + 1) % size;             //itererar
        counter++;
    }
    return false;

}


void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;
}

//---------------------------------------Ny Kod-------------------------------------------//
//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
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


    for (int i = 0, j = 0; i < T.size && j < T.nItems; ++i){
        //Skriv bara om item inte är empty och inte ett deleted item.
        if (T.hTable[i] && T.hTable[i] != Deleted_Item::get_Item()){
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


//Subscript operator
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


//----------------------------------------------------------------------------------------//

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
    Item** tempTable = hTable;          //newTable pekar på gamla table.
    int tempSize = size;
    size = nextPrime(size*2);           //Behövs för size ändras inte i insert-funktionen.
    hTable = new Item*[size];           //hTable skrivs nu över och är det dubbelt så stora & tomma tabell.

    cout << "The new size is " << size << "." << endl;

    for(int i = 0; i < size; i++){      //Gör hTable tom.
        hTable[i] = nullptr;
    }
                                        //hTable = tom, tempTable = gamla tabell med värden.
                                        //Överföra värdena
    nItems = 0;                         //för att insert funktionen plussar på nItems, vi vill förhindrar att det plussar på första omgången.

    for(int i = 0; i < tempSize; i++){
        if(tempTable[i] != nullptr && tempTable[i] != Deleted_Item::get_Item()){
            insert(tempTable[i]->key, tempTable[i]->value); // fel för när vi hamnar på nullptr slots så försöker den tilldela värden som inte finns där.
        }
    }

    for(int i = 0; i < tempSize; i++){
        if(tempTable[i] != Deleted_Item::get_Item()){
            delete tempTable[i];
        }
    }
    delete[] tempTable;
}

pair<int, int> HashTable::findPosition(string key) const {

    pair<int, int> response(NOT_FOUND, NOT_FOUND);
    bool flipped = false;

    for (int i = h(key, size); i < size; ++i) {

        if (!hTable[i]){
            // position is empty, return not found
            response.second = i;
            break;
        }
        else if (hTable[i] == Deleted_Item::get_Item()){
            // position holds a deleted item
            response.second = i;
        }
        else if (hTable[i] && hTable[i]->key == key){
            // key found!
            response.first = response.second = i;
            break;
        }

        // are we at the end of our array? start from the beginning!
        if (i == size - 1 && !flipped){
            i = -1;
            flipped = true;
        }
    }
    return response;
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

