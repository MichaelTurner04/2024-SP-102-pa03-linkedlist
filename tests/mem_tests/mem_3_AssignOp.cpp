#include "MyList.h"

int main() {

  MyList<int> your_list, other_list;
  your_list.push_front(1);
  your_list.push_front(2);
  your_list.push_front(3);

  other_list = your_list;

  return 0;
}
