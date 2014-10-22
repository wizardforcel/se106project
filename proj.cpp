#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

#include "UserInfo.h"
#include "Utility.h"
#include "PostInfo.h"
#include "FollowInfo.h"
#include "WizardDB.hpp"
#include "Priority.hpp"

#define GUEST_LOGIN 1
#define GUEST_REG 2
#define GUEST_EXIT 0

#define USER_LOGOUT 1
#define USER_CNGPW 2
#define USER_CNGINFO 3
#define USER_SEARCH 4
#define USER_SENDPOST 5
#define USER_READPOST 6
#define USER_RDMYPOST 7
#define USER_SEECONCERNS 8
#define USER_SEEFANS 9
#define USER_EXIT 0

//Globals

UserInfo CurUser;

WizardDB<UserInfo> Users("Users", "user");
WizardDB<PostInfo> Posts("Posts", "post");
WizardDB<ConcernInfo> Concerns("Follows", "concern");
WizardDB<FansInfo> Fans("Follows", "fans");


//Func dclr

void dowork();
void dowork_guest();
void login();
void reg();
void changepw();
void changeinfo();
void search();
void send_post();
void read_post();
void read_post(const string &un);
void see_concerns();
void see_fans();
void follow_others(const string &un);
void unfollow_others(const string &un);
void forward(const vector<PostInfo> &v);

int cgetint(const string &msg, int min = 0x80000000, int max = 0x7FFFFFFF);

//Func impl

int cgetint(const string &msg, int min, int max)
{
  int choose;
  bool valid;
  do {
    cout << msg << endl;
    string sval;
    getline(cin, sval);
    valid = isint(sval);
    if(valid) choose = stoi(sval);
  } while(!valid || !(choose >= min && choose <= max));
  return choose;
}

void forward(const vector<PostInfo> &v)
{
  if(v.size() == 0) return;
  while(true)
  {
    cout << "Would you like to forward a piece of post?" << endl;
    string ipt;
    do {
      getline(cin, ipt);
    } while(ipt != "yes" && ipt != "no" && ipt != "y" && ipt != "n");
    bool chs = ipt == "yes" || ipt == "y";
    if(!chs) return;

    cout << "Please input the number:" << endl;
    int num = cgetint("Your choice:", 0, v.size() - 1);

    string co;
    cout << "Please input the content." << endl;
    getline(cin, co);
    co += "//@" + v[num].un + ": " + v[num].content;
    if(co.size() > 140)
    {
      cout << "Message too long!" << endl;
      continue;
    }

    PostInfo p;
    p.un = CurUser.un;
    p.content = co;
    Posts.AddNew(p);
    cout << "Forward suceeded." << endl;
  }

}

void see_concerns()
{
  vector<ConcernInfo> v = Concerns.FindAll(CurUser.un);
  sort(v.begin(), v.end());
  cout << "============Your Concerns============" << endl;
  for(const auto &e : v)
    cout << e.concern << endl;
  cout << "=====================================" << endl;
}

void see_fans()
{
  vector<FansInfo> v = Fans.FindAll(CurUser.un);
  sort(v.begin(), v.end());
  cout << "==============Your Fans==============" << endl;
  for(const auto &e : v)
    cout << e.fans << endl;
  cout << "=====================================" << endl;
}


void unfollow_others(const string &un)
{
  ConcernInfo c;
  c.un = CurUser.un;
  c.concern = un;
  if(!Concerns.Find(c))
  {
    cout << "You didn't follow the user." << endl;
    return;
  }

  Concerns.Rm(c);
  FansInfo f;
  f.un = un;
  f.fans = CurUser.un;
  Fans.Rm(f);
  cout << "Succeed to unfollow." << endl;
}

void follow_others(const string &un)
{
  ConcernInfo c;
  c.un = CurUser.un;
  c.concern = un;
  if(Concerns.Find(c))
  {
    cout << "Already followed." << endl;
    return;
  }

  Concerns.AddNew(c);
  FansInfo f;
  f.un = un;
  f.fans = CurUser.un;
  Fans.AddNew(f);
  cout << "Succeed to follow." << endl;
}


