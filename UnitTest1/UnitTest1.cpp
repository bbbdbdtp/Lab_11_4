#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11_4/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(TestSearch)
		{
			Note S[3];

			S[0].surname = "Doe";
			S[0].name = "John";
			S[0].number = "0679584251";

			S[1].surname = "Smith";
			S[1].name = "Jane";
			S[1].number = "0579486324";

			S[2].surname = "Johnson";
			S[2].name = "Robert";
			S[2].number = "0975824657";

			string searchName = "Smith";
			searchBySurname(S, 3, searchName);
		}
	};
}