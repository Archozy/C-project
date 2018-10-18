unsigned long isqrt(unsigned long n){
	int r = (int) n;
	while (r*r > n){
		r = r + n/r;
		r = r/2;
	}
	return r;
}
