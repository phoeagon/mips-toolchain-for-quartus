int test(){
	while(1){
		int a = 1;
		//*(int*)(0xf094+a)=*(int *)(0xf000+a);
		for (a=0;a<0x25;a+=4)
			*(int*)(0xf098+a)=*(int *)(0xf000+a);
		/*
//		*(int*)(0xf094)=*(int *)(0xf000);
		*(int*)(0xf098)=*(int *)(0xf000);
		*(int*)(0xf09c)=*(int *)(0xf004);
		*(int*)(0xf0a0)=*(int *)(0xf008);
		*(int*)(0xf0a4)=*(int *)(0xf00c);
		*(int*)(0xf0a8)=*(int *)(0xf010);
		*(int*)(0xf0ac)=*(int *)(0xf014);
		*(int*)(0xf0b0)=*(int *)(0xf018);
		*(int*)(0xf0b4)=*(int *)(0xf01c);
		*(int*)(0xf0bc)=*(int *)(0xf020);
		*/
		//*(int*)(0xf094)=0xaaaaaa;
/*
		*(int*)(0xf098)=0;
		*(int*)(0xf09c)=1;
		*(int*)(0xf0a0)=0;
		*(int*)(0xf0a4)=1;
		*(int*)(0xf0a8)=0;
		*(int*)(0xf0ac)=1;
		*(int*)(0xf0b0)=;
		*(int*)(0xf0b4)=0;
		*(int*)(0xf0b8)=1;
		*(int*)(0xf0bc)=0;
*/

		*(int*)0xf088=*(int *)(0xf028);
		*(int*)0xf08c=*(int *)(0xf02c);
		*(int*)0xf090=*(int *)(0xf030);

	}
}
