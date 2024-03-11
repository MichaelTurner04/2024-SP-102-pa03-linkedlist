/*
 * Implementation file for a clean and simple linked list
 * std::forward_list syntax
 */

// These are freebies, touch only if attempting doubly-linked list
// Tests may depend on these working!
template <typename T> ListNode<T> *MyList<T>::begin() { return head; }

template <typename T> MyList<T>::MyList() {
  num_elements = 0;
  head = new ListNode<T>;
  head->next = nullptr;
}

template <typename T> int MyList<T>::size() { return num_elements; }

template <typename T> T &MyList<T>::front() { return head->data; }

template <typename T> void MyList<T>::push_front(const T &value) {
  ListNode<T> *tmp = new ListNode<T>;
  tmp->data = value;
  tmp->next = head;
  head = tmp;
  num_elements++;
}

template <typename T> void MyList<T>::pop_front() {

  if (num_elements > 0) {
    ListNode<T> *tmp = head->next;
    delete head;
    head = tmp;
    num_elements--;
  }
}

// Implement each of the functions below
// PLEASE READ MyList.h carefully for details on each!
// Check out unit_tests/ and mem_tests/ for grading details

template <typename T> MyList<T>::~MyList() {}

template <typename T> MyList<T> &MyList<T>::operator=(const MyList<T> &rhs) {

  // Finish Me!

  return *this;
}

template <typename T> MyList<T>::MyList(const MyList<T> &rhs) {}

template <typename T> void MyList<T>::assign(int count, const T &value) {}

template <typename T> void MyList<T>::clear() {}

template <typename T>
void MyList<T>::insert(LinkedListIterator<T> iter, const T &value) {}

template <typename T> void MyList<T>::erase(LinkedListIterator<T> iter) {}

template <typename T> void MyList<T>::reverse() {}

template <typename T> LinkedListIterator<T> MyList<T>::find(const T &value) {}

template <typename T>
void MyList<T>::splice_after(ListNode<T> *splice_point, MyList<T> &source) {}
