#include <iostream>
#include "Heap.h"

using namespace std;

int main()
{
	Heap new_heap;
	new_heap.insert(20);
	new_heap.insert(37);
	new_heap.insert(21);
	new_heap.insert(98);
	new_heap.insert(100);
	new_heap.insert(-4);
	new_heap.insert(-20);
	new_heap.insert(-25);
	new_heap.insert(-21);
	new_heap.insert(-24);
	new_heap.insert(53);
	new_heap.insert(9);
	new_heap.insert(-8);
	new_heap.insert(6);
	new_heap.heap_out();
	cout << endl;

	Iterator* itr;
	itr = new_heap.create_bfs_iterator();
	cout << "breadth first search: ";
	while (itr->has_next())
		cout << itr->next() <<"|";
	cout << endl;

	Iterator * Itr;
	Itr = new_heap.create_dfs_iterator();
	cout << "depth first search: ";
	while (Itr->has_next())
		cout << Itr->next() << "|";
	cout << endl << endl;


	cout << new_heap.contains(21) << endl;
	cout << new_heap.contains(33) << endl << endl;

	new_heap.remove(100);
	new_heap.heap_out();
	cout << endl << endl;

	new_heap.remove(6);
	new_heap.heap_out();
	cout << endl << endl;

	new_heap.remove(37);
	new_heap.heap_out();

	new_heap.insert(-21);
	new_heap.insert(-24);
	new_heap.insert(101);
	cout << endl << endl;

	new_heap.heap_out();
	
}
