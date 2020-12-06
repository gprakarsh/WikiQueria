#!/bin/bash
NUM_SAMPLES=$1
NUM_START=$2
NUM_END=$3
if [ -z $5 ]
then
echo "Usage: ./profile.sh 2>&1 NUM_SAMPLES NUM_START NUM_END IN_NAMES IN_EDGES"
echo "NUM_START and NUM_END are in tens of thousands"
exit 1
fi

shift 3
IN_NAMES=$1
IN_EDGES=$2

for ((i=NUM_START;i<=NUM_END;i++));
do
RUN=$(( i * 10000 ))
for ((sample=1;sample<=NUM_SAMPLES;sample++));
do
	/usr/bin/time --format="$RUN,$sample,%M" ./finalproj>/dev/null $1 $2 -x $RUN
if [ $? -ne 0 ]
then
	exit 1
fi
done
done
