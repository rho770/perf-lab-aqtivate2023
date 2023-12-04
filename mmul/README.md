# AQTIVATE Training Workshop: Performance Engineering Lab / Matrix Multiplication

## Introduction

The goal of this lab is to familiarise with the concepts of performance engineering. For this purpose, a simple numerical task is considered, namely the multiplication of two dense matrices, i.e. the operation $z \rightarrow x * y$ where *x*, *y* and *z* are densely populated square matrices of size *N*.

The following implementations of the numerical problem are provided:

- C programmers: [c/main.c](c/main.c), [c/mmul.c](c/mmul.c)
- Fortran programmers: [f90/main.f90](f90/main.f90), [f90/mmul.f90](f90/mmul.f90)

In the next section we formulate a set of tasks and questions that need to be addressed for completing this lab. We will ask you to use the performance analysis tool Scalasca. Practical information for how to use Scalasca is provided with the [General Instructions](../README.md) for this lab.

## Tasks and questions

For this lab, answer the following questions and address the following tasks:

1) Compute the arithmetic intensity for the numerical task $z \leftarrow x \cdot y$ as a function of the matrix size *N*. Assume the elements of the square matrices to be double precision numbers of size 8 Byte. Ignore the existence of caches.
2) Argue whether the application is compute performance or memory bandwidth limited.
3) Repeat this analysis for the cache blocked implementations of the numerical tasks (see functions/subroutines ``mmul_block1`` and/or ``mmul_block2``) and compute the arithmetic intensity as a function of the matrix size *N* and block size *B* under the assumption that the caches are large enough to hold at least one full block of each of the 3 matrices.
4) Use performance tools to collect performance figures for each task implementation of the numerical task (``mmul_ref``, ``mmul_block1``, ``mmul_block2``). Consider the following performance counters: cache counters, number of instructions, number of cycles. Select *N*=256 and choose different block sizes *B*. Compile the application using the options ``-O3 -march=native``. Explore the following questions:
   - Which is the optimal block size?
   - What level of Instructions per Cycle (IPC) is reached? Is this value large for the given processor architecture?
   - What fraction of the peak performance of the processor core is achieved?
5) How do the results obtained in task #4 compare to the theoretical results obtained in task #3? What could explain the deviations? (Hint: Review the assumptions that had been made for task #3.)
6) For (*N*,*B*)=(256,16) compile the code using different optimisation levels, i.e. ``-O0`` (no optimisation), ``-O1``, ``-O3``, and compare the results in terms of time spent in each kernel and number of instructions.
7) Bonus question: Did the compiler generate SIMD instructions? Hint: Use the compiler option ``-S`` to produce an assembler version of numerical task implementations.
