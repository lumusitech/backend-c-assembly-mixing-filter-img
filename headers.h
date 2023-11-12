#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef long int SIZE;
typedef FILE IMG;
typedef unsigned char PIXEL;

#define TAMANIO_PIXEL 1
#define NEGRO 0
#define BLANCO 255
#define RESULTADO "resultado.rgb"

void verificarCantParametros(int);
SIZE tamanio(FILE*);
void igualTamanio(SIZE, SIZE, SIZE);
PIXEL mezclar(PIXEL, PIXEL, PIXEL);
void enmascarar_c(PIXEL*, PIXEL*, PIXEL*, SIZE);
extern void enmascarar_asm(PIXEL*, PIXEL*, PIXEL*, SIZE);