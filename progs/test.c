int a=1;
int b;
int test(){
	//*(unsigned int*)0x84=0x0000aaaa;
	//unsigned int a = ( *(unsigned int*) 0xC0 ) & 0xffff;
	//*(unsigned int*)0x84=a;
	while(1){
		unsigned int a = ( *(unsigned int*) 0xC0 );
		unsigned int b = ( a / 32  )& 0x1f;
		unsigned int c = ( a ) & 0x1f ; //works
		*(unsigned int*) 0x88 = b;
		*(unsigned int*) 0x8c = c;
		*(unsigned int*) 0x90 = b+c;
	}
}
/*unsigned int get_num(int a);
int test(){
	unsigned int x = get_num(7);
	x |= x << 8;
	x |= x << 16;
	x |= x << 24;
	while(1){
		*(int*)(0x80)=0b10100100101001001010010010100100;
		*(int*)(0x84)=0b10100100101001001010010010100100;
	}
}
*/
/*int test()  __attribute__ ((noreturn));
int test() {
	int a = -4 ;
	int b = 0 ;
	int c ;
//	a *= b;
	c = a>b;
	if ( c )
		a=1;
	//int * ptr1 = (int*)0x80;
	//int * ptr2 = (int*)0x84;
//	while (1){
		//int a = *ptr2;
		//int b = *ptr1;
	//	*ptr2 = 0x55555555;
	//	*ptr1 = 0xaaaa;
//		*(int*)(0x80)=0xaaaa;
//	}
	asm(
	"li $v0,0xaaaa\n"
	"li $v1,0x80\n"
	"sw $v1,0($v0)\n"
	);
}
*/
/*
inline unsigned int get_num(int a){
			if ( a==0 )return 0b00000000000000000000000011000000;
	else 	if ( a==1 )return 0b00000000000000000000000011111001;
	else 	if ( a==2 )return 0b00000000000000000000000010010010;
	else 	if ( a==3 )return 0b00000000000000000000000010110000;
	else 	if ( a==4 )return 0b00000000000000000000000010011001;
	else 	if ( a==5 )return 0b00000000000000000000000010100100;
	else 	if ( a==6 )return 0b00000000000000000000000010000100;
	else 	if ( a==7 )return 0b00000000000000000000000011110001;
	else 	if ( a==8 )return 0b00000000000000000000000010000000;
	else 	if ( a==9 )return 0b00000000000000000000000011000000;
	else
	{
		return 0b00000000000000000000000011111111; //empty
	}
	
	
}
*/
