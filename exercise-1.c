#include <stdio.h>

int main(void){
	int i, precision = 1000;

	double a = 2;
	printf("Enter a real number: " );
	scanf("%lf", &a);

	double u = a;

	for(i = 0; i < precision; i++){
		u = (u + a / u) / 2;
	}

	printf("%lf\n", u);

	return 0;
}
