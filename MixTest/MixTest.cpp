#include "pch.h"
#include "CppUnitTest.h"
#include "../Курсовая/List.cpp"
#include "../Курсовая/prefix.cpp"
#include "../Курсовая/prefix_math.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MixTest
{
	TEST_CLASS(ListTest)
	{
	public:
		BiList Empty;
		BiList NotEmpty;
		TEST_METHOD_INITIALIZE(init)
		{
			NotEmpty.push_back("Some data");
		}
		TEST_METHOD(IsEmpty_for_NotEmpty)
		{
			Assert::AreEqual(NotEmpty.isEmpty(), false);
		}
		TEST_METHOD(IsEmpty_for_Empty)
		{
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(Get_Size_for_Empty)
		{
			size_t real_size = 0;
			Assert::AreEqual(Empty.get_size(), real_size);
		}
		TEST_METHOD(Get_Size_for_NotEmpty)
		{
			size_t real_size = 1;
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(at_correct_index)
		{
			string str = "Some data";
			Assert::AreEqual(NotEmpty.at(0), str);
		}
		TEST_METHOD(at_incorrect_index)
		{
			try
			{
				Empty.at(4);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Incorrect index.");
			}
		}
		TEST_METHOD(Push_Back_NotEmpty)
		{
			string str = "5";
			NotEmpty.push_back(str);
			Assert::AreEqual(NotEmpty.at(1), str );
		}
		TEST_METHOD(Push_Front_NotEmpty)
		{
			string str = "1";
			NotEmpty.push_front(str);
			Assert::AreEqual(NotEmpty.at(0), str);
		}
		TEST_METHOD(remove_correct_index)
		{
			NotEmpty.push_back("0");
			string temp = NotEmpty.at(NotEmpty.get_size()-2);
			NotEmpty.remove(NotEmpty.get_size()-1);
			Assert::AreEqual(NotEmpty.at(NotEmpty.get_size()-1), temp);
		}
		TEST_METHOD(Pop_Back_for_NotEmpty)
		{
			size_t real_size = NotEmpty.get_size() - 1;
			NotEmpty.pop_back();
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(Pop_Back_for_Empty)
		{
			Empty.pop_back();
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(Pop_Front_for_NotEmpty)
		{
			size_t real_size = NotEmpty.get_size() - 1;
			NotEmpty.pop_front();
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(insert_correct_index)
		{
			string str = "4";
			NotEmpty.insert("4", 0);
			Assert::AreEqual(NotEmpty.at(0),str);
		}
		TEST_METHOD(insert_incorrect_index)
		{
			try
			{
				Empty.insert("2", 0);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Incorrect index.", error);
			}
		}
		TEST_METHOD(remove_incorrect_index)
		{
			try
			{
				Empty.remove(2);
			}
			catch (const char* error)
			{
				Assert::AreEqual("Incorrect index.", error);
			}
		}
		TEST_METHOD(reverse_for_NotEmpty)
		{
			string last_inf = NotEmpty.at(NotEmpty.get_size() - 1);
			NotEmpty.reverse();
			Assert::AreEqual(NotEmpty.at(0), last_inf);
		}
		TEST_METHOD(Pop_Front_for_Empty)
		{
			Empty.pop_front();
			Assert::AreEqual(Empty.isEmpty(), true);
		}
		TEST_METHOD(set_correct_index)
		{
			NotEmpty.set(0, "3");
			string str = "3";
			Assert::AreEqual(NotEmpty.at(0), str);
		}
		TEST_METHOD(set_incorrect_index)
		{
			try
			{
				NotEmpty.set(10000000, "2");
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Incorrect index.");
			}
		}
		TEST_METHOD(Test_Clear_NotEmpty)
		{
			NotEmpty.clear();
			size_t real_size = 0;
			Assert::AreEqual(NotEmpty.get_size(), real_size);
		}
		TEST_METHOD(Test_Clear_Empty)
		{
			Empty.clear();
			size_t real_size = 0;
			Assert::AreEqual(Empty.get_size(), real_size);
		}
		TEST_METHOD(Push_Back_Empty)
		{
			Empty.push_back("5");
			string str = "5";
			Assert::AreEqual(Empty.at(0), str);
			Empty.pop_back();
		}
		TEST_METHOD(Push_Front_Empty)
		{
			Empty.push_front("0");
			string str = "0";
			Assert::AreEqual(Empty.at(0), str);
		}
	};
	TEST_CLASS(PrefixTest)
	{
		prefix Test;
		TEST_METHOD(SimpleMath)
		{
			string res = "+ 1 2 ";
			Test.make_prefix("1+2");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(TrigMath)
		{
			string res = "+ tg(pi) cos(e) ";
			Test.make_prefix("tg(pi) + cos(e)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(MathWithoutBracket_1)
		{
			string res = "+ + 1 * 2 3 4 ";
			Test.make_prefix("1+2*3+4");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(MathWithoutBracket_2)
		{
			string res = "+ * 1 2 * 3 4 ";
			Test.make_prefix("1*2+3*4");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(MathWithoutBracket_3)
		{
			string res = "+ + + 1 2 3 4 ";
			Test.make_prefix("1+2+3+4");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(MathWithBracket_1)
		{
			string res = "* + 1 2 + 3 4 ";
			Test.make_prefix("(1+2)*(3+4)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
		TEST_METHOD(MathWithBracket_2)
		{
			string res = "- 0 + -2 3 ";
			Test.make_prefix("-(-2+3)");
			Assert::AreEqual(Test.print_prefix(), res);
		}
	};
	TEST_CLASS(Prefix_Math_Test)
	{
		prefix test;
		TEST_METHOD(SimpleMath)
		{
			test.make_prefix("1+2");
			string result = "3.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(SimpleTrig)
		{
			test.make_prefix("sin(pi/2)");
			string result = "1.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(SimpleMath_With_Brackets)
		{
			test.make_prefix("(1+2)-(3+4)");
			string result = "-4.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(MixedMath)
		{
			test.make_prefix("cos(pi)-1");
			string result = "-2.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(Error_input)
		{
			try {
				test.make_prefix("tg(");
			}
			catch (const char*)
			{
				Assert::AreEqual(1, 1);
			}
			
		}
		TEST_METHOD(MixedMath_2)
		{
			test.make_prefix("sqrt(2+2)-2");
			string result = "0.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(StrangeMath)
		{
			test.make_prefix("sqrt(sin(pi^2/pi/2))+ln(e)");
			string result = "2.000000";
			Assert::AreEqual(test.get_result(), result);
		}
		TEST_METHOD(SimpleMath_with_const)
		{
			test.make_prefix("e*pi");
			string result = "8.539734";
			Assert::AreEqual(test.get_result(), result);
		}
	};
}
