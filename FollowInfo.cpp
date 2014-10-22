#include "FollowInfo.h"
using namespace std;

string ConcernInfo::KeyWord() const
{
  return un;
}

string FansInfo::KeyWord() const
{
  return un;
}

bool operator== (const ConcernInfo &c1, const ConcernInfo &c2)
{
  return c1.un == c2.un && c1.concern == c2.concern;
}

bool operator< (const ConcernInfo &c1, const ConcernInfo &c2)
{
  return c1.concern < c2.concern;
}

ifstream& operator>> (ifstream &ifs, ConcernInfo &c)
{
  ifs >> c.un >> c.concern;
  return ifs;
}

ofstream& operator<< (ofstream &ofs, const ConcernInfo &c)
{
  ofs << c.un << ' ' << c.concern << endl;
  return ofs;
}

fstream& operator>> (fstream &ifs, ConcernInfo &c)
{
  ifs >> c.un >> c.concern;
  return ifs;
}

fstream& operator<< (fstream &ofs, const ConcernInfo &c)
{
  ofs << c.un << ' ' << c.concern << endl;
  return ofs;
}

bool operator== (const FansInfo &f1, const FansInfo &f2)
{
  return f1.un == f2.un && f1.fans == f2.fans;
}

bool operator< (const FansInfo &f1, const FansInfo &f2)
{
  return f1.fans < f2.fans;
}

ifstream& operator>> (ifstream &ifs, FansInfo &f)
{
  ifs >> f.un >> f.fans;
  return ifs;
}

ofstream& operator<< (ofstream &ofs, const FansInfo &f)
{
  ofs << f.un << ' ' << f.fans << endl;
}

fstream& operator>> (fstream &ifs, FansInfo &f)
{
  ifs >> f.un >> f.fans;
  return ifs;
}

fstream& operator<< (fstream &ofs, const FansInfo &f)
{
  ofs << f.un << ' ' << f.fans << endl;
}
