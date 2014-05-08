
TEXTOFFSET := 0x0
DATAOFFSET := 0X100

CLFAGS := -O3 -fomit-frame-pointer
OBJDIR := obj
OUTDIR := mif
LDFLAGS :=
OBJDUMPOPT := -M no-aliases

READELF := mips-linux-gnu-readelf
CC :=  mips-linux-gnu-gcc
OBJDUMP := mips-linux-gnu-objdump
OBJCOPY := mips-linux-gnu-objcopy
LD := mips-linux-gnu-ld

all: $(OUTDIR)/data.mif $(OUTDIR)/prog.mif

clean:
	rm $(OBJDIR)/*.o $(OBJDIR)/prog $(OUTDIR)/prog.mif $(OBJDIR)/prog.asm $(OBJDIR)/prog.data  $(OUTDIR)/data.mif 

$(OBJDIR)/%.o: progs/%.c
	@echo + cc -Os $<
	-( test -d $(OBJDIR) || mkdir $(OBJDIR) )
	$(CC) -nostdinc $(CFLAGS) -c -o $@ $<


$(OBJDIR)/prog: $(OBJDIR)/test.o
	@echo + Linking
	-rm $(OBJDIR)/prog.data $(OBJDIR)/prog.bss
	$(LD) $(LDFLAGS) -N -e start -Ttext $(TEXTOFFSET) -Tdata $(DATAOFFSET) -o $@.out $^
	$(OBJDOPY) --rename-section .data=.rodata,alloc,load,readonly,data,contents $@ $@
	$(OBJDUMP) $(OBJDUMPOPT) -S $@.out >$@.asm
	$(OBJCOPY) -S -O binary -j .text $@.out $@

$(OBJDIR)/prog.data: $(OBJDIR)/prog
	touch $@.data
	$(READELF) -S $@.out | grep -q ".data"; \
	if [ $$? -eq 0 ];\
	then \
		echo "Parsing DATA";\
		offset=$$($(READELF) -S $@.out | grep ".data" | awk '{print $$5;}');\
		$(OBJCOPY) -S -O binary -j .data $@.out $@.data;\
	fi

$(OBJDIR)/tmp.out: $(OBJDIR)/prog
	#hexdump -v $^ | awk 'BEGIN {x=$(TEXTOFFSET)} {printf("%x : %s%s;\n",x,$$2,$$3);++x;printf("%x : %s%s;\n",x,$$4,$$5);++x;printf("%x : %s%s;\n",x,$$6,$$7);++x;printf("%x : %s%s;\n",x,$$8,$$9);++x;}' | grep -P '[0-9a-zA-Z]+ : [0-9a-zA-Z]+' >tmp.out
	hexdump -v -e ' 4/1 "%02x " "\n"' $^ | awk 'BEGIN {x=$(TEXTOFFSET)} {printf("%x : %s%s%s%s;\n",x,$$1,$$2,$$3,$$4);++x}' >$@

$(OBJDIR)/tmp.data.out:  $(OBJDIR)/prog.data
	touch $@
	hexdump -v -e ' 4/1 "%02x " "\n"' $^ | awk 'BEGIN {x=$(DATAOFFSET)} {printf("%x : %s%s%s%s;\n",x,$$1,$$2,$$3,$$4);++x}' >$@
	
$(OUTDIR)/prog.mif: $(OBJDIR)/tmp.out
	-rm $@
	echo "DEPTH = 128; % Memory depth and width are required % " 				>>$(OUTDIR)/prog.mif
	echo "WIDTH = 32; % Enter a decimal number % "				>>$(OUTDIR)/prog.mif
	echo "ADDRESS_RADIX = HEX; % Address and value radixes are optional % "				>>$(OBJDIR)/prog.mif
	echo "DATA_RADIX = HEX; % Enter BIN, DEC, HEX, or OCT; unless % "				>>$(OUTDIR)/prog.mif
	echo "% otherwise specified, radixes = HEX % "				>>$(OUTDIR)/prog.mif
	echo "CONTENT "				>>$(OUTDIR)/prog.mif
	echo "BEGIN "				>>$(OUTDIR)/prog.mif
	cat $(OBJDIR)/tmp.out			>>$(OUTDIR)/prog.mif
	-rm $(OBJDIR)/tmp.out	
	echo "END ; "				>>$(OUTDIR)/prog.mif

$(OUTDIR)/data.mif: $(OBJDIR)/tmp.data.out
	-rm $@
	echo "DEPTH = 128; % Memory depth and width are required % " 		>>$(OUTDIR)/data.mif
	echo "WIDTH = 32; % Enter a decimal number % "						>>$(OUTDIR)/data.mif
	echo "ADDRESS_RADIX = HEX; % Address and value radixes are optional % ">>$(OUTDIR)/data.mif
	echo "DATA_RADIX = HEX; % Enter BIN, DEC, HEX, or OCT; unless % "	>>$(OUTDIR)/data.mif
	echo "% otherwise specified, radixes = HEX % "						>>$(OUTDIR)/data.mif
	echo "CONTENT "				>>$(OUTDIR)/data.mif
	echo "BEGIN "				>>$(OUTDIR)/data.mif
	cat $(OBJDIR)/tmp.data.out		>>$(OUTDIR)/data.mif
	-rm $(OBJDIR)/tmp.data.out	
	echo "END ; "				>>$(OUTDIR)/data.mif
