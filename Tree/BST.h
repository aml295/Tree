//
//  BST.h
//  BST
//
//  Created by Ahmed Latif on 2/11/17.
//  Copyright © 2017 Ahmed Latif. All rights reserved.
//

#ifndef BST_h
#define BST_h


#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>


using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::ifstream;



/****************************************************************************
 **                                                                        **
 **                   class Node<T> declaration                            **
 **                                                                        **
 ****************************************************************************/


template <typename T>
class Node {
public:
    //T obj
    T info;
    
    //BST head
    Node<T>* right;
    Node<T>* left;
    
    //constructor
    Node(T = T(), Node<T>* = NULL, Node<T>* = NULL);
};


/****************************************************************************
 **                                                                        **
 **                   class Node<T> implementation                         **
 **                                                                        **
 ****************************************************************************/


template <typename T>
Node<T>::Node(T templateObj, Node<T> *nodeLeftPtr, Node<T> *nodeRightPtr ) {
    info = templateObj;
    left = nodeLeftPtr;
    right = nodeRightPtr;
}


//redesign for nodes
/*
template <typename T>
class BST_iterator
{
    
private:
    Node<T> *current;
    //pointer to point to the current
    //node in the linked list
    
public:
    
    //default constructor
    BST_iterator();
    
    BST_iterator(Node<T> *ptr);
    
    //overloaded operator *
    T& operator*();
    
    //overloaded ++ operator
    BST_iterator operator++();
    //overloaded -- operator
    BST_iterator operator--();
    
    //overloaded equality operator
    bool operator==(const BST_iterator &rhsObj) const;
    
    //overloaded != operator
    bool operator!=(const BST_iterator &rhsObj) const;
    
    
    
}; //END class BST_iterator

*/





/****************************************************************************
 **                                                                        **
 **                       class BST<T> declaration                         **
 **                                                                        **
 ****************************************************************************/


template <typename Comparable>
class BST {
    
    template <typename F>
    friend ostream& operator<<(ostream& os, const BST<F> &rhsObj);
    
protected:
    
    //copyList is a private function called to ensure deep copy
    void copyList(const BST<Comparable> &listToCopy);
    
    //thing
    void Delete(Comparable key, Node<Comparable> *&node);
                //Node<Comparable> *&prevNode);
    
    void insert(Comparable, Node<Comparable>*& node);
    
    
    int find(Comparable key, Node<Comparable> *&node, int height = 0);

    Node<Comparable>* findPredOrSucc(Node<Comparable>*);
    
    //printing
    void printInOrder(Node<Comparable>*);
    void printPostOrder(Node<Comparable>*);
    void printPreOrder(Node<Comparable>*);
    
    //height
    int printHeight(Node<Comparable>*, int);

    
    //clear
    void clear(Node<Comparable>*&);
    
public:
    Node<Comparable> *root; // root is head pointer

    //constructor
    BST();
    
    //destructor
    ~BST(){clear(root);}
    
    
    //copy constructor
    BST(const BST<Comparable> &otherBST);
    
    //overloaded = operator
    BST<Comparable> operator=(const BST<Comparable> &rhsObj);
    
    //void push_back(T);
    
    //add to front of list
    //void addToFront(T);
    
    //void pop_back();
    //void pop_front();
    
    //insert
    void insert(Comparable key){ insert(key, root); }

    //find
    int find(Comparable key) { return find(key, root); }


    //delete
    void Delete(Comparable key){ Delete(key, root); }

    void loadFile(string);
    
    void clear(){clear(root);}
    
    //prining
    void printInOrder(){printInOrder(root);}
    void printPostOrder(){printPostOrder(root);}
    void printPreOrder(){printPreOrder(root);}
    
    //print height
    void printHeight(){cout << printHeight(root, 0) << endl;}
    
    
    //returns number of objects in the linked list
    unsigned long size() const;
    
    //member function at, same as at function of vector class
    //Comparable& at(int ndx) const;
    
    //BST_iterator<Comparable> begin() const {return BST_iterator<Comparable>(head->next);}
    // BST_iterator<Comparable> end() const {return BST_iterator<Comparable>(head->prev /*sentinal node*/ );}
    //BST_iterator<Comparable> header() const {return BST_iterator<Comparable>(head);}
    
}; //END of BST



/****************************************************************************
 **                                                                        **
 **                       class BST<T> IMPLEMENTATION                      **
 **                                                                        **
 ****************************************************************************/

//constructor
template <typename T>
BST<T>::BST(){
    root = nullptr;
    
    //cout << "Inside default constructor for class BST<Comparable>" << endl;
}

template <typename T>
void BST<T>::insert(T key, Node<T> *&node){
 
    if(node == nullptr)
    {
        node  = new Node<T>(key);
    }
    
    //if less than
    else if (key < node->info)
    {
        insert(key, node->left);
    }

    //if greater than
    else if(node->info < key)
    {
        insert(key, node->right);
    }

    //if equal do nothing
    else if (node->info == key) {
        cout << "Warning, duplicate value, ignoring" << endl;
    }
    //return;
}


