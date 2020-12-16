//Test file
//Student: Thanh Nam Tran
#include <iostream>
#include <tuple>
#include "EntryList.h"
#include "Graph.h"

using std::cout;
using std::endl;
using std::range_error;

using namespace std;

int main() {


   EntryList testEntryList1;
   EntryList::Entry e;

   cout << "size: " << testEntryList1.size() << ", capacity: " << testEntryList1.capacity() << endl;
   testEntryList1.dump();
   cout << endl;

   for (int i = 1; i < 11; i++) {
     testEntryList1.insert( EntryList::Entry((i*5)%13, i) );
   }


   cout << "size: " << testEntryList1.size() << ", capacity: " << testEntryList1.capacity() << endl;
   testEntryList1.dump();
   cout << endl;

   cout<<"Insert this should change the capacity: "<<testEntryList1.insert( EntryList::Entry(13, 6) )<<endl;

   cout<<"Create Test 2 using CopyCon of Test 1: "<<endl;
   EntryList testEntryList2(testEntryList1);
   testEntryList1.remove(1,e);
   cout<<"Changed Entry1 check if Entry2 is the same"<<endl;
   testEntryList2.dump();
   cout<<endl;

   EntryList testEntryList3=testEntryList2;
   testEntryList2=testEntryList1;
   cout<<"Create EntryList3 using assignment operator, Changed EntryList2, check if EntryList3 is the same: "<<endl;
   testEntryList3.dump();
    cout<<"\nRemove 8 elements to check for resize down (Capacity should be back to default size): \n"<<endl;
    for (int i = 1; i < 8; i++) {
        testEntryList3.remove( i,e);
    }
    cout << "size: " << testEntryList3.size() << ", capacity: " << testEntryList3.capacity() << endl;
    cout<<"Try to remove empty entry expect 0: "<<testEntryList3.remove( 1,e)<<endl;
    cout<<"Try to check at() expect entry at index 1 shoud be (12:5) -> "<<testEntryList3.at( 1)<<endl;
    try{
        testEntryList3.at(3);
    }
    catch (exception e)
    {
        cout<<"This should throw exception because index is invalid"<<endl;
    }

    cout<<"Try to check getEntry at invalid index expect 0: "<<testEntryList3.getEntry(1,e)<<endl;
    cout<<"Try to check insert available vertex expect 0: "<<testEntryList3.insert( EntryList::Entry(13, 10) )<<endl;
    testEntryList3.dump();
    cout << endl;

   cout << "\nPrint using iterator:\n";
   for (auto itr = testEntryList3.begin(); itr != testEntryList3.end(); itr++) {
   cout << *itr << endl;}

   cout<<"\nThis is a test for Graph"<<endl;

    //Create Special Graph with no edge to the first vertex.
    Graph* testGraph1 = new Graph(5) ;
    try{
        Graph* testGraph1 = new Graph(-1) ;
    }
    catch (exception e)
    {
        cout<<"This should throw exception because number of vertices is invalid"<<endl;
    }

    //Graph* testEntryList2 = new Graph(-1) ; //this should throws
    testGraph1->addEdge(3, 4, 1);
    testGraph1->addEdge(1, 4, 1);
    testGraph1->addEdge(2, 3, 1);
    testGraph1->addEdge(3, 1, 1);
    testGraph1->addEdge(1, 2, 1);
    testGraph1->addEdge(2, 4, 1);
    try{
    testGraph1->addEdge(6, 4, 1);
    }
    catch(exception e)
    {
        cout<<"This should throws because I add invalid vertex"<<endl;
    }
    try{
        testGraph1->addEdge(2, 6, 1);
    }
    catch(exception e)
    {
        cout<<"This should throws because I add invalid vertex"<<endl;
    }
    try{
        testGraph1->addEdge(6, -1, 1);
    }
    catch(exception e)
    {
        cout<<"This should throws because I add invalid vertex"<<endl;
    }
    try{
        testGraph1->addEdge(-1, 6, 1);
    }
    catch(exception e)
    {
        cout<<"This should throws because I add invalid vertex"<<endl;
    }

    try{
        testGraph1->removeEdge(-1,1);
    }
    catch(exception e)
    {
        cout<<"This should throws because I try to remove invalid vertex"<<endl;
    }
    try{
        testGraph1->removeEdge(1,6);
    }
    catch(exception e)
    {
        cout<<"This should throws because I try to remove invalid vertex"<<endl;
    }
    // Dump the graph
    cout << "\nInitial graph (G1):\n";
    testGraph1->dump() ;

    // Make a copy using copy constructor
    Graph* testGraph2 = new Graph(*testGraph1) ;
    cout << "\nCopy G2 = Graph(G1):\n" ;
    testGraph2->dump() ;

    // Get rid off original graph; check if new (copy) graph is still correct.
    delete testGraph1;
    cout << "\nCopy (G2) after deleting original (G1):\n" ;
    testGraph2->dump() ;

    // Make another graph and dump it
    Graph testGraph3(3) ;
    testGraph3.addEdge(1, 1, 1);
    testGraph3.addEdge(1, 2, 1);
    testGraph3.addEdge(1, 2, 1);
    cout << "\nNew graph (testGraph3):\n";
    testGraph3.dump();

    // Assign testGraph2 to testGraph3 and dump testGraph3
    testGraph3 = *testGraph2 ;
    cout << "\nAssign testGraph3 = G2:\n";
    testGraph3.dump() ;

    //delete testGraph2
    delete testGraph2 ;

    testGraph3=testGraph3;
    //Print testGraph3 using NbIterator and EdgeIterator
    //If _itr is uninitialized or something then it should fail
    Graph::NbIterator nit ;

    for (int i = 0; i < testGraph3.numVert(); i++) {
        cout << "\nThe neighbors of vertex " << i << " are:\n" ;
        for (nit = testGraph3.nbBegin(i); nit != testGraph3.nbEnd(i) ; nit++) {
            cout << "(" << (*nit).first << ", " << (*nit).second << ")" << " " ;
        }
        cout << endl ;
    }

    Graph::EgIterator eit ;
    std::tuple<int,int,int> edge ;

    cout << "\nnumVert = " << testGraph3.numVert() << ", numEdge = " << testGraph3.numEdge() << endl;
    cout << "The edges in the graph are:\n" ;
    for (eit = testGraph3.egBegin() ; eit != testGraph3.egEnd() ; eit++) {

        edge = *eit ;   // get current edge

        // the two data members of a pair are first and second
        //
        cout << "(" << get<0>(edge) << ", "
             << get<1>(edge) << ", "
             << get<2>(edge) << ") " ;

    }
    cout << endl ;



}