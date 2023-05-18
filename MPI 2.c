#include <mpi.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
        int my_rank, N, comm_size, i;
        double buf;
        double summ = 0;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
        N = atoi(argv[1]);
        if (argc != 2)
                printf("bad way\n");
        else if (argc == 2)
                if (!my_rank)
                {
                        //printf("Я главный %d", N);
                        for (i = 1; i < comm_size; i++)
                        {
                                MPI_Recv(&buf, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                                summ += buf;
                        }
                        printf("summ is : %f\n", summ);

                }
                else
                {
                        for (i = (my_rank-1)*N / (comm_size-1) + 1; i <= (my_rank)* N / (comm_size-1); i++)
                        {
                                //printf("i == %d", i);
                                summ +=(double) 1/ (double) i;
                        }

                        MPI_Send(&summ, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
                }
        //printf(" my rank is %d ; my summ is %d\n", my_rank, summ);
        MPI_Finalize();
}

//2.c