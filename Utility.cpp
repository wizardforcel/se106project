#include "Utility.h"
#include <ctype.h>
#include <time.h>
using namespace std;

#define isvarname(a) (isalnum(a) || (a) == '_')

int skipblank(const string &str, int index)
{
  int len = str.size();
  while(index != len && str[index] == ' ')
    index++;
  return index;
}

bool parseint(const string &str, int &index, int &res)
{
  if(!isdigit(str[index])) return false;
  int end = index;
  int len = str.size();
  while(isdigit(str[end]) && end != len)
    end++;
  string tmp = str.substr(index, end - index);
  res = stoi(tmp);
  index = end;
  return true;
}

bool parseletter(const string &str, int &index, string &res)
{
  if(!isalpha(str[index])) return false;
  int end = index;
  int len = str.size();
  while(isalpha(str[end]) && end != len)
    end++;
  res = str.substr(index, end - index);
  index = end;
  return true;
}

bool parsevar(const string &str, int &index, string &res)
{
  if(!isalpha(str[index])) return false;
  int end = index;
  int len = str.size();
  while(isvarname(str[end]) && end != len)
    end++;
  res = str.substr(index, end - index);
  index = end;
  return true;
}

string stolower(const string &str)
{
  string res = str;
  int len = res.size();
  for(int i = 0; i < len; i++)
  {
    if(isupper(res[i]))
      res[i] = tolower(res[i]);
  }
  return res;
}

bool isint(const string &str)
{
  int index = skipblank(str, 0);
  if(!(isdigit(str[index]) || str[index] == '-'))
    return false;
  
  index++;
  int len = str.size();
  for( ; index < len && str[index] != ' '; index++)
  {
    if(!isdigit(str[index])) return false;
  }
  index = skipblank(str, index);
  if(index != len) return false;
  else return true;

}

bool valid_num(const string &str)
{
  int len = str.size();
  for(int i = 0; i < len; i++)
  {
    if(!(isdigit(str[i]) || str[i] == '_'))
      return false;
  }
  return true;
}

bool valid_un(const string &un)
{
  int len = un.size();
  for(int i = 0; i < len; i++)
  {
    if(!(isalnum(un[i]) || un[i] == '_'))
      return false;
  }
  return true;
}

int ComputeHash(const string &str)
{
  int sum = 0;
  int len = str.size();
  for(int i = 0; i < len; i++)
    sum += (unsigned char)str[i];
  sum %= 1000;
  return sum;
}

string UnixTimeToLocal(time_t tick)
{
  char buff[100];
  tm *local = localtime(&tick);
  strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", local);
  string str = buff;
  return str;
}
