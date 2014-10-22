#ifndef USERINFO_H
#define USERINFO_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

struct UserInfo
{
  string un;
  string pw;
  string name;
  bool ismale;
  int year;
  int month;
  int date;

  UserInfo();

  bool Empty() const;
  void Clear();
  void ShowMsg() const;
  string KeyWord() const;
};

bool operator== (const UserInfo &u1, const UserInfo &u2);
bool operator< (const UserInfo &u1, const UserInfo &u2);

ifstream& operator>> (ifstream &ifs, UserInfo &u);
ofstream& operator<< (ofstream &ofs, const UserInfo &u);

fstream& operator>> (fstream &ifs, UserInfo &u);
fstream& operator<< (fstream &ofs, const UserInfo &u);

#endif //USERINFO_H
