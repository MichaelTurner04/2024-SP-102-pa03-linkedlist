#include "MyList.h"
#include "test_utils.hpp"
#include <ctime>
#include <forward_list>
#include <stdlib.h>

int main(const int argc, const char **argv) {
  return test_wrapper(argc, argv, []() {
    time_t seed;
    srand(time(&seed));

    int r = rand() % 50;

    MyList<int> your_list;
    std::forward_list<int> test_list{r, r, r};

    your_list.push_front(51);
    your_list.assign(3, r);

    LinkedListIterator<int> iter = your_list.begin();
    auto test_iter = test_list.begin();

    for (int k = 0; k < 3; k++) {
      if (*test_iter++ != iter->data)
        return false;
      iter + 1;
    }
    return true;
  });
}