void read_post()
{
  
  Priority<PostInfo, 50> msg;
  vector<PostInfo> v = Posts.FindAll(CurUser.un);
  for(const auto &e : v)
    msg.Insert(e);

  vector<ConcernInfo> list = Concerns.FindAll(CurUser.un);
  for(const auto &elem : list)
  {
    v = Posts.FindAll(elem.concern);
    for(const auto &e : v)
      msg.Insert(e);
  }

  int index = 0;
  v.clear();
  cout << "==============All Posts=============" << endl;
  for(const auto &elem : msg)
  {
    cout << index << ' ';
    elem.ShowMsg();
    v.push_back(elem);
    index++;
  }
  cout << "=====================================" << endl;

  forward(v);
}

void read_post(const string &un)
{
  vector<PostInfo> v = Posts.FindAll(un);
  Priority<PostInfo, 50> msg;
  for(const auto &e : v)
    msg.Insert(e);

  int index = 0;
  cout << "=============Posts List=============" << endl;
  for(const auto &e : msg)
  {
    cout << index << ' ';
    e.ShowMsg();
    index++;
  }
  cout << "=====================================" << endl;

  forward(v);
}

void send_post()
{
  string co;
  cout << "Please input the content (1 ~ 140 words): " << endl;
  getline(cin, co);
  if(co.size() > 140)
  {
    cout << "Content too large." << endl;
    return;
  }

  PostInfo p;
  p.un = CurUser.un;
  p.content = co;
  Posts.AddNew(p);

  cout << "Success to send a post." << endl;
}

void changeinfo()
{
  CurUser.ShowMsg();
  cout << "What do you want to change?" << endl
       << "1. sex 2. name 3. birthday 0 return"  << endl;
  int chs = cgetint("Your choice:", 0, 3);

  string name;
  string input;
  int y, m, d;
  bool male;
  
  switch(chs)
  {
  case 1:
    do {
      cout << "Your sex: ";
      getline(cin, input);
    } while(input != "male" && input != "female");
    CurUser.ismale = male;
    break;
  case 2:
    cout << "Please input your name:" <<endl;
    getline(cin, name);
    CurUser.name = name;
    break;
  case 3:
    cout << "Please input your birthday (year month date):" << endl;
    cin >> y >> m >> d;
    cin.sync();
    CurUser.year = y;
    CurUser.month = m;
    CurUser.date = d;
    break;
  case 0:
    return;
  default:
    throw logic_error("internal error");
  }

  Users.Update(CurUser);
  cout << "Suceed to change personal information." << endl;
}

void changepw()
{
  string pw;
  cout << "Please input the current password: " << endl;
  getline(cin, pw);
  if(pw != CurUser.pw)
  {
    cout << "current password wrong!" << endl;
    return;
  }

  cout << "Please input a new password (6~16 words):" << endl;
  getline(cin, pw);
  if(pw.size() < 6 || pw.size() > 16)
  {
    cout << "invalid password!" << endl;
    return;
  }

  string pw2;
  cout << "Please input it again:" << endl;
  getline(cin, pw2);
  if(pw != pw2)
  {
    cout <<"Two input differ!" << endl;
    return;
  }

  CurUser.pw = pw;
  Users.Update(CurUser);
  cout << "Success to change password!" << endl;
}

void search()
{
  cout << "Please input the username to find:" << endl;
  string tofind;
  getline(cin, tofind);
  
  if(tofind == CurUser.un)
  {
    cout << "You cannot find yourself." << endl;
    return;
  }

  UserInfo u;
  if(!Users.Find(tofind, u))
  {
    cout << "not found!" << endl;
    return;
  }

  u.ShowMsg();

  ConcernInfo c;
  c.un = CurUser.un;
  c.concern = tofind;
  bool isconcern = Concerns.Find(c);
  if(isconcern)
    cout << "You concerned " << (u.ismale?"him":"her")
         << '.' << endl;
  else
    cout << "You didn't concern " << (u.ismale?"him":"her")
         << '.' << endl;

  FansInfo f;
  f.un = CurUser.un;
  f.fans = tofind;
  bool isfans = Fans.Find(f);
  if(isfans)
    cout << (u.ismale?"He":"She") << " is your fans." << endl;
  else
    cout << (u.ismale?"He":"She") << " is not your fans." << endl;

  while(true) 
  {
    cout << "What do you want to do?"
         << "1: see posts 2: " << (isconcern?"unfollow":"follow") 
         << " 0: return" << endl;
  
    int chs = cgetint("Your choice:", 0, 2);

    switch(chs)
    {
      case 0:
        return;
      case 1:
        read_post(tofind);
        break;
      case 2:
        isconcern? unfollow_others(tofind): follow_others(tofind);
        isconcern = !isconcern;
        break;
      default:
        throw logic_error("internal error");
    }
  }
}



