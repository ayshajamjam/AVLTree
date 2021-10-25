#ifndef NODE_H
#define NODE_H

using namespace std;

template <typename T>
class Node
{
    
public:
    Node( const T & = T());
    
    void setData( const T & );
    T & getData();
    
    void setLeftChild( Node<T> * );
    Node<T> * getLeftChild() const;
    
    void setRightChild( Node<T> * );
    Node<T> * getRightChild() const;
    
private:
    
    T data;
    Node * leftChild;
    Node * rightChild;
    
};

template <typename T>
Node<T>::Node( const T & data ){

    this->data = data;
    this->leftChild = NULL;
    this->rightChild = NULL;
    
}

template <typename T>
void Node<T>::setData( const T & data ){
    this->data = data;
}

template <typename T>
T & Node<T>::getData(){
    return data;
}

template <typename T>
void Node<T>::setLeftChild( Node<T> * leftChild ){
    this->leftChild = leftChild;
}

template <typename T>
Node<T> * Node<T>::getLeftChild() const{
    return leftChild;
}

template <typename T>
void Node<T>::setRightChild( Node<T> * rightChild ){
    this->rightChild = rightChild;
}

template <typename T>
Node<T> * Node<T>::getRightChild() const{
    return rightChild;
}

#endif
