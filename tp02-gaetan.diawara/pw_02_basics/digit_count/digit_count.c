unsigned char digit_count(unsigned long n){
  unsigned char c = 1;
  for(;n>=10;n/=10)c++;
  return c;


}
