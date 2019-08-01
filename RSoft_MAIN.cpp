#include "RSoft/RSoft.hpp"
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

int main(int argc, char* argv[])
{

  std::string str_read, str_RSoftSF, str_out;
  std::vector<std::string> bc;
  std::vector< std::vector<double> > pos_t, bb_t, SF_t;
  std::vector<double> radius_t;
  std::vector<int> type_t;
  int n_f;

  if(argc!=6)
  {   
    std::cout << "INPUT FORM: './CalcSFAllTimesteps [in_nc] [in_RSoftSF] ";
    std::cout << "[out_SF] [bc_x] [bc_y]'\n";
    assert(argc==6);
  }   
  else
  {   
    str_read = argv[1];
    str_RSoftSF = argv[2];
    str_out = argv[3];
    bc.push_back(argv[4]);
    bc.push_back(argv[5]);
  }  


  // Opens RSoft and DumpIO objects
  RSoft rs;
  rs.OpenSFO(str_out);
  rs.OpenSFI(str_RSoftSF);
  NetCDFIO nc;
  nc.OpenI(str_read);
  n_f = nc.NumFrames();

  for(int f=0; f<n_f; f++)
  {

    std::cout << "frame = " << f << "/" << n_f << "\n";
    std::cout << std::flush;

    nc.GetPos(f, pos_t);
    nc.GetBB(f, bb_t);

    rs.SetPos(pos_t);
    rs.SetBB(bb_t);
    rs.SetBC(bc);
    rs.WriteSFs(f);
  }


  nc.CloseI();
  rs.CloseSFO();
  rs.CloseSFI();
}
