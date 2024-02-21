#include "function.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

const int max_name_size = 20;
const int max_time_size = 5;

struct Time {
    int hour;
    int minutes;
};

struct Task{
    char name[max_name_size + 1];
    char time_start[max_time_size + 1];
    char duration[max_time_size + 1];
    
    Task() {}
    
    Task(string name, string time_start, string duration) {
        for (int i = 0; i < max_name_size; i++) this->name[i] = name[i];
        this->name[max_name_size] = '\0';
        for (int i = 0; i < max_time_size; i++) {
            this->time_start[i] = time_start[i];
            this->duration[i] = duration[i];
        }
        this->time_start[max_time_size] = '\0';
        this->duration[max_time_size] = '\0';
    }
};


string to_do_list(vector <string>  *times, vector <string>  *dur_list){
    string name;
    string line;
    vector<Task> tasks;
    FILE* file;
    vector <string> text;
    vector <string> times_st, dur_st;
    string task_name, time_start, duration = "0";
    bool isFirst = true;
    
//  вводимо імʼя файлу
    cout << "Enter input file: ";
    cin >> name;
    name = name + ".dat";
    
    file = fopen(name.c_str(), "w");
//    ofstream fout(name, ios::binary);
//    fout.open(name, ofstream::app);
    char new_line = 'y';
    while(new_line == 'y'){
        cout<<"Enter a name of task(maximum number of characters - 20): ";
        cin>>task_name;
        task_name = verifyName(task_name);
        
        cout<<"Enter an event start time in this format HH:MM: ";
        cin>>time_start;
        time_start = verifyTime(time_start, duration, times_st);
        times_st.push_back(time_start);
        
        cout<<"Enter a duration in this format HH:MM: ";
        cin>>duration;
        duration = verifyDuration(duration, time_start);
        dur_st.push_back(duration);
        
        Task task(task_name, time_start, duration);
        
        tasks.push_back(task);
        fwrite(&task, 1, sizeof(task), file);
        if(duration_normal(duration, time_start)){
            cout << "\nDo you want to continue input task?[y/n]: ";
            cin >> new_line;
        }
        else{
            new_line = 'n';
        }
    }
    for (int i = 0; i < tasks.size(); i++)
        {
            cout << tasks[i].name << endl;
//            fout.write((char*)&task, sizeof(Task));
        }

    fclose(file);
    *times = times_st;
    *dur_list = dur_st;
    return name;
}


string verifyName(string name){
    while (name.size()>20 || name.size()<1){
        cout << "Enter a name again: ";
        cin >> name;
    }
    return name;
}

string verifyTime(string time, string duration, vector <string> times){
    bool flag_hours = hours(time);
    bool flag_duration = dur(time, duration, times);

    while(time.size()!=5 || time[2]!=':' || flag_hours || flag_duration){
        cout << "Enter a time again: ";
        cin >> time;
    }
    return time;
}

string verifyDuration(string duration, string time){
    bool flag_hours = hours(duration);
    bool flag_dif = false;
    if(time_to_int(duration)+time_to_int(time) > 1440) flag_dif = true;
    while(duration.size()!=5 || duration[2]!=':' || flag_hours || flag_dif){
        cout << "Enter a duration again: ";
        cin >> duration;
    }
    return duration;
}

bool hours(string time){
    bool flag = true;
    string h, m;
    h = time.substr(0, 2);
    m = time.substr(3, 2);
    int number_h = atoi(h.c_str()), number_m = atoi(m.c_str());

    if(number_h>=0 || number_h<=23){
        if(number_m>=0 || number_m<=59){
            flag = false;
        }
    }
    return flag;
}

bool dur(string time, string duration, vector <string> times){
    bool flag = false;
    int number = time_to_int(time);
    if(time.size()!=0){
        if(times.size()!=0){
            int num_t = times.size()-1;
            int time_before = time_to_int(times[num_t]);
            int d = time_to_int(duration);
            if(time_before + d > number){
                flag = true;
            }
        }
    }
    return flag;
}

int time_to_int(string time){
    string h, m;
    h = time.substr(0, 2);
    m = time.substr(3, 2);
    int number = atoi(h.c_str())*60 + atoi(m.c_str());
    return number;
}

