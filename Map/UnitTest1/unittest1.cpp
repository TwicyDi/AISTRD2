#include "stdafx.h"
#include "CppUnitTest.h"
#include "c:\Users\Диана\source\repos\Map\Map\map.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_for_map
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(insert_int_int)
		{
			map<int, int> map;
			map.insert(9, 1);
			map.insert(8, 2);
			map.insert(7, 3);
			map.insert(6, 4);
			map.insert(1, 4);
			int check[5] = { 2,4,1,4,3 };
			auto it = map.create_bft_iterator();
			for (int i = 0; it != nullptr; it++,i++)
			{
				Assert::AreEqual(*it, check[i]);
			}
		}
		TEST_METHOD(insert_int_color)
		{
			map<int, int> map;
			map.insert(9, 1);  
			map.insert(8, 2);  
			map.insert(7, 3);
			map.insert(6, 4);
			map.insert(1, 4);			
			bool check[5] = { 0,0,0,1,1 };
			auto it = map.create_bft_iterator();
			for (int i = 0; it != nullptr; it++,i++)
			{
				Assert::AreEqual(it.current_color(), check[i]);
			}
		}
		TEST_METHOD(insert_int_char)
		{
			map<int, char> map;
			map.insert(9, 'a');
			map.insert(8, 'b');
			map.insert(7, 'c');
			map.insert(6, 'd');
			map.insert(1, 'e');
			char check[5] = { 'b','d','a','e','c' };
			auto it = map.create_bft_iterator();
			for (int i = 0; it != nullptr; it++,i++)
			{
				Assert::AreEqual(*it, check[i]);
			}
		}

		TEST_METHOD(insert_int_char_color)
		{
			map<int, char> map;
			map.insert(9, 'a');
			map.insert(8, 'b');
			map.insert(7, 'c');
			map.insert(6, 'd');
			map.insert(1, 'e');
			bool check[5] = { 0,0,0,1,1 };
			auto it = map.create_bft_iterator();
			for (int i = 0; it != nullptr; it++, i++)
			{
				Assert::AreEqual(it.current_color(), check[i]);
			}
		}

		TEST_METHOD(tree_root_color)
		{
			map<int, int> map;
			map.insert(1, 1);
			auto it = map.create_bft_iterator();
			for (; it != nullptr; it++)
			{
				Assert::IsFalse(it.current_color());
			}
		}

		TEST_METHOD(remove_int_char)
		{
			map<int, char> map;
			map.insert(9, 'a');
			map.insert(8, 'b');
			map.insert(7, 'c');
			map.insert(6, 'd');
			map.insert(1, 'e');
			map.remove(8);			
			char check[4] = { 'c','d','a','e' };
			auto it = map.create_bft_iterator();
			for (int i = 0; it != nullptr; it++,i++)
			{
				Assert::AreEqual(*it, check[i]);
			}
		}

		TEST_METHOD(remove_int_char_color)
		{
			map<int, char> map;
			map.insert(9, 'a');
			map.insert(8, 'b');
			map.insert(7, 'c');
			map.insert(6, 'd');
			map.insert(1, 'e');
			map.remove(8);			
			bool check[4] = { 1,0,0,1 };
			auto it = map.create_bft_iterator();
			for (int i = 0; it != nullptr; it++,i++)
			{
				Assert::AreEqual(it.current_color(), check[i]);
			}
		}

		TEST_METHOD(remove_int_char_exception)
		{
			map<int, char> map;
			map.insert(9, 'a');
			map.insert(8, 'b');
			map.insert(7, 'c');
			map.insert(6, 'd');
			map.insert(1, 'e');
			try {
				map.remove(0);
			}
			catch (const std::out_of_range& error)
			{
				Assert::AreEqual("no this element", error.what());
			}

		}

		TEST_METHOD(remove_int_char_exception_empty_map)
		{
			map<int, char> map;
			try {
				map.remove(0);
			}
			catch (const std::out_of_range& error)
			{
				Assert::AreEqual("error", error.what());
			}

		}

		TEST_METHOD(find_int)
		{
			map<int, int> map;
			map.insert(9, 1);
			map.insert(8, 2);
			map.insert(7, 3);
			map.insert(6, 4);
			map.insert(1, 4);
			Assert::AreEqual(3, map.find(7));
		}

		TEST_METHOD(find_char)
		{
			map<int, char> map;
			map.insert(9, 'a');
			map.insert(8, 'b');
			map.insert(7, 'c');
			map.insert(6, 'd');
			map.insert(1, 'e');
			Assert::AreEqual('c', map.find(7));
		}

		TEST_METHOD(find_int_exception)
		{
			map<int, int> map;
			map.insert(9, 1);
			map.insert(8, 2);
			map.insert(7, 3);
			map.insert(6, 4);
			map.insert(1, 4);
			try { map.find(0); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}


		TEST_METHOD(find_int_exception_empty_map)
		{
			map<int, int> map;
			try { map.find(0); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}

		TEST_METHOD(get_keys_exception_empty_map)
		{
			map<int, int> map;
			try { map.get_keys(); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}

		TEST_METHOD(get_value_exception_empty_map)
		{
			map<int, int> map;
			try { map.get_value(); }
			catch (const std::out_of_range& error) { Assert::AreEqual("error", error.what()); }
		}

	};
}