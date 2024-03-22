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

template <typename T> MyList<T>::~MyList() {
  clear();
  delete head;
}

template <typename T> MyList<T> &MyList<T>::operator=(const MyList<T> &rhs) {

  // Finish Me!
  clear();
  ListNode<T> *pos_ptr = head;
  ListNode<T> *data_ptr = rhs.head;
  while (data_ptr->next != nullptr) {
    insert(pos_ptr, data_ptr->data);
    pos_ptr = pos_ptr->next;
    data_ptr = data_ptr->next;
  }

  return *this;
}

template <typename T> MyList<T>::MyList(const MyList<T> &rhs) {
  head = new ListNode<T>;
  head->next = nullptr;
  *this = rhs;
}

template <typename T> void MyList<T>::assign(int count, const T &value) {
  clear();
  for (int i = 0; i < count; ++i) {
    push_front(value);
  }
}

template <typename T> void MyList<T>::clear() {
  ListNode<T> *tmp = head->next;
  while (tmp != nullptr) {
    ListNode<T> *nextNode = tmp->next;
    delete tmp;
    tmp = nextNode;
  }
  head->next = nullptr;
  num_elements = 0;
}

template <typename T>
void MyList<T>::insert(LinkedListIterator<T> iter, const T &value) {
  ListNode<T> *tmp = new ListNode<T>;
  tmp->data = iter->data;
  tmp->next = iter->next;
  iter->data = value;
  iter->next = tmp;
  num_elements++;
}

template <typename T> void MyList<T>::erase(LinkedListIterator<T> iter) {
  if (iter->next != nullptr) {
    ListNode<T> *tmp = iter->next;
    iter->data = tmp->data;
    iter->next = tmp->next;
    delete tmp;
    tmp = nullptr;
    num_elements--;
  }
}

template <typename T> void MyList<T>::reverse() {
  ListNode<T> *prevNode = nullptr;
  ListNode<T> *currNode = head;
  ListNode<T> *nextNode = nullptr;
  while (currNode != nullptr) {
    nextNode = currNode->next;
    currNode->next = prevNode;
    prevNode = currNode;
    currNode = nextNode;
  }
  head = prevNode;
}

template <typename T> LinkedListIterator<T> MyList<T>::find(const T &value) {
  ListNode<T> *runner = head;
  while (runner->next != nullptr) {
    if (value == runner->data) {
      return runner;
    }
    runner = runner->next;
  }
  return nullptr;
}

template <typename T>
void MyList<T>::splice_after(ListNode<T> *splice_point, MyList<T> &source) {
  ListNode<T> *lastNode = source.head;
  while (lastNode->next != nullptr) {
    lastNode = lastNode->next;
  }
  lastNode->next = splice_point->next;
  splice_point->next = source.head->next;
  num_elements += source.size();
  source.head->next = nullptr;
  source.num_elements = 0;
}
