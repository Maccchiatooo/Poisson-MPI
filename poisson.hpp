#ifndef _poisson_H_
#define _poisson_H_

#include <mpi.h>
#include <fstream>
#define ghost 2
class Poisson2d
{
    double dx, dy;

public:
    Poisson2d(int rank, int *global_length, int x, int y, int *cart_num_proc)
        : m_rank(rank),
          m_len(global_length),
          m_x(x),
          m_y(y),
          m_cart(cart_num_proc)
    {

        dx = 1.0 / (global_length[0] - 1);
        dy = 1.0 / (global_length[1] - 1);
        local_lenx = m_len[0] / m_cart[0];
        local_leny = m_len[1] / m_cart[1];

        local_x_start = x * local_lenx;
        local_x_end = local_x_start + m_len[0] / m_cart[0] - 1;
        local_y_start = y * local_leny;
        local_y_end = local_y_start + m_len[1] / m_cart[1] - 1;
    }
    void init(MPI_Comm &cart_comm);

    void exchange();
    void update();
    void output();

    int m_rank, m_x, m_y;
    double local_x_start, local_y_start;
    double local_x_end, local_y_end;
    int local_lenx, local_leny;
    int *m_len;
    int *m_cart;
    double m_up, m_down, m_left, m_right = 0;
    double m_cellvalue = 0;
    double **m_fb;

    double *m_rcvBufferLast = NULL;
    double *m_rcvBufferCurrent = NULL;
};

#endif