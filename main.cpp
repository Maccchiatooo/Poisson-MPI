#include <mpi.h>
#include "poisson.hpp"
#include <iostream>
#include <unistd.h>
#include <stdexcept>
#define dim 2
int main(int argc, char *argv[])
{
    int rank, process;
    int px, py;
    int coord[dim];
    int cart_num_proc[dim];
    int config_e;
    int global_length[dim];
    MPI_Comm cart_comm;
    int cmax = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &process);
    printf("rank %d\n", rank);

    global_length[0] = 25;
    global_length[1] = 25;

    for (int i = 1; i < process; i++)
    {
        if (process % i == 0)
        {
            px = i;
            py = process / i;
            config_e = 1. / (2. * (global_length[1] * (px - 1) / py + global_length[0] * (py - 1) / px));
        }
        if (config_e >= cmax)
        {
            cmax = config_e;
            cart_num_proc[0] = px;
            cart_num_proc[1] = py;
        }
    }
    int periodic[2] = {1, 1};
    int reorder = 0;

    MPI_Cart_create(MPI_COMM_WORLD, 2, cart_num_proc, periodic, reorder, &cart_comm);
    MPI_Comm_rank(cart_comm, &rank);
    MPI_Cart_coords(cart_comm, rank, 2, coord);
    int x = coord[0];
    int y = coord[1];
    Poisson2d p2(rank, global_length, x, y, cart_num_proc);

    p2.init(cart_comm);

    //for (int i = 1; i < 50; i++)
    // {
    //   p2.exchange();
    // p2.update();
    //MPI_Barrier(MPI_COMM_WORLD);
    //}
}
