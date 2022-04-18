
#include <stdio.h>
#include <stdlib.h>

#include "..\..\Libs\numeric.h"

// Especificando sub-rotina do fortran (fgauss_completo.f95)
void fortran_gauss_completo_(double *A, int *n, double *b, double *icog, int *ord);

int main( void )
{
	register int i, j;
	unsigned *ordena, ordem; // inteiro = natural
	Fmatriz matriz;
	double *termos_in, *icognitas; // termos independentes e icogintas
	double somas = 0.00;

	// Ler a ordem da matriz c/ validacao
	puts("Digite a Ordem da matriz.");
	ordem = ler_linha();

	// "Inicializar" a matriz -> representada atraves de um vetor
	criar_matriz_func(&matriz, ordem, ordem);

	// Alocacoes: Vetor p/ Ordenacao, termos_independentes, icognitas
	ordena = (unsigned *)malloc( ordem * sizeof(unsigned));
	if (ordena == NULL)
	{
		puts("Falha na alocacao de memoria Programa abortado");
		exit(3);
	}

	termos_in = (double *)malloc(ordem * sizeof(double));
	if (termos_in == NULL)
	{
		puts("Falha na alocacao de memoria Programa abortado");
		exit(4);
	}

	icognitas = (double *)malloc(ordem * sizeof(double));
	if (icognitas == NULL)
	{
		puts("Falha na alocacao de memoria Programa abortado");
		exit(5);
	}

	// Chamada do metodo ler matriz
	matriz.ler_matriz(&matriz);

	puts("Digite os Termos independentes.");
	for (i = 0; i < ordem; i++)
	{
		termos_in[i] = ler_linha();
		ordena[i] = i; // Aproveitando o loop para atribuição de valores em ordena
	}
	
    // matriz.mostrar_matriz(&matriz);

	// Cronometro p/ o Gauss Completo sem a retro solucao!
    INICAR_CRONOMETRO;
	fortran_gauss_completo_(matriz.matriz, &ordem, termos_in, icognitas, ordena);
    FINALIZAR_CRONOMETRO;

	puts("\n");
	puts("Matriz Triangular correspondente");
	for( i = 0; i < ordem; i++ )
		for( j = 0; j < ordem; j++ )
		{
			j < ordem -1?
			printf("%.*lf ", PRECISAO, matriz.get_pos(&matriz, j, i)) : 
			printf("%.*lf = %.*lf\n", PRECISAO, matriz.get_pos(&matriz, j, i), PRECISAO, termos_in[i] ); 
		}
	puts("\n");

	
	// Solução de sistemas triângulares //
	for (i =( ordem - 1 ); i >= 0; --i)
	{
		somas = 0.00;
		for (j = i + 1; j < ordem; j++)
            somas += (icognitas[j] * matriz.get_pos(&matriz, j, i));
		
		icognitas[i] = (termos_in[i] - somas )/ matriz.get_pos(&matriz, i, i);
	}

	puts("Solucao");
	// Mostrar Solução
	for (i = 0; i < ordem; i++)
		for (j = 0; j < ordem; j++)
			if (ordena[j] == i)
			{
				printf("(%.*lf)\n", PRECISAO, icognitas[j] );
				break;
			}

    printf("Tempo de execucao: %lf\n", calcular_tempo(&t1, &t0));
    
	free(ordena);
	free(icognitas);
	free(termos_in);

	matriz.finalizar(&matriz);

	return 0;
}