CPPFLAGS="-c"
INCLUDE="-I libevent/libevent_ext"
OBJS="main.o"
OBJS+="libevent/lib/libevent.a"
OBJS+="libevent/lib/libevent_core.a"
CPPFLAGS+="$(INCLUDE) "


all: libevent_prepare libevent_build main
	
libevent_prepare:
	@{ cd libevent; cmake libevent_ext; }

libevent_build:
	@{ cd libevent; make; }

main: main.o
	g++ $(OBJS) -o cwmp_pp

main.o:
	g++ $(CPPFLAGS) main.cpp
	
