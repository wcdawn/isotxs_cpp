# include <iostream> // std::cout, etc.
# include <fstream> // std::ifstream, etc.
# include <sstream> // std::stringstream

std::stringstream msg;

// TO-DO: write raiseWarn()
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

int main()
{
  // TO-DO: this should be a command line argument
  std::string fname("ISOTXS.u235");
  // open the file as a binary file
  // TO-DO: look into endian-ness
  std::ifstream myFile (fname.c_str(), std::ios::in | std::ios::binary);
  if (!myFile)
  {
    msg << "failed to open " << fname << '\n';
    raiseFatal();
  }

  // begin actually reading the file
  const int RECORD_DELIMITER_LENGTH = 4;
  myFile.seekg(RECORD_DELIMITER_LENGTH, std::ios::cur);
  myFile.read((char*) &buffer,1000);
  for (int i{0}; i < 1000; ++i)
    std::cout << buffer[i];
  std::cout << '\n';

  myFile.close();

  return 0;
}
