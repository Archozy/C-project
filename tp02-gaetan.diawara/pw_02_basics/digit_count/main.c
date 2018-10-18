#include "digit_count.h"
#include <stdio.h>
unsigned long power_of_two(unsigned char n){
	unsigned long r = 1;
	for(;n > 0; n--){r*=2;}
	return  r;
}

int main(){
	for(int i = 0 ; i < 64 ; i++){
	  printf("digit_count(%ld) = %d\n",power_of_two(i), digit_count(power_of_two(i)));
	}
}

