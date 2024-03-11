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

    your_list.push_front(rand() % 50);
    your_list.push_front(rand() % 50);
    your_list.push_front(rand() % 50);
    if (your_list.find(51).is_null() == false) {
      cerr << "find function returned a non nullptr when it shouldn't have.\n";
      return false;
    }

    int n = rand() % 1000;
    your_list.push_front(n);
    your_list.push_front(rand() % 50);

    if (your_list.find(n).is_null() == true) {
      cerr << "find function returned a nullptr when it shouldn't have.\n";
      return false;
    }
    if (your_list.find(n)->data != n) {
      cerr << "find function returned a pointer, but the data within the "
              "pointed node isn't correct.\n";
      return false;
    }

    return true;
  });
}
