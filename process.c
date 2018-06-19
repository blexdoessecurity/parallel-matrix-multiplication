#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

long double calc(int total, int start, int iterations);
int main(int argc, char **argv) {
    long double pi, total;


    long totaliterations = 1000;
    long iterations = 100;

    MPI_init(&argc, &argv);

    while(1) {
        total = 0.0;
        long long CURRENT;
        MPI_Status status;
        MPI_recv(&CURRENT, 1, MPI_LONG_LONG, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(!status) sprintf(STDERR, "Error on recv\n");

        for(int current = CURRENT; current<totaliterations; current+=iterations){
            printf("total %ld, current, %d, iterations %ld, total %Lf\n",totaliterations,current,iterations,total);
            total+= calc(totaliterations, current, iterations);
        }

        MPI_send(&total, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    return 0;
}

long double calc(int totaliterations, int current, int iterations){
    long double a,b,c,calc = 0.0;
    for (long i=current; i<current+iterations; i++) {
        c = ((long double)i - 0.5) / ((long double)totaliterations);
        b = pow(c, 2.0);
        a = 1.0 + b;
        calc += 1.0/a;
    }
    return calc;
}
