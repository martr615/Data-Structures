/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr) {
 }


//Dereferencing operator
ELEMENT& BiIterator::operator*() const {
    //ADD CODE
}


//Member access operator
ELEMENT* BiIterator::operator->() const {
    //ADD CODE

    //hur vet vi om man skickar first eller second?
    return &(current->value);

   // cout << "debug: operator ->" << endl;

}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const {

    if(this->current == it.current){
        return true;
    }
    return false;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const {

    return !(*this == it);
}


//Pre increment operator
BiIterator& BiIterator::operator++(){

    if(!current->r_thread){//if there is a right subtree...
        current = current->right->findMin();
    }  //find smallest value in that subtree
    else{
        current = current->right;
    } //go to right, which will be node after root

    return *this;
}

//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int) {
   //ADD CODE

    if(!current->r_thread){
        //find smallest node in the right subtree
        current = current->right->findMin();
    }
    else{
        current = current->right;
    }
    return *this;
}

//Pre decrement operator
BiIterator& BiIterator::operator--() {
   //ADD CODE
    if (!current->l_thread)
    current = current->left->findMax();
    else
    current = current->left;
    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int) {
   //ADD CODE
    if(!current->l_thread){
        //find smallest node in the right subtree
        current = current->left->findMax();
    }
    else{
        current = current->left;
    }
    return *this;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
