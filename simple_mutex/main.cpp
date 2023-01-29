#include <algorithm>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

std::list<int> shared_list;
std::mutex m;

void add_to_list(int new_value) {
  std::lock_guard<std::mutex> guard(m);
  shared_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
  std::lock_guard<std::mutex> guard(m);

  auto value_position =
      std::find(shared_list.begin(), shared_list.end(), value_to_find);

  bool found = (value_position != shared_list.end());

  std::cout << "found: " << (found ? "yes" : "no") << std::endl;
  return found;
}

int main() {
  /* Althrough the lock avoids race condition,
  The two threads are not synchronized for execution order.
  Thus, sometimes list_contains returns true, sometimes false.
  */
  std::thread t1(add_to_list, 1);
  std::thread t2(list_contains, 1);

  t1.join();
  t2.join();

  return 0;
}