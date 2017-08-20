# include <iostream>
# include <string>
# include <sstream>

std::stringstream msg;

// TO-DO: move these to another file
void raiseFatal()
{
  std::cout << std::string(80,'*') << '\n';
  for (int i{0}; i < 13; ++i)
    std::cout << "FATAL ";
  std::cout << std::string(2,'\n');
  std::cout << msg.str();
  std::cout << '\n';
  for (int i{0}; i < 13; ++i)
    std::cout << "FATAL ";
  std::cout << '\n';
  std::cout << std::string(80,'*') << '\n';
  msg.str("");
  msg.clear();
  exit(1);
}

void raiseWarn()
{
  std::cout << std::string(80,'.') << '\n';
  for (int i{0}; i < 10; ++i)
    std::cout << "WARNING ";
  std::cout << std::string(2,'\n');
  std::cout << msg.str();
  std::cout << '\n';
  for (int i{0}; i < 10; ++i)
    std::cout << "WARNING ";
  std::cout << '\n';
  std::cout << std::string(80,'.') << '\n';
  msg.str("");
  msg.clear();
}
