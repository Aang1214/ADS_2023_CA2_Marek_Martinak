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
		
		TEST_METHOD(validateTest1)
		{
			ifstream* fileStream = new ifstream("../x64/Debug/File.xml");
			string test1 = xmlToString(fileStream);
			Assert::AreEqual(true, validateXML(test1));
		}


		TEST_METHOD(buildTreeTest) 
		{// it is unable to read the file and i dont know why
			// but it should work normaly 
			string fileName = "../x64/Debug/File.xml";
			Tree<DataMemory*> tree(nullptr);
			
			createTree(tree, fileName);
			TreeIterator<DataMemory*> iter(&tree);
			iter.down();
			Assert::AreEqual(12, tree.count());
		}
		TEST_METHOD(MyTreeTest2)
		{
			Tree<DataMemory*> tree = MyTree();
			Assert::AreNotEqual(4, tree.count());
		}
		TEST_METHOD(MyTreeTest1) 
		{
			Tree<DataMemory*> tree = MyTree();
			Assert::AreEqual(5, tree.count());
		}

		TEST_METHOD(EpartTest)
		{
			
			Tree<DataMemory*> tree = MyTree();
			TreeIterator<DataMemory*> iter(&tree);
			E_displayTreeWithSize(iter, "");
		}
		TEST_METHOD(xmlToStringTest)
		{
			
		}
		
	};
}
