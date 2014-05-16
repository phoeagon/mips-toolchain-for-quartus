
int c  , b , a , mode ;
//int t=1;
//int b;
int test(){
	while(1){
		*(unsigned int*) 0x80 = 0xaaaaaaaa ;
		*(unsigned int*) 0x8c = 0x55555555 ;
		//*(unsigned int*) 0x8c = 1 ;
		//*(unsigned int*) 0x88 = 2 ;
		//*(unsigned int*) 0x90 = 14 ;
	}
}
/*int test(){
	while(1){
		c = *(unsigned int*) 0xC8 ;
		b = *(unsigned int*) 0xCC ;
		*(unsigned int*) 0x8c = b % c ;
		*(unsigned int*) 0x88 = b ;
		*(unsigned int*) 0x90 = c ;
	}
}*/
/*
int test(){
	for ( a = 1; a<10 ;++a){
		c += a;
	}
	while (1)
		*(unsigned int*) 0x90 = c ;
}
*/
/*
int test(){
	//unsigned int c , b , a , mode ;
	// *(unsigned int*)0x84=0x0000aaaa;
	// unsigned int a = ( *(unsigned int*) 0xC0 ) & 0xffff;
// *(unsigned int*)0x84=a;
	//*(unsigned int*) 0x88 = 11;
	//*(unsigned int*) 0x8c = 12;
	while(1){
		a = ( *(unsigned int*) 0xC0 ) ;
		b = ( a / 16 )& 0xf;
		c = ( a ) & 0xf ; 
		//b = 32 ;
		//c = 16;
		mode = ( a / 256 ) & 0xf;
		//b = *(unsigned int*) 0xc8 ;
		//c = *(unsigned int*) 0xcc ;
		//mode = *(unsigned int*) 0xd0 ; //; ( a / 256 ) & 1;
		//unsigned int b = *(unsigned int*)0xc8;
		//unsigned int c = *(unsigned int*)0xcc;
		//*(unsigned int*) 0x8c = b * c;
		*(unsigned int*) 0x8c = b % c ;
		*(unsigned int*) 0x88 = b ;
		*(unsigned int*) 0x90 = c ;
		//*(unsigned int*) 0x8c = b+c  ;
		
	}
}

*/
