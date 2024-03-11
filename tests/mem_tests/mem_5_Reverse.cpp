#include "MyList.h"

int main() {

  MyList<int> your_list;
  your_list.push_front(1);
  your_list.push_front(2);
  your_list.push_front(3);

  your_list.reverse();

  return 0;
}
