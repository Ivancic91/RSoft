#include "MDTools.hpp"
#include <math.h>
#include "../VectorTools/VectorTools.hpp"

void MDTools::GetCellPos(
    std::vector< std::vector<double> >& bb_t,
    double R_c,
    std::vector< std::vector<double> >& cell_pos_arr,
    double& L_cut_cell)
{

    // Initialize parameters
    int n_cells_tot, cell_idx;
    double L;
    std::vector<double> filler_vec, cell_pos;
    VectorTools vtool;
    vtool.Clear2DVec(cell_pos_arr);
    n_cells.clear();
    cell_lengths.clear();

    // Determine cell size
    L_cut_cell = 0.0;
    for(int dd=0; dd<d; dd++)
    {
        L = bb_t[dd][1] - bb_t[dd][0];

        // number of cells
        n_cells.push_back(int(L/R_c));
        if(n_cells[dd] < 3)
        {
             n_cells[dd] = 3;
        }

        // length of each cell dimension
        cell_lengths.push_back(L/double(n_cells[dd]));
        L_cut_cell += 0.25*cell_lengths[dd]*cell_lengths[dd];
    }

    L_cut_cell = sqrt(L_cut_cell);

    // Reserve space for particles_cell
    n_cells_tot = 1;
    for(int dd=0; dd<d; dd++)
    {
            n_cells_tot *= n_cells[dd];
    }

    // Initialize particles_cell
    for(int cell=0; cell<n_cells_tot; cell++)
    {
            cell_pos_arr.push_back(filler_vec);
    }

    // Reserve space for particles_cell
    n_cells_tot = 1;
    for(int idx_x=0; idx_x<n_cells[0]; idx_x++)
    {
        for(int idx_y=0; idx_y<n_cells[1]; idx_y++)
        {
            for(int idx_z=0; idx_z<n_cells[2]; idx_z++)
            {

                cell_pos.clear();
                cell_pos.push_back(bb_t[0][0] + (0.5+idx_x)*cell_lengths[0]);
                cell_pos.push_back(bb_t[1][0] + (0.5+idx_y)*cell_lengths[1]);
                cell_pos.push_back(bb_t[2][0] + (0.5+idx_z)*cell_lengths[2]);

                Stack(cell_pos, bb_t, cell_idx);
                cell_pos_arr[cell_idx] = cell_pos;

            }
        }
    }
}
