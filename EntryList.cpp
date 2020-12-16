
#include "EntryList.h"

using std::cout;
using std::endl;
using std::range_error;

// Constructor - DO NOT MODIFY
EntryList::EntryList() {
    _array = new Entry[DEFAULT_SIZE];
    _capacity = DEFAULT_SIZE;
    _size = 0;
}

EntryList::EntryList(const EntryList& rhs) {


    _array = new Entry [rhs._capacity];
    _capacity = rhs._capacity;
    _size = rhs._size;
    for (int i = 0; i < rhs._size; i++)
    {
        _array[i]._vertex=rhs._array[i]._vertex;
        _array[i]._weight=rhs._array[i]._weight;
    }

}


const EntryList& EntryList::operator=(const EntryList& rhs) {

    if (&rhs != this)
    {
        delete[] _array;

        _array = new Entry [rhs._capacity];
        _capacity=rhs._capacity;
        _size = rhs._size;
        for (int i = 0 ; i < rhs._size ; i++)
        {
            _array[i]._vertex=rhs._array[i]._vertex;
            _array[i]._weight=rhs._array[i]._weight;
        }
    }

    return *this;
}

EntryList::~EntryList() {
    delete[] _array;

}

// Insert the entry e.  The elements of the list must be kept in
// increasing order by vertex.  If inserting the new element would
// exceed the capacity of the EntryList, then the array must be
// expanded, doubling the capacity.  Returns 'true' if new entry
// inserted, 'false' if there is already an entry with the same
// vertex as e.
bool EntryList::insert(const Entry& e) {

    int index,count=0;
    for (int i=0;i<_size;i++)
    {
        if (e._vertex==_array[i]._vertex)
            return false;
        if (e._vertex>_array[i]._vertex)
            count++;
    }
    index=count;
    if (_size>=_capacity)
    {
        reserve(std::max(DEFAULT_SIZE,2*_capacity));
    }

    for (int j=_size-1;j>=index;j--){
        _array[j+1]._vertex=_array[j]._vertex;
        _array[j+1]._weight=_array[j]._weight;
}

    _array[index]._weight=e._weight;
    _array[index]._vertex=e._vertex;
    _size++;
    return true;
}

//In textbook Page 234 Chapter 6
void EntryList::reserve(int cap)
{

    Entry* newArray= new Entry[cap];
    for (int j = 0; j< _size;j++)
        newArray[j]=_array[j];
    if (_array!=NULL)
        delete[] _array;

    this->_array=newArray;
    this->_capacity = cap;
}

// Update the entry e; return 'true' if an entry with the same
// vertex as e exists and was updated, 'false' if there is not entry
// with the same vertex as e.
bool EntryList::update(const Entry& e) {
    bool uped=false;
    for (int i=0;i<_size;i++)
    {
        if (e._vertex!=_array[i]._vertex)
            uped= false;
        else
        {
            _array[i]._weight=e._weight;
            uped=true;
            break;
        }
    }
    return uped;
}


// Get the entry with given vertex value; return the entry in ret.
// Returns 'true' if an entry with the specified vertex was found,
// 'false' if there is no entry with the specified vertex.
bool EntryList::getEntry(int vertex, Entry &ret) {
    for (int i=0;i<_size;i++)
    {
        if (_array[i]._vertex==vertex)
        { ret._vertex=_array[i]._vertex;
            return true;   }
    }
    return false;
}
// Remove the entry with given vertex value; return the entry that
// was removed in ret. If, after successfully removing an Entry, the
// number of Entries is *less than* 1/4 of the capacity, then the
// EntryList array must be shrunk, halving its capacity.  The
// capacity must never be reduced below DEFAULT_SIZE, a constant
// defined EntryList.h.  Returns 'true' if an entry with the same
// vertex as e exists and was removed, returns 'false' if there is
// no entry with the specified vertex.
bool EntryList::remove(int vertex, Entry &ret) {

    int index=0;
    bool found=false;
    for (int i=0;i<_size;i++)
    {
        if (_array[i]._vertex==vertex)
        {
            index=i;
            found=true;
            ret._vertex=_array[i]._vertex;
            break;
        }
    }

    for (int j = index+1 ; j<_size; j++)
        _array[j-1]=_array[j];

    _size--;

    if (_size<_capacity/4)
        reserve(std::max(DEFAULT_SIZE,_capacity/2));

    return found;
}
// Access an element of the EntryList by index.  Throws range_error
// if indx is not a valid index into the EntryList's array.
// WARNING: at() allows modification of an Entry, but changing the
// vertex value could ruin the ordering of the entries!
EntryList::Entry& EntryList::at(int indx) const {
    bool found=false;
    for (int i=0; i <_size; i++)
    {
        if (i==indx)
        { found = true; break; }
    }
    if (found!=true)
        throw range_error("No index found");

    return _array[indx];
}


// dump data structure - DO NOT MODIFY
void EntryList::dump() {

    for (int i = 0; i < _size; i++) {
        cout << "  " << _array[i] << endl;
    }
}
//EntryList *_ELptr;  // pointer to the associated EntryList
//Constructor for iterator for an EntryList object; indx can be used to set _indx for begin and end iterators.
EntryList::Iterator::Iterator(EntryList *EList, int indx) {
    _ELptr=EList; _indx=indx;
}

//Comparison operators for EntryList iterators.
bool EntryList::Iterator::operator!=(const EntryList::Iterator& rhs) {
    if ((_ELptr!=rhs._ELptr) ||(_indx!=rhs._indx))
        return true;
    else return false;
}

bool EntryList::Iterator::operator==(const EntryList::Iterator& rhs) {
    if ((_ELptr==rhs._ELptr) &&(_indx==rhs._indx))
        return true;
    else return false;
}

//Advance the iterator to the next entry; if the iterator is already at the end, leave it unchanged.
void EntryList::Iterator::operator++(int dummy) {
    if (_indx < _ELptr->size())
        _indx++;
}

EntryList::Entry EntryList::Iterator::operator*() {

    return _ELptr->_array[_indx];
}

EntryList::Iterator EntryList::begin() {
    return EntryList::Iterator(this, 0 );
}

EntryList::Iterator EntryList::end() {
    return EntryList::Iterator(this,_size);
}

// Insertion operator for Entry objects - DO NOT MODIFY
ostream& operator<<(ostream& sout, const EntryList::Entry& e) {
    sout << e._vertex << ": " << e._weight;
    return sout;
}
