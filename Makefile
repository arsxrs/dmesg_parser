src = $(wildcard *.cpp)
obj = $(src:.c=.o)

LDFLAGS = -lavrocpp_s -lboost_program_options  -lboost_iostreams


parse_dmesg: $(obj)
	g++ -o $@ $^ $(LDFLAGS)

