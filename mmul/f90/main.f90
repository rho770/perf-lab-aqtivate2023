! Copyright (c) 2021, Dirk Pleiter, KTH
!
! Redistribution and use in source and binary forms, with or without
! modification, are permitted provided that the following conditions
! are met:
!  * Redistributions of source code must retain the above copyright
!    notice, this list of conditions and the following disclaimer.
!  * Redistributions in binary form must reproduce the above copyright
!    notice, this list of conditions and the following disclaimer in the
!    documentation and/or other materials provided with the distribution.
!  * Neither the name of NVIDIA CORPORATION nor the names of its
!    contributors may be used to endorse or promote products derived
!    from this software without specific prior written permission.
!
! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
! EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
! PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
! CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
! EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
! PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
! OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
! (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
! OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

program mmul

    implicit none

    integer, parameter                          :: N = 256      ! matrix size
    integer, parameter                          :: B = 16       ! block size
    integer, parameter                          :: M = 100      ! number of kernel executions
    real(kind=8), dimension(:,:), allocatable   :: x
    real(kind=8), dimension(:,:), allocatable   :: y
    real(kind=8), dimension(:,:), allocatable   :: z
    integer                                     :: i, j

    allocate(x(n,n), y(n,n), z(n,n))

    ! Initialise input matrices
    do j = 1, N
        do i = 1, N
            x(i,j) = N * i + j
            y(i,j) = -1.0 * x(i,j)
        end do
    end do

    ! Compute z <- x * y
    write(*,*) '>>> Start benchmark (N=', N, ', B=', B, ', M=', M, ')'

    write(*,*) '    mmul_ref'
    do i = 1, M
        call mmul_ref(z, x, y, N)
    end do

    write(*,*) '    mmul_block1'
    do i = 1, M
        call mmul_block1(z, x, y, N, B)
    end do

    write(*,*) '    mmul_block2'
    do i = 1, M
        call mmul_block2(z, x, y, N, B)
    end do

    write(*,*) '    completed'

    ! Clean-up
    deallocate(x, y, z);

end program