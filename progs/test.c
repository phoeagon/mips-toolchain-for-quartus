int test()  __attribute__ ((noreturn));
int test() {
	int a = 4 ;
	int b = 12 ;
	a *= b;
	//int * ptr1 = (int*)0x80;
	//int * ptr2 = (int*)0x84;
//	while (1){
		//int a = *ptr2;
		//int b = *ptr1;
	//	*ptr2 = 0x55555555;
	//	*ptr1 = 0xaaaa;
//		*(int*)(0x80)=0xaaaa;
//	}
	/*asm(
	"li $v0,0xaaaa\n"
	"li $v1,0x80\n"
	"sw $v1,0($v0)\n"
	);*/
}
