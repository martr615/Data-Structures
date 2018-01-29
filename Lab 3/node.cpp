/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    if(!l_thread){
        delete left;
    }
    if(!r_thread){
        delete right;
    }
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    Node *temp = this;// this är positionen vi är på, root->left

    while(true){
        //insert new node to the LEFT
        if(v.first < temp->value.first && temp->l_thread){
            Node* newNode = new Node(v, temp->left, temp);
            newNode->l_thread = newNode->r_thread = true;
            temp->left = newNode;
            temp->l_thread = false; //vi gör left thread false på nuvarande nod som vi är på
            return true;
        }
        //insert new node to the RIGHT
        else if(v.first > temp->value.first && temp->r_thread){
            Node* newNode = new Node(v, temp, temp->right);
            newNode->l_thread = newNode->r_thread = true;
            temp->right = newNode;
            temp->r_thread = false;
            return true;
        }
        //if keys are equal, add to the counter and abort
        else if(v.first == temp->value.first){
            temp->value.second++; //ska man göra såhär?
            return false;
        }
        //if key is smaller and pointer is NOT a thread, go to next left
        else if(v.first < temp->value.first && !temp->l_thread){
            temp = temp->left;
        }
        //if key is larger and pointer is NOT a thread, go to next left
        else if(v.first > temp->value.first && !temp->r_thread){
            temp = temp->right;
        }
    }
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight) {

    //ADD CODE
    //Kolla om noden finns
        if(key < value.first){
            if(l_thread){     //Key finns inte i BST.
                return false;
            }
            else{//Rekursivt, gå till nästa åt vänster.
                return this->left->remove(key, this, false); //kanske ta bort this
            }
        }
        else if(key > value.first){
            if(r_thread){
                return false;
            }
            else{
                return this->right->remove(key, this, true);
            }
        }
        else if(!l_thread && !r_thread){ //har två child
            //Ersätt det här värdet med det minsta value.
            value = right->findMin()->value;
            return this->right->remove(value.first, this, true);
        }
        else if(key == value.first){
            this->removeMe(parent, isRight);
            return true;
        }
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight) {

    //1a: a left child with only a right child
    if(!isRight && l_thread==true && r_thread==false){
        this->right->findMin()->left = this->left; //redirect threaded pointer
        parent->left = this->right; //redirect pointers
    }
    //1b: a left child with only a left child
    else if(!isRight && l_thread==false && r_thread==true){
        this->left->findMax()->right = this->right;
        parent->left = this->left;
    }
    //1c: a left child with no children
    else if(!isRight && l_thread==true && r_thread==true){
        parent->l_thread = true;
        parent->left = this->left;
    }
    //2a: a right child with only a right child
    else if(isRight && l_thread==true && r_thread==false){
        this->right->findMin()->left = this->left;
        parent->right = this->right;
    }
    //2b: a right child with only a left child
    else if(isRight && l_thread==false && r_thread==true){
        this->left->findMax()->right = this->right;
        parent->right = this->left;
    }
    //2c: a right child with no children
    else if (isRight && l_thread==true && r_thread==true){
        parent->r_thread = true;
        parent->right = this->right;
    }
    l_thread = r_thread = true;
    delete this;
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key) {

    Node *temp = this;

    while(true){
        //if key is lower, but reached end of tree, return null
        if(key < temp->value.first && temp->l_thread){
            return nullptr;
        }
        //if key is higher, but reached end of tree, return null
        else if(key > temp->value.first && temp->r_thread){
            return nullptr;
        }
        //if key is lower, and left is NOT a thread, go left
        else if(key < temp->value.first && !temp->l_thread){
            temp = temp->left;
        }
        //if key is higher, and right is NOT a thread, go right
        else if(key > temp->value.first && !temp->r_thread){
            temp = temp->right;
        }
        //if key is found, return pointer to node "temp"
        else if(key == temp->value.first){
            return temp;
        }
    }
    return nullptr;
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin() {

    Node *temp = this;

    if(!temp){
        return nullptr;
    }
    //Längst ut till vänster
    while(!temp->l_thread){
        temp = temp->left;
    }
    return temp;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax() {

    Node *temp = this;

    if(!temp){
        return nullptr;
    }
    //Längst ut till höger
    while(!temp->r_thread){
        temp = temp->right;
    }

    return temp;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const {

    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
