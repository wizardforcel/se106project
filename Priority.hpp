#ifndef PRIORITY_H
#define PRIORITY_H

typedef unsigned int size_t;

template<class T, size_t maxlen>
class Priority
{
private:

  struct node
  {
    T data;
    node *next;
  };

  node *root;
  int count;

  Priority(const Priority &p);
  Priority& operator= (const Priority &p);

  void rDelete(node *n);
  void CheckCount();

public:

  Priority();
  ~Priority();

  void Insert(const T &elem);

  //template<class T>
  class Iterator
  {
  private:
    node *cur;

  public:
    Iterator(node *n = 0);
    Iterator& operator++ ();
    bool operator==(const Iterator &that);
    bool operator!=(const Iterator &that);
    T& operator*();
    T* operator->();
  };

  Iterator begin();
  Iterator end();

};

template<class T, size_t maxlen>
void Priority<T, maxlen>::CheckCount()
{
  if(count > 50)
  {
    node **cur = &root;
    if (cur == 0) return;
    while((*cur)->next != 0)
    {
      cur = &((*cur)->next);
    }
    delete *cur;
    *cur = 0;
    count--;
  }
}

template<class T, size_t maxlen>
void Priority<T, maxlen>::rDelete(node *n)
{
  if(n == 0) return;
  rDelete(n->next);
  delete n;
}

template<class T, size_t maxlen>
Priority<T, maxlen>::Priority()
  : root(0), count(0) {}

template<class T, size_t maxlen>
Priority<T, maxlen>::~Priority()
{
  rDelete(root);
}

template<class T, size_t maxlen>
void Priority<T, maxlen>::Insert(const T &elem)
{
  node **cur = &root;
  while(*cur != 0)
  {
    if((*cur)->data < elem)
      break;
    cur = &((*cur)->next);
  }
  if(*cur == 0 && count == maxlen)
    return;
  node *n = new node();
  n->data = elem;
  n->next = *cur;
  *cur = n;
  count++;
  CheckCount();
}

template<class T, size_t maxlen>
Priority<T, maxlen>::Iterator::Iterator(node *n)
  : cur(n) {}

template<class T, size_t maxlen>
typename Priority<T, maxlen>::Iterator&
  Priority<T, maxlen>::Iterator::operator++ ()
{
  cur = cur->next;
  return *this;
}

template<class T, size_t maxlen>
bool Priority<T, maxlen>::Iterator::operator==
  (const Priority<T, maxlen>::Iterator &that)
{
  return this->cur == that.cur;
}

template<class T, size_t maxlen>
bool Priority<T, maxlen>::Iterator::operator!=
  (const Priority<T, maxlen>::Iterator &that)
{
  return this->cur != that.cur;
}

template<class T, size_t maxlen>
T& Priority<T, maxlen>::Iterator::operator*()
{
  return cur->data;
}

template<class T, size_t maxlen>
T* Priority<T, maxlen>::Iterator::operator->()
{
  return &(cur->data);
}

template<class T, size_t maxlen>
typename Priority<T, maxlen>::Iterator
  Priority<T, maxlen>::begin()
{
  return Priority<T, maxlen>::Iterator(root);
}

template<class T, size_t maxlen>
typename Priority<T, maxlen>::Iterator
  Priority<T, maxlen>::end()
{
  return Priority<T, maxlen>::Iterator(0);
}

#endif
