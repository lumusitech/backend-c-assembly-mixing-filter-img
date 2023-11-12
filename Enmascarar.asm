;######################################################################################
;##################### Trabajo Práctico de Organización del Compurador 2 ######################
;#####################################################################################

section .data

;inicializamos etiqueta con 4 bytes blancos para comparar con las imágenes.
pixeles_blancos 	db	0xFF,0xFF,0xFF,0xFF

;para inicializar en cero el indice de recorrido.
pixel_inicial			db	0x0,

section .text

global enmascarar_asm 

enmascarar_asm: 

;instrucciones para no desestructurar la pila.
    push ebp
    mov ebp,esp

;copiamos a los registros los parametros de la función en su respectivo orden.
    mov eax, [ebp+8]
    mov ecx, [ebp+12]
    mov edx, [ebp+16]

;copiamos los pixeles para comparar.    
    mov edi, [pixeles_blancos]
;inicializamos el registro índice.
    mov esi, [pixel_inicial]
    
;en xmm3 colocaremos los pixeles de la imagen resultado de la combinación.    
recorrer_imagen:

	movd xmm2, [edx+esi]		;xmm2 = dir base de mask
            
	movd xmm1, [ecx+esi]		;xmm1 = dir base de img2
    
    movd xmm0, [eax+esi]    ;xmm0 = dir base de img1  
    
    cmp [edx+esi], edi				;cmp si pixel 0 de mascara es blanco.
    
    je ponerPixel_imgen2			;SI, entonces salta a Pixel de imagen 2
    
    movapd xmm3,xmm0			;NO, entonces xmm3 = valores de imagen 1.
    
    jmp control							;salta a Control de recorrido de imagen.

ponerPixel_imgen2:

    movapd xmm3,xmm1			;xmm3 = valores de imagen 2
    
control:         
    
    add esi, 4								;avanzamos el indice
     
    cmp esi, [ebp+20]				;controlamos si recorrimos toda la imagen.
    
    jle recorrer_imagen			;salta si el valor es menor o igual

;instrucciones para devolver a la pila su estado inicial.
    mov esp,ebp
    pop ebp
    
ret
