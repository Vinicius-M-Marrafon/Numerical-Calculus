/*
 *  Autor: Vinicius Mari Marrafon
 *  Assinatura: ViMM
 *  Data 20/01/22
 *
 *  Funcoes, variaveis e metodos p/ calculo numerico
 * 
 *  C99 + Fortran95
 */
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <time.h>


#include "numeric.h"

#define  TRUE   1
#define FALSE   0


uint8_t PRECISAO = 3;
struct timeval t1, t0;

// Cronometro
double calcular_tempo(struct timeval *t1, struct timeval *t0)
{
    return (double)(t1->tv_usec - t0->tv_usec) / 1e6 + (double)(t1->tv_sec - t0->tv_sec);
}

// Implementacao dos metodos da estrutura Fmatriz
void ler_matriz_func(Fmatriz *fm)
{
    printf("Digite os coeficientes da Fmatriz\n");
    for (uint16_t i = 0; i < fm->colunas; i++)
        for (uint16_t j = 0; j < fm->linhas; j++)
            fm->matriz[(j * fm->colunas) + i] = ler_linha();
}

double *setar_pos_func(Fmatriz *fm, uint32_t lin, uint32_t col)
{
    return &fm->matriz[(lin * fm->colunas) + col];
}

double get_pos_func(Fmatriz *fm, uint32_t lin, uint32_t col)
{
    return fm->matriz[(lin * fm->colunas) + col];
}

void mostrar_matriz_func(Fmatriz *fm)
{
    for (uint16_t i = 0; i < fm->colunas; i++)
    {
        printf("- In C - ");

        for (uint16_t j = 0; j < fm->linhas; j++)
            printf("%.*lf ", PRECISAO, fm->matriz[(j * fm->colunas) + i]);
        
        printf("\t - In Fortran -\t");

        for (uint16_t j = 0; j < fm->linhas; j++)
            printf("%.*lf ", PRECISAO, fm->matriz[(i * fm->colunas) + j]);

        printf("\n");
    }
}

void finalizar_func(Fmatriz *fm)
{
    // Destruir matriz
    free(fm->matriz);
    fm->linhas = fm->colunas = 0;
    printf("Fmatriz finalizada com sucesso!\n");
}

void criar_matriz_func(Fmatriz *fm, uint32_t col, uint32_t lin)
{
    fm->colunas = col;
    fm->linhas  = lin;

    fm->matriz = (double *)malloc((col * lin)* sizeof(double));
    if (fm->matriz == NULL)
    {
        fm->colunas = fm->linhas = 0;
        fprintf(stderr, "Falha na alocacao de memoria! - numeric.c:88\n");
        exit(1);
    }

    printf("Fmatriz inicializada com sucesso!\n");

    fm->ler_matriz = ler_matriz_func;
    fm->setar_pos  = setar_pos_func;
    fm->get_pos    = get_pos_func;
    fm->mostrar_matriz = mostrar_matriz_func;
    fm->finalizar  = finalizar_func;
}

// Implementacao de funcao p/ validacao de entrada
// - aceita apenas valores reais -
char *Scanner(uint8_t *prec)
{
    char *buffer = NULL;
    uint32_t pos = 0, length = 0;
    _Bool c = FALSE;
    char in;

    while (( in = fgetc(stdin)) != '\n' && in != ' ' && in != EOF)
    {
        if (pos + 1 > length)
        {
            if (length == 0) length = 32;
            else if (length < INT_MAX/ 2) length *= 2;
            else
            {
                printf("Buffer Overflow\n");
                free(buffer);
                return NULL;
            }

            char *new_buffer = realloc(buffer, length * sizeof(char));

            buffer = new_buffer;
        }

        if (c == TRUE && ('0' <= in && in <= '9'))
            ( *prec )++;

        buffer[pos++] = in;

        if (in == '.') c = TRUE;
    }

    if (buffer == NULL && in == EOF) return NULL;

    char *minimal = (char *)malloc((pos + 1)* sizeof(char));
    strncpy(minimal, buffer, pos);
    minimal[pos] = '\0';
    
    free(buffer);

    return minimal;
}

double ler_linha(void)
{
    while (TRUE)
    {
        char *input;
        uint8_t input_precision = 0;

        input = Scanner(&input_precision);

        double number;
        char  checker;

        if (sscanf(input, "%lf %c", &number, &checker) == 1)
        {
            if (input_precision > PRECISAO) 
                PRECISAO = input_precision;

            free(input);
            return number;
        }

        printf("\rRetry: ");
        input_precision = 0;
    }
}

void swap(double *a, double *b)
{
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}