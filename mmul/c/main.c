/*
 * Copyright (c) 2021, Dirk Pleiter, KTH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifndef N
#define N 256            // Matrix size
#endif

#ifndef B
#define B 16            // Block size (N must be multiple of B)
#endif

#define M 100           // Number of kernel executions

void mmul_ref(double *, double *, double *, int);
void mmul_block1(double *, double *, double *, int, int);
void mmul_block2(double *, double *, double *, int, int);

int main()
{
    double *x;
    double *y;
    double *z;

    x  = (double*) malloc(N * N * sizeof(double));
    y  = (double*) malloc(N * N * sizeof(double));
    z  = (double*) malloc(N * N * sizeof(double));

    assert(N%B == 0);

    // Initialise input matrices
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            x[N*i+j] = (double) (N * i + j);
            y[N*i+j] = -1.0 * x[N*i+j];
        }

    // Compute z <- x * y
    printf(">>> Start benchmark (N=%d, B=%d, M=%d)\n", N, B, M);

    printf ("    mmul_ref()\n");
    for (int m = 0; m < M; m++)
        mmul_ref(z, x, y, N);

    printf ("    mmul_block1()\n");
    for (int m = 0; m < M; m++)
        mmul_block1(z, x, y, N, B);

    printf ("    mmul_block2()\n");
    for (int m = 0; m < M; m++)
        mmul_block2(z, x, y, N, B);

    printf ("    completed\n");

    // Clean-up
    free(x);
    free(y);
    free(z);

    return 0;
}
