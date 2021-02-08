// CMSC 341 - Spring 2020 - Project 1
//
// Header file for the Graph class
//
// Graph has two nested iterator classes:
//   (1) EgIterator - edge iterator
//   (2) NbIterator - neighbor iterator

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "EntryList.h"  // Uses EntryList objects for ajacency lists
#include <iostream>     // Standard screen i/o stuff
#include <stdexcept>    // For invalid_argument exceptions
#include <tuple>        // For tuple template

using std::ostream;
using std::tuple;
using std::pair;

class Graph {

  friend class Grader;
  
public:

  //
  // Constructors and memory management
  //
  
  // Graph constructor; must give number of vertices (n).  Throws
  // invalid_argument if n <= 0.
  Graph(int n);

  // Graph copy constructor, assignment operator, destructor
  Graph(const Graph& G);
  const Graph& operator=(const Graph& rhs);
  ~Graph();

  //
  // Basic operations
  //
  
  // Return number of vertices
  int numVert() const;

  // Return number of edges
  int numEdge() const;

  // Add an edge between u and v with weight x.  Throws
  // invalid_argument if u or v is not a valid vertex number.
  void addEdge(int u, int v, weight_t x);

  // Remove the edge (u, v).  Returns 'true' if an edge is removed;
  // 'false' if there is no edge (u,v). Throws invalid_argument if u
  // or v is not a valid vertex number
  bool removeEdge(int u, int v);

  // print out data structure for debugging
  void dump() const;

  //
  // Iterators
  //
  
  // Edge Iterator inner class
  class EgIterator {

  public: 
    // Edge Iterator constructor.
    //   If Gptr is nullptr, create an unitialized iterator.
    //   If Gptr points to a host Graph object:
    //      If enditr == false, create a begin() iterator.
    //      If enditr == true, create an end() iterator.
    EgIterator(Graph *Gptr = nullptr, bool enditr = false);

    // Compare two iterators.  Mainly used to end a for loop using the
    // iterator.
    bool operator!= (const EgIterator& rhs);
	 
    // Advanced the iterator to the next edge; if already at the end()
    // iterator, leave unchanged.  Throws invalid_argument if the
    // iterator is uninitialized.
    void operator++(int dummy); 

    // Return edge at iterator location as a tuple (u, v, weight).
    // Throws invalid_argument if the iterator is uninitialized or if
    // derefrence of _itr failes.
    tuple<int,int,weight_t> operator*();

  private:
    Graph *_Gptr;                 // Pointer to host Graph
    int _row;                     // Current row of the matrix
    EntryList::Iterator _itr;     // Iterator to current row
  };

  // Create an initial edge Iterator.
  EgIterator egBegin();

  // Create an end edge Iterator.
  EgIterator egEnd();

  // Neighbor Iterator inner class
  class NbIterator {
    
  public: 
    // Constructor for iterator for vertices adjacent to vertex v.
    //   If Gptr == nullptr, creat an uninitialized iterator.
    //   If Gptr points to a host Graph object:
    //      If enditr == true, create an end iterator for row v.
    //      If enditr == false, crete a begin iterator for row v.
    // Throws invalid_argument if v is not a valid vertex number.
    NbIterator(Graph *Gptr = nullptr, int v = 0, bool enditr = false);

    // Compare iterators.
    bool operator!=(const NbIterator& rhs);

    // Advance iterator to the next neighbor.
    void operator++(int dummy);

    // Return neighbor and weight at current iterator position. Throws
    // invalid_argument if the iterator is null or invalid.
    pair<int,weight_t> operator*();

  private:
    Graph *_Gptr;               // Pointer to host Graph
    int _row;                   // Row (source vertex) over which we
				// are iterating
    EntryList::Iterator _itr;   // Iterator to the current row (which
				// is an EntryList)
  };

  // Make an initial neighbor iterator for row v.  Throws
  // invalid_argument if v is not a valid node index.
  NbIterator nbBegin(int v);

  // Make an end neighbor iterator. Throws invalid_argument if v is
  // not a valid node index.
  NbIterator nbEnd(int v);

private:
  EntryList **_rows;  // Array of pointers to EntryLists. _rows[i]
		      // points to an EntryList object, the adjacency
		      // list for vertex i.
  int _numVert;       // number of vertices in the graph
  int _numEdge;       // number of edges in the graph
};

#endif
