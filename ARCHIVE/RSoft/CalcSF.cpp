#include "RSoft/RSoft.hpp"
#include "LammpsIO/DumpIO/DumpIO.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

int main(int argc, char* argv[])
{

  std::string str_dump, str_RSoftSF, str_out;
  std::vector<std::string> bc;
  std::vector< std::vector<double> > pos_t, bb_t, SF_t;
  std::vector<int> type_t;
  int f_start, f_end;

  if(argc!=9)
  {   
    std::cout << "INPUT FORM: './CalcSF [in_dump] [in_RSoftSF] ";
    std::cout << "[out_SF] [bc_x] [bc_y] [bc_z] [f_start] [f_end]'\n";
    assert(argc==9);
  }   
  else
  {   
    str_dump = argv[1];
    str_RSoftSF = argv[2];
    str_out = argv[3];
    bc.push_back(argv[4]);
    bc.push_back(argv[5]);
    bc.push_back(argv[6]);
    f_start = atoi(argv[7]);
    f_end = atoi(argv[8]);
  }  


  // Opens RSoft and DumpIO objects
  RSoft rs;
  rs.OpenSFO(str_out);
  rs.OpenSFI(str_RSoftSF);
  std::ifstream read_stream(str_dump.c_str());
  DumpIO dump;
  dump.OpenI(read_stream);

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
    rs.WriteSFs(f-f_start);
  }


  rs.CloseSFO();
  rs.CloseSFI();
}
