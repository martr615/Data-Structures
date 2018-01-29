/*
  Name: hashTable.h
  Author: Aida Nordman
  Course: TND004, Lab 1
  Description: template class to represent a set of elements of type T
               implementation uses a sorted doubly-linked list
*/

#include <iostream>
#include <new>
#include <cassert>

using namespace std;


/** \brief Template class to represent a Set of elements of type T
 *
 * Set is implemented as a sorted doubly linked list
 * \invariant Sets should not contain repetitions, i.e.
 * two objects with the same value cannot belong to a Set
 *
 * \param T is the type of the objects (elements) stored in the set
 * \note All Set operations have a linear complexity, in the worst case
 */

template<typename T>
class Set
{
    private:

        /** \brief Class Node
         *
         * This class represents an internal node of a doubly linked list storing objects of type T
         * \param T is the type of the object (element) stored in a Node
         * \note All members of class Node are public
         * but only class Set can access them, since Node is declared in the private part of class Set
         *
         */

        class Node
        {
            public:
           /** \brief Constructor
            *
            * \param nodeVal an object of type T whose copy will be stored in the Node
            * \param nextPtr a pointer to the next Node in the list
            * \param prevPtr a pointer to the previous Node in the list
            * \pre Type T should support the following operations:
            *  default constructor T(), operator<<, operator<=,
            *
            */
            //Constructor
           Node (T nodeVal = T(), Node* nextPtr = NULL, Node* prevPtr = NULL) //ändrade nullptr till NULL
            : value (nodeVal), next (nextPtr), prev(prevPtr)
            {  };

           //Data members
           T value;    /**< Object (element) stored in the Node */
           Node* next; /**< Pointer to the next Node */
           Node* prev; /**< Pointer to the previous Node */
        };


    public:

       /** \brief Default constructor
        *
        * Create an empty Set
        *
        */
        //Default constructor
       Set ();


       /** \brief Conversion constructor
        *
        * Convert an object val into a singleton {val}
        * \param val an object of type T
        *
        */
        //Conversion constructor
       Set (T val);


       /** \brief Constructor to create a Set from an array of objects
        *
        * Create a Set with (a copy of) all objects in array a
        * \param a sorted array of objects of type T
        * \param n number of objects in array a
        *
        */
        //Constructor to create a Set from a sorted array
       Set (T a[], int n);


       /** \brief Copy constructor
        *
        * Create a new Set as a copy of Set b
        * \param b Set to be copied
        * \note This function does not modify Set b in any way
        *
        */
        //Copy constructor
       Set (const Set& b);


       /** \brief Destructor
        *
        * Deallocate all memory (Nodes) allocated by the constructor
        *
        */
        //Destructor
       ~Set ();


       /** \brief Assignment operator
        *
        * Assigns new contents to the Set, replacing its current content
        * \param b Set to be copied into Set *this
        * \note This function does not modify Set b in any way
        * \return *this
        *
        */
        //Assignment operator
       const Set& operator=(const Set& b);


       /** \brief Test whether the Set is empty
        *
        * \note This function does not modify the Set in any way
        * \return true if the set is empty, otherwise false
        *
        */
        //Test whether a set is empty
       bool is_empty () const;


       /** \brief Count the number of objects stored in the Set
        *
        * \note This function does not modify the Set in any way
        * \return An int larger or equal to zero
        *
        */
        //Return number of elements in the set
       int cardinality() const;


       /** \brief Test whether an object belongs to the Set
        *
        * \param val an object of type T to be searched for
        * \note This function does not modify the Set in any way
        * \return true if val belongs to the set, otherwise false
        *
        */
        //Test set membership
       bool is_member (T val) const;


        /** \brief Remove all elements from the Set
        *
        * Transform the Set into an empty set
        * \return None
        *
        */
        //Make the set empty
       void clear();


       /** \brief Test whether *this is a subset of Set b
        *
        * a <= b iff every member of a is a member of b
        * \param b a Set
        * \note This function does not modify *this nor b in any way
        * \return true, if *this is a subset of b, otherwise false
        *
        */
        //Return true, if the set is a subset of b, otherwise false
        //a <= b iff every member of a is a member of b
       bool operator<=(const Set& b) const;


       /** \brief Test whether *this and b represent the same set
        *
        * a == b, iff a <= b but not b <= a
        * \param b a Set
        * \note This function does not modify *this nor b in any way
        * \return true, if *this stores the same elements as Set b, otherwise false
        *
        */
        //Return true, if the set is equal to set b
        //a == b, iff a <= b but not b <= a
       bool operator==(const Set& b) const;


