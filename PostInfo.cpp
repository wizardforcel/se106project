#include "PostInfo.h"
#include "Utility.h"
#include <iostream>
#include <time.h>
using namespace std;

//#define _DEBUG

PostInfo::PostInfo()
{
  ptime = time(0);
}

string PostInfo::KeyWord() const
{
  return un;
}


void PostInfo::ShowMsg() const
{
  cout << un << ": " << content
       << " " << UnixTimeToLocal(ptime) << endl;
}

bool operator== (const PostInfo &p1, const PostInfo &p2)
{
  return p1.un == p2.un && p1.content == p2.content &&
         p1.ptime == p2.ptime;
}

bool operator< (const PostInfo &p1, const PostInfo &p2)
{
  return p1.ptime < p2.ptime;
}

ifstream& operator>> (ifstream &ifs, PostInfo &p)
{
  string line;
  getline(ifs, line);
  if(!ifs) return ifs;
  int delim1 = line.find(' ');
  p.ptime = stoi(line.substr(0, delim1));
#ifdef _DEBUG
  cout << "DEBUG: " << line.substr(0, delim1) << endl;
#endif
  delim1++;
  int delim2 = line.find(' ', delim1);
  p.un = line.substr(delim1, delim2 - delim1);
#ifdef _DEBUG
  cout << "DEBUG: " << p.un << endl;
#endif
  delim2++;
  p.content = line.substr(delim2, line.size() - delim2);
#ifdef _DEBUG
  cout << "DEBUG: " << p.content << endl;
#endif

  //ifs >> p.ptime >> p.un >> p.content;
  //return ifs;
}

ofstream& operator<< (ofstream &ofs, const PostInfo &p)
{
  ofs << p.ptime << ' ' << p.un
      << ' ' << p.content << endl;
  return ofs;
}

fstream& operator>> (fstream &ifs, PostInfo &p)
{
  string line;
  getline(ifs, line);
  if(!ifs) return ifs;
  int delim1 = line.find(' ');
  p.ptime = stoi(line.substr(0, delim1));
#ifdef _DEBUG
  cout << "DEBUG: " << line.substr(0, delim1) << endl;
#endif
  delim1++;
  int delim2 = line.find(' ', delim1);
  p.un = line.substr(delim1, delim2 - delim1);
#ifdef _DEBUG
  cout << "DEBUG: " << p.un << endl;
#endif
  delim2++;
  p.content = line.substr(delim2, line.size() - delim2);
#ifdef _DEBUG
  cout << "DEBUG: " << p.content << endl;
#endif

  //ifs >> p.ptime >> p.un >> p.content;
  //return ifs;
}

fstream& operator<< (fstream &ofs, const PostInfo &p)
{
  ofs << p.ptime << ' ' << p.un
      << ' ' << p.content << endl;
  return ofs;
}
