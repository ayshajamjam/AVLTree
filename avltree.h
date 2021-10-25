#ifndef avltree_h
#define avltree_h

#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include <cmath>
#include "avlnode.h"
#include "nosuchobject.h"

using namespace std;

template <typename T>
class AVLTree{
    
public:
    
    AVLTree();
    AVLTree(const T &);
    
    // Single Rotations
    AVLNode<T> * rightRotate(AVLNode<T> * );
    AVLNode<T> * leftRotate(AVLNode<T> * );
    
    // Double Rotations
    AVLNode<T> * doubleLeftRotate(AVLNode<T> * );
    AVLNode<T> * doubleRightRotate(AVLNode<T> * );
    
    void insertItr(const T & data);
    int setBalanceFactor(AVLNode<T> *);
    AVLNode<T> * balance(AVLNode<T> *);
    
    void remove(const T & data);
    AVLNode<T> * removeHelper(AVLNode<T> *, const T &);
    AVLNode<T> * findMin(AVLNode<T> *);
    
    void display() ;
    void helperPrint(AVLNode<T> *) const;
    void printData(AVLNode<T> * root);
    
    int getCount();
    void setCount(const T &);
    
    void clear(AVLNode<T> *);
    ~AVLTree();
    
private:
    
    AVLNode<T> * root;
    int count;
    
};

template <typename T>
AVLTree<T>::AVLTree(){
    root = NULL;
    count = 0;
}

// Insertion into left subtree of leftChild of the node
template <typename T>
AVLNode<T> * AVLTree<T>::rightRotate(AVLNode<T> * root){
    
    AVLNode<T> * newRoot = root->getRightChild();
    root->setRightChild(newRoot->getLeftChild());
    newRoot->setLeftChild(root);
    
    root = newRoot;
    
    return newRoot;
    
}

// Insertion into right subtree of rightChild of the node
template <typename T>
AVLNode<T> * AVLTree<T>::leftRotate(AVLNode<T> * root){
    
    AVLNode<T> * newRoot = root->getLeftChild();
    root->setLeftChild(newRoot->getRightChild());
    newRoot->setRightChild(root);
    
    root = newRoot;
    
    return newRoot;
    
}

template <typename T>
AVLNode<T> * AVLTree<T>::doubleLeftRotate(AVLNode<T> * root){
    
    root->setLeftChild(rightRotate(root->getLeftChild()));
    return leftRotate(root);
    
}

template <typename T>
AVLNode<T> * AVLTree<T>::doubleRightRotate(AVLNode<T> * root){
    
    root->setRightChild(leftRotate(root->getRightChild()));
    return rightRotate(root);
    
}

template <typename T>
void AVLTree<T>::insertItr(const T & data){

    count++;
    if(root == NULL){
        root = new AVLNode<T>(data);
    }
    else{
        AVLNode<T> * node = root;
        count++;
        while(node != NULL){
            count++;
            if(data > node->getData() && node->getRightChild() != NULL){
                count++;
                node = node->getRightChild();
            }
            else if(data > node->getData() && node->getRightChild() == NULL){
                count+=2;
                node->setRightChild(new AVLNode<T>(data));
                node = NULL;
            }
            else if(data < node->getData() && node->getLeftChild() != NULL){
                count+=3;
                node = node->getLeftChild();
            }
            else if(data < node->getData() && node->getLeftChild() == NULL){
                count+=4;
                node->setLeftChild(new AVLNode<T>(data));
                node = NULL;
            }
        }
    }
    
    setBalanceFactor(root);
    root = balance(root);
    
}

template <typename T>
int AVLTree<T>::setBalanceFactor(AVLNode<T> * node){
    
    if(root->getLeftChild() == NULL && root->getRightChild() == NULL){
        node->setBalanceFac(0);
        return 0;
    }
    else{
        int leftH = 0;
        int rightH = 0;
        
        if(node->getLeftChild() != NULL){
            leftH++;
            leftH += setBalanceFactor(node->getLeftChild());
        }
        if(node->getRightChild() != NULL){
            rightH++;
            rightH += setBalanceFactor(node->getRightChild());
        }
        if(leftH >= rightH){
            node->setBalanceFac(rightH - leftH);
            return leftH;
        }
        else{
            node->setBalanceFac(rightH - leftH);
            return rightH;
        }
    }
}

