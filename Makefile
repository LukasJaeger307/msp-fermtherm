P = msp-fermtherm

SRCDIR = src
HDIR = include
BINDIR = bin
OBJDIR = obj
DOCDIR = doc

SOURCES := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(HDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

AR = ar
CC = gcc
CROSS = msp430-elf
CROSS_COMPILE = ${CROSS}-${CC}
CROSS_AR = ${CROSS}-${AR}
MACHINEFLAGS=-mmcu=msp430g2553
TOOLCHAINFLAGS=$(HOME)/ti/msp430-gcc/include
CFLAGS = -Os -g -I$(TOOLCHAINFLAGS) -Iinclude -Wextra -std=c99 $(MACHINEFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	$(CROSS_COMPILE) -c -o $@ $< $(CFLAGS)
	
$(BINDIR)/$(P) : folders $(OBJECTS)
	$(CROSS_COMPILE) -L$(TOOLCHAINFLAGS) $(OBJECTS) $(MACHINEFLAGS) -o $(BINDIR)/$(P)
		
$(BINDIR):
	mkdir $(BINDIR)
			
$(OBJDIR):
	mkdir $(OBJDIR)
				
$(DOCDIR):
	mkdir $(DOCDIR)
					
folders : $(BINDIR) $(OBJDIR)

install : $(BINDIR)/$(P)
	mspdebug rf2500 "prog bin/$(P)"


clean : 
	rm -f $(OBJDIR)/*.o $(BINDIR)/*.hex $(BINDIR)/*.elf
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
	rm -rf $(DOCDIR)
													
serial : $(BINDIR)/$(P)
	screen /dev/ttyACM0 115200 
								
												
documentation : $(DOCDIR) $(SOURCES) $(INCLUDES)
	doxygen Doxyfile

git : 
	git add include/*.h src/*.c Makefile .gitignore Doxyfile
	git status
