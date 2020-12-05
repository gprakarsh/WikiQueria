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

$(EXENAME): build/main.o build/Graph.o build/Vertex.o build/Edge.o build/BFS.o build/Mock.o
	$(LD) $^ $(LDFLAGS) -o $(EXENAME)

build/readFromFile.o: src/readFromFile.cpp headers/readFromFile.hpp
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@ 

build/main.o: src/main.cpp headers/Graph.h headers/Vertex.h headers/Edge.h
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

build/Mock.o: src/Mock/Mock.cpp headers/Mock.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

build/BFS.o: src/BFS/BFS.cpp headers/Graph.h headers/Vertex.h headers/Edge.h headers/BFS.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

build/catch.o: tests/catch.cpp tests/catch.hpp
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

test: tests/tests.cpp build/catch.o tests/catchmain.cpp build/Vertex.o build/Graph.o build/Edge.o build/BFS.o build/Mock.o
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