
int c  , b , a , d , mode ;
//int t=1;
//int b;
/*
 * int test(){
	a = 13 ;
	b = 10 ;
	c = a % b;
}*/


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
		if ( mode == 0 ){
			*(unsigned int*) 0x8c = b + c ;
		}else if ( mode == 1 ) {
			*(unsigned int*) 0x8c = b * c ;
		}else if ( mode == 2 ){
			a = b ; d = c ;
			while ( a && d ){
				if ( a > d )
					a -= d;
				else d -= a;
			}
			*(unsigned int*) 0x8c = a | d ;
		}else if ( mode == 3 ){
			a = 1 ;
			if ( c < b ){
				*(unsigned int*) 0x8c = 0 ;
				break;
			}
			for ( d = b+1 ; d <= c ; ++d )
				a *= d;
			for ( d = 1 ; d <= c-b; ++d )
				a /= d;
			*(unsigned int*) 0x8c = a ;			
		}
		*(unsigned int*) 0x88 = b ;
		*(unsigned int*) 0x90 = c ;
		//*(unsigned int*) 0x8c = b+c  ;
		
	}
}


