#include "RSoft/RSoft.hpp"
#include "LammpsIO/DumpIO/DumpIO.hpp"
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

int main(int argc, char* argv[])
{

  std::string str_dump, str_RSoftPlane, str_out;
  std::vector<std::string> bc;
  std::vector< std::vector<double> > pos_t, bb_t, SF_t;
  std::vector<int> type_t;
  std::vector<double> s_t;
  int f_start, f_end;

  if(argc!=9)
  {   
    std::cout << "INPUT FORM: './CalcSoft [in_dump] [in_RSoftPlane] ";
    std::cout << "[out_nc] [bc_x] [bc_y] [bc_z] [f_start] [f_end]'\n";
    assert(argc==9);
  }   
  else
  {   
    str_dump = argv[1];
    str_RSoftPlane = argv[2];
    str_out = argv[3];
    bc.push_back(argv[4]);
    bc.push_back(argv[5]);
    bc.push_back(argv[6]);
    f_start = atoi(argv[7]);
    f_end = atoi(argv[8]);
  }  


  // Opens RSoft and DumpIO objects
  RSoft rs;
  std::cout << str_RSoftPlane << "\n";
  rs.OpenPlaneI(str_RSoftPlane);
  std::ifstream read_stream(str_dump.c_str());
  DumpIO dump;
  dump.OpenI(read_stream);
  NetCDFIO nc;
  nc.OpenO(str_out);

  // Skips to correct frame
  for(int f=0; f<f_start; f++)
  {
    dump.LoadNextFrame(read_stream);
  }

  for(int f=f_start; f<f_end; f++)
  {

    std::cout << "frame = " << f-f_start << "/" << f_end-f_start << "\n";
    std::cout << std::flush;

    dump.LoadNextFrame(read_stream);
    dump.SortByID();
    dump.GetPos(pos_t);
    dump.GetBB(bb_t);

    rs.SetPos(pos_t);
    rs.SetBB(bb_t);
    rs.SetBC(bc);
    rs.GetSoftness(s_t);

    nc.SetPos(f-f_start, pos_t);
    nc.SetBB(f-f_start, bb_t);
    nc.Sett(f-f_start, f-f_start);
    nc.SetDataCol(f-f_start, "S", s_t);

  }


  rs.ClosePlaneI();
  nc.CloseO();
}
