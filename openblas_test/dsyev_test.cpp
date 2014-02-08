/*
Copyright 2014 NAKATA Maho. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY NAKATA Maho ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL NAKATA Maho OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of NAKATA Maho.
*/

#include <iostream>
#include <stdio.h>
#if defined USE_MKL
#include <mkl_lapacke.h>
#else 
#include <lapacke.h>
#endif

//Matlab/Octave format
void printmat(lapack_int N, lapack_int M, double *A, lapack_int LDA)
{
    double mtmp;
    printf("[ ");
    for (lapack_int i = 0; i < N; i++) {
	printf("[ ");
	for (lapack_int j = 0; j < M; j++) {
	    mtmp = A[i + j * LDA];
	    printf("%5.2e", mtmp);
	    if (j < M - 1)
		printf(", ");
	}
	if (i < N - 1)	    printf("]; ");
	else	    printf("] ");
    }
    printf("]");
}

int main()
{
    lapack_int n = 3;
    lapack_int ret;
    double *A = new double[n * n];
    double *w = new double[n];
    //setting A matrix
    A[0 + 0 * n] = 1;    A[0 + 1 * n] = 2;    A[0 + 2 * n] = 3;
    A[1 + 0 * n] = 2;    A[1 + 1 * n] = 5;    A[1 + 2 * n] = 4;
    A[2 + 0 * n] = 3;    A[2 + 1 * n] = 4;    A[2 + 2 * n] = 6;

    printf("A =");    printmat(n, n, A, n);    printf("\n");
    //get Eigenvalue
    ret = LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', n, A, n, w);
    //print out some results.
    printf("#eigenvalues \n");
    printf("w =");    printmat(n, 1, w, 1);    printf("\n");
    printf("#eigenvecs \n");
    printf("U =");    printmat(n, n, A, n);    printf("\n");
    printf("#Check Matlab/Octave by:\n");
    printf("eig(A)\n");
    printf("U'*A*U\n");
    delete[]w;
    delete[]A;
}
