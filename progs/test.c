int c , b , a , d , mode ;
int test(){
	while(1){
		a = ( *(unsigned int*) 0xc0 );
		b = ( a / 16 ) & 0xf;
		c = (a) & 0xf ;
		mode = ( a / 256 ) & 0xf ;
		if ( mode == 0 )  //add
			*(unsigned int*) 0x8c = b + c ;
		else if ( mode == 1 ) //multi
			*(unsigned int*) 0x8c = b * c ;
		else if ( mode == 2 ){
			//GCD
			a = b ; d = c ;
			while ( a && d ) {
				if ( a > d ) a -= d;
				else d -= a ;
			}
			*(unsigned int*) 0x8c = a | d ;
		}else { //binomial coeff
			a = 1 ;
			if ( c<b )
				*(unsigned int*)0x8c = 0;
			else{
				for ( d = b + 1 ; d <= c ; ++d )
					a *= d;
				for ( d = 1; d <= c-b ; ++d )
					a /= d;
				*(unsigned int*) 0x8c = a ;
			}
		}
		*(unsigned int*) 0x88 = b;
		*(unsigned int*) 0x90 = c ;
	}
}
