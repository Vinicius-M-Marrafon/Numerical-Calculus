/*
 *  Autor: Vinicius Mari Marrafon
 *  Assinatura: ViMM
 *  Data 20/01/22
 *
 *  Funcoes, variaveis e metodos p/ calculo numerico
 * 
 *  C99 + Fortran95
 */

#ifndef NUMERIC_H
#define NUMERIC_H

// Variaveis
// Representacao da matriz p/ Fortran! - Vetor unidimensional (Column-major)
#include <stdint.h>

extern uint8_t PRECISAO;

typedef struct Fmatriz
{
    double *matriz;
    uint32_t colunas, linhas;

    // "Metodos" da estrutura
    void (*ler_matriz)(struct Fmatriz *);
    double *(*setar_pos)(struct Fmatriz *, uint32_t, uint32_t);
    double (*get_pos)(struct Fmatriz *, uint32_t, uint32_t);
    void (*mostrar_matriz)(struct Fmatriz *);
    void (*finalizar)(struct Fmatriz *);
}
Fmatriz;

void criar_matriz_func(Fmatriz *, uint32_t, uint32_t);
void ler_matriz_func(Fmatriz *);
double *setar_pos_func(Fmatriz *, uint32_t, uint32_t);
double get_pos_func(Fmatriz *, uint32_t, uint32_t);
void mostrar_matriz_func(Fmatriz *);
void finalizar_func(Fmatriz *);

// Area de Cronometro
#ifdef __linux__
    #include <time.h>
#elif _WIN32
    #include <time.h>
    #include <sys/time.h>
#endif

extern struct timeval t0, t1;

#define    INICAR_CRONOMETRO gettimeofday(&t0, NULL)
#define FINALIZAR_CRONOMETRO gettimeofday(&t1, NULL)

// Calcula o tempo
double calcular_tempo(struct timeval *t1, struct timeval *t0);

// Funcao p/ validacao de entrada
char *Scanner(uint8_t *);
double ler_linha(void);

// Swap
void swap(double *a, double *b);


#endif //NUMERIC_H