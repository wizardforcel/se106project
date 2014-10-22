#ifndef POSTINFO_H
#define POSTINFO_H

#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

struct PostInfo
{
  string un;
  string content;
  int ptime;

  PostInfo();

  void ShowMsg() const;
  string KeyWord() const;
};

ifstream& operator>> (ifstream &ifs, PostInfo &p);
ofstream& operator<< (ofstream &ofs, const PostInfo &p);

fstream& operator>> (fstream &ifs, PostInfo &p);
fstream& operator<< (fstream &ofs, const PostInfo &p);

bool operator== (const PostInfo &p1, const PostInfo &p2);
bool operator<(const PostInfo &p1, const PostInfo &p2);

#endif
