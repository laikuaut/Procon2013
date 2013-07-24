#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#include"Procon2013\Core\Core.h"
#include"opencv2\opencv.hpp"

namespace test
{		
	TEST_CLASS(test_Timer)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			pro::Exception e;
			pro::Timer timer;
			pro::charToString("test");
			pro::Dir dir;
			cv::Mat mat;
			asdfg aa;
			//boost::filesystem::path pp;
			//Assert::AreEqual(3,3,
			//	// Tolerance:
			//	0.01,
			//	// Message:
			//	L"Basic test failed",
			//	// Line number - used if there is no PDB file:
			//	LINE_INFO());
		}

	};
}