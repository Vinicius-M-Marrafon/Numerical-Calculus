! By: Vinicius Mari Marrafon
! Language: Fortran 95
! Signature: ViMM

! Metodo de solucao de sistemas lineares: Gauss Completo

! Parametros da subroutine
! A = matriz
! n = ordem da matriz
! b = termos independentes
! icog = icognitas
! ord  = ordena

subroutine Fortran_Gauss_Completo (A, n, b, icog, ord)
    implicit NONE;

    ! Parametros
    integer, intent(inout):: n, ord(n);
    real * 8, intent(inout):: A(n, n);
    real * 8, intent(inout):: b(n), icog(n);

    ! Iteradores
    integer:: i, j, k;

    ! Variaveis do metodo 
    real * 8:: maior, fator;
    integer:: max_i, max_j;

    ! Ok!
    ! print *, "Matriz recebida na funcao fortran_gauss_completo_";
    ! do i = 1, n
    !     print *, (A(i, j), j = 1, n)
    ! enddo

    do i = 1, (n - 1)
    
        maior = A(i, i);
        max_i = i;
        max_j = i;

        ! Encontrando o maior valor na matriz (A) e sua coordenada
        do j = i, n
            do k = i, n
                if (ABS(A(j, k)) > ABS(maior)) then
                    maior = A(j, k);
                    max_i = j;
                    max_j = k;
                endif 
            enddo
        enddo

        ! Trocar linhas se necessario for
        if (.not. (max_i .eq. i)) then
            do j = 1, n
                A(i, j) = A(i, j) + A(max_i, j)
                A(max_i, j) = A(i, j) - A(max_i, j)
                A(i, j) = A(i, j) - A(max_i, j);
            enddo

            b(i) = b(i) + b(max_i);
            b(max_i) = b(i) - b(max_i);
            b(i) = b(i) - b(max_i);
            
        endif

        ! Trocar colunas se necessario for
        if (.not. (max_j .eq. i)) then
            icog(i) = icog(i) + icog(max_j);
            icog(max_j) = icog(i) - icog(max_j);
            icog(i) = icog(i) - icog(max_j);

            ord(i) = ord(i) + ord(max_j);
            ord(max_j) = ord(i) - ord(max_j);
            ord(i) = ord(i) - ord(max_j);

            do j = 1, n
                A(j, i) = A(j, i) + A(j, max_j)
                A(j, max_j) = A(j, i) - A(j, max_j)
                A(j, i) = A(j, i) - A(j, max_j);
            enddo
        endif

        ! Soma das linhas
        do j = i + 1, n
            fator = - (A(j, i)/ A(i, i));
            do k = i, n 
                A(j, k) = A(j, k) + (fator * A(i, k));
            enddo
            b(j) = b(j) + (fator * b(i));
        enddo
    enddo

    ! do i = 1, n
    !     print *, (A(i, j), j = 1, n)
    ! enddo

end subroutine Fortran_Gauss_Completo