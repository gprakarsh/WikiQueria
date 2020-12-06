# bathula2-pg12-rishic2-sahansk2
Final Project

# Disclaimer

We assume that you are running on EWS for all of these commands.

## Profiling

We provide a Bash script that lets you easily profile the memory usage of our program, specifically with regards to loading edges. It outputs a CSV to STDOUT in the columns:

```
"number of edges loaded","sample number","memory usage in KiB"
```

### Prerequisites

On EWS, there are no extra prerequisites.

### Usage

The invocation of `profile.sh` is as follows:

```
./profile.sh 2>&1 NUM_SAMPLES NUM_START NUM_END IN_NAMES IN_EDGES"
```

There are five required arguments, appearing in this order:

`NUM_SAMPLES`
* Number of samples to be taken for each edge-count
* ex. `5`

`NUM_START`
* The initial number of edges to sweep through, in tens of thousands
* ex. `10`

`NUM_END`
* The final number of edges to sweep through, in tens of thousands
* ex. `40`

`IN_NAMES`
* The name of the input file containing vertex names
* ex. `tests/mock-data/large-names.csv`

`IN_EDGES`
* The name of the input file containing the edges
* ex. `tests/mock-data/large-edges.txt`

An example invocation using the example arguments above would look like this:

```
./profile.sh 2>&1 5 10 40 tests/mock-data/large-names.csv tests/mock-data/large-edges.txt
```

## Generating fake data

We provide a Python script that lets you create mock data that works with our program.

### Prerequisites

This program requires Python 3, and it requires the use of the `networkx` module.
If you do not already have it, you can install it by running

```
pip3 install --user networkx
```
### Usage

After you do this, simply invoke the python script by running it in this manner:

```
python3 ./make-mock.py OUTNAMES OUTEDGES OUTSCCFILE VERTEXCOUNT CONNECTEDNESS
```

There are four required arguments, and they must appear in this order:

`OUTNAMES`
* output filename for generated names
* example: `data/wiki-names.txt`

`OUTEDGES`:
* output filename for generated edges
* example: `data/wiki-edges.txt`

`OUTSCCFILE`:
* output filename for detected strongly connected components by `networkx`
* example: `data/wiki-scc.txt`

`VERTEXCOUNT`
* number of vertices
* example: `10`

`CONNECTEDNESS`
* a decimal from [0, 1.0] representing the probability any given directed edge exists
* example: `0.03`

An example invocation with the example arguments listed above would look like this:

```
python3 ./make-mock.py data/wiki-names.txt data/wiki-edges.txt 10 0.03
```

This will output the vertex name labels to a file `data/wiki-names.txt`, and the edge list to a file `data/wiki-edges.txt`.

**Warning!** The expected number of edges using this file, given probability `p` and vertex count `n` is `n(n-1)p/2`.
For example, with `n=5000` and `p=0.05`, the expected number of edges is `624875`. 
The program will output your expected number of edges before you continue. Please be careful and pay attention, you might wreck your RAM otherwise!