#!/bin/bash

for thousands in {10..30}
do
RUN=$(( thousands * 10000 ))
for sample in {1..5}
do
	/usr/bin/time --format="$RUN,$sample,%M" ./finalproj>/dev/null ../large-names.csv ../large-edge.txt $RUN
if [ $? -ne 0 ]
then
	exit 1
fi
done
done
