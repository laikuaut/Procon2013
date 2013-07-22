#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include"Procon2013\Core\Dir.h"
//#include<boost\filesystem.hpp>

namespace test
{		
	TEST_CLASS(test_Timer)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			pro::Dir dir;
			//asdfg aa;
			//boost::filesystem::path pp;
			Assert::AreEqual(3,3,
				// Tolerance:
				0.01,
				// Message:
				L"Basic test failed",
				// Line number - used if there is no PDB file:
				LINE_INFO());
		}

	};
}