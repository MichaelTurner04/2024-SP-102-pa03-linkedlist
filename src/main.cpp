
/*
        Check the README for specifications!
*/

#include "MyList.h"

void HashFunction(const int &key);
void ApplyHashFunction(MyList<int> keys);

int main() {
  MyList<int> l;

  string line;
  while (std::cin >> line) {

    // Finish Me!
  }

  return 0;
}

// "Suggested" Functions, feel free to change

// Takes in an integer (hash key) and prints the corresponding hash-code
// (see README)
void HashFunction(const int &key) {}

// Takes a list of hash keys
// Prints the hash codes for every element
void ApplyHashFunction(MyList<int> keys) {}
