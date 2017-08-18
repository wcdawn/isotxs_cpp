# include <iostream> // std::cout, etc.
# include <fstream> // std::ifstream, etc.
# include <sstream> // std::stringstream

# include <array>
# include <vector>


std::stringstream msg;
const int holl_len{8};

struct ISOTXS
{
  std::array<char,holl_len> hname;
  std::array<std::array<char,holl_len>,2> huse;
  int32_t ivers;

  int32_t ngroup;
  int32_t niso;
  int32_t maxup;
  int32_t maxdn;
  int32_t maxord;
  int32_t ichist;
  int32_t nscmax;
  int32_t nsblok;

  std::array<std::array<char,holl_len>,12> hsetid;
  std::vector<std::array<char,holl_len>> hisonm;
  std::vector<float> chi;
  std::vector<float> vel;
  std::vector<float> emax;
  float emin;
  std::vector<int32_t> loca;

  std::vector<std::vector<float>> chi_fw;
  std::vector<int32_t> isspec;
};

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

void bRead(std::ifstream &file, auto &var)
{
  file.read((char*) &var, sizeof(var));
}

void recordChange(std::ifstream &file)
{
  int32_t zero;
  int32_t number;
  bRead(file,number);
//  bRead(file,zero);
  std::cout << "number: " << number << '\n';
//  std::cout << "zero:   " << zero   << '\n';
}

void vectorRead(std::ifstream &file, std::vector<auto> &vec)
{
  for (unsigned int i{0}; i < vec.capacity(); ++i)
    bRead(file,vec[i]);
}

void dummyInt(std::ifstream &file)
{
  int32_t itemp;
  for (int i{0}; i < 30; ++i)
  {
    bRead(file,itemp);
    std::cout << itemp << '\n';
  }
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
    msg.str("");
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
  bRead(myFile,iso_data.ivers);
  recordChange(myFile);
  std::cout << "--- end FILE IDENTIFICATION\n";
  recordChange(myFile);
  bRead(myFile,iso_data.ngroup);
  bRead(myFile,iso_data.niso);
  bRead(myFile,iso_data.maxup);
  bRead(myFile,iso_data.maxdn);
  bRead(myFile,iso_data.maxord);
  bRead(myFile,iso_data.ichist);
  bRead(myFile,iso_data.nscmax);
  bRead(myFile,iso_data.nsblok);
  
  
  
  
  iso_data.hisonm.reserve(iso_data.niso);
  iso_data.chi.reserve(iso_data.ngroup);
  iso_data.vel.reserve(iso_data.ngroup);
  iso_data.emax.reserve(iso_data.ngroup);
  iso_data.loca.reserve(iso_data.niso);

  iso_data.chi_fw.reserve(iso_data.ichist);
  for (unsigned int i{0}; i < iso_data.chi_fw.capacity(); ++i)
    iso_data.chi_fw[i].reserve(iso_data.ngroup);
  iso_data.isspec.reserve(iso_data.ngroup);





  if (iso_data.nsblok  != 1) 
  {
    msg << "nsblok must == 1\n";
    msg << "nsblok = " << iso_data.nsblok << '\n';
    raiseFatal();
  }
  recordChange(myFile);
  std::cout << "--- end 1D\n";
  recordChange(myFile);
  for (unsigned int i{0}; i < iso_data.hsetid.size(); ++i)
  {
    for (unsigned int j{0}; j < iso_data.hsetid[i].size(); ++j)
    {
      bRead(myFile,iso_data.hsetid[i][j]);
    }
  }
  for (unsigned int i{0}; i < iso_data.hisonm.capacity(); ++i)
  {
    std::cout << '*';
    for (unsigned int j{0}; j < iso_data.hisonm[i].size(); ++j)
    {
      bRead(myFile,iso_data.hsetid[i][j]);
      std::cout << iso_data.hsetid[i][j];
    }
    std::cout << "*\n";
  }
  if (iso_data.ichist == 1)
  {
    vectorRead(myFile,iso_data.chi);
  }
  vectorRead(myFile,iso_data.vel);
  vectorRead(myFile,iso_data.emax);
  bRead(myFile,iso_data.emin);
  vectorRead(myFile,iso_data.loca);
  recordChange(myFile);
  std::cout << "--- end 2D\n";
  if (iso_data.ichist > 1)
  {
    msg << "this is untested. no file from the test suite has ichist > 1\n";
    raiseWarn();
    recordChange(myFile);
    // matrixRead(myFile,iso_data.chi_fw);
    vectorRead(myFile,iso_data.isspec);
  }






  myFile.close();

  return 0;
}
