#include "pch.h"
#include "block.h"

int main()
{
  std::cout << "Hello World!\n";
  auto b = block::create_block(operation::type::identity);
  auto result = b.apply(10);
  std::cout << result;
}
