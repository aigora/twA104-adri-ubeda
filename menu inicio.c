#include <stdio.h>


////// direcciones ////
#define ARRIBA 72+256
#define ABAJO 80+256
#define INTRO 13

//prototipos
void menu0();
void menu1();

void main()
{
	int intro=0, i=0;
	menu0();
while(intro==0){
	
	int tecla;
	tecla=getch();
 
	if(tecla==224||tecla==0){
	tecla=256 + getch();
    }
    system("cls"); /*LIMPIAMOS LA PANTALLA*/
    switch(tecla){
    	case ARRIBA: i=0;break;
        case ABAJO:  i=1;break;
        case INTRO:  intro=1;break;
	}

	if(i==0){
	menu0();
	} 
	if(i==1){
    menu1();
    }
}
system("cls"); /*LIMPIAMOS LA PANTALLA*/
printf("Pulsaste intro\n");


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
