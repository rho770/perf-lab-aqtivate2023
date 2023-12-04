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

void mmul_ref(double *z, double *x, double *y, int n)
{
    for (int n0 = 0; n0 < n; n0++)
        for (int n1 = 0; n1 < n; n1++)
        {
            z[n*n0+n1] = x[n*n0+0] * y[n*0+n1];
            for (int n2 = 1; n2 < n; n2++)
                z[n*n0+n1] += x[n*n0+n2] * y[n*n2+n1];
        }

    return;
}

void mmul_block1(double *z, double *x, double *y, int n, int b)
{
    for (int b0 = 0; b0 < n/b; b0++)
        for (int b1 = 0; b1 < n/b; b1++)
        {
            for (int n0 = 0; n0 < b; n0++)
                for (int n1 = 0; n1 < b; n1++)
                {
                    z[n*(b*b0+n0)+(b*b1+n1)] = x[n*(b*b0+n0)+(b* 0+ 0)] *
                                               y[n*(b* 0+ 0)+(b*b1+n1)];
                    for (int n2 = 1; n2 < b; n2++)
                        z[n*(b*b0+n0)+(b*b1+n1)] += x[n*(b*b0+n0)+(b* 0+n2)] *
                                                    y[n*(b* 0+n2)+(b*b1+n1)];
                }

            for (int b2 = 1; b2 < n/b; b2++)
                for (int n0 = 0; n0 < b; n0++)
                    for (int n1 = 0; n1 < b; n1++)
                        for (int n2 = 0; n2 < b; n2++)
                            z[n*(b*b0+n0)+(b*b1+n1)] += x[n*(b*b0+n0)+(b*b2+n2)] *
                                                        y[n*(b*b2+n2)+(b*b1+n1)];
        }

    return;
}

void mmul_block2(double *z, double *x, double *y, int n, int b)
{
    for (int b0 = 0; b0 < n/b; b0++)
        for (int b1 = 0; b1 < n/b; b1++)
        {
            for (int n0 = 0; n0 < b; n0++)
                for (int n1 = 0; n1 < b; n1++)
                {
                    z[n*(b*b0+n0)+(b*b1+n1)] = x[n*(b*b0+n0)+(b* 0+ 0)] *
                                               y[n*(b* 0+ 0)+(b*b1+n1)];
                    for (int n2 = 1; n2 < b; n2++)
                        z[n*(b*b0+n0)+(b*b1+n1)] += x[n*(b*b0+n0)+(b* 0+n2)] *
                                                    y[n*(b* 0+n2)+(b*b1+n1)];
                }
        }

    for (int b0 = 0; b0 < n/b; b0++)
        for (int b1 = 0; b1 < n/b; b1++)
        {
            for (int b2 = 1; b2 < n/b; b2++)
                for (int n0 = 0; n0 < b; n0++)
                    for (int n1 = 0; n1 < b; n1++)
                        for (int n2 = 0; n2 < b; n2++)
                            z[n*(b*b0+n0)+(b*b1+n1)] += x[n*(b*b0+n0)+(b*b2+n2)] *
                                                        y[n*(b*b2+n2)+(b*b1+n1)];
        }

    return;
}