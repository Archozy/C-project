#include "isqrt.h"
#include <stdio.h>
int main(){
	for(int i = 0 ; i < 201 ; i++){
		if(i%8 == 0){
			printf("isqrt(%d) = %ld\n",i, isqrt(i));
		}
	}
}

