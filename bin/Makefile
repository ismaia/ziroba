#Makefile: Ziroba Robot Project
#By Isaac Maia
LIBSDIR=../libs
SRCDIR=../src
CPP=g++
C=gcc


C_CFLAGS=-std=gnu11 -O2 -I$(SRCDIR)/bbb
C_LDFLAGS=-lbluetooth -lreadline -lncurses

CPP_CFLAGS=-std=gnu++11 -O2 -I$(LIBSDIR)/blacklib -I$(SRCDIR)/bbb
CPP_LDFLAGS=-L$(LIBSDIR)/blacklib -L$(LIBSDIR)/zirobalib -lncurses -lblacklib -lbluetooth 


BINDIR=./bin
SRCDIR=../src

C_SOURCES=$(wildcard $(SRCDIR)/bbb/*.c)
C_BINS=$(basename $(notdir $(C_SOURCES)))

CPP_SOURCES=$(SRCDIR)/bbb/ziroba_keypad.cpp \
	    $(SRCDIR)/bbb/joystick_client.cpp \
	    $(SRCDIR)/bbb/ziroba_server.cpp \
	    $(SRCDIR)/bbb/servo.cpp

CPP_BINS=$(basename $(notdir $(CPP_SOURCES)))

CPP_LIBSOURCES=$(SRCDIR)/bbb/ZirobaRobot.cpp 
CPP_LIBOBJS=$(addsuffix .o, $(basename $(notdir $(CPP_LIBSOURCES))))

all: $(C_BINS) $(CPP_BINS) $(CPP_LIBS_UPCASE)	
	        
% : $(SRCDIR)/bbb/%.c  
	$(C)  $(C_CFLAGS) $< -o $@  $(C_LDFLAGS)

% : $(SRCDIR)/bbb/%.cpp $(CPP_LIBOBJS) 
	$(CPP)  $(CPP_CFLAGS) $< -o $@ $(CPP_LIBOBJS) $(CPP_LDFLAGS)

%.o : $(SRCDIR)/bbb/%.cpp 
	$(CPP)  $(CPP_CFLAGS) -c $< -o $@  $(CPP_LDFLAGS)


clean:
	rm -f $(C_BINS) $(CPP_BINS) $(CPP_LIBBINS) $(CPP_LIBOBJS)

debug:
	@echo $(CPP_SOURCES)
	@echo $(CPP_BINS)
	@echo $(C_SOURCES)
	@echo $(C_BINS)
	@echo $(CPP_LIBSOURCES)	
	@echo $(CPP_LIBOBJS)
