hdr = $(wildcard *.h)
src = $(wildcard *.C)
obj = $(src:.C=.o)
exe = Kindergarten

all: $(exe)

$(exe): $(obj)
	g++ -g -std=c++0x $(obj) -o $@

%.o: %.C $(hdr)
	g++ -c -g -Wall -std=c++0x $< -o $@

clean: 
	rm $(obj) $(exe)
