#include "RBtree.h"
#include <iostream>

using namespace std;

int main(){
    
    int ch,y=0;
    RBtree obj;
    int const SIZE = 6;
    int arr[SIZE] = {30,28,21,11,17,4};
    
    for(int i = 0; i < SIZE; i++){
        obj.insert(arr[i]);
    }
    
    return 0;
}