       /** \brief Test whether *this is a strict subset of Set b
        *
        * a < b iff a <= b but not b <= a
        * \param b a Set
        * \note This function does not modify *this nor b in any way
        * \return true, if *this is a strict subset of b, otherwise false
        *
        */
        //Return true, if the set is a strict subset of S, otherwise false
        //a < b iff a <= b but not b <= a
       bool operator<(const Set& b) const;


    private:
       Node *head;  /**< Pointer to the dummy header Node */
       Node *tail;  /**< Pointer to the dummy tail Node */
       int counter; /**< Count number of elements in the Set */

       //Private member functions

       /** \brief Insert a new Node storing val before the Node pointed by p
        *
        * \param p pointer to a Node
        * \param val value to be inserted  before position p
        * \return *this
        *
        */
        //Insert a new Node storing val before the Node pointed by p
       Set& insert(Node *p, T val);


        /** \brief Remove the Node pointed by p
        *
        * \param p pointer to a Node
        * \return *this
        *
        */
        //Remove the Node pointed by p
       Set& erase(Node *p);


        /** \brief Initialize the Set to an empty Set
        *
        * \return None
        *
        */
        //Initialize the Set to an empty Set
        void init();


        /** \brief Display the Set to ostream os
        *
        * \note This function does not modify *this in any way
        * \return None
        *
        */
        //Display the Set to ostream os
        void print(ostream& os) const;


        /** \brief Set union of *this with Set S
        *
        * \param S a Set
        * \note This function does not modify *this nor S in any way
        * \return A new Set representing the union of *this with Set S
        *
        */
        //Return a new set with the elements in S1 or in S2 (without repeated elements)
        Set _union(const Set& S) const;


        /** \brief Set intersection of *this with Set S
        *
        * \param S a Set
        * \note This function does not modify *this nor S in any way
        * \return A new Set representing the intersection of *this with Set S
        *
        */
        //Return a new set with the elements in both sets S1 and S2
        Set _intersection(const Set& S) const;


        /** \brief Set difference of *this with Set S
        *
        * \param S a Set
        * \note This function does not modify *this nor S in any way
        * \return A new Set representing the difference of *this with Set S
        *
        */
        //Return a new set with the elements in set S1 that do not belong to set S2
        Set _difference(const Set& S) const;



       //overloaded operators: union, intersection, difference, operator<<


       /** \brief Overloaded operator<<
        *
        * \param os output stream
        * \param b Set to be displayed
        * \return parameter os
        *
        */
         friend ostream& operator<< (ostream& os, const Set<T>& b)
         {
             if (b.is_empty ())
                os << "Set is empty!" << endl;
             else
             {
                b.print(os); //call the private function Set<T>::print
             }

            return os;
         }


       /** \brief Overloaded operator+: to represent Set union S1+S2
        *
        * S1+S2 is the Set of elements in Set S1 or in Set S2 (without repeated elements)
        * \param S1 a Set
        * \param S2 a Set
        * \note This function does not modify S1 nor S2 in any way
        * \return A new Set representing the union of S1 with S2, S1+S2
        *
        */
        friend Set<T> operator+ (const Set<T>& S1, const Set<T>& S2)
        {
            return S1._union(S2); //call the private function Set<T>::_union
        };



       /** \brief Overloaded operator*: to represent Set intersection S1*S2
        *
        * S1*S2 is the Set of elements in both Sets S1 and set S2
        * \param S1 a Set
        * \param S2 a Set
        * \note This function does not modify S1 nor S2 in any way
        * \return A new Set representing the intersection of S1 with S2, S1*S2
        *
        */
        friend Set<T> operator* (const Set<T>& S1, const Set<T>& S2)
        {
            return S1._intersection(S2); //call the private function Set<T>::_intersection
        };


       /** \brief Overloaded operator-: to represent Set difference S1-S2
        *
        * S1-S2 is the Set of elements in Set S1 that do not belong to Set S2
        * \param S1 a Set
        * \param S2 a Set
        * \note This function does not modify S1 nor S2 in any way
        * \return A new Set representing the set difference S1-S2
        *
        */
        friend Set<T> operator- (const Set<T>& S1, const Set<T>& S2)
        {
           return S1._difference(S2); //call the private function Set<T>::_difference
        }


};


/*****************************************************
* Implementation of the member functions             *
******************************************************/

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//Default constructor
template<typename T>
Set<T>::Set ()
{
    init();
}


//conversion constructor
template<typename T>
Set<T>::Set (T n)
{
   //ADD CODE
   //Skapar lista
    init();
    //temp nod som är den andra noden.
    //Node *temp = head->next;
    //insert(temp,n);

    insert(tail, n);
}


