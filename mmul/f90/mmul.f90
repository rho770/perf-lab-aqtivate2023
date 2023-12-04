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

subroutine mmul_ref(z, x, y, n)

    implicit none

    integer, intent(in)                         :: n
    real(kind=8), intent(out), dimension(n,n)   :: z
    real(kind=8), intent(in), dimension(n,n)    :: x
    real(kind=8), intent(in), dimension(n,n)    :: y
    integer                                     :: n0, n1, n2

    do n1 = 1, n
        do n0 = 1, n
            z(n0,n1) = x(n0,1) * y(1,n1)
            do n2 = 2, n
                z(n0,n1) = z(n0,n1) + x(n0,n2) * y(n2,n1)
            end do
        end do
    end do

end subroutine


subroutine mmul_block1(z, x, y, n, b)

    implicit none

    integer, intent(in)                         :: n
    integer, intent(in)                         :: b
    real(kind=8), intent(out), dimension(n,n)   :: z
    real(kind=8), intent(in), dimension(n,n)    :: x
    real(kind=8), intent(in), dimension(n,n)    :: y
    integer                                     :: n0, n1, n2
    integer                                     :: b0, b1, b2

    do b1 = 0, n/b-1
        do b0 = 0, n/b-1

            do n1 = 1, b
                do n0 = 1, b
                    z(b*b0+n0,b*b1+n1) = x(b*b0+n0,b* 0+ 1) * y(b* 0+ 1,b*b1+n1)
                    do n2 = 2, b
                        z(b*b0+n0,b*b1+n1) = z(b*b0+n0,b*b1+n1) + &
                            x(b*b0+n0,b* 0+n2) * y(b* 0+n2,b*b1+n1)
                    end do
                end do
            end do

            do b2 = 1, n/b-1
                do n1 = 1, b
                    do n0 = 1, b
                        do n2 = 1, b
                            z(b*b0+n0,b*b1+n1) = z(b*b0+n0,b*b1+n1) + &
                                x(b*b0+n0,b*b2+n2) * y(b*b2+n2,b*b1+n1)
                        end do
                    end do
                end do
            end do

        end do
    end do

end subroutine


subroutine mmul_block2(z, x, y, n, b)

    implicit none

    integer, intent(in)                         :: n
    integer, intent(in)                         :: b
    real(kind=8), intent(out), dimension(n,n)   :: z
    real(kind=8), intent(in), dimension(n,n)    :: x
    real(kind=8), intent(in), dimension(n,n)    :: y
    integer                                     :: n0, n1, n2
    integer                                     :: b0, b1, b2

    do b1 = 0, n/b-1
        do b0 = 0, n/b-1
            do n1 = 1, b
                do n0 = 1, b
                    z(b*b0+n0,b*b1+n1) = z(b*b0+n0,b*b1+n1) + &
                        x(b*b0+n0,b* 0+ 1) * y(b* 0+ 1,b*b1+n1)
                    do n2 = 2, b
                        z(b*b0+n0,b*b1+n1) = z(b*b0+n0,b*b1+n1) + &
                            x(b*b0+n0,b* 0+n2) * y(b* 0+n2,b*b1+n1)
                    end do
                end do
            end do
        end do
    end do

    do b1 = 0, n/b-1
        do b0 = 0, n/b-1
            do b2 = 1, n/b-1
                do n1 = 1, b
                    do n0 = 1, b
                        do n2 = 1, b
                            z(b*b0+n0,b*b1+n1) = z(b*b0+n0,b*b1+n1) + &
                                x(b*b0+n0,b*b2+n2) * y(b*b2+n2,b*b1+n1)
                        end do
                    end do
                end do
            end do
        end do
    end do

end subroutine