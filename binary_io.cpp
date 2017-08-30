# include <iostream>
# include <fstream> // std::ifstream, etc.
# include <sstream> // std::stringstream
# include <iomanip> // std::setprecision

# include <cstdlib>

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
  for (unsigned int i{0}; i < mat[0].capacity(); ++i)
  {
    for (unsigned int j{0}; j < mat.capacity(); ++j)
    {
      bRead(file,mat[j][i]);
    }
  }
}

void holl_arrayRead(std::ifstream &file, std::array<auto,holl_len> &array)
{
  for (unsigned int i{0}; i < array.size(); ++i)
    bRead(file,array[i]);
}

// TO-DO: move this to an output file
void holl_arrayWrite(std::ofstream &file, const std::array<auto,holl_len> &array)
{
  file << '*';
  for (unsigned int i{0}; i < array.size(); ++i)
    file << array[i];
  file << '*';
}

// TO-DO: move this to an output file
void isotxsWrite(const ISOTXS &iso)
{
  std::ofstream outf("wm_format.out");

  // if we couldn't open the output file steream for writing
  if (!outf)
  {
    // print an error and exit
    std::cerr << "hey dummy, sample.dat could not be opened for writing\n";
    exit(1);
  }

  outf << std::scientific;
  outf << std::setprecision(6);
  holl_arrayWrite(outf,iso.hname); 
  outf << "\tHNAME\thollerith file name - ISOTXS\n";
  for (unsigned int i{0}; i < iso.huse.size(); ++i)
  {
    holl_arrayWrite(outf,iso.huse[i]);
    outf << "\tHUSE(" << i << ")\thollerith user identification\n";
  }
  outf << iso.ivers << "\tIVERS\tfile version number\n";
  
  outf << "\nFILE CONTROL    (1D RECORD)\n";
  outf << iso.ngroup << "\tNGROUP\tnumber of energy groups in file\n";
  outf << iso.niso << "\tNISO\tnumber of isotopes in file\n";
  outf << iso.maxup << "\tMAXUP\tmaximum number of upscatter groups\n";
  outf << iso.maxdn << "\tMAXDN\tmaximum number of downscatter groups\n";
  outf << iso.maxord << "\tMAXORD\tmaximum scattering order\n";
  outf << iso.ichist << "\tICHIST\tfile-wide fission spectrum flag\n";
  outf << iso.nscmax << "\tNSCMAX\tmaximum number of blocks of scattering data\n";
  outf << iso.nsblok << "\tNSBLOK\tsubblocking control for scatter matricies\n";
  
  outf << "HSETID\thollerith identification of file\n";
  for (unsigned int i{0}; i < iso.hsetid.size(); ++i)
  {
    holl_arrayWrite(outf,iso.hsetid[i]);
  }
  outf << '\n';
  outf << "HISONM\thollerith isotope label for isotope i\n";
  for (unsigned int i{0}; i < iso.hisonm.capacity(); ++i)
  {
    holl_arrayWrite(outf,iso.hisonm[i]);
    outf << '\n';
  }
  outf << "VEL\tmean neutron velocity in group j [cm/s]\n";
  for (unsigned int g{0}; g < iso.vel.capacity(); ++g)
  {
    outf << iso.vel[g] << '\n';
  }
  outf << "EMAX\tmaximum energy bound of group j [eV]\n";
  for (unsigned int g{9}; g < iso.emax.capacity(); ++g)
  {
    outf << iso.emax[g] << '\n';
  }
  outf << "EMIN\tminimum energy bound of set [eV]\n";
  outf << iso.emin << '\n';
  outf << "LOCA\tnumber of records to be skipped to read data for isotope i\n";
  for (unsigned int i{0}; i <iso.loca.capacity(); ++i)
  {
    outf << iso.loca[i] << '\n';
  }

  outf << std::string(80,'*') << '\n';
  outf << "INDIVIDUAL ISOTOPIC DATA\n";
  outf << std::string(80,'*') << '\n';
  outf << "ISOTOPE CONTROL AND GROUP INDEPENDENT DATA    (4D RECORD)\n";
  holl_arrayWrite(outf,iso.habsid);
  outf << "\tHABSID\thollerith absolute isotope label\n";
  holl_arrayWrite(outf,iso.hident);
  outf << "\tHIDENT\tidentifier of library from which basic data came\n";
  holl_arrayWrite(outf,iso.hmat);
  outf << "\tHMAT\tisotope identification\n";
  outf << iso.amass << "\tAMASS\tgram atomic weight\n";
  outf << iso.efiss << "\tEFISS\ttotal thermal energy yield/fission [W*s/fiss]\n";
  outf << iso.ecapt << "\tECAPT\ttotal thermal energy yield/capture [W*s/capt]\n";
  outf << iso.temp << "\tTEMP\tisotope temperature [K]\n";
  outf << iso.sigpot << "\tSIGPOT\taverage effective potential scattering in resonance range [barns/atom]\n";
  outf << iso.adens << "\tADENS\tdensity of isotoope in mixture in which isotope cross sections were generated (atom/barn/cm)\n";
  outf << iso.kbr << "\tKBR\titoopte classification (see documentation)\n";
  outf << iso.ichi << "\tICHI\tisotope fission spectrum flag\n";
  outf << iso.ifis << "\tIFIS\t(n,f) crosss section flag\n";
  outf << iso.ialf << "\tIALF\t(n,alpha) cross section flag\n";
  outf << iso.inp << "\tINP\t(n,p) cross section flag\n";
  outf << iso.in2n << "\tIN2N\t(n,2n) cross section flag\n";
  outf << iso.ind << "\tIND\t(n,D) cross section flag\n";
  outf << iso.intritium << "\tINT\t(n,T) cross section flag\n";
  outf << iso.ltot << "\tLTOT\tnumber of moments of total cross section provided\n";
  outf << iso.ltrn << "\tLTRN\tnumber of moments of transport cross section\n";
  outf << iso.istrpd << "\tISTRPD\tnumber of coordinate directions .. (must == 0)\n";

  outf << "IDSCT scattering matrix identification for block N\n";
  for (int n{0}; n < iso.nscmax; ++n)
    outf << iso.idsct[n] << '\n';
  outf << "LORD number of scattering orders in block N\n";
  for (int n{0}; n < iso.nscmax; ++n)
    outf << iso.lord[n] << '\n';
  outf << "JBAND number of groups that scatter into group j including self-"
    << "scatter, in scattering block n\n";
  for (int j{0}; j < iso.ngroup; ++j)
  {
    for (int n{0}; n < iso.nscmax; ++n)
    {
      outf << std::setw(4) << iso.jband[j][n] << ' ';
    }
    outf << '\n';
  }
  outf << "IJJ position of in-group scattering cross section in scattering " <<
    "data for group j, scattering block n, counted from the first word of " << 
    "group j data\n";
  for (int j{0}; j < iso.ngroup; ++j)
  {
    for (int n{0}; n < iso.nscmax; ++n)
    {
      outf << iso.ijj[j][n] << ' ';
    }
    outf << '\n';
  }
  outf << "STRPL PL weighted transport cross section\n";
  for (int j{0}; j < iso.ngroup; ++j)
  {
    for (int l{0}; l < iso.ltrn; ++l)
    {
      outf << iso.strpl[j][l] << ' ';
    }
    outf << '\n';
  }
  outf << "STOTPL PL weighted total cross section\n";
  for (int j{0}; j < iso.ngroup; ++j)
  {
    for (int l{0}; l < iso.ltot; ++l)
    {
      outf << iso.stotpl[j][l] << ' ';
    }
    outf << '\n';
  }
  outf << "SNGAM\tSFIS\tSNUTOT\tCHISO\tSNALF\tSNP\tSN2N\tSND\tSNT\n";
  for (int j{0}; j < iso.ngroup; ++j)
    outf << iso.sngam[j] << '\t' << iso.sfis[j] << '\t' << iso.snutot[j] <<
      '\t' << iso.chiso[j] << '\t' << iso.snalf[j] << '\t' << iso.snp[j] << 
      '\t' << iso.sn2n[j] << '\t' << iso.snd[j] << '\t' << iso.snt[j] << '\n';



}

