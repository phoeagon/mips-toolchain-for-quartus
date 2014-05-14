
unsigned int c , b , a , mode ;
//int t=1;
//int b;
int test(){
	unsigned int c , b , a , mode ;
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
		//mode = 14;
		//b = *(unsigned int*) 0xc8 ;
		//c = *(unsigned int*) 0xcc ;
		//mode = *(unsigned int*) 0xd0 ; //; ( a / 256 ) & 1;
		//unsigned int b = *(unsigned int*)0xc8;
		//unsigned int c = *(unsigned int*)0xcc;
//		*(unsigned int*) 0x90 = (1-mode)*(b+c)+mode*(b*c) ;
		*(unsigned int*) 0x88 = b ;
		*(unsigned int*) 0x90 = c ;
		*(unsigned int*) 0x8c = b+c  ;
		
	}
}
