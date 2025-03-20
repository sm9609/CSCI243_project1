#
# Created by gmakemake (Ubuntu Jul 25 2014) on Wed Mar 19 13:49:35 2025
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb
CFLAGS =	-ggdb
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags


CPP_FILES =	
C_FILES =	agent.c brace_topia.c display.c use_getopt.c
PS_FILES =	
S_FILES =	
H_FILES =	agent.h display.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	agent.o display.o 

#
# Main targets
#

all:	brace_topia use_getopt 

brace_topia:	brace_topia.o $(OBJFILES)
	$(CC) $(CFLAGS) -o brace_topia brace_topia.o $(OBJFILES) $(CLIBFLAGS)

use_getopt:	use_getopt.o $(OBJFILES)
	$(CC) $(CFLAGS) -o use_getopt use_getopt.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

agent.o:	agent.h
brace_topia.o:	
display.o:	display.h
use_getopt.o:	

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) brace_topia.o use_getopt.o core

realclean:        clean
	-/bin/rm -f brace_topia use_getopt 
