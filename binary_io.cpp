# include <iostream>
# include <fstream> // std::ifstream, etc.
# include <sstream> // std::stringstream

# include <array>
# include <vector>

# include "isotxs_struct.h"
# include "exception_handler.h"

void bRead(std::ifstream &file, auto &var)
{
  file.read((char*) &var, sizeof(var));
}

void recordChange(std::ifstream &file)
{
  int32_t number;
  bRead(file,number);
  std::cout << "number: " << number << '\n';
}

void vectorRead(std::ifstream &file, std::vector<auto> &vec)
{
  for (unsigned int i{0}; i < vec.capacity(); ++i)
    bRead(file,vec[i]);
}

void matrixRead(std::ifstream &file, std::vector<std::vector<auto>> &mat)
{
  for (unsigned int i{0}; i < mat.capacity(); ++i)
  {
    for (unsigned int j{0}; j < mat[i].capacity(); ++j)
    {
      bRead(file,mat[i][j]);
    }
  }
}

void holl_arrayRead(std::ifstream &file, std::array<auto,holl_len> &array)
{
  for (unsigned int i{0}; i < array.size(); ++i)
    bRead(file,array[i]);
}

int main()
{
  // TO-DO: this should be a command line argument
  std::string fname("ISOTXS.u235");
  fname = "ISOTXS.soft_fuel";
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
  recordChange(myFile);
  holl_arrayRead(myFile,iso_data.hname);
  for (unsigned int i{0}; i < iso_data.huse.size(); ++i)
  {
    holl_arrayRead(myFile,iso_data.huse[i]);
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

  iso_data.idsct.reserve(iso_data.nscmax);
  iso_data.lord.reserve(iso_data.nscmax);
  iso_data.jband.reserve(iso_data.nscmax);
  for (unsigned int i{0}; i < iso_data.jband.capacity(); ++i)
    iso_data.jband[i].reserve(iso_data.ngroup);
  iso_data.ijj.reserve(iso_data.nscmax);
  for (unsigned int i{0}; i < iso_data.ijj.capacity(); ++i)
    iso_data.ijj[i].reserve(iso_data.ngroup);









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
    holl_arrayRead(myFile,iso_data.hsetid[i]);
  }
  for (unsigned int i{0}; i < iso_data.hisonm.capacity(); ++i)
  {
    holl_arrayRead(myFile,iso_data.hisonm[i]);
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
    matrixRead(myFile,iso_data.chi_fw);
    vectorRead(myFile,iso_data.isspec);
    recordChange(myFile);
    std::cout << "--- end 3D\n";
  }
  for (int i{0}; i < iso_data.niso; ++i);
  {
    recordChange(myFile);
    holl_arrayRead(myFile,iso_data.habsid);
    holl_arrayRead(myFile,iso_data.hident);
    holl_arrayRead(myFile,iso_data.hmat);
    bRead(myFile,iso_data.amass);
    bRead(myFile,iso_data.efiss);
    bRead(myFile,iso_data.ecapt);
    bRead(myFile,iso_data.temp);
    bRead(myFile,iso_data.sigpot);
    bRead(myFile,iso_data.adens);
    bRead(myFile,iso_data.kbr);
    bRead(myFile,iso_data.ichi);
    bRead(myFile,iso_data.ifis);
    bRead(myFile,iso_data.ialf);
    bRead(myFile,iso_data.inp);
    bRead(myFile,iso_data.in2n);
    bRead(myFile,iso_data.ind);
    bRead(myFile,iso_data.intritium);
    bRead(myFile,iso_data.ltot);
    bRead(myFile,iso_data.ltrn);
    bRead(myFile,iso_data.istrpd);
    vectorRead(myFile,iso_data.idsct);
    vectorRead(myFile,iso_data.lord);
    matrixRead(myFile,iso_data.jband);
    matrixRead(myFile,iso_data.ijj);
    if (iso_data.istrpd != 0)
    {
      msg << "istrpd != 0\n";
      msg << "this mode is not supported\n";
      msg << "istrpd: " << iso_data.istrpd << '\n';
      raiseFatal();
    }
    recordChange(myFile);
    
    
    iso_data.strpl.reserve(iso_data.ltrn);
    for (unsigned int i{0}; i < iso_data.strpl.capacity(); ++i)
      iso_data.strpl[i].reserve(iso_data.ngroup);
    iso_data.stotpl.reserve(iso_data.ltot);
    for (unsigned int i{0}; i < iso_data.stotpl.capacity(); ++i)
      iso_data.stotpl[i].reserve(iso_data.ngroup);
    iso_data.sngam.reserve(iso_data.ngroup);
    iso_data.sfis.reserve(iso_data.ngroup);
    iso_data.snutot.reserve(iso_data.ngroup);
    iso_data.chiso.reserve(iso_data.ngroup);
    iso_data.snalf.reserve(iso_data.ngroup);
    iso_data.snp.reserve(iso_data.ngroup);
    iso_data.sn2n.reserve(iso_data.ngroup);
    iso_data.snd.reserve(iso_data.ngroup);
    iso_data.snt.reserve(iso_data.ngroup);
    
    iso_data.chiiso.reserve(iso_data.ngroup);
    for (unsigned int i{0}; i < iso_data.chiiso.capacity(); ++i)
      iso_data.chiiso[i].reserve(iso_data.ichi);
    iso_data.isopec.reserve(iso_data.ngroup);


    std::cout << "--- end 4D\n";
    recordChange(myFile);
    matrixRead(myFile,iso_data.strpl);
    matrixRead(myFile,iso_data.stotpl);
    vectorRead(myFile,iso_data.sngam);
    // TO-DO: make sure all xs initialized to 0.0
    if (iso_data.ifis > 0)
    {
      vectorRead(myFile,iso_data.sfis);
      vectorRead(myFile,iso_data.snutot);
    }
    if (iso_data.ichi == 1)
      vectorRead(myFile,iso_data.chiso);
    if (iso_data.ialf > 0)
      vectorRead(myFile,iso_data.snalf);
    if (iso_data.inp > 0)
      vectorRead(myFile,iso_data.snp);
    if (iso_data.in2n > 0)
      vectorRead(myFile,iso_data.sn2n);
    if (iso_data.ind > 0)
      vectorRead(myFile,iso_data.snd);
    if (iso_data.intritium > 0)
      vectorRead(myFile,iso_data.snt);
    recordChange(myFile);
    std::cout << "--- end 5D\n";
    if (iso_data.ichi > 1)
    {
      msg << "this is untested. no file from the test suite has ichi > 1\n";
      raiseWarn();
      recordChange(myFile);
      matrixRead(myFile,iso_data.chiiso);
      vectorRead(myFile,iso_data.isopec);
      recordChange(myFile);
    }

    iso_data.scat.reserve(iso_data.nscmax);
    for (int j{0}; j < iso_data.nscmax; ++j)
    {
      if (iso_data.lord[j] > 0)
      {
        recordChange(myFile);
        int kmax{0};
        for (int k{0}; k < iso_data.ngroup; ++k)
          kmax += iso_data.jband[j][k];
        iso_data.scat[j].reserve(kmax);
        for (unsigned int k{0}; k < iso_data.scat[j].capacity(); ++k)
          iso_data.scat[j][k].reserve(iso_data.lord[j]);
        matrixRead(myFile,iso_data.scat[j]);
        recordChange(myFile);
        std::cout << "--- end 7D\n";
        // TO-DO: .resize(0)
      }
    }



  }






  myFile.close();

  return 0;
}
