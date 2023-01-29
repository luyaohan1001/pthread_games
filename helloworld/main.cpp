#include <iostream>
#include <thread>

void hello() { std::cout << "Hello concurrent world!" << std::endl; }

int main() {
  std::thread t(hello);
  /* With join(), the main thread waits for hello() to finish before issues end
   * of the process. */
  t.join();
}