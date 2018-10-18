#include "is_perfect_number.h"
#include "divisor_sum.h"
#include <stdio.h>
int main(){
	for(unsigned long i = 1 ; i<8500 ; i++){
	    if(is_perfect_number(i)){
	        printf("%ld \n", i);
	    }
	}
}

