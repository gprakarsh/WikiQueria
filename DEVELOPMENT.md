# Development

## Week 1 (11/16 to 11/29)

In the first week, we established our goals to work on the BFS traversal and the A* Search, and Landmark Path algorithms.
We all met several times over break, and discussed various aspects of the project, including the project structure, the underlying data structure for the graph, and the desired API of the data structure.
We first had an implementation that used pointers to keep track of various vertices.
However, because of concerns about memory management and readability and bad pointer usage, we then began work on implementing all pointer-like operations with iterators to STL containers instead.
While memory management would no longer be an issue, a problem that we faced was readability and usage -- while STL is "safer" than pointers, pointers are easier to reason about than STL containers and iterators.
Simultaneously, when some of our group members tried to work on A*, we realized that this algorithm did not make sense for our dataset (since we have no heuristic), and we met again to decide to switch to **_Dijkstra's Algorithm_** instead.
By Nov. 29th, we had a Graph data structure with a clean API that we can now use for algorithms. This GraphADT data structure also has its own tests where each group member contributed for atleast one test.

## Week 2 (11/30 to 12/04)

We completed the Graph ADT implementation and also did a lot of research on Dijkstra implementation and Landmark path problem implementation.
We realized that Dijkstra would not be a useful algorithm for us, since the edges are unweighted, so we started looked into the Strongly Connected Components algorithm. We also wrote out tests for our graph, vertex and edge implementations. We also had our check in meeting with our TA assigned to the project and discussed our plan moving forward. After the meeting, we realized that we should also get started on pre-processing our data which we worked upon and have it more or less completed. We have also implemented a user interface that the user can use if they want to display the graph, and we introduced functionality to import data from files passed as CLI arguments, so we didn't have to recompile every time we had new data.
We also created a Python script to automatically generate mock data, using `networkx`. We did this so that we can make sure input validation will always work, and more importantly, when we start implementing strongly connected components, we can check our algorithm against `networkx`'s results. 
This week we also had multiple team meetings and our Discord channel was also very active. Our plan moving forward is to complete whatever development work is left by the weekend and finish wrapping up the project by mid of next week. 

## Week 3 (12/05 to 12/11)

In this week, the bulk of the final algorithm implementations were done. We decided to implement the strongly connected components algorithm as a class that inherits from `Graph`, so that we can easily run BFS traversals and queries on it. We also fixed a bug in our file parsing, where we were reading in the quotes. With both of these fixed, we were able to implement the Landmark Path algorithm in the `Graph` class, which meant that it also worked in the `SCCGraph` class. We were able to optimize our Landmark Path algorithm by running it on the `SCCGraph` class first, and then running the true Landmark path algorithm on the original Graph if the call to `SCCGraph` did not return an empty vector. We also added dumping of graphs as images using Graphviz to the UI.
We created an ArgumentParser class to help with passing in command line arguments. These command line arguments could limit the number of edges loaded, which is crucial since our program could not handle many edges before running out of RAM, and we want to make sure our program was usable.
We also created the `benchmark` binary to time our functions, complete with many command line arguments. It gave an expected linear runtime for the creation of SCCGraph, but we detected that our BFS algorithm was quadratic on vertices instead of linear. We solved this by refactoring the inner data structure to keep track of an `unvisited` set, instead of iterating through the entire graph's vertices to find an unvisited vertex.