#include "fibo.h"
#include <stdio.h>
int main(){
	for(int i = 0 ; i < 91 ; i++){
		printf("fibo(%d) = %ld\n",i, fibo(i));
	}
}

