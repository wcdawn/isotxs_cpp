# include <iostream> // std::cout, etc.
# include <fstream> // std::ifstream, etc.
# include <sstream> // std::stringstream

# include <array>


std::stringstream msg;

struct ISOTXS
{
  std::array<char,8> hname;
  std::array<std::array<char,8>,2> huse;
  int16_t ivers;
};

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

void bRead(std::ifstream &file, auto &var)
{
  file.read((char*) &var, sizeof(var));
}

void recordChange(std::ifstream &file)
{
  int16_t zero;
  int16_t number;
  bRead(file,number);
  bRead(file,zero);
  std::cout << "number: " << number << '\n';
  std::cout << "zero:   " << zero   << '\n';
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

  ISOTXS iso_data;
  
  // begin actually reading the file
  // REMINDER: how big is everything? character(8), real(4), integer(?)
//  myFile.read((char*) &zero,sizeof(zero));
  recordChange(myFile);
  std::cout << '*';
  for (unsigned int i{0}; i < iso_data.hname.size(); ++i)
  {
    bRead(myFile,iso_data.hname[i]);
    std::cout << iso_data.hname[i];
  }
  std::cout << "*\n";
  for (unsigned int i{0}; i < iso_data.huse.size(); ++i)
  {
    std::cout << '*';
    for (unsigned int j{0}; j < iso_data.huse[i].size(); ++j)
    {
      bRead(myFile,iso_data.huse[i][j]);
      std::cout << iso_data.huse[i][j];
    }
    std::cout << "*\n";
  }
  recordChange(myFile);
  recordChange(myFile);
  std::cout << "--- end1\n";
  recordChange(myFile);
  





  //int nbPoints;
  //myFile.seekg(RECORD_DELIMITER_LENGTH, std::ios::cur);
  //myFile.read((char*) &nbPoints, sizeof(nbPoints));



  myFile.close();

  return 0;
}
