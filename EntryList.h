// CMSC 341 - Spring 2020 - Project 1
//
// Header file for EntryList class
//
// An EntryList is a dynamically-resized array storing Entry objects.
// The Entry objects are stored in ascending order by vertex.
//
// EntryList has one nested class, Entry, which defines the objects
// stored in an EntryList.

#ifndef _ENTRY_LIST
#define _ENTRY_LIST

#include <iostream>  // Standard screen i/o stuff

using std::ostream;

typedef float weight_t;  // typedef for edge weights

class EntryList {

    friend class Grader;

public:

    // Default (initial) size of _array.  The array starts at this size
    // and should never be "shrunk" below this size.
    const int DEFAULT_SIZE = 10;


    // Nested Entry class.  EntryList stores an array of Entry objects.
    // An Entry object stores a vertex number and an edge weight; it has
    // basic getter/setter methods.
    class Entry {
        friend EntryList;
    public:
        Entry(int vertex = 0, weight_t weight = 0) {
            _vertex = vertex;
            _weight = weight;
        }
        int getVertex() const { return _vertex; }
        weight_t getWeight() const { return _weight; }
        void setWeight(weight_t w) { _weight = w; }
        friend ostream& operator<<(ostream& sout, const Entry& e);
    private:
        int _vertex;   // A vertex number
        weight_t _weight;   // An edge weight
    };

    //
    // Constructors and memory management
    //

    // Default constructor.  Creates an EntryList with capacity
    // DEFAULT_SIZE.
    EntryList();

    // Copy constructor, assignment operator, destructor
    EntryList(const EntryList& rhs);
    const EntryList& operator=(const EntryList& rhs);
    ~EntryList();

    //
    // Basic operations
    //

    // Insert the entry e.  The elements of the list must be kept in
    // increasing order by vertex.  If inserting the new element would
    // exceed the capacity of the EntryList, then the array must be
    // expanded, doubling the capacity.  Returns 'true' if new entry
    // inserted, 'false' if there is already an entry with the same
    // vertex as e.
    bool insert(const Entry& e);

    // Update the entry e; return 'true' if an entry with the same
    // vertex as e exists and was updated, 'false' if there is not entry
    // with the same vertex as e.
    bool update(const Entry& e);

    // Get the entry with given vertex value; return the entry in ret.
    // Returns 'true' if an entry with the specified vertex was found,
    // 'false' if there is no entry with the specified vertex.
    bool getEntry(int vertex, Entry &ret);

    // Remove the entry with given vertex value; return the entry that
    // was removed in ret. If, after successfully removing an Entry, the
    // number of Entries is *less than* 1/4 of the capacity, then the
    // EntryList array must be shrunk, halving its capacity.  The
    // capacity must never be reduced below DEFAULT_SIZE, a constant
    // defined EntryList.h.  Returns 'true' if an entry with the same
    // vertex as e exists and was removed, returns 'false' if there is
    // no entry with the specified vertex.
    bool remove(int vertex, Entry &ret);

    // Access an element of the EntryList by index.  Throws range_error
    // if indx is not a valid index into the EntryList's array.
    //
    // WARNING: at() allows modification of an Entry, but changing the
    // vertex value could ruin the ordering of the entries!
    Entry& at(int indx) const;

    // Get the size (numer of Entries actually stored)
    int size() const { return _size; }

    // Get the capacity (size of _array; number of Entries that could be
    // stored without resizing).
    int capacity() const { return _capacity; }

    // Dump the contents of _array.  For debugging.
    void dump();

    // EntryList Iterator class
    class Iterator {

    public:
        // Constructor for iterator for vertices adjacent to vertex v;
        // indx can be used to set _indx for begin and end iterators.
        Iterator(EntryList *EList = nullptr, int indx = 0);

        // Comparison operators for EntryList iterators
        bool operator!=(const Iterator& rhs);
        bool operator==(const Iterator& rhs);

        // Advance iterator to next neighbor; if the iterator is already
        // at the end, leave it unchanged
        void operator++(int dummy);

        // Return neighbor (Entry) at the current iterator position
        EntryList::Entry operator*();

    private:
        EntryList *_ELptr;  // pointer to the associated EntryList
        int _indx;          // current index in the EntryList
    };

    // Create an initial iterator
    EntryList::Iterator begin();

    // Create an end iterator
    EntryList::Iterator end();

private:
    Entry   *_array;
    int _capacity;
    int _size;

    // *****************************************
    void reserve(int N);
    // *****************************************

};

#endif