void dowork()
{
  cout << "Welcome back, " << CurUser.un
       << ". What would you like to do?" << endl
       << "Input the number before the action to choose it: " << endl
       << "1: logout 2: change password 3: see/change personal info "
          "4: search user 5 send a post 6 read posts 7 read my posts "
          "8 see concerns 9 see fans 0: exit" << endl;

  int choose = cgetint("Your choice:", 0, 9);

  switch(choose)
  {
  case USER_LOGOUT:
    CurUser.Clear();
    cout << "Succeed to logout." << endl;
    break;
  case USER_CNGPW:
    changepw();
    break;
  case USER_CNGINFO:
    changeinfo();
    break;
  case USER_SEARCH:
    search();
    break;
  case USER_SENDPOST:
    send_post();
    break;
  case USER_READPOST:
    read_post();
    break;
  case USER_RDMYPOST:
    read_post(CurUser.un);
    break;
  case USER_SEECONCERNS:
    see_concerns();
    break;
  case USER_SEEFANS:
    see_fans();
    break;
  case USER_EXIT:
    exit(0);
    break;
  default:
    throw logic_error("internal error");
  }  
}

void reg()
{
  cout << "Please input a username (1~16 words):" << endl;
  string un;
  getline(cin, un);
  if(!valid_un(un))
  {
    cout << "invalid username!" << endl;
    return;
  }

  UserInfo u;
  if(Users.Find(un, u))
  {
    cout << "already occupied!" << endl;
    return;
  }
  
  string pw;
  cout << "Please input a password (6~16 words):" << endl;
  getline(cin, pw);
  if(pw.size() < 6 || pw.size() > 16)
  {
    cout << "invalid password!" << endl;
    return;
  }

  string pw2;
  cout << "Please input it again: " << endl;
  getline(cin, pw2);
  if(pw != pw2)
  {
    cout << "two inputs differ!" << endl;
    return;
  }

  string name;
  cout << "Please input your name: " << endl;
  getline(cin, name);
  
  string morf;
  do {
    cout << "Are you male or female?" << endl;
    getline(cin, morf);
  } while(morf != "male" && morf != "female");
  bool ismale = (morf == "male");

  int year, month, date;
  cout << "input your birthday (year month day): " << endl;
  cin >> year >> month >> date;
  if(!cin)
  {
    cout << "input data format error" << endl;
    return;
  }
  cin.sync();

  u.un = un;
  u.pw = pw;
  u.name = name;
  u.ismale = ismale;
  u.year = year;
  u.month = month;
  u.date = date;

  Users.AddNew(u);
  CurUser = u;
  cout << "Succeed to registrate!" << endl;
}

void login()
{
  
  cout << "Please input username:" << endl;
  string un;
  getline(cin, un);

  UserInfo u;
  if(!Users.Find(un, u))
  {
    cout << "Username not found!" << endl;
    return;
  }

  cout << "Please input password:" << endl;
  string pw;
  getline(cin, pw);
  if(u.pw != pw)
  {
    cout << "password wrong!" << endl;
    return;
  }

  cout << "Login succeeded!" << endl;
  CurUser = u;
}


void dowork_guest()
{
  cout << "Hello, guest. Please login or rigiste." << endl
       << "Input the number before the action to choose it: " << endl
       << "1: login 2: registrate 0: exit" << endl;

  int choose = cgetint("Your choice:", 0, 2);

  switch(choose)
  {
  case GUEST_LOGIN:
    login();
    break;
  case GUEST_REG:
    reg();
    break;
  case GUEST_EXIT:
    exit(0);
    break;
  default:
    throw logic_error("internal error");
  }
}


int main()
{
  while(true)
  {
    try {

    if(CurUser.Empty())
      dowork_guest();
    else
      dowork();

    }
    catch(exception &ex)
    { cout << ex.what() << endl; }
  }

  return 0;
}






