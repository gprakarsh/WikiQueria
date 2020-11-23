.PHONY: all-data
all-data: data/enwiki-2013-names.csv data/enwiki-2013.txt

data/enwiki-2013-names.csv: data
	curl --output data/enwiki-2013-names.csv.gz 'https://snap.stanford.edu/data/enwiki-2013-names.csv.gz'
	gunzip -d data/enwiki-2013-names.csv.gz 

data/enwiki-2013.txt: data
	curl --output data/enwiki-2013.txt.gz 'https://snap.stanford.edu/data/enwiki-2013.txt.gz'
	gunzip -d data/enwiki-2013.txt.gz

data:
	mkdir data

