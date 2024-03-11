#include "MyList.h"
#include "test_utils.hpp"
#include <ctime>
#include <forward_list>
#include <stdlib.h>

int main(const int argc, const char **argv) {
  return test_wrapper(argc, argv, []() {
    time_t seed;
    srand(time(&seed));

    int r_seq[]{rand() % 50, rand() % 50, rand() % 50};

    MyList<int> your_list;
    std::forward_list<int> test_list{r_seq[0], r_seq[1], r_seq[2]};

    your_list.push_front(r_seq[0]);
    your_list.push_front(r_seq[1]);
    your_list.push_front(r_seq[2]);
    your_list.reverse();

    LinkedListIterator<int> iter = your_list.begin();
    auto test_iter = test_list.begin();

    for (int k = 0; k < 3; k++) {
      if (iter->data != *test_iter++)
        return false;
      iter + 1;
    }

    return true;
  });
}
