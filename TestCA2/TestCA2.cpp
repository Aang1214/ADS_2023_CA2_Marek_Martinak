#include "pch.h"
#include "CppUnitTest.h"
#include "../CA2_Algorithm/CA2_Algorithm.cpp"
#include "../CA2_Algorithm/TreeIterator.h"
#include "../CA2_Algorithm/Tree.h"
#include "../CA2_Algorithm/DList.h"
#include "../CA2_Algorithm/DListIterator.h"
#include "../CA2_Algorithm/DListNode.h"
#include "../CA2_Algorithm/MyStack.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCA2
{
	TEST_CLASS(TestCA2)
	{
	public:
		
		TEST_METHOD(IsItTrue)
		{
			ifstream* fileStream = new ifstream("../x64/Debug/File.xml");
			string test1 = xmlToString(fileStream);
			Assert::AreEqual(true, validateXML(test1));
		}



		TEST_METHOD(TestMethod2)
		{
			
		}
	};
}
