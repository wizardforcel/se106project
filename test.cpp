#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

#include "UserInfo.h"
#include "PostInfo.h"
#include "FollowInfo.h"
#include "WizardDB.hpp"

WizardDB<UserInfo> Users("Users", "user");
WizardDB<PostInfo> Posts("Posts", "post");
WizardDB<ConcernInfo> Concerns("Follows", "concern");
WizardDB<FansInfo> Fans("Follows", "fans");

//#define _DEBUG

string GenUN()
{
  string res;
  for(int i = 0; i < 6; i++)
  {
    double tmp = (double)rand() / (unsigned)(RAND_MAX + 1);
    char c = tmp * ('z' - 'a') + 'a';
    res += c;
  }
  return res;
}


int main()
{
  //for(int i = 0; i < 10000; i++)
  //  cout << GenUN() << endl;

  //return 0;

  cout << "Please input the num: ";
  int num;
  cin >> num;

  vector<UserInfo> v;
  srand(time(0));

  clock_t clk = clock();
  for(int i = 0; i < num; i++)
  {
    string un = GenUN();
#ifdef _DEBUG
    cout << "UN: " << un << endl;
#endif
    UserInfo u;
    u.un = un;
    u.pw = "123456";
    u.name = "nothing";
    u.ismale = true;
    u.year = 0;
    u.month = 0;
    u.date = 0;
    Users.AddNew(u);
    v.push_back(u);
  }
  clk = clock() - clk;
  double tm = (double)clk * 1000 / CLOCKS_PER_SEC;
  cout << "Add: " << tm << " ms" << endl;

  clk = clock();
  for(int i = 0; i < v.size(); i++)
  {
    Users.Find(v[i]);
  }
  clk = clock() - clk;
  tm = (double)clk * 1000 / CLOCKS_PER_SEC;
  cout << "Find: " << tm << " ms" << endl;

  clk = clock();
  for(int i = 0; i < v.size(); i++)
  {
    Users.Update(v[i]);
  }
  tm = (double)clk * 1000 / CLOCKS_PER_SEC;
  cout << "Fix: " << tm << " ms" << endl;

  clk = clock();
  for(int i = 0; i < v.size(); i++)
  {
    Users.Rm(v[i]);
  }
  tm = (double)clk * 1000 / CLOCKS_PER_SEC;
  cout << "Remove: " << tm << " ms" << endl;

  return 0;
}
