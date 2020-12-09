# Development

## Week 1 (11/21 to 11/29)

In the first week, we established our goals to work on the BFS traversal and the A* Search, and Landmark Path algorithms.
We all met several times over break, and discussed various aspects of the project, including the project structure, the underlying data structure for the graph, and the desired API of the data structure.
We first had an implementation that used pointers to keep track of various vertices.
However, because of concerns about memory management and readability and bad pointer usage, we then began work on implementing all pointer-like operations with iterators to STL containers instead.
While memory management would no longer be an issue, a problem that we faced was readability and usage -- while STL is "safer" than pointers, pointers are easier to reason about than STL containers and iterators.
Simultaneously, when some of our group members tried to work on A*, we realized that this algorithm did not make sense for our dataset (since we have no heuristic), and we met again to decide to switch to **_Dijkstra's Algorithm_** instead.
By Nov. 29th, we had a Graph data structure with a clean API that we can now use for algorithms. This GraphADT data structure also has its own tests where each group member contributed for atleast one test.

## Week 2 (11/29 to 12/04)

This week was very crucial for us and we got a lot of roadblocks removed. We completed the Graph ADT implementation and also did a lot of research on Dijkstra implementation and Landmark path problem implementation.
We realized that Dijkstra would not be a useful algorithm for us, since the edges are unweighted, so we started looked into the Strongly Connected Components algorithm. We also wrote out tests for our graph, vertex and edge implementations. We also had our check in meeting with our TA assigned to the project and discussed our plan moving forward. After the meeting, we realized that we should also get started on pre-processing our data which we worked upon and have it more or less completed. We have also implemented a user interface that the user can use if they want to display the graph, and we introduced functionality to import data from files passed as CLI arguments, so we didn't have to recompile every time we had new data.
We also created a Python script to automatically generate mock data, using `networkx`. We did this so that we can make sure input validation will always work, and more importantly, when we start implementing strongly connected components, we can check our algorithm against `networkx`'s results. 
This week we also had multiple team meetings and our Discord channel was also very active. Our plan moving forward is to complete whatever development work is left by the weekend and finish wrapping up the project by mid of next week. 
