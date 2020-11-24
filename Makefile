# =================== SETTINGS ===================
EXENAME = finalproj

CXX			:=	clang++
CXXFLAGS	:=	$(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic -Iheaders
LD			:=	clang++
LDFLAGS		:=	-std=c++1y -stdlib=libc++ -lc++abi -lm -Iheaders
#----------------------------------------------

define make-build-dir
	@mkdir -p build
endef 

.PHONY: all-data all clean

# $^ = all dependencies
# $< = first dependency
# $@ = target

all : $(EXENAME)

$(EXENAME): build/main.o build/Edge.o build/Graph.o build/Vertex.o
	$(LD) $^ $(LDFLAGS) -o $(EXENAME)

build/main.o: src/main.cpp headers/Graph.h headers/Vertex.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@ 

build/Graph.o: src/GraphADT/Graph.cpp headers/Graph.h headers/Vertex.h headers/Edge.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

build/Vertex.o: src/GraphADT/Vertex.cpp headers/Vertex.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

build/Edge.o: src/GraphADT/Edge.cpp headers/Edge.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

test: tests/tests.cpp tests/catchmain.cpp
	$(LD) $^ $(LDFLAGS) -o test

clean:
	rm -rf build/ $(EXENAME) test

# =================== CREATE DATA ===================

all-data: data/enwiki-2013-names.csv data/enwiki-2013.txt

data/enwiki-2013-names.csv: data
	curl --output data/enwiki-2013-names.csv.gz 'https://snap.stanford.edu/data/enwiki-2013-names.csv.gz'
	gunzip -d data/enwiki-2013-names.csv.gz 

data/enwiki-2013.txt: data
	curl --output data/enwiki-2013.txt.gz 'https://snap.stanford.edu/data/enwiki-2013.txt.gz'
	gunzip -d data/enwiki-2013.txt.gz

data:
	mkdir data