#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <time.h>
using std::string;

int skipblank(const string &str, int index);

bool parseint(const string &str, int &index, int &res);
bool parseletter(const string &str, int &index, string &res);
bool parsevar(const string &str, int &index, string &res);

string stolower(const string &str);

bool isint(const string &str);

int ComputeHash(const string &str);

bool valid_un(const string &un);
bool valid_num(const string &str);

string UnixTimeToLocal(time_t tick);

#endif //UTILITY_H
