#ifndef function_hpp
#define function_hpp
#include <string>
using namespace std;

string to_do_list(vector <string>*, vector <string>*);
string verifyName(string);
string verifyTime(string, string, vector <string>);
string verifyDuration(string, string);
bool hours(string);
bool dur(string, string, vector <string>);
bool duration_normal(string, string);
int time_to_int(string);
vector <string> file_to_text(string);
void next_event(vector <string>, vector <string>);
string free_time(vector <string>, vector <string>);
void output(string);
int verifyDif(string, int);
string int_to_time(int);

#endif
