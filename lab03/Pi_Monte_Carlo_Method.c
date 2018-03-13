#include <mpi.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define MSG_TAG 100

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    srand(time(NULL));

    int size,rank;
    int *recivArry;
    uint64_t howManyPoints = 100000000;
    uint64_t sumNumberHit;
    double est;
    int i;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0) {
        recivArry = malloc(sizeof(int) * size);        
        for (i=1; i< size; i++) {
            MPI_Recv(&recivArry[i-1], 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Recive %d\n", recivArry[i-1]);
        }
        sumNumberHit = 0;
        for(i = 0; i < (size-1); i++) {
            sumNumberHit += (uint64_t) recivArry[i];
        }
        printf("sumNumberHit = %d\n", sumNumberHit);
        est = 4.0 * (((double) sumNumberHit) / ((double) (howManyPoints*(size-1))));
        printf("Number of Points Used:      %d\n", howManyPoints);
        printf("Estimate of Pi:         %24.16lf\n", est);
        free(recivArry);
    } 
    else {
        int numberHit = 0;
        double x, y;
        int kl;
        for(kl = 0; kl < howManyPoints; kl++) {
            x = ((double) rand()) / ((double) RAND_MAX);
            y = ((double) rand()) / ((double) RAND_MAX);
            if(((x*x) + (y*y)) <= 1) { numberHit++; }
        }
        MPI_Send(&numberHit, 1, MPI_INT, 0, MSG_TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}