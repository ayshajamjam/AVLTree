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
    
    int getCount();
    
    void clear(AVLTree<T> *);
    //~AVLTree(); // NEED TO CODE A DESTRUCTOR
    
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
    
    /*
     AVLNode<T> * newRoot = root->getLeftChild();
     root->setLeftChild(newRoot->getRightChild());
     newRoot->setRightChild(root);
     
     root = newRoot;
     
     return newRoot;*/
    
    AVLNode<T> * newRoot = root->getRightChild();
    root->setRightChild(newRoot->getLeftChild());
    newRoot->setLeftChild(root);
    
    root = newRoot;
    
    return newRoot;
    
}

// Insertion into right subtree of rightChild of the node
template <typename T>
AVLNode<T> * AVLTree<T>::leftRotate(AVLNode<T> * root){
    
    /*AVLNode<T> * newRoot = root->getRightChild();
     root->setRightChild(newRoot->getLeftChild());
     newRoot->setLeftChild(root);
     
     root = newRoot;
     
     return newRoot;*/
    
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
            if(data > node->getData() && node->getRightChild() != NULL){
                count++;
                node = node->getRightChild();
            }
            else if(data > node->getData() && node->getRightChild() == NULL){
                count += 2;
                node->setRightChild(new AVLNode<T>(data));
                node = NULL;
            }
            else if(data < node->getData() && node->getLeftChild() != NULL){
                count += 3;
                node = node->getLeftChild();
            }
            else if(data < node->getData() && node->getLeftChild() == NULL){
                count += 4;
                node->setLeftChild(new AVLNode<T>(data));
                node = NULL;
            }
        }
    }
    
    setBalanceFactor(root);
    root = balance(root);
    
}

template <typename T>
int AVLTree<T>::setBalanceFactor(AVLNode<T> * root){
    
    cout << "Here" << endl;
    
    if(root->getLeftChild() == NULL && root->getRightChild() == NULL){
        root->setBalanceFac(0);
        return 0;
    }
    else{
        int leftH = 0;
        int rightH = 0;
        
        if(root->getLeftChild() != NULL){
            cout << "Entered" << endl;
            leftH++;
            leftH += setBalanceFactor(root->getLeftChild());
        }
        if(root->getRightChild() != NULL){
            cout << "Shouldn't enter" << endl;
            rightH++;
            rightH += setBalanceFactor(root->getRightChild());
        }
        
        if(leftH >= rightH){
            cout << "ENTER" << endl;
            root->setBalanceFac(rightH - leftH);
            return leftH;
        }
        else{
            cout << "NO ENTER" << endl;
            root->setBalanceFac(rightH - leftH);
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
        else{
            if(abs(root->getBalanceFac()) <= 1){
                if(root->getLeftChild() != NULL){
                    root->setLeftChild(balance(root->getLeftChild()));
                } // if
                if(root->getRightChild() != NULL){
                    root->setRightChild(balance(root->getRightChild()));
                } // if
            } // if
            else{
                if(root->getBalanceFac() > 0){
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
                else{
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
        }
    }
    
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
        count++;
        root->setRightChild(removeHelper(root->getRightChild(), data));
    }
    
    // Found the node to be deleted
    else{
        // Case 1: No child
        if(root->getLeftChild() == NULL && root->getRightChild() == NULL){
            count++;
            delete root;
            root = NULL;
        }
        // Case 2: One child (no left)
        else if(root->getLeftChild() == NULL){
            count++;
            AVLNode<T> * temp = root;
            root = root->getRightChild();
            delete temp;
        }
        // Case 3: One child (no right)
        else if(root->getRightChild() == NULL){
            count++;
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
    
    cout << "Root: " << root->getData() << endl;
    
    return root;
}

template <typename T>
AVLNode<T> * AVLTree<T>::findMin(AVLNode<T> * root){
    
    count++;
    if(root == NULL){
        return NULL;
    }
    
    count++;
    while(root->getLeftChild() != NULL){
        count++;
        root = root->getLeftChild();
    }
    return root;
    
}


template <typename T>
void AVLTree<T>::display(){
    
    helperPrint(root);
    cout << endl;
    
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

/*
 template <typename T>
 void AVLTree<T>::clear(AVLTree<T> * root){
 
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
 */



string filename = argv[1];

string str = "";
int bstInsertCount;
int bstRemovalCount;
int avlInsertCount;
int avlRemovalCount;
int bstTotal;
int avlTotal;

// Open file

ifstream inputFile;
inputFile.open(filename.c_str());

if(!inputFile){
    cerr << "Unable to open file" << endl;
    }
    
    BST<int> bstTree;
    AVLTree<int> avlTree;
    
    int num;
    getline(inputFile, str);
    stringstream element(str);
    
    while(element >> num){
        bstTree.insertItr(num);
        avlTree.insertItr(num);
    }
    
    bstTree.display();
    cout << endl;
    bstInsertCount = bstTree.getCount();
    cout << "BST After Insertion Comparison Count: " << bstInsertCount << endl;
    cout << endl;
    
    avlTree.display();
    cout << endl;
    avlInsertCount = avlTree.getCount();
    cout << "AVL After Insertion Comparison Count: " << avlInsertCount << endl;
    cout << endl;
    
    char dollar;
    getline(inputFile, str);
    stringstream sep(str);
    
    sep >> dollar;
    
    int numToRemove;
    getline(inputFile, str);
    stringstream removeElement(str);
    
    bstTree.setCount(0);
    avlTree.setCount(0);
    
    avlTree.remove(5);
    
    
    
    while(removeElement >> numToRemove){
        bstTree.remove(numToRemove);
        avlTree.remove(numToRemove);
    }
    
    bstTree.display();
    cout << endl;
    bstRemovalCount = bstTree.getCount();
    cout << "BST After Removal Comparison Count: " << bstRemovalCount << endl;
    cout << endl;
    
    avlTree.display();
    cout << endl;
    avlRemovalCount = avlTree.getCount();
    cout << "AVL After Removal Comparison Count: " << avlRemovalCount << endl;
    cout << endl;
    
    bstTotal = bstInsertCount + bstRemovalCount;
    avlTotal = avlInsertCount + avlRemovalCount;
    
    cout << "BST Total Comparison Count: " << bstTotal << endl;
    cout << "AVL Total Comparison Count: " << avlTotal << endl;
    
    cout << endl;
    
    if(bstTotal > avlTotal){
        cout << "BST has greater comparison count" << endl;
    }
    else if(bstTotal < avlTotal){
        cout << "BST has greater comparison count" << endl;
    }
    else{
        cout << "BST and AVL have equal comparison count" << endl;
    }
    
    cout << endl;
    
    

#endif /* avltree_h */
