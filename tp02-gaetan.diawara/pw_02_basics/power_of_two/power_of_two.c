unsigned long power_of_two(unsigned char n){
	unsigned long r = 1;
	for(;n > 0; n--){r*=2;}
	return  r;
}
