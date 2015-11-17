sorttest_SRCS = test.cxx

CFLAGS += -std=gnu++11 -flto -O3 -DNDEBUG
LDFLAGS += -flto

all: sorttest

sorttest: $(sorttest_SRCS:.cxx=.o)
	$(CXX) -o $@ $^ -lboost_program_options $(LDFLAGS)

%.o: %.cxx
	$(CXX) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f sorttest
