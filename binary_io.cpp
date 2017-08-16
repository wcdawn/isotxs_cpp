# include <iostream>
# include <fstream>

int main()
{
  std::string fname("IOSTXS.u235");
  std::ifstream myFile (fname.c_str(), std::ios::in | std::ios::binary);
  // hello
  myFile.close();

  return 0;
}
