#include "UserInfo.h"
#include <iostream>
using namespace std;

UserInfo::UserInfo()
{
  Clear();
}

bool UserInfo::Empty() const
{
  return un.empty();
}

void UserInfo::Clear()
{
    un = "";
    pw = "";
    name = "";
    ismale = false;
    year = 0;
    month = 0;
    date = 0;
}

string UserInfo::KeyWord() const
{
  return un;
}

void UserInfo::ShowMsg() const
{
  cout << "name: " << name << endl
       << "sex: " << (ismale? "male": "female") << endl
       << "birthday: " << year << '-' << month
       << '-' << date << endl;
}

bool operator== (const UserInfo &u1, const UserInfo &u2)
{
  return u1.un == u2.un && u1.pw == u2.pw &&
         u1.name == u2.name && u1.ismale == u2.ismale
         && u1.year == u2.year && u1.month == u2.month
         && u1.date == u2.date;
}

bool operator< (const UserInfo &u1, const UserInfo &u2)
{
  return u1.un < u2.un;
}

ifstream& operator>> (ifstream &ifs, UserInfo &u)
{
  ifs >> u.un >> u.pw >> u.name >> u.ismale
      >> u.year >> u.month >> u.date;
  return ifs;
}

ofstream& operator<< (ofstream &ofs, const UserInfo &u)
{
  ofs << u.un << ' ' << u.pw << ' ' << u.name << ' '
      << (u.ismale? 1: 0) << ' ' << u.year 
      << ' '  << u.month << ' '  << u.date << endl;
  return ofs;
}

fstream& operator>> (fstream &ifs, UserInfo &u)
{
  ifs >> u.un >> u.pw >> u.name >> u.ismale
      >> u.year >> u.month >> u.date;
  return ifs;
}

fstream& operator<< (fstream &ofs, const UserInfo &u)
{
  ofs << u.un << ' ' << u.pw << ' ' << u.name << ' '
      << (u.ismale? 1: 0) << ' ' << u.year 
      << ' '  << u.month << ' '  << u.date << endl;
  return ofs;
}
