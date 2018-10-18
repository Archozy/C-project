#include "power_of_two.h"
#include <stdio.h>
int main(){
	for(int i = 0 ; i < 64 ; i++){
		printf("power_of_two(%d) = %lu\n",i, power_of_two(i));
	}
}

