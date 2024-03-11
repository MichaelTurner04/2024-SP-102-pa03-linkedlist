#include "MyList.h"
#include "test_utils.hpp"
#include <ctime>
#include <forward_list>
#include <stdlib.h>

int main(const int argc, const char **argv) {
  return test_wrapper(argc, argv, []() {
    time_t seed;
    srand(time(&seed));

    MyList<int> your_list;
    std::forward_list<int> test_list;

    for (int k = 0; k < 3; k++) {
      int r = rand() % 50;
      your_list.push_front(r);
      test_list.push_front(r);
    }

    LinkedListIterator<int> iter = your_list.begin()->next;
    auto test_iter = test_list.begin();

    your_list.insert(iter, 51);
    test_list.insert_after(test_iter, 51);
    iter = your_list.begin();
    test_iter = test_list.begin();
    while (iter->next != nullptr) {
      if (*test_iter++ != iter->data)
        return false;
      iter + 1;
    }

    return true;
  });
}
