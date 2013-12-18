AlgoHW2.1
=========

Algo Part2.1
Comprises of the following things
1. Clustering Algo for edges with weight given in input file. Required number of Clusters is 4.
2. UnionFind data structure
  a.Union : Merges two clusters and keeps track of the leaders.
  b.Find  : Finds the leaders of any two nodes in a Graph.
  c.Decompile : Prints the No of Clusters and nodes in a cluster at specific time.
  d.Member :: Graph : Pointer to a vector of nodes.
3. Heap Data Structure
  a. Extract-Min: Gives the minimum weight edge in the heap.
  b. Insert     : Inserts a edge into the heap.
  c. Free Heap  : Frees the memory taken by heap container at the end of the code execution.
4. Input file


Build Instructions
1. Run ./build.sh in the current directory.

Execution Instruction
1. Run ./Clustering for the specified input file.
