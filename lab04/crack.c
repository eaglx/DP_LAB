//#include <mpi.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 4 literowe
aa5UYq6trT5u.
bahAZ9Hk7SCf6
ddoo3WocSpthU
jkmD2RlhoMyuA
zzm4NUIIb7VIk
kkv864igyJC9o

5 literowe
aaSPfLTmjh3fU

6 literowe
aaLTdQr7DyHuU 
*/

char *stro="aa5UYq6trT5u.";


int main(int argc, char **argv)
{
    //MPI_Init(&argc, &argv);

    int size,rank;
    //MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //MPI_Comm_size(MPI_COMM_WORLD, &size);

    char salt[3]={0};
    salt[0]=stro[0];
    salt[1]=stro[1];

    /* Ten fragment kodu nalezy _jakos_ zrównoleglić */
    /* pewnie będzie potrzebna jakaś pętla... */
    int i,j,k,l;
    char cmp[5]={0};
    cmp[4] = '\0';
    for(i = 97; i < 123; i++){
        cmp[0] = i;
        for(j = 97; j < 123; j++) { 
            cmp[1] = j;
            for(k = 97; k < 123; k++) {
                cmp[2] = k;
                for(l = 97; l < 123; l++) {
                    cmp[3] = l;
                    char * x = crypt(cmp, salt);
                    if ((strcmp(x,stro))==0)
                    {
                        /* w docelowej wersji przeslac odgadnięte hasło masterowi */
	                    printf("Udalo sie: %s %s %s\n", cmp, x, stro);
                        //MPI_Finalize();
	                    exit(0);
                    }
                }
            }
        }
    }
    
   /* Koniec fragmentu kodu */

    //MPI_Finalize();
}