//Constructor to create a Set from a sorted array
template<typename T>
Set<T>::Set (T a[], int n)
{
    //ADD CODE
    init();
    Node *temp = head->next;
    //gå igenom hela array
    for(int i = 0; i < n; i++){
        //insert(temp, a[i]); stod så innan
        insert(this->tail, a[i]);
    }
}


//Copy constructor
template<typename T>
Set<T>::Set (const Set& b)
{
    //ADD CODE
    init();
    Node *temp = b.head->next; //S1
    while(temp != b.tail){

        this->insert(this->tail, temp->value);
        temp = temp->next;
    }


}


//Destructor
template<typename T>
Set<T>::~Set ()
{
    //ADD CODE
    this->clear(); //cleara set

    //ta bort head och tail som du initierat.
    delete head; //kanske delete[] istället.
    delete tail;

}


//Assignment operator
template<typename T>
const Set<T>& Set<T>::operator=(const Set& b)
{
    //ADD CODE
    this->clear(); //tex S4 har värden redan som ska skrivas över. Därför cleara den.

    Node *temp = b.head->next;
    while(temp != b.tail){

        insert(this->tail, temp->value);
        temp = temp->next;
    }
    return *this;
}


//Test whether a set is empty
template<typename T>
bool Set<T>::is_empty () const
{
   //ADD CODE
   if(head->next == tail){
        return true;
   }
   return false; //delete this code
}


//Test set membership
template<typename T>
bool Set<T>::is_member (T val) const
{
   //ADD CODE

   //TÄNK PÅ O(n)
   Node *temp = head->next;
   while(temp != tail){
        if(temp->value == val){
            return true;
        }
        temp = temp->next;
   }
   return false; //delete this code
}


//Return number of elements in the set
template<typename T>
int Set<T>::cardinality() const
{
    //ADD CODE
    int counter = 0;

    Node *temp = this->head->next;
    while(temp != this->tail){
        counter++;
        temp = temp->next;
    }
    return counter;
}


//Make the set empty
template<typename T>
void Set<T>::clear()
{
    //ADD CODE
    Node *temp = this->head->next;

    while(temp != this->tail){
        temp = temp->next;
        erase(temp->prev);
    }

}

//Return true, if the set is a subset of b, otherwise false
//a <= b if every member of a is a member of b
template<typename T>
bool Set<T>::operator<=(const Set& b) const
{
    //ADD CODE
    //"S2 <= S3" betyder om s2 är subset av s3.
    //s2 = this, s3 = b.
    Node *thisTemp = this->head->next;
    Node *bTemp = b.head->next;

    while(thisTemp != this->tail || bTemp != b.tail){ //Tar hänsyn till olika längder på listorna.


        //hänsyn till längd
        if(thisTemp == this->tail){ //Om s2 nått sin tail, så break;.
            break;
        }
        if(bTemp == b.tail){
            return false; // Om det "undersökta subset:et" är större än huvudset:et, det är orimligt. //om s2 är större i size än s3 så är inget subset.
            //break;
        }


        if(thisTemp->value > bTemp->value ){
            bTemp = bTemp->next;
            continue;
        }
        else if(thisTemp->value < bTemp->value){
            return false; //Vet att värdet inte finns, kolla anteckn.
        }
        else if(thisTemp->value == bTemp->value){
            //Båda listorna går ett steg.
            thisTemp = thisTemp->next;
            bTemp = bTemp->next;

            continue;
        }
    }
    return true;
}


//Return true, if the set is equal to set b
//a == b, iff a <= b and b <= a
template<typename T>
bool Set<T>::operator==(const Set& b) const
{
    //ADD CODE
    Node *thisTemp = this->head->next;
    Node *bTemp = b.head->next;

    while(thisTemp != this->tail && bTemp != b.tail){

        if(thisTemp->value == bTemp->value){
            thisTemp = thisTemp->next;
            bTemp = bTemp->next;
            continue;
        }
        else{
            return false; //om ej samma värde
        }
    }
    //ifall listorna är olika långa.
    if(thisTemp == this->tail && bTemp == b.tail){
        return true;
    }
    else{
        return false;
    }
}


//Return true, if the set is a strict subset of S, otherwise false
//a == b, iff a <= b but not b <= a
template<typename T>
bool Set<T>::operator<(const Set& b) const
{
    //ADD CODE
    if(*this <= b && !(b <= *this)){
        return true;
    }
    return false;
}


/****************************************************
* Private member functions                          *
*****************************************************/

