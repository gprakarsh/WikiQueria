# bathula2-pg12-rishic2-sahansk2
Final Project

# Disclaimer

We assume that you are running on EWS for all of these commands.

## Step 1: Setting up datasets

### Original Dataset

We are using [Stanford's English Wikipedia Hyperlink Network](https://snap.stanford.edu/data/enwiki-2013.html).
You may download and extract the files yourself, but we also provide a Makefile recipe for convenience.

To download the data, run:

```
make all-data
```

After this command is complete, you will see a new directory and two new files:

```
./data/
├── enwiki-2013-names.csv
└── enwiki-2013.txt
```

### Custom datasets

If you wish to run your own data, you may do so. We expect that the data you provide will be in this format:

Vertex file -- the first field is the vertex ID, and the second field is the name of the page represented by the vertex ID.

```
0,"First page"
1,"Second page"
2,"Third page"
3,"Commas in quotes, they're okay"
```

Edge file -- vertex IDs are separated by a space, and there is a newline separating each edge. The first field is the source vertex ID, the second field is the destination vertex ID.

```
0 1
1 2
2 3
3 10
3 4
```

If you would like to create your own fake data to run with this, but don't want to deal with the tediousness, please see the section **Generating Fake Data** to see how you can painlessly create compatible data.

## Step 2: Building and running the program
First, be sure to load the necessary environment:

```
module load llvm/6.0.1
```

Then, run `make all` to build all binaries:

* `finalproj`
* `benchmark`
* `test`

## `finalproj`

Binary to launch interactive tool for graph processing.

Invocation:

```
./finalproj [-e LIMIT] path-to-vertex-file path-to-edge-file
```

The `-e` flag is optional. If specified, it will limit the number of loaded edges from the original file. Otherwise, no limit is assumed.

If you are loading the original dataset, we recommend you specify this, since the original dataset has `101311614` edges. 

TODO: note the maximum number of edges loaded before SCCGraph caused a segfault.

TODO: Explain which menu would be most useful in grading correctness of algorithms


## `test`

Test binary to run unit tests.

Invocation:

```
./test [FILTERS]
```

Filters:

* `[graphadt]`: Run tests related to the graph data structure. Primary file: `tests/tests-graphadt.cpp`
* `[bfs]`: Run tests related to BFS. Primary file: `tests/tests-bfs.cpp`
* `[scc]`: Run tests related to the generation and output of detecting strongly connected components. Primary file: `tests/tests-scc.cpp`
* `[landmark]`: Run tests related to finding a landmark path. Primary file: `tests/tests-landmark.cpp`
* `[parsing]`: Run tests related to file processing and user input validation. Primary file: `tests/tests-misc.cpp`

Please do not modify or rename the files in `tests/mock-data/`. You may have trouble with running this binary otherwise.


## `benchmark`

Binary to output timing metrics of various options on a certain swept parameter. 
It will output CSVs to `stderr`, so if you run this program, we recommend you redirect `stderr` to a file of your choice so you can use your data as a CSV however you want.
The first field of the CSV is the value used in that run. The second field is the recorded runtime in milliseconds.

Here is an explanation of arguments:

* `-m SAMPLES`: Sets the number of samples for metrics -- the average of all values will be recorded. Default is `10`.
* `-e EDGES`: Limits the number of loaded edges. Default is no limit.
* `--bfs`: Sets benchmarking to track BFS runtime. Sweeps number of BFS steps.
* `--scc`: Sets benchmarking to track SCC algorithm runtime. Sweeps number of edges. This flag will disable `-e`

Sweeping arguments (**REQUIRED**):

* `--from START`: Sweep values from `START`.
* `--step SIZE`: Increase values by `SIZE` every step.
* `--count STEPS`: Record `STEPS` number of steps.


General invocation:

```
./benchmark [ARGS] vertex-file edge-file
```

Example invocations:

```
./benchmark -m 10 -e 20000 --bfs --from 1600 --step 200 --count 12 ./data/enwiki-2013-names.csv ./data/enwiki-2013.txt 2>bfs-metric.csv
```

For details, run `./benchmark`.

# Generating fake data

We provide a Python script that lets you create mock data that works with our program.

## Prerequisites

This program requires Python 3, and it requires the use of the `networkx` module.
If you do not already have it, you can install it by running

```
pip3 install --user networkx
```
## Usage

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