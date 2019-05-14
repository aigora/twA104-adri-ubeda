#define _CRT_SECURE_NO_WARNINGS  //Evitar la sintaxis de la versión.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>               //strlen() y strcmp()
#include<conio.h>                //_getch
#include<time.h>                 //rand() y srand()

/* Direcciones del teclado */
#define ARRIBA 72+256
#define ABAJO 80+256
#define INTRO 13

#define _CRT_SECURE_NO_WARNINGS  //Evitar la sintaxis de la versión.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>               //strlen() y strcmp()
#include<conio.h>                //_getch
#include<time.h>                 //rand() y srand()

/* Direcciones del teclado */
#define ARRIBA 72+256
#define ABAJO 80+256
#define INTRO 13

#define NUM_PALABRAS 16           //Numero de palabras 
#define MAX_STRING 20            //Longitud máxima de la cadena inicial.
#define NUM_INTENTOS 5           //Número de intentos, en el ahorcado clásico suelen ser 6. Se puede cambiar aquí.

/*     PROTOTIPOS      */

void titulo();                   //Titulo principal en ascii
void menu0();                    //menú seleccionando 1 jugador
void menu1();                    //menú seleccionando 2 jugadores
void guiones(int);               //Pista inicial.
void historial(char letra, char* palabra, char* vector, int largo, int* flag, int intentos);     //Funcion iterativa que rellena la palabra.

