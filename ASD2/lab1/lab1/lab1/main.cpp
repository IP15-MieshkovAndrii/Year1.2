#include <iostream>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;

int* bubble_sort(int[], int);
int* comb_sort(int[], int);
void output(int[], int);

int main() {
    int size;
    
    cout << "n = ";
    cin >> size;

    int *arr = new int[size];
    int *bub = new int[size];
    int *comb = new int[size];

    srand(time(NULL));
    //1
//    for (int i = 0; i < size; i++) {
//        arr[i]=i+1;
//    }
    //2
//    for (int i = 0; i < size; i++) {
//        arr[i]=size-i;
//    }
    //3
    int k=0;
    int num = size;
    string name = "r" + to_string(num) + ".dat";
    ifstream in(name, ios::binary);

    while (!in.eof())
    {
        in >> arr[k];
        k++;
    }
    in.close();
    

//    output(arr, size);
    
    bub = bubble_sort(arr, size);
//    output(bub, size);
    
//    comb = comb_sort(arr, size);
//    output(comb, size);
 

    delete [] arr;
}

int* bubble_sort(int arr[], int size){
    int comparison=0, permutation=0;
    int temp;
    bool is;
    for (int i = 0; i < size - 1; i++) {
        is = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                is = true;
                permutation++;
            }
            comparison++;
        }
        if(!is) break;
    }
    cout<<"comparison: "<<comparison<<endl;
    cout<<"permutation: "<<permutation<<endl;
    return arr;
}


int* comb_sort(int arr[], int size){
    int temp;
    int comparison=0, permutation=0;
    double factor = 1.2473309;
    int step = size - 1;
    while (step >= 1){
        for (int i = 0; i + step < size; i++){
            if (arr[i] > arr[i + step]){
                temp = arr[i];
                arr[i] = arr[i + step];
                arr[i + step] = temp;
                permutation++;
            }
            comparison++;
        }
        step /= factor;
    }
    cout<<"comparison: "<<comparison<<endl;
    cout<<"permutation: "<<permutation<<endl;
    return arr;
}

void output(int arr[], int size){
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout<<endl<<endl;
}
