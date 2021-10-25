#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "main.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    try{
        
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
            cout << "AVL has greater comparison count" << endl;
        }
        else{
            cout << "BST and AVL have equal comparison count" << endl;
        }
        
        cout << endl;
        
    } // try
    
    catch ( NoSuchObject& e ){
        cout << e.what() << endl;
    }
    catch ( invalid_argument& e ){
        cout << "Invalid argument: " << e.what() << endl;
    } // catch
    catch ( logic_error& e ){
        cout << "Logic error: " << e.what() << endl;
    } // catch
    catch ( bad_alloc& e){
        cout << "Bad alloc: " << e.what() << endl;
    }
    catch (...){
        cout << "Unkown exception!" << endl;
    } // catch
    
    return 0;
    
}
