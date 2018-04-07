CPPFLAGS="-MD"
CPPFLAGS+="-c"
CPPFLAGS+="-Wfatal-errors"
INCLUDE="-Ilibevent/libevent_ext/include"
INCLUDE+="-Ilibevent/include"
INCLUDE+="-Iboost"
OBJS=main.o
OBJS+=cwmp_config.o
ALIBS+=libevent/lib/libevent.a
ALIBS+=libevent/lib/libevent_core.a
ALIBS+=boost/stage/lib/libboost_program_options.a
CPPFLAGS+=$(INCLUDE)

all: libevent_prepare libevent_build main
	
libevent_prepare:
	@{ cd libevent; cmake libevent_ext; }

libevent_build:
	@{ cd libevent; make; }

main: $(OBJS) 
	g++ $(OBJS) $(ALIBS) -o cwmp_pp

%.o: %.cpp 
	g++ $(CPPFLAGS) $^
	
clean:
	rm *.o cwmp_pp
