# ifndef ISOTXS_STRUCTH
# define ISOTXS_STRUCTH


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

  std::array<char,holl_len> habsid;
  std::array<char,holl_len> hident;
  std::array<char,holl_len> hmat;
  float amass;
  float efiss;
  float ecapt;
  float temp;
  float sigpot;
  float adens;
  int32_t kbr;
  int32_t ichi;
  int32_t ifis;
  int32_t ialf;
  int32_t inp;
  int32_t in2n;
  int32_t ind;
  int32_t intritium;
  int32_t ltot;
  int32_t ltrn;
  int32_t istrpd;
  std::vector<int32_t> idsct;
  std::vector<int32_t> lord;
  std::vector<std::vector<int32_t>> jband;
  std::vector<std::vector<int32_t>> ijj;

  std::vector<std::vector<float>> strpl;
  std::vector<std::vector<float>> stotpl;
  std::vector<float> sngam;
  std::vector<float> sfis;
  std::vector<float> snutot;
  std::vector<float> chiso;
  std::vector<float> snalf;
  std::vector<float> snp;
  std::vector<float> sn2n;
  std::vector<float> snd;
  std::vector<float> snt;

  std::vector<std::vector<float>> chiiso;
  std::vector<float> isopec;

  std::vector<std::vector<std::vector<float>>> scat; // yeah, it's 3D
};




# endif
