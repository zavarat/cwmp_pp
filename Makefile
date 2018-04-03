CPPFLAGS="-MD"
CPPFLAGS="-c"
INCLUDE="-Ilibevent/libevent_ext"
INCLUDE+="-Iboost"
OBJS=main.o
OBJS+=cwmp_config.o
ALIBS+=libevent/lib/libevent.a
ALIBS+=libevent/lib/libevent_core.a
ALIBS+=boost/bin.v2/libs/program_options/build/gcc-7.3.1/release/link-static/threading-multi/libboost_program_options.a
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
	
