#ifndef avlnode_h
#define avlnode_h

using namespace std;

template <typename T>
class AVLNode
{
    
public:
    
    AVLNode( const T & = T());
    
    void setData( const T & );
    T & getData();
    
    void setLeftChild( AVLNode<T> * );
    AVLNode<T> * getLeftChild() const;
    
    void setRightChild( AVLNode<T> * );
    AVLNode<T> * getRightChild() const;
    
    void setBalanceFac( const T & );
    int & getBalanceFac();
 
private:
    
    T data;
    AVLNode * leftChild;
    AVLNode * rightChild;
    int balanceFac;
    
};

template <typename T>
AVLNode<T>::AVLNode( const T & data ){
    
    this->data = data;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->balanceFac = 0; // new nodes are added as leaves
    
}

template <typename T>
void AVLNode<T>::setData( const T & data ){
    this->data = data;
}

template <typename T>
T & AVLNode<T>::getData(){
    return data;
}

template <typename T>
void AVLNode<T>::setLeftChild( AVLNode<T> * leftChild ){
    this->leftChild = leftChild;
}

template <typename T>
AVLNode<T> * AVLNode<T>::getLeftChild() const{
    return leftChild;
}

template <typename T>
void AVLNode<T>::setRightChild( AVLNode<T> * rightChild ){
    this->rightChild = rightChild;
}

template <typename T>
AVLNode<T> * AVLNode<T>::getRightChild() const{
    return rightChild;
}

template <typename T>
void AVLNode<T>::setBalanceFac( const T & balanceFac ){
    this->balanceFac = balanceFac;
}

template <typename T>
int & AVLNode<T>::getBalanceFac(){
    return balanceFac;
}

#endif /* avlnode_h */
