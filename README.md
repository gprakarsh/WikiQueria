# bathula2-pg12-rishic2-sahansk2
Final Project

# Disclaimer

We assume that you are running on EWS for all of these commands.

## Generating fake data

We provide a Python script that lets you create mock data that works with our program.

### Prerequisites

This program requires Python 3, and it requires the use of the `networkx` module.
If you do not already have it, you can install it by running

```
pip3 install --user networkx
```

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