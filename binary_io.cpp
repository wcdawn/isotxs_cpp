# include <iostream> // std::cout, etc.
# include <fstream> // std::ifstream, etc.
# include <sstream> // std::stringstream

# include <string> // std::string
# include <vector> // std::vector

std::vector<std::string> msg;
std::stringstream myMsg;

void raiseFatal()
{
  std::cout << std::string(80,'*') << '\n';
  for (int i{0}; i < 13; ++i)
    std::cout << "FATAL ";
  std::cout << std::string(2,'\n');
  std::cout << myMsg.str();
  std::cout << '\n';
  for (int i{0}; i < 13; ++i)
    std::cout << "FATAL ";
  std::cout << '\n';
  std::cout << std::string(80,'*') << '\n';
  myMsg.str("");
  myMsg.clear();
  exit(1);
}

void msgAdd(const char *letters)
{
  msg.push_back(std::string(letters));
}

int main()
{
  std::string fname("ISOTXS.u235");
  std::ifstream myFile (fname.c_str(), std::ios::in | std::ios::binary);
  if (!myFile)
  {
    myMsg << "failed to open " << fname << '\n';
    raiseFatal();
  }



  myFile.close();

  return 0;
}
