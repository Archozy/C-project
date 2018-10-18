unsigned long fibo(unsigned long n){
	if(n == 0){return 0;}
	if(n==1){return 1;}
	int a = 1;
	int b = 0;
	int c = 0;

	for( ; n >= 1 ; n--){
		c = b;
		b = a + b;
		a = c;

	}
	return b;
}
