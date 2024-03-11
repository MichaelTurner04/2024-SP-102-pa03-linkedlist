#include "MyList.h"
#include "test_utils.hpp"
#include <ctime>
#include <forward_list>
#include <stdlib.h>

int main(const int argc, const char **argv) {
  return test_wrapper(argc, argv, []() {
    time_t seed;
    srand(time(&seed));

    int r1 = rand() % 50, r2 = rand() % 50;

    int r_seq[]{1, 2, r1, r2, 3};

    MyList<int> your_list;
    MyList<int> other_list;
    std::forward_list<int> test_list{r_seq[0], r_seq[1], r_seq[2], r_seq[3],
                                     r_seq[4]};

    your_list.push_front(3);
    your_list.push_front(2);
    your_list.push_front(1);
    other_list.push_front(r2);
    other_list.push_front(r1);

    ListNode<int> *splice_point = your_list.begin()->next;
    your_list.splice_after(splice_point, other_list);

    LinkedListIterator<int> iter = your_list.begin();
    auto test_iter = test_list.begin();

    for (int k = 0; k < 5; k++) {
      if (iter->data != *test_iter++)
        return false;
      iter + 1;
    }

    return true;
  });
}