// TO-DO: delete this. it's for debugging.
void dummyIntOut(std::ifstream &file)
{
  for (int i{0}; i < 100; ++i)
  {
    int32_t dummy{0};
    bRead(file,dummy);
    std::cout << dummy << '\n';
  }
}

int main()
{
  // TO-DO: this should be a command line argument
  std::string fname("ISOTXS.u235");
  // fname = "ISOTXS.soft_fuel";
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
  for (unsigned int k{0}; k < iso_data.chi_fw.capacity(); ++k)
    iso_data.chi_fw[k].reserve(iso_data.ngroup);
  iso_data.isspec.reserve(iso_data.ngroup);

  iso_data.idsct.reserve(iso_data.nscmax);
  iso_data.lord.reserve(iso_data.nscmax);
  iso_data.jband.reserve(iso_data.ngroup);
  for (unsigned int j{0}; j < iso_data.jband.capacity(); ++j)
    iso_data.jband[j].reserve(iso_data.nscmax);
  iso_data.ijj.reserve(iso_data.ngroup);
  for (unsigned int j{0}; j < iso_data.ijj.capacity(); ++j)
    iso_data.ijj[j].reserve(iso_data.nscmax);









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

  iso_data.strpl.reserve(iso_data.ngroup);
  iso_data.stotpl.reserve(iso_data.ngroup);
  iso_data.sngam.reserve(iso_data.ngroup);
  iso_data.sfis.reserve(iso_data.ngroup);
  iso_data.snutot.reserve(iso_data.ngroup);
  iso_data.chiso.reserve(iso_data.ngroup);
  iso_data.snalf.reserve(iso_data.ngroup);
  iso_data.snp.reserve(iso_data.ngroup);
  iso_data.sn2n.reserve(iso_data.ngroup);
  iso_data.snd.reserve(iso_data.ngroup);
  iso_data.snt.reserve(iso_data.ngroup);
  // this next loop is for the individual isotopic data
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
    
    
    for (unsigned int i{0}; i < iso_data.strpl.capacity(); ++i)
      iso_data.strpl[i].reserve(iso_data.ltrn);
    for (unsigned int i{0}; i < iso_data.stotpl.capacity(); ++i)
      iso_data.stotpl[i].reserve(iso_data.ltot);

    std::cout << "--- end 4D\n";
    recordChange(myFile);
    for (int32_t j{0}; j < iso_data.ngroup; ++j)
    {
      iso_data.sngam[j]  = 0.0f;
      iso_data.sfis[j]   = 0.0f;
      iso_data.snutot[j] = 0.0f;
      iso_data.chiso[j]  = 0.0f;
      iso_data.snalf[j]  = 0.0f;
      iso_data.snp[j]    = 0.0f;
      iso_data.sn2n[j]   = 0.0f;
      iso_data.snd[j]    = 0.0f;
      iso_data.snt[j]    = 0.0f;
      for (int32_t l{0}; l < iso_data.ltrn; ++l)
        iso_data.strpl[j][l] = 0.0f;
      for (int32_t l{0}; l < iso_data.ltot; ++l)
        iso_data.stotpl[j][l] = 0.0f;
    } 
    matrixRead(myFile,iso_data.strpl);
    matrixRead(myFile,iso_data.stotpl);

    vectorRead(myFile,iso_data.sngam);
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
      iso_data.chiiso.reserve(iso_data.ngroup);
      for (unsigned int i{0}; i < iso_data.chiiso.capacity(); ++i)
        iso_data.chiiso[i].reserve(iso_data.ichi);
      iso_data.isopec.reserve(iso_data.ngroup);
      matrixRead(myFile,iso_data.chiiso);
      vectorRead(myFile,iso_data.isopec);
      recordChange(myFile);
    }

    iso_data.scat.reserve(iso_data.nscmax);
    for (unsigned int n{0}; n < iso_data.scat.capacity(); ++n)
    {
      if (iso_data.lord[n] > 0)
      {
        // do stuff
        recordChange(myFile);
        int kmax{0};
        for (int j{0}; j < iso_data.ngroup; ++j)
        {
          kmax += iso_data.jband[j][n];
        }
        iso_data.scat[n].reserve(kmax);
        for (int k{0}; k < kmax; ++k)
        {
          iso_data.scat[n][k].reserve(iso_data.lord[n]);
        }
        matrixRead(myFile,iso_data.scat[n]);
        recordChange(myFile);
        std::cout << "--- end 7D\n";
      }
    }










  }

  // TO-DO: isotxsWrite(iso_data);
  // there will need to be a separate write for each isotope
  // convieniently (obviously) this will mimic how we create an xsLib
  // we should focus on storing micros and then passing micros & nden to DIF3D
  isotxsWrite(iso_data);




  myFile.close();

  return 0;
}