int main(void) {
	titulo();

	int intro = 0, gamemode = 0;
	printf("Bienvenido al juego del ahorcado.\n\n");
	printf("En este trepidante juego tendras que adivinar una palabra antes de que cuelguen al ahorcado.\n\n");
	printf("Vas a acceder al menu del juego.\n\nPor favor utilice las flechas ARRIBA y ABAJO para seleccionar el modo de juego.");
	system("pause>>null \n\n"); //Paramos el programa sin mensaje.
	system("cls"); /*LIMPIAMOS LA PANTALLA*/

	menu0();
	while (intro == 0) {

		int tecla;
		tecla = _getch();

		if (tecla == 224 || tecla == 0) {
			tecla = 256 + _getch();
		}
		system("cls"); /*LIMPIAMOS LA PANTALLA*/
		switch (tecla) {
		case ARRIBA: gamemode = 0; break;
		case ABAJO:  gamemode = 1; break;
		case INTRO:  intro = 1; break;
		}

		if (gamemode == 0) {
			menu0();
		}
		if (gamemode == 1) {
			menu1();
		}
	}
	system("cls"); /*LIMPIAMOS LA PANTALLA*/


	/*Fin del menu*/

	int  largo;                                          //Guarda la longitud de la palabra.
	char *palabra = NULL, letra;                         //Cadena de la palabra y la letra introducida por el usuario.
	int  intentos = 0;                                   //Numero de intentos.
	int  flag = 0;                                       //Flag de control, nos la devuelve la función, útil para hardware.

	if (gamemode == 0) //Un Jugador, es decir, se tiene que elegir la palabra aleatoriamente.
	{
		/* Initialize words to be chosen*/
		srand(time(NULL)); //cambiar la seed de aleatoriedad.
		char *bateria[] = { "CAMION","PUENTE","COCODRILO","SAPO","SOMBRERO","DELEGADO","HELADO","LATA","PELOTA","PIMIENTO","AGUA",
							"CHOCOLATE","HIPOPOTAMO","APROBAR","TRABAJO","INFORMATICA" };
		int aleatorio = rand() % ((NUM_PALABRAS - 1) + 1);
		//ESTRUCTURA RARA PARA QUE genere entre 0 1 2 3 4 y no entre 1 2 3 4 5 (en el caso de 5)

		largo = strlen(bateria[aleatorio]) + 1;
		palabra = (char*)calloc(largo, sizeof(char));

		if (palabra == NULL) {
			printf("No se ha podido reservar la memoria.");
			exit(1);
		}

		else strcpy(palabra, bateria[aleatorio]);
		printf("Una palabra ha sido escogida. Buena Suerte!");
		// printf("la palabra introducida es: %s\n",bateria[aleatorio]);  //check.
	}


	if (gamemode == 1) //Dos Jugadores, es decir, se tiene que pedir la palabra por teclado.
	{

		char buffer[MAX_STRING];  //Cadena inicial (buffer) que será sustituida por una mas eficiente con declaración dinámica de memoria.

	/*  Introducir la palabra y a continuación asignarla a un espacio asignado dinámicamente. */

		printf("%s \n", "Primer jugador, ingresa una palabra: ");
		fgets(buffer, MAX_STRING, stdin);
		system("cls");
		largo = strlen(buffer);
		palabra = (char*)calloc(largo, sizeof(char));
		if (palabra == NULL) {
			printf("No se ha podido reservar la memoria.");
			exit(1);
		}
		else strcpy(palabra, buffer);
		buffer[0] = '\0';                                                  //eliminamos la primera entrada.

		/*Convertidor a mayusculas*/
		int i;
		for (i = 0; i < largo; i++) {
			if (*(palabra + i) >= 97)
				*(palabra + i) = *(palabra + i) - 32;
		}
		printf("La palabra ya ha sido introducida por el Jugador 1. Buena suerte!.\n\n");

		//printf("%d",strlen(palabra));                                 //check
	}//Fin de codigo exclusivo para Dos Jugadores.

	guiones(largo);

	//Inicializamos el vector historial que es del mismo tamaño que el de la palabra. De forma dinamica con un puntero.
	char *vector;
	//vector = (char *)malloc(largo);                                   //Vector relleno de basura.
	vector = (char*)calloc(largo, sizeof(char));                        //Vector vacio.
	if (vector == NULL) {
		printf("No se ha podido reservar la memoria.");
		exit(1);
	};

	/* Inicializamos las fases del ahorcado */

	char *ahorcado[] = {
					 " ",
					 "                                                                      |=====|\n"
					 "                                                                            |\n"
					 "                                                                            |\n"
					 "                                                                            |\n"
					 "                                                                           ===\n",
					 "                                                                      |=====|\n"
					 "                                                                      O     |\n"
					 "                                                                            |\n"
					 "                                                                            |\n"
					 "                                                                           ===\n",
					 "                                                                      |=====|\n"
					 "                                                                      O     |\n"
					 "                                                                      |     |\n"
					 "                                                                            |\n"
					 "                                                                           ===\n",
					 "                                                                      |=====|\n"
					 "                                                                      O     |\n"
					 "                                                                     -|-    |\n"
					 "                                                                            |\n"
					 "                                                                           ===\n",
					 "                                                                      |=====|\n"
					 "                                                                      O     |\n"
					 "                                                                     -|-    |\n"
					"                                                                     / \\    |\n"
					 "                                                                           ===\n"

	};



	//bucle del juego*****

	while (flag == 0) {


		/* Introducción de la letra por el usuario */
		printf("Adivina una letra:  ");
		scanf("%c", &letra);
		printf("\n");
		getchar();


		while (letra < 65 || (letra > 90 && letra < 97) || letra>122) {            // Condiciones de introducir una letra mayus o minus.
			printf("Por favor, introduzca un caracter valido.");
			scanf("%c", &letra);
			getchar();
		}
		system("cls");
		//transformamos todas las letras a mayusculas                 
		if (letra >= 97) letra = letra - 32;

		/*Comprobar si la letra introducida está en la palabra y completar los huecos*/
		historial(letra, palabra, vector, largo, &flag, intentos);

		//printf("%s\n",palabra);                                                 //CHECKS
		//printf("%s\n",vector);                                                  //

		if (flag == 2)
		{
			intentos++;
			printf("LETRA INCORRECTA.");
			printf("\n\n%s\n\n", ahorcado[intentos]);                             //imprimimos un ahorcado.

			if (intentos >= NUM_INTENTOS)
			{
				printf("Se acabo, ha muerto ahorcado.\n");
				printf("La palabra correcta era %s.\n", palabra);                 //CAMBIO GITHUB
				break;                                                            //acabar el juego sale del while
			}
			switch (intentos) {
			case 1:printf("Ten mas cuidado...\n\n"); break;
			case 2:printf("Esto puede ser peligroso...\n\n"); break;
			case 3:printf("La cosa se pone muy fea...\n\n"); break;
			case 4:printf("Se acerca su final!\n\n"); break;
			}
		}
		if (flag == 1)
		{
			if (intentos > 0)
			{
				printf("LETRA CORRECTA.");
				printf("\n\n%s\n\n", ahorcado[intentos]);
			}
			printf("Bien hecho!\n");
		}
		/* Reseteamos el valor de la flag para que vuelva al bucle */
		flag = 0;


	}


	system("pause");
	free(palabra); // a veces da fallo, estudiar.
	free(vector);
	return 0;
}

/*     FUNCIONES      */

