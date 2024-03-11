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
    }

    your_list.clear();
    if (your_list.begin()->next != nullptr)
      return false;

    return true;
  });
}
