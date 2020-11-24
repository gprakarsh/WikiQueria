# =================== SETTINGS ===================
EXENAME = finalproj

CXX			:=	clang++
CXXFLAGS	:=	$(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic -Iheaders
LD			:=	clang++
LDFLAGS		:=	-std=c++1y -stdlib=libc++ -lc++abi -lm -Iinclude
#----------------------------------------------
define make-build-dir
	@mkdir -p build
endef 

.PHONY: all-data all clean output_msg

# $^ = all dependencies
# $< = first dependency
# $@ = target

all : $(EXENAME)

$(EXENAME): build/main.o build/readFromFile.o build/Graph.o build/Vertex.o
	$(LD) $^ $(LDFLAGS) -o $(EXENAME)

build/readFromFile.o: src/readFromFile.cpp include/readFromFile.hpp
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

build/main.o: src/main.cpp include/readFromFile.hpp
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@ 

build/Graph.o: src/Preprocess/Graph.cpp include/Preprocess/Graph.h include/Preprocess/Vertex.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

build/Vertex.o: src/Preprocess/Vertex.cpp include/Preprocess/Vertex.h
	$(make-build-dir)
	$(CXX) $(CXXFLAGS) $< -o $@

test: tests/tests.cpp tests/catchmain.cpp build/readFromFile.o
	$(LD) tests/tests.cpp tests/catchmain.cpp build/readFromFile.o $(LDFLAGS) -o test

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