void titulo() {

	printf("\n\n\n");
	printf("     \333\333\333       \333\333\260 \333\333   \260\333\333\333\333   \333\333\337\333\333\333   \334\333\333\333\334    \334\334\334      \261\333\333\333\333\333\334  \260\333\333\333\333\333  \n");
	printf("    \260\333\333\333\333\334    \261\333\333\260 \333\333\260\260\333\333\260  \333\333\260\261\333\333 \260 \333\333\260\260\333\333\337 \337\333  \260\333\333\333\333\334    \260\333\333\337 \333\333\333\260\333\333\260  \333\333\260\n");
	printf("    \260\333\333  \337\333\334  \260\333\333\337\337\333\333\260\260\333\333\260  \333\333\260\261\333\333 \260\334\333 \260\260\261\333    \334 \260\333\333  \337\333\334   \260\333    \333\260\333\333\260  \333\333\260\n");
	printf("    \260\333\333\334\334\334\334\333\333 \260\261\333 \260\333\333 \260\333\333   \333\333\260\260\333\333\337\337\333\334  \260\261\261\334 \334\333\333\260\260\333\333\334\334\334\334\333\333 \260\261\333\334   \333\260\333\333   \333\333\260\n");
	printf("     \261\333   \261\333\333\260\260\261\333\260\260\333\333\261\260 \333\333\333\333\261\260\260\260\333\333\261 \260\333\333\260\260 \261\333\333\333\337 \260 \261\333   \261\333\333\260\260\260\333\333\333\333\261 \260 \333\333\333\333\261\260\260\n");
	printf("     \260\260   \261\260\333\260 \260 \260\260\260\260\260\260 \260\260\260\260\260\260 \260 \260\261 \260\260\261\260\260 \260\260 \260  \260 \260\260   \261\260\333\260 \260\260\261  \260 \260 \260\260\260\260\260\260 \n");
	printf("      \260   \260\260 \260 \260 \260\260\260 \260  \260 \260 \260\260   \260\260 \260 \260\260  \260  \260     \260   \260\260 \260 \260 \260  \260   \260 \260 \260\260 \n");
	printf("      \260   \260    \260  \260\260 \260\260 \260 \260 \260    \260\260   \260 \260          \260   \260    \260 \260  \260 \260 \260 \260 \260  \n");
	printf("          \260  \260 \260  \260  \260    \260 \260     \260     \260 \260            \260  \260   \260        \260 \260  \n");
	printf("                                        \260                   \260               \n\n");
	printf("\n\n                Developed by Adri%cn Bedmar y Guillermo %cbeda.", 160, 233);


	system("pause>>null \n\n"); //Paramos el programa sin el mensaje.
	system("cls"); /*LIMPIAMOS LA PANTALLA*/
}
void menu0()
{
	printf("\n\n\n\n\n\n\n");
	printf("                        ******************************\n");
	printf("                        **                          **\n");
	printf("                        **   >   Un Jugador    <    **\n");
	printf("                        **      Dos Jugadores       **\n");
	printf("                        **                          **\n");
	printf("                        ******************************\n");
}

void menu1()
{
	printf("\n\n\n\n\n\n\n");
	printf("                        ******************************\n");
	printf("                        **                          **\n");
	printf("                        **       Un Jugador         **\n");
	printf("                        **   >  Dos Jugadores  <    **\n");
	printf("                        **                          **\n");
	printf("                        ******************************\n");
}

void guiones(int largo) {
	int i = 0;
	printf("\n\n");
	printf("Adivina la palabra:                 ");
	for (i = 1; i < largo; i++) {
		printf("_ ");

	}
	printf("\n\n");
}

void historial(char letra, char *palabra, char* vector, int largo, int* flag, int intentos) {
	int i, j, aciertos = 0; //para ver si hay al menos un acierto y asi cambiar el flag CAMBIO GITHUB
	for (i = 0; i < largo; i++) {
		if (letra == *(palabra + i)) {
			/*
			 Si la letra introducida por el usuario está en la palabra,
			 se sustituirá por ella en el vector y se cambiara el valor
			 de la bandera.
		   */
			aciertos++;
			*(vector + i) = letra;
			//*flag = 1;
		}
		else
		{
			/*
			  Se pondrá en vector un '_' en cada emplazamiento vacio.
			*/

			/* Identificar las letras en el vector */
			if (*(vector + i) >= 65 && *(vector + i) <= 90); // NO poner un '_' si existe una letra en ese espacio.
			else *(vector + i) = '_'; // para el resto sí.
		}
	}
	if (aciertos >= 1)
		*flag = 1;
	else {
		*flag = 2;
	}
	aciertos = 0;
	/* Imprimimos el vector CON UN ESPACIO ENTRE MEDIAS. */
	printf("\n\n");
	printf("                                    ");
	for (i = 0; i < largo - 1; i++)
	{
		printf("%c ", *(vector + i));
	}
	printf("\n\n");

	//comprobar si hemos ganado y final del juego.
	int final = 1;
	for (j = 0; j < largo - 1; j++) {      // para que no llegue al \0 ya que al ser distinto de mayuscula imprimiría un guión
		if (*(vector + j) == *(palabra + j)) final = final * 1;   //proceso equivalente a stringcompare.
		else final = final * 0;
	}
	if (final == 1) {
		if (intentos == 0) printf("Enhorabuena, has salvado al ahorcado sin fallos");
		else
		{
			printf("\n\nEnhorabuena, has salvado al ahorcado con %d fallo", intentos);
			if (intentos > 1) printf("s");
			printf("!!\n\n");
			system("pause>>null \n\n"); //Paramos el programa sin mensaje.
			exit(0);
		}

		system("PAUSE");
	}

	return;
}

