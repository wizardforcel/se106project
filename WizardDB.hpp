#ifndef WIZARDDB_H
#define WIZARDDB_H

#include <string>
#include <vector>
#include <fstream>
#include "Utility.h"
using namespace std;

template<class T>
class WizardDB
{
private:
  //vector<T> List;
  //int FileNum;
  string FolderName;
  string FileName;

  //vector<T> LoadList(int fileno);
  //void SaveList(vector<T> &list, int fileno);
  //void LoadCache(const string &kw);
  //void SaveCache();
  //int FindIndex(const string &kw);
  //int FindIndex(const T &elem);

public:
  WizardDB(const string &folder, const string &file);
  
  void AddNew(const T &elem);
  //bool Rm(const string &kw);
  //int RmAll(const string &kw);
  bool Rm(const T &elem);
  bool Update(const T &elem);
  bool Find(const string &kw, T &res);
  bool Find(const T &elem);
  vector<T> FindAll(const string &kw);
};

template<class T>
WizardDB<T>::WizardDB(const string &folder, const string &file)
  : FolderName(folder), FileName(file) {}

/*template<class T>
vector<T> WizardDB<T>::LoadList(int fileno)
{
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";
  vector<T> list;
  
  ifstream ifs(fname, ios::in);
  if(!ifs) return list;

  while(!ifs.eof())
  {
    T elem;
    ifs >> elem;
    if(!ifs) break;
    list.push_back(elem);    
  }
  ifs.close();

  return list;
}

template<class T>
void WizardDB<T>::SaveList(vector<T> &list, int fileno)
{
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";

  ofstream ofs(fname, ios::out | ios::trunc);

  for(const auto &elem : list)
    ofs << elem;

  ofs.close();
}

template<class T>
void WizardDB<T>::LoadCache(const string &kw)
{
  int hash = ComputeHash(kw);
  if(hash != FileNum)
  {
    List = LoadList(hash);
    FileNum = hash;
  }
}

template<class T>
void WizardDB<T>::SaveCache()
{
  SaveList(List, FileNum);
}

template<class T>
int WizardDB<T>::FindIndex(const string &kw)
{
  int len = List.size();
  for(int i = 0; i < len; i++)
  {
    if(List[i].KeyWord() == kw)
      return i;
  }
  return -1;
}

template<class T>
int WizardDB<T>::FindIndex(const T &elem)
{
  int len = List.size();
  for(int i = 0; i < len; i++)
  {
    if(List[i] == elem)
      return i;
  }
  return -1;
}*/

template<class T>
void WizardDB<T>::AddNew(const T &elem)
{
  int hash = ComputeHash(elem.KeyWord());
  string fname = FolderName + "/" + FileName + to_string(hash) + ".dat";
  ofstream ofs(fname, ios::out | ios::app);
  ofs << elem;
  ofs.close();
}

template<class T>
bool WizardDB<T>::Find(const string &kw, T &res)
{
  int fileno = ComputeHash(kw);
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";
  
  ifstream ifs(fname, ios::in);
  if(!ifs) return false;

  bool found = false;
  while(true)
  {
    T tmp;
    ifs >> tmp;
    if(!ifs) break;
    if(tmp.KeyWord() == kw)
    {
      found = true;
      res = tmp;
      break;
    }
  }
  ifs.close();

  return found;
}

template<class T>
bool WizardDB<T>::Find(const T &elem)
{
  int fileno = ComputeHash(elem.KeyWord());
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";
  
  ifstream ifs(fname, ios::in);
  if(!ifs) return false;

  bool found = false;
  while(true)
  {
    T tmp;
    ifs >> tmp;
    if(!ifs) break;
    if(tmp == elem)
    {
      found = true;
      break;
    }
  }
  ifs.close();

  return found;
}

template<class T>
bool WizardDB<T>::Update(const T &elem)
{
  int fileno = ComputeHash(elem.KeyWord());
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";
  
  fstream fs(fname, ios::in | ios::out);
  if(!fs) return false;

  bool found = false;
  int spos = 0;
  int epos = 0;
  while(true)
  {
    T tmp;
    spos = fs.tellg();
    if(fs.peek() == 0xa)
      spos++;
    fs >> tmp;
    if(!fs) break;
    if(tmp.KeyWord() == elem.KeyWord())
    {
      found = true;
      epos = fs.tellg();
      if(fs.peek() == 0xa)
        epos++;
      int size = epos - spos;
      fs.seekp(spos, ios::beg);
      string bnk(size, ' ');
      fs << bnk;
      fs.seekp(0, ios::end);
      fs << elem << endl;
      fs.close();
      break;
    }
  }

  return found;  
}

template<class T>
vector<T> WizardDB<T>::FindAll(const string &kw)
{
  vector<T> res;

  int fileno = ComputeHash(kw);
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";
  
  ifstream ifs(fname, ios::in);
  if(!ifs) return res;

  while(true)
  {
    T tmp;
    ifs >> tmp;
    if(!ifs) break;
    if(tmp.KeyWord() == kw)
      res.push_back(tmp);
  }
  ifs.close();

  return res;
}

template<class T>
bool WizardDB<T>::Rm(const T &elem)
{
  int fileno = ComputeHash(elem.KeyWord());
  string fname = FolderName + "/" + FileName + to_string(fileno) + ".dat";
  
  fstream fs(fname, ios::in | ios::out);
  if(!fs) return false;

  bool found = false;
  int spos = 0;
  int epos = 0;
  while(true)
  {
    T tmp;
    spos = fs.tellg();
    if(fs.peek() == 0xa)
      spos++;
    fs >> tmp;
    if(!fs) break;
    if(tmp == elem)
    {
      found = true;
      epos = fs.tellg();
      if(fs.peek() == 0xa)
        epos++;
      int size = epos - spos;
      fs.seekp(spos, ios::beg);
      string bnk(size, ' ');
      fs << bnk;
      break;
    }
  }
  fs.close();

  return found;
}

#endif
