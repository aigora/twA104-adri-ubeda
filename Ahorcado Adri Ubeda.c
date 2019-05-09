#define _CRT_SECURE_NO_WARNINGS  //Evitar la sintaxis de la versión.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>               //strlen() y strcmp()
#include<conio.h>                //

/*Direcciones del teclado */
#define ARRIBA 72+256
#define ABAJO 80+256
#define INTRO 13

#define MAX_STRING 20            //Longitud máxima de la cadena inicial.
#define chances 6                //Número de intentos, en el ahorcado clásico suelen ser 6. Se puede cambiar aquí.

/* PROTOTIPOS */
void guiones(int);
void historial(char letra,char* palabra, char* vector,int largo, int* flag);

int main(void) {
		int intro=0,gamemode=0;
printf("Bienvenido al juego del ahorcado.\n\n");
printf("Vas a acceder al menu del juego.\nPor favor utilice las flechas arriba y abajo para seleccionar el modo de juego.");
system("pause>>null \n\n");
 system("cls"); /*LIMPIAMOS LA PANTALLA*/

	menu0();
while(intro==0){
	
	int tecla;
	tecla=getch();
 
	if(tecla==224||tecla==0){
	tecla=256 + getch();
    }
    system("cls"); /*LIMPIAMOS LA PANTALLA*/
    switch(tecla){
    	case ARRIBA: gamemode=0;break;
        case ABAJO:  gamemode=1;break;
        case INTRO:  intro=1;break;
	}

	if(gamemode==0){
	menu0();
	} 
	if(gamemode==1){
    menu1();
    }
}
system("cls"); /*LIMPIAMOS LA PANTALLA*/


/*Fin del menu*/

int  largo;               //Guarda la longitud de la palabra.
char *palabra,letra;      //Cadena de la palabra y la letra introducida por el usuario.
int  intentos=chances;    //Numero de intentos.
int  flag=0;              //Flag de control, nos la devuelve la función, útil para hardware.
    
if(gamemode==0) //Un Jugador, es decir, se tiene que elegir la palabra aleatoriamente.
{
	printf("En mantenimiento sorry");
}


if(gamemode==1) //Dos Jugadores, es decir, se tiene que pedir la palabra por teclado.
{
	
    char buffer[MAX_STRING];  //Cadena inicial (buffer) que será sustituida por una mas eficiente con declaración dinámica de memoria.
    
   



/*  Introducir la palabra y a continuación asignarla a un espacio asignado dinámicamente. */

   printf("%s: \n","Ingrese palabra: ");
    fgets(buffer,MAX_STRING,stdin);
	largo=strlen(buffer);
	palabra = (char*)malloc(sizeof(char)*(largo+1)); 
    if (palabra==NULL) printf("No se ha podido reservar la memoria.");
    else strcpy(palabra,buffer);
    buffer[0]='\0';                                                  //eliminamos la primera entrada.
    
    /*Convertidor a mayusculas*/
	int i; 
   for(i=0;i<largo;i++){
   if(*(palabra+i)>=97) *(palabra+i)=*(palabra+i)-32; 
    }
   
   //printf("la palabra introducida es: %s\n",palabra);                             //check.
	guiones(largo);
		
}//Fin de codigo exclusivo para Dos Jugadores.

//Inicializamos el vector historial que es del mismo tamaño que el de la palabra. De forma dinamica con un puntero.
   char *vector;
   vector = (char *)malloc(largo);
   if (vector==NULL) printf("No se ha podido reservar la memoria.");
   *(vector+(largo-1))='\0';


//bucle del juego*****

while(flag==0){ 

/* Introducción de la letra por el usuario */                
printf("Introduzca una letra.\n");                            
scanf("%c",&letra);  
getchar();                                             
while(letra<64 || (letra>90&&letra<97) ||  letra>122){        // Condiciones de introducir una letra mayus o minus.
printf("Por favor, introduzca un caracter valido.");          
scanf("%c",&letra);  
getchar();                                         
}                                                             
//transformamos todas las letras a mayusculas                 
if(letra>=97) letra=letra-32;                                 

/*Comprobar si la letra introducida está en la palabra y completar los huecos*/
historial(letra, palabra, vector, largo, &flag);
//printf("%s\n",palabra);                                                      //CHECKS
//printf("%s\n",vector);                                                       //

if(flag==0)
{
	intentos--;
	 if(intentos == 0)
     {
     	printf("Has Perdido, te has quedado sin intentos.\n");
     	break;
     //acabar el juego
     }
     printf("Letra incorrecta.\n");
     //imprimimos un ahorcado.
} 
    /* Reseteamos el valor de la flag para que vuelva al bucle */
    flag=0; 
	printf("Te quedan %d intentos",intentos);                                            
}

system("pause");
return 0;   
}
void menu0()
{
printf("******************************\n");
printf("**                          **\n");
printf("**  >    Un Jugador    <    **\n");
printf("**      Dos Jugadores       **\n");
printf("**                          **\n");
printf("******************************\n");
}
void menu1()
{
printf("******************************\n");
printf("**                          **\n");
printf("**       Un Jugador         **\n");
printf("**  >   Dos Jugadores  <    **\n");
printf("**                          **\n");
printf("******************************\n");
}

void guiones(int largo) {
	int i = 0;                      //Pasamos la dirección de memoria del primer miembro de la cadena.
	for(i=0;i<largo-1;i++) {
	 printf("_ ");

	}
	printf("\n\n");
}

void historial(char letra,char *palabra, char* vector,int largo, int* flag){
	int i,j;
	for(i=0;i<largo-1;i++){
		if(letra==*(palabra+i)){
			  /*
               Si la letra introducida por el usuario está en la palabra, 
               se sustituirá por ella en el vector y se cambiara el valor 
               de la bandera.
             */
            *(vector + i) = letra;
            *flag = 1;
        }
            else
        {
            /*
              Se pondrá un '_' en cada emplazamiento vacio.
            */

            /* To identify letters in the array */
            if(*(vector + i) >= 65 && *(vector + i) <= 90 ) ; // NO poner un '_' si existe una letra en ese espacio.
            else *(vector + i) = '_'; // para el resto sí.
        }
    }

//Imprimimos el vector CON UN ESPACIO ENTRE MEDIAS.
            for(i = 0; i < largo-1; i++)
	{
        printf("%c ", *(vector + i)); 
    }

    //comprobar si hemos ganado y final del juego.
    int final=1;
    for(j=0;j<largo-1;j++){
    	if(*(vector+j)==*(palabra+j)) final=final*1;
    	else final=final*0;	
	}
    if(final==1){
        printf("\n\n Enhorabuena,has adiviando la palabra.\n\n");
        exit(0);
    }

    return;
}

	
	
	
	
	
	



