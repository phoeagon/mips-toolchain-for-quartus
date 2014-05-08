TEXTOFFSET := 0x0
DATAOFFSET := 0X100

CLFAGS := -O3 -fomit-frame-pointer
OBJDIR := obj
LDFLAGS :=
OBJDUMPOPT := -M no-aliases

READELF := mips-linux-gnu-readelf
CC :=  mips-linux-gnu-gcc
OBJDUMP := mips-linux-gnu-objdump
OBJCOPY := mips-linux-gnu-objcopy
LD := mips-linux-gnu-ld

all: $(OBJDIR)/prog.mif

clean:
	-rm $(OBJDIR)/*.o $(OBJDIR)/prog $(OBJDIR)/prog.mif $(OBJDIR)/prog.asm $(OBJDIR)/prog.data $(OBJDIR)/prog.bss

$(OBJDIR)/%.o: progs/%.c
	@echo + cc -Os $<
	-( test -d $(OBJDIR) || mkdir $(OBJDIR) )
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<


$(OBJDIR)/prog: $(OBJDIR)/test.o
	@echo + Linking
	-rm $(OBJDIR)/prog.data $(OBJDIR)/prog.bss
	$(LD) $(LDFLAGS) -N -e start -Ttext $(TEXTOFFSET) -Tdata $(DATAOFFSET) -o $@.out $^
	$(OBJDUMP) $(OBJDUMPOPT) -S $@.out >$@.asm
	$(OBJCOPY) -S -O binary -j .text $@.out $@
	$(READELF) -S $@.out | grep -q ".data"; \
	if [ $$? -eq 0 ];\
	then \
		echo "Parsing DATA";\
		offset=$$($(READELF) -S $@.out | grep ".data" | awk '{print $$5;}');\
		$(OBJCOPY) -S -O binary -j .data $@.out $@.data;\
	fi
	$(READELF) -S $@.out | grep -q ".sbss"; \
	if [ $$? -eq 0 ];\
	then \
		echo "Parsing BSS";\
		offset=$$($(READELF) -S $@.out | grep ".sbss" | awk '{print $$5;}');\
		$(OBJCOPY) -S -O binary -j .sbss $@.out $@.bss;\
	fi

$(OBJDIR)/tmp.out: $(OBJDIR)/prog
	#hexdump -v $^ | awk 'BEGIN {x=$(TEXTOFFSET)} {printf("%x : %s%s;\n",x,$$2,$$3);++x;printf("%x : %s%s;\n",x,$$4,$$5);++x;printf("%x : %s%s;\n",x,$$6,$$7);++x;printf("%x : %s%s;\n",x,$$8,$$9);++x;}' | grep -P '[0-9a-zA-Z]+ : [0-9a-zA-Z]+' >tmp.out
	hexdump -v -e ' 4/1 "%02x " "\n"' $^ | awk 'BEGIN {x=$(TEXTOFFSET)} {printf("%x : %s%s%s%s;\n",x,$$1,$$2,$$3,$$4);++x}' >tmp.out
	
$(OBJDIR)/prog.mif: $(OBJDIR)/tmp.out
	-rm $(OBJDIR)/prog.mif
	echo "DEPTH = 128; % Memory depth and width are required % " 				>>$(OBJDIR)/prog.mif
	echo "WIDTH = 32; % Enter a decimal number % "				>>$(OBJDIR)/prog.mif
	echo "ADDRESS_RADIX = HEX; % Address and value radixes are optional % "				>>$(OBJDIR)/prog.mif
	echo "DATA_RADIX = HEX; % Enter BIN, DEC, HEX, or OCT; unless % "				>>$(OBJDIR)/prog.mif
	echo "% otherwise specified, radixes = HEX % "				>>$(OBJDIR)/prog.mif
	echo "CONTENT "				>>$(OBJDIR)/prog.mif
	echo "BEGIN "				>>$(OBJDIR)/prog.mif
	cat tmp.out					>>$(OBJDIR)/prog.mif
	-rm tmp.out
	echo "END ; "				>>$(OBJDIR)/prog.mif
