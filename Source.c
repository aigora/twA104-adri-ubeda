#include<stdio.h>

int main() {
	int a, b, suma;
	float c, d;
	char e, f;
	
	printf("Introduce 2 números enteros");
	scanf_s("%d%d",&a,&b);
	printf("Introduce 2 números decimales");
	scanf_s("%f%f",&c,&d);
	printf("Introduce 2 caracteres");
	scanf_s("%c%c",&e,&f);
	printf("%d%f%c",a+b,c+d,e+f);
	system("PAUSE");
}
