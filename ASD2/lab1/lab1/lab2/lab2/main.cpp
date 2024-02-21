#include <iostream>
#include <ctime>
#include "function.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    vector <string> times, dur_list;
    
    string name_in = to_do_list(&times, &dur_list);//створення вихідного файлу
    cout<<endl;
    output(name_in);//вивід вихідного файлу
    
    vector <string> text = file_to_text(name_in);
    
    next_event(times, text);
    
    string name_out = free_time(times, dur_list);//переписання вихідного файлу
    output(name_out);//вивід створеного файлу
    cout<<endl;
    cin.get();
    

}
