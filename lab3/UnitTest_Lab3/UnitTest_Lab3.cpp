#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/lab3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab3
{
	TEST_CLASS(UnitTestLab3)
	{
	public:
		
		TEST_METHOD(bfs_iterator_next)
		{
			Heap new_heap;
			new_heap.insert(3);
			Iterator* itr = new_heap.create_bfs_iterator();
			Assert::AreEqual(3, itr->next());
			try 
			{
				itr->next();
			}
			catch(out_of_range & exception)
			{
				Assert::AreEqual("no more elements\n", exception.what());
			}
		}

		TEST_METHOD(bfs_iterator_has_next)
		{
			Heap new_heap;
			new_heap.insert(3);
			Iterator* itr = new_heap.create_bfs_iterator();
			Assert::AreEqual(true, itr->has_next());
			itr->next();
			Assert::AreEqual(false, itr->has_next());
		}

		TEST_METHOD(dfs_iterator_next_error)
		{
			Heap new_heap;
			new_heap.insert(3);
			Iterator* Itr = new_heap.create_dfs_iterator();
			try
			{
				Itr->next();
			}
			catch (out_of_range & exception)
			{
				Assert::AreEqual("no more elements\n", exception.what());
			}
		}

		TEST_METHOD(dfs_iterator_has_next_and_next)
		{
			Heap new_heap;
			new_heap.insert(15);
			new_heap.insert(12);
			new_heap.insert(9);
			new_heap.insert(6);
			new_heap.insert(3);
			Iterator* itr = new_heap.create_dfs_iterator();
			Assert::IsTrue(itr->has_next());
			Assert::AreEqual(itr->next(), 15);
			Assert::AreEqual(itr->next(), 12);
			Assert::AreEqual(itr->next(), 6);
			Assert::IsTrue(itr->has_next());
			Assert::AreEqual(itr->next(), 3);
			Assert::AreEqual(itr->next(), 9);
			Assert::IsFalse(itr->has_next());
		}

		TEST_METHOD(heap_insert)
		{
			Heap new_heap;
			new_heap.insert(3);
			new_heap.insert(6);
			new_heap.insert(9);
			new_heap.insert(-3);
			Iterator* itr = new_heap.create_dfs_iterator();
			Assert::AreEqual(itr->next(), 9);
			Assert::AreEqual(itr->next(), 3);
			Assert::AreEqual(itr->next(), -3);
			Assert::AreEqual(itr->next(), 6);
			Assert::IsFalse(itr->has_next());
		}

		TEST_METHOD(heap_remove_error)
		{
			Heap new_heap;
			try 
			{
				new_heap.remove(3);
			}
			catch (invalid_argument & exception)
			{
				Assert::AreEqual("heap doesn't contain element\n", exception.what());
			}
			catch (runtime_error & exception)
			{
				Assert::AreEqual("heap is empty\n", exception.what());
			}
		}

		TEST_METHOD(heap_remove)
		{
			Heap new_heap;
			new_heap.insert(3);
			new_heap.insert(6);
			new_heap.insert(9);
			new_heap.insert(-3);
			new_heap.insert(-9);
			new_heap.insert(12);
			new_heap.insert(-33);
			new_heap.remove(12);
			new_heap.remove(-3);
			Iterator* itr = new_heap.create_bfs_iterator();
			Assert::AreEqual(itr->next(), 9);
			Assert::AreEqual(itr->next(), 3);
			Assert::AreEqual(itr->next(), 6);
			Assert::AreEqual(itr->next(), -33);
			Assert::AreEqual(itr->next(), -9);
			Assert::IsFalse(itr->has_next());
		}

		TEST_METHOD(heap_contains)
		{
			Heap new_heap;
			new_heap.insert(3);
			new_heap.insert(6);
			new_heap.insert(9);
			Assert::AreEqual(new_heap.contains(6), true);
			Assert::AreEqual(new_heap.contains(-3), false);
		}

		TEST_METHOD(heap_contains_error)
		{
			try
			{
			Heap new_heap;
			new_heap.contains(6);
			}
			catch (runtime_error & exception)
			{
				Assert::AreEqual("heap is empty\n", exception.what());
			}
		}
	};
}
