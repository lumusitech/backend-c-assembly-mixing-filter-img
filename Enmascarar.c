#include "headers.h"

extern void enmascarar_asm(PIXEL *pixel_img1, PIXEL *pixel_img2, PIXEL *pixel_mascara, SIZE tamanio);
//extern void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant, unsigned char *result);

int main(int argc, char const *argv[])
{

	system("clear");
	verificarCantParametros(argc);

	///////////////////////////////////////////////////////////////////////////////////

	IMG *img1;
	img1 = fopen(argv[1], "rb");
	if(img1 == NULL){
		printf("No se pudo encontrar la primer imagen en la dirección: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	IMG *img2;
	img2 = fopen(argv[2], "rb");
	if(img2 == NULL){
		printf("No se pudo encontrar la segunda imagen en la dirección: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	IMG *mascara;
	mascara = fopen(argv[3], "rb");
	if(mascara == NULL){
		printf("No se pudo encontrar la imagen máscara en la dirección: %s\n", argv[3]);
		exit(EXIT_FAILURE);
	}

	///////////////////////////////////////////////////////////////////////////////////

	SIZE tamanio_img1 = tamanio(img1);
	SIZE tamanio_img2 = tamanio(img2);
	SIZE tamanio_mascara = tamanio(mascara);

	igualTamanio(tamanio_img1, tamanio_img2, tamanio_mascara);

	PIXEL *pixel_img1 = (PIXEL *) malloc(tamanio_mascara);
	PIXEL *pixel_img2 = (PIXEL *) malloc(tamanio_mascara);
	PIXEL *pixel_mascara = (PIXEL *) malloc(tamanio_mascara);

	///////////////////////////////////////////////////////////////////////////////////
	
	fread(pixel_img1, TAMANIO_PIXEL, tamanio_img1, img1);
	fclose(img1);

	fread(pixel_img2, TAMANIO_PIXEL, tamanio_img2, img2);
	fclose(img2);

	fread(pixel_mascara, TAMANIO_PIXEL, tamanio_mascara, mascara);
	fclose(mascara);

	///////////////////////////////////////////////////////////////////////////////////
	
	static clock_t reloj_inicio_c, reloj_fin_c;
	static double tiempo_ejecucion_c = 0;
	reloj_inicio_c = clock();

    enmascarar_c(pixel_img1, pixel_img2, pixel_mascara, tamanio_mascara);

    reloj_fin_c = clock();
    tiempo_ejecucion_c = (double)(reloj_fin_c - reloj_inicio_c) / CLOCKS_PER_SEC;
    printf("La ejecución en C, ha demorado %f\n", tiempo_ejecucion_c);

	///////////////////////////////////////////////////////////////////////////////////
	
	static clock_t reloj_inicio_asm, reloj_fin_asm;
	static double tiempo_ejecucion_asm = 0;
	reloj_inicio_asm = clock();

    //enmascarar_asm(pixel_img1, pixel_img2, pixel_mascara, tamanio_mascara);
    enmascarar_asm(pixel_img1, pixel_img2, pixel_mascara, tamanio_mascara);

    reloj_fin_asm = clock();
    tiempo_ejecucion_asm = (double)(reloj_fin_asm - reloj_inicio_asm) / CLOCKS_PER_SEC;
    printf("La ejecución en ASSEMBLER, ha demorado %f\n", tiempo_ejecucion_asm);

	///////////////////////////////////////////////////////////////////////////////////

	return 0;

}

//extern enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int ancho, int alto);

void verificarCantParametros(int argc){
	if(argc != 4){
		printf("Debe ingresar las 3 imágenes para procesar, usted ingresó %d\n", (argc-1));
		exit(EXIT_FAILURE);
	}
}

SIZE tamanio(FILE *img) {
  fseek(img, 0, SEEK_END); //se mueve el puntero al fin
  SIZE tamanio = ftell(img); //se pregunta la posición en la que quedó
  fseek(img, 0, SEEK_SET); //se coloca el puntero de nuevo en la posición inicial
  return tamanio;
}

void igualTamanio(SIZE s1, SIZE s2, SIZE s3){
	if(s1 != s3 || s2 != s3){
		puts("ERROR, La resolución de las 3 imágenes debe coincidir");
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////

void enmascarar_c(PIXEL *pixel_img1, PIXEL *pixel_img2, PIXEL *pixel_mascara, SIZE tamanio) {

  FILE *resultado = fopen("resultado.rgb", "wb");
  
  SIZE cursor = 0;

  while(cursor < tamanio){

  	//Se va avanzando pixel por pixel y
  	//Se van guardando los pixeles obtenidos al mezclar
  	*(pixel_img1 + cursor) = mezclar(*(pixel_img1 + cursor), *(pixel_img2 + cursor), *(pixel_mascara + cursor));

  	cursor++;
  }

  fwrite(pixel_img1, TAMANIO_PIXEL, tamanio, resultado);
  fclose(resultado);

}

PIXEL mezclar(PIXEL pixel_img1, PIXEL pixel_img2, PIXEL pixel_mascara) {
  if(pixel_mascara == NEGRO) return pixel_img1;
  if(pixel_mascara == BLANCO) return pixel_img2;
}
