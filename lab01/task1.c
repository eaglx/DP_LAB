#include <mpi.h>
#include <stdio.h>

#define ROOT 0
#define MSG_TAG 100

int main(int argc, char **argv)
{
	int i, size, tid;
	MPI_Status status;

	MPI_Init(&argv, &argv);

	printf("Checking!\n");
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &tid);
	printf("My id is %d from %d\n", tid, size);

	i = 1;
	if(tid == ROOT)
	{
		MPI_Send(&i, 1, MPI_INT, i, MSG_TAG, MPI_COMM_WORLD);
		printf("## Send %d to %d\n", i, i);
		MPI_Recv(&i, 1, MPI_INT, size - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("## Reciv number %d from %d\n", i, status.MPI_SOURCE);
	}
	else
	{
		MPI_Recv(&i, 1, MPI_INT, tid-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		i += 1;
		i %= size;
		MPI_Send(&i, 1, MPI_INT, i, MSG_TAG, MPI_COMM_WORLD);
		printf("#### Send %d to %d\n", i, i);
	}

	MPI_Finalize();
}
