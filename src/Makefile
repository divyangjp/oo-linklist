########################################################
# command	output
# -------   	-----------------------------------
# make		Makes executable without debug info
# make debug	Makes executable with debug info
# make clean	Cleans executable, object files and core
#######################################################

#------------------------------------------------------------------------------

SOURCE=uselist.cpp
MYPROGRAM=uselist
MYINCLUDES=../hdr

MYLIBRARIES=

CFLAGS= -Wall
CDEBUGFLAGS= -g -DDEBUG

CC=g++

#------------------------------------------------------------------------------


all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(CFLAGS) -I$(MYINCLUDES) $(SOURCE) -o$(MYPROGRAM) 

debug: $(SOURCE)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) -I$(MYINCLUDES) $(SOURCE) -o$(MYPROGRAM)

clean:
	rm -f $(MYPROGRAM) *.o core
