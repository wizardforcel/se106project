#ifndef FOLLOWINFO_H
#define FOLLOWINFO_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

struct ConcernInfo
{
  string un;
  string concern;

  string KeyWord() const;
};

struct FansInfo
{
  string un;
  string fans;

  string KeyWord() const;
};


bool operator== (const ConcernInfo &c1, const ConcernInfo &c2);
bool operator< (const ConcernInfo &c1, const ConcernInfo &c2);

ifstream& operator>> (ifstream &ifs, ConcernInfo &c);
ofstream& operator<< (ofstream &ofs, const ConcernInfo &c);

fstream& operator>> (fstream &ifs, ConcernInfo &c);
fstream& operator<< (fstream &ofs, const ConcernInfo &c);

bool operator== (const FansInfo &f1, const FansInfo &f2);
bool operator< (const FansInfo &f1, const FansInfo &f2);

ifstream& operator>> (ifstream &ifs, FansInfo &f);
ofstream& operator<< (ofstream &ofs, const FansInfo &f);

fstream& operator>> (fstream &ifs, FansInfo &f);
fstream& operator<< (fstream &ofs, const FansInfo &f);
#endif