bool duration_normal(string duration, string time){
    bool flag = true;
    if(time_to_int(duration) + time_to_int(time) == 1440) flag = false;
    return flag;
}

void output(string name){//виводимо текст файлу
//    FILE* file;
    Task pack;

    ifstream fin;
    fin.open(name);
    cout<<"File "<<name<<": \n";
    string i;
//    while (getline(file, i)){
//        cout << i << endl;
//    }
//    file.close();
    while(fin.read((char*)&pack, sizeof(Task))){
        cout<< pack.name <<", "<< pack.time_start << ", " <<pack.duration<< ";";
        cout<<endl;
        
    }
    
    fin.close();
    cout<<endl;
}

vector <string> file_to_text(string name){
    // потік read_file (тільки для читання)
    ifstream read_file(name, ios::binary);
    vector <string> text;
    
    // поміщаємо текст з потоку у змінну text
    string i;
    while (getline(read_file,i))
    {
        text.push_back(i);
    }
    
    read_file.close();
    
    return text;
}

void next_event(vector <string> times, vector <string> text){
    int j;
    string time_list;
    time_t rawtime;
    int time_now;
    int dif, min = 1440;
    string m;
    struct tm * timeinfo;
    time( &rawtime );
    timeinfo = localtime ( &rawtime );
    int hour = timeinfo->tm_hour, minute = timeinfo->tm_min;
    if(hour>=10 && minute<10) cout<<"Time now: "<< hour << ":" << "0"<< minute <<endl;
    if(hour<10 && minute<10) cout<<"Time now: "<< "0" << hour << ":" << "0"<< minute <<endl;
    if(hour<10 && minute>=10) cout<<"Time now: "<< "0" << hour << ":" << minute <<endl;
    if(hour>=10 && minute>=10) cout<<"Time now: "<< hour << ":" << minute <<endl;
    time_now = hour * 60 + minute;
    for(int i = 0; i < times.size(); i++){
        time_list = times[i];
        dif = verifyDif(time_list, time_now);
        if(dif>0 && dif<min){
            j = i;
            min = dif;
        }
    }
    if(dif>0){
        cout<<"Next event: "<<text[j]<<endl<<endl;
        
    }
}

int verifyDif(string time_list, int time_now){
    int dif;
    int all_time;
    all_time = time_to_int(time_list);
    dif = all_time - time_now;
    return dif;
}

string free_time(vector <string> times, vector <string> durations){
    string s, i;
    FILE* free_file;
    int time_n, dur_n;
    string start, finish, free_dur;
    string name2;
    string line;
    bool isFirst = true;
    vector <string> free_text;
    cout<<"Enter output file: "; cin>>name2;//називаємо другий файл

    name2+=".dat";
    free_file = fopen(name2.c_str(), "w");
    ofstream out(name2, ios::binary);
    for(int i = 0; i < times.size(); i++){
        time_n = time_to_int(times[i]);
        dur_n = time_to_int(durations[i]);
        if(time_n + dur_n>=780){
            start = int_to_time(time_n + dur_n);
            if(i + 1 < times.size()){
                finish = times[i+1];
            }
            else finish = "23:59";
            free_dur = int_to_time(time_to_int(finish) - time_to_int(start));
            line = start + " - " + finish + ", " + "duration: " + free_dur + ";";
            free_text.push_back(line);
        }
    }
    for (int i = 0; i < free_text.size(); i++)
        {
            fwrite(<#const void *__ptr#>, <#size_t __size#>, <#size_t __nitems#>, <#FILE *__stream#>);
        }
    out.close();
    
    return name2;
        
}

string int_to_time(int num){
    string time;
    int h, m;
    h = num/60;
    m = num%60;
    if(h<10 && m<10) time ="0" + to_string(h) + ":" + "0" + to_string(m);
    if(m<10 && h>=10) time = to_string(h) + ":" + "0" + to_string(m);
    if(h<10 && m>=10) time = "0" + to_string(h) + ":" + to_string(m);
    if(h>=10 && m>=10) time = to_string(h) + ":" + to_string(m);
    return time;
}
       