template <typename T>
int BST<T>::find(T key, Node<T> *&node, int height){
    
    //if null do nothing
    if (node == nullptr)
    {
        return -1;
    }

    //if same
    else if(node->info == key)
    {
        return height;
    }
    
    //if less than
    else if (key < node->info)
    {
        height++;
        return find(key, node->left, height);
    }
    
    //if greater than
    else if(node->info < key)
    {
        height++;
        return find(key, node->right, height);
    }
    else
        return -1;
    
}



 /****** MAKE POINTER OF THING WANT TO DELETE == nullptr*/
 
template <typename T>
void BST<T>::Delete(T key, Node<T> *&node){
    //cout << "in delete funciton" << endl;
    
    //find the node you want to delete
    if (node == nullptr) {
        return;
    }
    else if (key < node->info)
    {
        Delete(key, node->left);
        return;
    }
    
    //if greater than
    else if(node->info < key)
    {
        Delete(key, node->right);
        return;
    }
    
    
    //***** delete the node *****
    
    //no children
    if( node->left == nullptr && node->right == nullptr )
    {
        if(node->info == key)
        {
            Node<T>* t = node;
            delete t;
            node = nullptr;
        }
        return;
    }
    
    
    //two children
    else if ( node->left != nullptr && node->right != nullptr )
    {
        //place holder for node to delete
        Node<T>* childToReplace = findPredOrSucc(node);
        
        Delete(childToReplace->info, root);
        node->info = childToReplace->info;

    }

    
    //one child
    else if ( node->left != nullptr || node->right != nullptr )
    {
        if(node->left == nullptr)
        {
            Node<T>* holder = node;
            delete holder;
            node = node->right;
            
        }
        else if (node->right == nullptr)
        {
            Node<T>* holder = node;
            delete holder;
            node = node->left;
        }
        
  
    }

}

template <typename T>
Node<T>* BST<T>::findPredOrSucc(Node<T>* node){
    if(node->left != nullptr)
    {
        node = node->left;
        
        while(node->right!=nullptr)
            node = node->right;
    
        return node;
        
    }
    
    else if(node->right != nullptr)
    {
        node = node->right;
        
        while(node->left!=nullptr)
            node = node->left;

        return node;
    }
    
    return nullptr;
}

//************* need to test
template <typename T>
void BST<T>::loadFile(string fileName){

    ifstream inputFile;
    
    inputFile.open(fileName.c_str());
    
    if(!inputFile)
    {
        cout << "\nThe file name you have entered is incorrect.\n";
        
    }
    else
    {
        cout << "regular implmentation of loadFile" << endl;
        while (inputFile)
        {
            T info;
            inputFile >> info;
            insert(info);
        }
    }

}

//************* need to test
template <>
void BST<string>::loadFile(string fileName){
    
    ifstream inputFile;
    
    inputFile.open(fileName.c_str());
    
    if(!inputFile)
    {
        cout << "\nThe file name you have entered is incorrect.\n";
        
    }
    else
    {
        cout << "string implmentation of loadFile" << endl;
        while (inputFile)
        {
            string info;
            inputFile >> info;
            //info = info.c_str();
            insert(info.c_str());
        }
    }
    
}

template <typename T>
void BST<T>::printInOrder(Node<T>* node){
    if(node!=nullptr){
        /*cout << "this node " << node->info << " points to ";
        if(node->left!=nullptr)
            cout << node->left->info;
        else cout << "null ";
        
        cout << " on the left and ";
        if(node->right!=nullptr)
            cout << node->right->info;
        else cout << "null ";*/
        //cout <<"on the right" << endl;
        
        printInOrder(node->left);
        cout << node->info << " ";
        printInOrder(node->right);
    }
}

template <typename T>
void BST<T>::printPostOrder(Node<T>*node){
    if(node!=nullptr){
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->info << " ";
    }

}

template <typename T>
void BST<T>::printPreOrder(Node<T>* node){
    if(node!=nullptr){
        cout <<node->info << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

}

template <typename T>
int BST<T>::printHeight(Node<T>* node, int height){
    
    if (node->right != nullptr && node->left != nullptr) {
        height++;
        int lhs = printHeight(node->left, height);
        
        int rhs = printHeight(node->right, height);
        if (lhs > rhs) height = lhs;
        else height = rhs;
    }
    else if (node->right != nullptr)
    {
        height++;
        height = printHeight(node->right, height);
    }
    else if (node->left != nullptr)
    {
        height++;
        height = printHeight(node->left, height);
    }
    else if (node == nullptr)
        return 0;

    return height;
}


template <typename T>
void BST<T>::clear(Node<T>*& node){
    /*if (node->right != nullptr && node->left != nullptr) {
        
    }
    else if (node->right != nullptr)
    {
        
    }
    else if (node->left != nullptr)
    {
            }
    else if (node == nullptr)
        return ;*/
    
    if(node!=nullptr){
        clear(node->left);
        clear(node->right);
        Node<T>* holder = node;
        delete holder;
        node = nullptr;
    }

    //printPreOrder(root); cout << endl;
    //if (root == nullptr) cout << "root is null" << endl;
}

#endif /* BST_h */