//Insert a new Node storing val before the Node pointed by p
template<typename T>
Set<T>& Set<T>::insert(Node *p, T val)
{
    //ADD CODE
    Node* newNode = new Node(val, p, p->prev);
    p->prev = p->prev->next = newNode;

    //return *this; //delete this code
}


//Delete the Node pointed by p
template<typename T>
Set<T>& Set<T>::erase(Node *p)
{
    //ADD CODE
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;

    //return *this; //delete this code
}

//Create an empty Set
template<typename T>
void Set<T>::init()
{
    //ADD CODE
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;

}


//Display all elements in the Set
template<typename T>
void Set<T>::print(ostream& os) const
{
    //ADD CODE
    Node *temp = head->next;

    //medans inte nått slutet av list.1
    while(temp != tail){
        cout << temp->value << " " ;
        temp = temp->next;
    }
}


//Set union
//Return a new set with the elements in S1 or in S2 (without repeated elements)
template<typename T>
Set<T> Set<T>::_union(const Set& b) const
{
    //ADD CODE
    //höger till vänster, 4 först. 4 är b, och s2 är this.
    Set<T> newSet{}; //skrivs med måsklamrar.

    //s1 är this, s2 är b.
    Node *thisTemp = this->head->next;
    Node *bTemp = b.head->next;

    while(thisTemp != this->tail || bTemp != b.tail){ //Tar hänsyn till olika längder på listorna.

        if(thisTemp == this->tail){ //Om nått slutet i ena, lägg resten av värdena från andra.
            while (bTemp != b.tail) {
                newSet.insert(newSet.tail, bTemp->value);
                bTemp = bTemp->next;
            }
            break;
        }
        else if(bTemp == b.tail){   //Samma som ovan men omvänt.
            while (thisTemp != this->tail){
                newSet.insert(newSet.tail, thisTemp->value);
                thisTemp = thisTemp->next;
            }
            break;
        }
        else if(thisTemp->value > bTemp->value ){   //Kollerna nedan, gör så att inga dubbletter uppstår.
            newSet.insert(newSet.tail, bTemp->value);
            bTemp = bTemp->next;
            continue;
        }
        else if(thisTemp->value < bTemp->value){
            newSet.insert(newSet.tail, thisTemp->value);
            thisTemp = thisTemp->next;
            continue;
        }
        else if(thisTemp->value == bTemp->value){
            thisTemp = thisTemp->next;
            continue;
        }
    }
    return newSet;
}


//Set intersection
//Return a new set with the elements in both sets S1 and S2
template<typename T>
Set<T> Set<T>::_intersection(const Set& b) const
{
    //ADD CODE
    Set<T> newSet{}; //skrivs med måsklamrar.

    //s1 är this, s2 är b.
    Node *thisTemp = this->head->next;
    Node *bTemp = b.head->next;

    while(thisTemp != this->tail && bTemp != b.tail){

        if(thisTemp->value == bTemp->value){            //Om samma, sätt in i nya Set.
            newSet.insert(newSet.tail, thisTemp->value);
            thisTemp = thisTemp->next;
            bTemp = bTemp->next;
        }
        else if(thisTemp->value > bTemp->value){    //Om s1 är större än s2, vandra vidare i  s2.
            bTemp = bTemp->next;
        }
        else{
            thisTemp = thisTemp->next;              //Om s2 större än s1, gå vidare i s1.
        }
    }

    return newSet;
}


//Set difference
//Return a new set with the elements in set S1 that do not belong to set S2
template<typename T>
Set<T> Set<T>::_difference(const Set& b) const
{
    //ADD CODE
    Set<T> newSet{}; //skrivs med måsklamrar.

    //s1 är this, s2 är b.
    Node *thisTemp = this->head;
    Node *bTemp = b.head;


    while(thisTemp->next != this->tail){

        if(bTemp->next == b.tail){   //Samma som ovan men omvänt.
            while (thisTemp->next != this->tail){
                newSet.insert(newSet.tail, thisTemp->next->value);
                thisTemp = thisTemp->next;
            }
            break;
        }

        if(thisTemp->next->value == bTemp->next->value){ //Om samma, gå bara vidare
            thisTemp = thisTemp->next;
            bTemp = bTemp->next;
        }
        else if(thisTemp->next->value > bTemp->next->value){ //om s1 är större gå vidare i s2.
            bTemp = bTemp->next;
        }
        else{ //om s1's värde är lägre än s2.
            newSet.insert(newSet.tail, thisTemp->next->value); //Set:en är sorterade, alltså finns inte siffran från s1 i s2.
            thisTemp = thisTemp->next;                   //Gå vidare i s1.
        }
    }
    return newSet;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

