/*
 * If you want to know what the functions do,
 * Read the links in the assignment description from en.cppreference.
 */

#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T> class ListNode {
public:
  T data;

  ListNode<T> *next;
  // ListNode<T> *prev;

  /*
        You may create a singly-linked forward list
        (Similar to the implementation discussed in class)
        Or you may attempt a doubly-linked list
        (Will require different code for most ops)
        Uncomment the line above if you're up for the challenge
  */
};

template <typename T> class LinkedListIterator {
  ListNode<T> *ptr;

public:
  LinkedListIterator(ListNode<T> *p) { ptr = p; } // constructor
  ListNode<T> &operator*() {
    return *ptr;
  } // de-referencing iterator gives access to the current node
  ListNode<T> *operator->() { return ptr; }
  void operator+(int increment) {
    int hops = 0;
    while (hops < increment && ptr != nullptr) {
      ptr = ptr->next; // "advance" the pointer to next node
      hops++;
    }
  }
  bool is_null() { return ptr == nullptr; }
};

template <typename T> class MyList {
private:
  ListNode<T> *head = nullptr;

  int num_elements;

public:
  ListNode<T> *begin(); // For mimicking stdlib iterators

  MyList();

  ~MyList();

  MyList<T> &operator=(const MyList<T> &rhs);

  MyList(const MyList<T> &rhs);

  T &front();

  int size();

  // Turn list into 'count' copies of 'value'
  // Any existing data should be safely removed if necessary
  void assign(int count, const T &value);

  // Default list size of 0, with one sentinel node
  void clear();

  // Insert `value` to the head of the list
  void push_front(const T &value);

  // Erase the value at the head of the list, if size > 0
  void pop_front();

  // Insert 'value' to the position pointed to by 'iter'
  // The element pointed to by 'iter' should come after 'value' when finished
  void insert(LinkedListIterator<T> iter, const T &value);

  // Removes all elements in list that are equal to value.
  // You do NOT need a special case for 0-big lists (i.e., no if size == 0).
  void remove(const T &value);

  // Removes element at position pointed to by 'iter'
  void erase(LinkedListIterator<T> iter);

  // If 'value' is in the list, return iterator to first node containing 'value'
  // If 'value' is not in the list, return nullptr
  LinkedListIterator<T> find(const T &value);

  // Reverse the order of elements in the list
  // COMMON INTERVIEW CHALLENGE
  // Can be done with clever manipulation of pointers, no new/delete needed!
  void reverse();

  // READ CAREFULLY
  // Moves data elements from 'source' into list
  // 'source' should be an empty list afterwards
  // Data from 'source should go after the position pointed to by 'splice_point'
  // Ex:
  // list - [1, 2, 3(splice_point), 4], source - [5, 6]
  // list.splice_after(splice_point, source)
  // list - [1, 2, 3, 5, 6, 4], source - []
  // Can be done with precision pointer surgery, no new/delete needed!
  void splice_after(ListNode<T> *splice_point, MyList &source);
};

#include "MyList.hpp"

#endif
