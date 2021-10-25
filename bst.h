#ifndef bst_h
#define bst_h

#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include <cmath>
#include "node.h"
#include "nosuchobject.h"

using namespace std;

template <typename T>
class BST{
    
public:
    
    BST();
    BST(const T & data);
    
    void insertItr(const T & data);

    void remove(const T & data);
    Node<T> * removeHelper(Node<T> * root, const T & data);
    Node<T> * findMin(Node<T> * root);
    
    void display() const;
    void helperPrint(Node<T> * root) const;
    
    int getCount();
    void setCount(const T &);
    
    void clear(Node<T> * root);
    ~BST();
    
private:
    
    Node<T> * root;
    int count;
    
};

template <typename T>
BST<T>::BST(){
    root = NULL;
    count = 0;
}

template <typename T>
BST<T>::BST(const T & data){
    root = new Node<T>(data);
    count = 0;
}

// Insert iterative approach
template <typename T>
void BST<T>::insertItr(const T & data){
    
    count++;
    if(root == NULL){
        root = new Node<T>(data);
    }
    else{
        Node<T> * node = root;
        count++;
        while(node != NULL){
            count++;
            if(data > node->getData() && node->getRightChild() != NULL){
                count++;
                node = node->getRightChild();
            }
            else if(data > node->getData() && node->getRightChild() == NULL){
                count+=2;
                node->setRightChild(new Node<T>(data));
                node = NULL;
            }
            else if(data < node->getData() && node->getLeftChild() != NULL){
                count+=3;
                node = node->getLeftChild();
            }
            else if(data < node->getData() && node->getLeftChild() == NULL){
                count+=4;
                node->setLeftChild(new Node<T>(data));
                node = NULL;
            }
        }
    }
}


template <typename T>
void BST<T>::display() const{
    
    helperPrint(root);

}

template <typename T>
void BST<T>::helperPrint(Node<T> * root) const{

    // Depth First Traversal: Preorder
    
    if ( root == NULL ){
        return;
    }
    
    /* For leaf nodes, the program should not print its null
     children (it should only print a null node if it’s a null
     child of a parent with one non-null child */
    
    // Print key and an open bracket when traversing down 1 depth to a child node
    cout << "[" << root->getData();
    helperPrint(root->getLeftChild());
    
    // Leaf node - print NULL if left child but no right child
    if((root->getLeftChild() != NULL) && (root->getRightChild() == NULL)){
        cout << "[]";
    }
    
    // Leaf node - print NULL if right child but no left child
    if((root->getRightChild() != NULL) && (root->getLeftChild() == NULL)){
        cout << "[]";
    }
    
    helperPrint(root->getRightChild());
    
    // Print a close bracket for each depth retreated
    cout << "]";
    
    
}

template <typename T>
Node<T> * BST<T>::findMin(Node<T> * root){
    
    count++;
    if(root == NULL){
        return NULL;
    }
    
    while(root->getLeftChild() != NULL){
        count++;
        root = root->getLeftChild();
    }
    return root;
}

template <typename T>
void BST<T>::remove(const T & data){
    
    removeHelper(root, data);
    
}

template <typename T>
Node<T> * BST<T>::removeHelper(Node<T> * root, const T & data){
    
    count++;
    if( root == NULL ){
        return root;
    }
    else if( data < root->getData()){
        count+=2;
        root->setLeftChild(removeHelper(root->getLeftChild(), data));
    }
    else if( data > root->getData()){
        count+=2;
        root->setRightChild(removeHelper(root->getRightChild(), data));
    }
    else{
        
        // Case 1: No child
        if(root->getLeftChild() == NULL && root->getRightChild() == NULL){
            count++;
            delete root;
            root = NULL;
        }
        // Case 2: One child (no left)
        else if(root->getLeftChild() == NULL){
            count+=2;
            Node<T> * temp = root;
            root = root->getRightChild();
            delete temp;
        }
        // Case 3: One child (no right)
        else if(root->getRightChild() == NULL){
            count+=3;
            Node<T> * temp = root;
            root = root->getLeftChild();
            delete temp;
        }
        // Case 4: Two children
        else{
            Node<T> * temp = findMin(root->getRightChild());
            root->setData(temp->getData());
            root->setRightChild(removeHelper(root->getRightChild(), temp->getData()));
        }
    }
    
    return root;
    
}

template <typename T>
int BST<T>::getCount(){
    return count;
}

template <typename T>
void BST<T>::setCount(const T & count){
    this->count = count;
}


template <typename T>
void BST<T>::clear(Node<T> * root){
    
    if(root == NULL){
        return;
    }
    
    clear(root->getLeftChild());
    clear(root->getRightChild());
    
    delete root;
    
}

template <typename T>
BST<T>::~BST<T>(){
    clear(root);
}

#endif /* bst_h */
