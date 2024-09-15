#include <iostream>
#include "include/lab1.h"
#include <string>

int main()
{
  std::string number;
  std::cout << "Введите двоичное число: ";
  std::cin  >> number;

  std::cout << "result: " << eliminate_unset_bits(number) << std::endl;

  return 0;
}
