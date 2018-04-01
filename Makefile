CPPFLAGS="-MD"
CPPFLAGS="-c"
INCLUDE="-I libevent/libevent_ext"
OBJS=main.o
OBJS+=cwmp_config.o
ALIBS+=libevent/lib/libevent.a
ALIBS+=libevent/lib/libevent_core.a
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
	
