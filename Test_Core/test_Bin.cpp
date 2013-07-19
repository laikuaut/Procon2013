#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include"Procon2013\Core\Core.h"

namespace test
{		
	TEST_CLASS(Bin)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(3,3);
		}

	};
}