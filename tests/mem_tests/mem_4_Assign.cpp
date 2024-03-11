#include "MyList.h"

int main() {

  MyList<int> your_list;
  your_list.push_front(1);
  your_list.push_front(2);
  your_list.push_front(3);

  your_list.assign(3, 51);

  MyList<int> your_second_list;
  your_second_list.push_front(4);
  your_second_list.push_front(5);
  your_second_list.push_front(6);
  your_second_list.push_front(7);

  your_second_list.assign(2, 1000);

  return 0;
}
