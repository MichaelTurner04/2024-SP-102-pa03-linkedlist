#include "MyList.h"
#include "test_utils.hpp"
#include <ctime>
#include <forward_list>
#include <stdlib.h>

int main(const int argc, const char **argv) {
  return test_wrapper(argc, argv, []() {
    time_t seed;
    srand(time(&seed));

    MyList<int> your_list, your_copy;
    std::forward_list<int> test_list;

    for (int k = 0; k < 3; k++) {
      int r = rand() % 50;
      your_list.push_front(r);
    }

    your_copy = your_list;
    LinkedListIterator<int> iter = your_list.begin();
    LinkedListIterator<int> test_iter = your_copy.begin();
    while (iter->next != nullptr) {
      if (iter->data != test_iter->data)
        return false;
      iter + 1;
      test_iter + 1;
    }

    your_list.push_front(51);
    if (your_copy.begin()->data == 51) {
      cerr << "deep copy test failed" << endl;
      return false;
    }

    return true;
  });
}
