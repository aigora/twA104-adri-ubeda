#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define max 50        //numero de caracteres maximos para la primera entrada
#define INT 6         //numero de intentos
void main() {
	char entrada[10];
	printf("Introduzca su palabra: \n");
		gets(entrada);
		
	//scanf("%s \n",entrada);
	
	int largo,coincidencias=0,i;
	int intentos=6;
	char letra;
	
	largo= strlen(entrada);                                                    //longitud de la cadena
   //printf("%d",largo);                               
	while(intentos>0){                  
		printf("Introduzca una letra: \n");
		scanf("%c",&letra); 
	 
		
	for(i=0;i<largo;i++){                                                      //Recorrer la cadena comparando el caracter introducido 
		if(letra==entrada[i]) coincidencias++;                                 //con el de la palabra	      		         
	}
	printf("%c",letra);
	intentos=intentos-1;
	printf("Quedan %d intentos \n",intentos);                                  //intentos que quedan
	if(coincidencias==(largo)) intentos=0;                                     //Mensaje final	   
	else printf("%d coincidencias.\n",coincidencias);                 //aviso si ha habido coincidencias o no.	
	getchar();
}
    printf("Enhorabuena has ganado");
system("pause");
}
