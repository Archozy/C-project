#include "is_perfect_number.h"
#include "divisor_sum.h"

int is_perfect_number(unsigned long n)
{
    if(divisor_sum(n) != n){
        return 0;
    }
    return n;
}