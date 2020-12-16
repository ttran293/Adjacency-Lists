#include <iostream>
#include "Graph.h"
#include "EntryList.h"
#include <tuple>

using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;

using namespace std;

// Constructor - DO NOT MODIFY
Graph::Graph(int n) {
    if (n <= 0)
        throw invalid_argument("Graph::Graph(): number of vertices must be positive");

    _rows = new EntryList*[n];
    for (int i = 0; i < n; i++) {
        _rows[i] = new EntryList();
    }
    _numVert = n;
    _numEdge = 0;
}

Graph::Graph(const Graph& G) {
    if (G._numVert <= 0)
        throw invalid_argument("Graph::Graph(): number of vertices must be positive");

    _rows = new EntryList*[G._numVert];
    for ( int i = 0; i < G._numVert; i++ )
    {
        _rows[i] = new EntryList;
        for ( int j = 0; j < G._rows[i]->size(); j++)
            _rows[i]->insert(G._rows[i]->at(j));
    }
    _numVert = G._numVert;
    _numEdge = G._numEdge;
}

const Graph& Graph::operator=(const Graph& rhs) {
    if (rhs._numVert <= 0)
        throw invalid_argument("Graph::Graph(): number of vertices must be positive");
    if (this != &rhs)
    {
        for (int i = 0; i < _numVert; i++)
            delete _rows[i];
        delete[] _rows;

        _rows = new EntryList*[rhs._numVert];
        for ( int i = 0; i < rhs._numVert; i++ )
        {
            _rows[i] = new EntryList;
            for ( int j = 0; j < rhs._rows[i]->size(); j++ )
                _rows[i]->insert(rhs._rows[i]->at(j));
        }
        _numVert = rhs._numVert;
        _numEdge = rhs._numEdge;
    }
    return *this;
}

Graph::~Graph() {
    for (int i = 0; i < _numVert; i++)
        delete _rows[i];
    delete[] _rows;
}

// Number of vertices - DO NOT MODIFY
int Graph::numVert() const {
    return _numVert;
}

// Number of edges - DO NOT MODIFY
int Graph::numEdge() const {
    return _numEdge;
}

void Graph::addEdge(int u, int v, weight_t x) {


    if ((u < 0 || u > _numVert) || (v < 0|| v>_numVert))
        throw invalid_argument("Invalid vertex");

    _rows[u]->insert(v);
    _rows[u]->update( EntryList::Entry(v, x));
    _numEdge++;

}

bool Graph::removeEdge(int u, int v) {
    if ((u < 0 || u > _numVert) || (v < 0|| v>_numVert))
        throw invalid_argument("Invalid vertex");

    EntryList::Entry e;
    _numEdge--;
    return _rows[u]->remove(v,e);
}

///////////////////////////////////////////////////////////////////////////////////////
// Dump the graph - DO NOT MODIFY
void Graph::dump() const {

    cout << "Dump of graph (numVert = " << _numVert
         << ", numEdge = " << _numEdge << ")" << endl;

    for (int i = 0; i < _numVert; i++) {
        cout << "Row " << i << ": \n";
        _rows[i]->dump();
    }
}
// Edge Iterator constructor.
//   If test is nullptr, create an unitialized iterator.
//   If test points to a host Graph object:
//      If enditr == false, create a begin() iterator.
//      If enditr == true, create an end() iterator.
Graph::EgIterator::EgIterator(Graph *Gptr, bool enditr) {

    if (Gptr == nullptr)
        _itr;
    else
    {
        _Gptr=Gptr;
        if (enditr==false)
        {
            int index=-1;
            for (int i=0; i <= (_Gptr->_numVert-1);i++)
            {
                if (_Gptr->_rows[i]->size()!=0)
                {
                    index=i;
                    break;
                }
            }
            _row = index;
            _itr=_Gptr->_rows[_row]->begin();
        }
        if (enditr==true)
        {
            int index=0;
            for (int i=_Gptr->numVert()-1; i>=0;i--)
            {
                if (_Gptr->_rows[i]->size()!=0)
                {
                    index=i;
                    break;
                }
            }
            _row = index;
            _itr=_Gptr->_rows[_row]->end();

        }
    }
}
// Return edge at iterator location as a tuple (u, v, weight).
// Throws invalid_argument if the iterator is uninitialized or if
// derefrence of _itr failes.
tuple<int,int,weight_t> Graph::EgIterator::operator*() {
    if (_itr.operator!=(nullptr)
        ||_itr.operator*().getVertex()!=0
            ||_itr.operator*().getWeight()!=0)
    {
        return std::tuple<int,int,int>
                (_row,
                 _itr.operator*().getVertex(),
                 _itr.operator*().getWeight());
    }
    else
        throw invalid_argument("wrong");

}
// Compare two iterators.  Mainly used to end a for loop using the
// iterator.
bool Graph::EgIterator::operator!=(const EgIterator& rhs) {
    return _itr.operator!=(rhs._itr);
}

void Graph::EgIterator::operator++(int dummy) {
    auto temp=_itr;
    temp++;
    if (temp.operator==(_Gptr->egEnd()._itr))
    {
        _itr=_Gptr->_rows[_row]->end();
    }
    else
    {
        if (temp==_Gptr->_rows[_row]->end())
        { int next = -1;
            for (int i = _row+1; i < _Gptr->numVert() - 1; i++)
            {
                if (_Gptr->_rows[i]->size() > 0)
                {
                    next=i;
                    break;
                }
            }
            _row=next;
            _itr=_Gptr->_rows[_row]->begin();}
        else
            _itr.operator++(dummy);

    }
}

Graph::EgIterator Graph::egBegin() {
    return Graph::EgIterator(this, false);
}

Graph::EgIterator Graph::egEnd() {
    return Graph::EgIterator(this, true);
}

Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool enditr)
{
    if (v < 0)
        throw invalid_argument("Invalid vertex");
    if (Gptr == nullptr)
        _itr;
    else {
        _Gptr=Gptr;
        if (enditr==true)
            _itr = _Gptr->_rows[v]->end();
        if (enditr==false)
            _itr = _Gptr->_rows[v]->begin();
    }
}

bool Graph::NbIterator::operator!=(const NbIterator& rhs) {
    return _itr.operator!=(rhs._itr);

}

void Graph::NbIterator::operator++(int dummy) {
    _itr.operator++(dummy);
}

pair<int,weight_t> Graph::NbIterator::operator*() {
    if(_itr.operator==(nullptr))
        throw invalid_argument("wrong");
    else
        return std::pair<int,int>(_itr.operator*().getVertex(),_itr.operator*().getWeight() );
}

Graph::NbIterator Graph::nbBegin(int v) {
    return Graph::NbIterator(this,v, false);
}

Graph::NbIterator Graph::nbEnd(int v) {
    return Graph::NbIterator(this,v,true);
}