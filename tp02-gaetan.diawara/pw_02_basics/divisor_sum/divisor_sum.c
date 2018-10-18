unsigned long divisor_sum(unsigned long n){
  unsigned long h = 0;
  for(unsigned long i = 1; i < n-1 ; i++){
    if(n%i == 0){
      h+=i ;
    }
  }
  return h;

}
