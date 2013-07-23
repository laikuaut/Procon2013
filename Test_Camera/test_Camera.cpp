#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include"Procon2013\Exception\Exceptions.h"


namespace test
{		
	TEST_CLASS(Camera)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			pro::Exception e;
			pro::FileException ef;
			pro::DirException de;
			pro::OutOfRangeException<int> of;
		}

	};
}