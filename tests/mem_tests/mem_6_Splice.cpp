#include "MyList.h"

int main() {

  MyList<int> your_list, other_list;
  your_list.push_front(1);
  your_list.push_front(2);
  other_list.push_front(3);
  other_list.push_front(4);

  your_list.splice_after(your_list.begin()->next, other_list);

  return 0;
}
