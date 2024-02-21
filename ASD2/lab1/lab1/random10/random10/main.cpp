#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int size=50000;
    int* arr = new int [size];
    string name = "r50000.dat";
    string as;
    ofstream out(name);
    int k=0;
    int a;
    string text="";
    bool num;

    while(k<size){
        num = false;
        a = rand()%size + 1;
        for(int j=0; j<k; j++){
            if(a == arr[j]){
                num = true;
            }
        }
        if(num == false){
            arr[k]=a;
            k++;
        }
    }
    for(int i=0; i<size; i++){
        out<<arr[i] << " ";
        
    }
    out.close();
    
}
