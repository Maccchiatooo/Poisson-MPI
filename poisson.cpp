#include "poisson.hpp"
#include <math.h>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <fstream>

double u_init(double x, double y)
{
    double pi = 3.1415926;
    double value = sin(pi * x * y);
    return value;
}

//Poisson2d::Poisson2d()
//{
//}

void Poisson2d::init(MPI_Comm &cart_comm)
{
    double phi_x;
    double phi_y;
    int *g_x, *g_y;

    for (int i = local_x_start; i < local_x_end; i++)
    {
        for (int j = local_y_start; j < local_y_end; j++)
        {
            phi_x = i * dx;
            phi_y = j * dy;
            if (i == 0 || i == m_len[0] || j == 0 || j == m_len[1])
            {
                this->m_fb[i][j] = u_init(phi_x, phi_y);
            }
            else
                this->m_fb[i][j] = 0.0;
        }
    }
}