template <typename T>
AVLNode<T> * AVLTree<T>::balance(AVLNode<T> * root){
    
    if(root == NULL){
        return NULL;
    } // if
    else{
        if(root->getLeftChild() == NULL && root->getRightChild() == NULL){
            return root;
        } // if
        
        
        if(root->getLeftChild() != NULL){
            root->setLeftChild(balance(root->getLeftChild()));
        } // if
        if(root->getRightChild() != NULL){
            root->setRightChild(balance(root->getRightChild()));
        } // if
        
            if(root->getBalanceFac() >= 2){
                if(root->getRightChild()->getBalanceFac() >= 0){
                    AVLNode<T> * temp = rightRotate(root);
                    setBalanceFactor(temp);
                    return temp;
                } // if
                else{
                    AVLNode<T> * temp = doubleRightRotate(root);
                    setBalanceFactor(temp);
                    return temp;
                } // else
            } // if
            if(root->getBalanceFac() <= -2){
                if(root->getLeftChild()->getBalanceFac() <= 0){
                    AVLNode<T> * temp = leftRotate(root);
                    setBalanceFactor(temp);
                    return temp;
                }
                else{
                    AVLNode<T> * temp = doubleLeftRotate(root);
                    setBalanceFactor(temp);
                    return temp;
                }
            }
    }

    if(root->getLeftChild() != NULL){
        root->setLeftChild(balance(root->getLeftChild()));
    } // if
    if(root->getRightChild() != NULL){
        root->setRightChild(balance(root->getRightChild()));
    } // if
    
    return root;
    
}

template <typename T>
void AVLTree<T>::remove(const T & data){
    removeHelper(root, data);
}

template <typename T>
AVLNode<T> * AVLTree<T>::removeHelper(AVLNode<T> * root, const T & data){
    
    count++;
    
    if(root == NULL){
        return root;
    }
    
    // Node to be deleted is in left subtree
    if( data < root->getData() ){
        count++;
        root->setLeftChild(removeHelper(root->getLeftChild(), data));
    }
    // Node to be deleted is in the right subtree
    else if(data > root->getData()){
        count+=2;
        root->setRightChild(removeHelper(root->getRightChild(), data));
    }
    // Found the node to be deleted
    else{
        // Case 1: No child
        if(root->getLeftChild() == NULL && root->getRightChild() == NULL){
            count++;
            delete root;
            return NULL;
        }
        // Case 2: One child (no left)
        else if(root->getLeftChild() == NULL){
            count+=2;
            AVLNode<T> * temp = root;
            root = root->getRightChild();
            delete temp;
        }
        // Case 3: One child (no right)
        else if(root->getRightChild() == NULL){
            count+=3;
            AVLNode<T> * temp = root;
            root = root->getLeftChild();
            delete temp;
        }
        // Case 4: Two children
        else{
            AVLNode<T> * temp = findMin(root->getRightChild());
            root->setData(temp->getData());
            root->setRightChild(removeHelper(root->getRightChild(), temp->getData()));
        }
    
    }
    
    setBalanceFactor(root);
    root = balance(root);
    
    return root;
}

template <typename T>
AVLNode<T> * AVLTree<T>::findMin(AVLNode<T> * root){
    
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
void AVLTree<T>::display(){
//    printData(root);
    
    helperPrint(root);
    
}

template <typename T>
void AVLTree<T>::printData(AVLNode<T> * root) {
    if (root != NULL) {
        cout << "Data: " << root->getData() << endl;
        cout << "BF: " << root->getBalanceFac() << endl;
        printData(root->getLeftChild());
        printData(root->getRightChild());
    }
}

template <typename T>
void AVLTree<T>::helperPrint(AVLNode<T> * root) const{
    
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
    
    //return;
    
}

template <typename T>
int AVLTree<T>::getCount(){
    return count;
}

template <typename T>
void AVLTree<T>::setCount(const T & count){
    this->count = count;
}


template <typename T>
void AVLTree<T>::clear(AVLNode<T> * root){
 
     if(root == NULL){
         return;
     }
    
    clear(root->getLeftChild());
    clear(root->getRightChild());
     
    delete root;
 
 }
 
template <typename T>
AVLTree<T>::~AVLTree<T>(){
    clear(root);
}


#endif /* avltree_h */
