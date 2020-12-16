#ifndef heap_h
#define heap_h
#include <iostream>
#include <stdexcept>
using namespace std;

class Iterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
};

class Heap
{
	int* heap;
	size_t heap_size;
	size_t capacity;
	Iterator* bfsiterator;
	Iterator* dfsiterator;
public:

	Heap()
	{
		heap = new int[10];
		capacity = 10;
		heap_size = 0;
		bfsiterator = nullptr;
		dfsiterator = nullptr;
	}

	class bfs_iterator : public Iterator
	{
		size_t current_index;
		Heap* new_heap;

	public:
		bfs_iterator(size_t begin, Heap* heap)
		{
			current_index = begin;
			new_heap = heap;
		}
		int next() override // goes to next bfs iterator of heap element
		{
			if (!has_next())
				throw out_of_range("no more elements\n");
			current_index++;
			return new_heap->heap[current_index - 1];
		}
		////check if bfs iterator of heap has next element
		bool has_next() override { return (current_index != (new_heap->heap_size)); } 
	};

	class dfs_iterator : public Iterator
	{
		size_t current_index;
		Heap* new_heap;
		bool* visited;
		int* stack;

	public:

		dfs_iterator(size_t begin, Heap* heap)
		{
			current_index = begin;
			new_heap = heap;
			visited = new bool[new_heap->heap_size];
			for (int i = 0; i < new_heap->heap_size; i++) {	visited[i] = false;	}
		}

		int next() override	// goes to next bfs iterator of heap element
		{
			if (!has_next())
				throw out_of_range("no more elements\n");
			size_t previous_index = current_index;
			visited[previous_index] = 1;
			if (!has_next())
				return new_heap->heap[previous_index];
			size_t child1, child2;
			while (1)
			{
				child1 = current_index * 2 + 1;
				child2 = current_index * 2 + 2;
				if (child1 < new_heap->heap_size)
				{
					if (!visited[child1])
					{
						current_index = child1;
						break;
					}
				}
				if (child2 < new_heap->heap_size)
				{
					if (!visited[child2])
					{
						current_index = child2;
						break;
					}
				}
				current_index = (current_index - 1) / 2;
			}
			return new_heap->heap[previous_index];
		}

		bool has_next() override //check if dfs iterator of heap has next element
		{
			if (new_heap->heap_size == 0)
				return false;
			size_t next_index = current_index;
			size_t left, right;
			while (1)
			{
				left = (next_index * 2) + 1;
				right = (next_index * 2) + 2;
				if (left < new_heap->heap_size)
				{
					if (!visited[left])
						return true;
				}
				if (right < new_heap->heap_size)
				{
					if (!visited[right])
						return true;
				}
				if (next_index != 0)
					next_index = (next_index - 1) / 2;
				else if (!visited[next_index])
					return true;
				else
					return false;
			}
		}

		~dfs_iterator()
		{
			delete[] visited;
		}
	};

	Iterator* create_dfs_iterator()
	{
		if (dfsiterator != nullptr)
			delete dfsiterator;
		dfsiterator = new dfs_iterator(0, this);
		return dfsiterator;
	}

	Iterator* create_bfs_iterator()
	{
		if (bfsiterator != nullptr)
			delete bfsiterator;
		bfsiterator = new bfs_iterator(0, this);
		return bfsiterator;
	}

	void heap_down(int index) {
		int left, right;
		int temp;
		left = 2 * index + 1;
		right = 2 * index + 2;
		if (left < heap_size) {
			if (heap[index] < heap[left]) {
				temp = heap[index];
				heap[index] = heap[left];
				heap[left] = temp;
				heap_down(left);
			}
		}
		if (right < heap_size) {
			if (heap[index] < heap[right]) {
				temp = heap[index];
				heap[index] = heap[right];
				heap[right] = temp;
				heap_down(right);
			}
		}
	}

	void heap_up(int heap_size)
	{
		int i, parent;
		i = heap_size;
		parent = (i - 1) / 2;

		while (parent >= 0 && i > 0) {
			if (heap[i] > heap[parent]) {
				int temp = heap[i];
				heap[i] = heap[parent];
				heap[parent] = temp;
			}
			i = parent;
			parent = (i - 1) / 2;
		}
	}

	void insert(int element) //inserts element to heap
	{
		if (heap_size == capacity)
		{
			int* new_heap = new int[capacity + 100];
			for (int i = 0; i < capacity; i++)
				new_heap[i] = heap[i];
			capacity += 100;
			delete[] heap;
			heap = new_heap;
		}
		heap[heap_size] = element;
		heap_up(heap_size);
		heap_size++;
	}

	void remove(int element)	//removes element from heap
	{

		if (!contains(element))
			throw invalid_argument("heap doesn't contain element\n");

		for (int index = 0; index < heap_size; index++)
		{
			if (heap[index] == element)
			{
				if (index != (heap_size - 1))
				{
					heap[index] = heap[heap_size - 1];
					heap_size -= 1;
					int temp = heap[index];
					heap_up(index);
					if (temp == heap[index])
						heap_down(index);
				}
				else
					heap_size--;
			}
		}
	}

	bool contains(int key)	// checks if heap contains entered element
	{
		if (heap_size == 0) throw runtime_error("heap is empty\n");
		for (int i = 0; i < heap_size; i++)
		{
			if (heap[i] == key) return true;
		}
		return false;
	}

	void heap_out() // prints heap
	{
		if (heap_size == 0) throw runtime_error("heap is empty\n");
		int i = 0;
		int k = 1;
		while (i < heap_size) {
			while ((i < k) && (i < heap_size)) {
				cout << heap[i] << " ";
				i++;
			}
			cout << endl;
			k = k * 2 + 1;
		}
	}

	~Heap()
	{
		delete[] heap;
	}
};

#endif
