
#include <iostream>
#include <fstream>
#include <string>
#include "DList.h" 
#include "Tree.h" 
#include "TreeIterator.h" 
#include "MyStack.h"
#include "DListIterator.h"
#include "DListNode.h"

using namespace std;



bool validateXML(const string& xml) {
    MyStack<string> *file = new MyStack<string>;

    int i = 0;
    while ( i < xml.length()) {
        if (xml[i] == '<') {
            if (xml[i + 1] == '/') {
				string tag = "";
				i += 2;
                while (xml[i] != '>') {
					tag += xml[i];
					i++;
				}
                if (tag != file->top()) {
					return false;
				}
				file->pop();


			}
            
            else {
				string tag = "";
				i++;
                while (xml[i] != '>') {
					tag += xml[i];
					i++;
				}
				file->push(tag);


			}
		}
		i++;
    }
}

int countFiles(Tree<string>* root) {
	
}

int main()
{
    
    string xmlData = R"(
    <dir>
        <name>ADS_Single_LinkedList_Exercises</name>
        <dir>
            <name>.git</name>
            <file>
                <name>config</name>
                <length>353 b</length>
                <type>config</type>
            </file>
            <file>
                <name>description</name>
                <length>73 b</length>
                <type>description</type>
            </file>
            <file>
                <name>HEAD</name>
                <length>23 b</length>
                <type>HEAD</type>
            </file>
        </dir>
        <dir>
            <name>.vs</name>
            <dir>
                <name>ADS_Single_LinkedList_Exercises</name>
                <dir>
                    <name>v17</name>
                </dir>
            </dir>
        </dir>
    <dir>
        <name>Debug</name>
        <file>
            <name>SinglyLinkedList.pdb</name>
            <length>978944 b</length>
            <type>pdb</type>
        </file>
        <file>
            <name>TestSinglyLinkedList.exp</name>
            <length>41528 b</length>
            <type>exp</type>
        </file>
        <file>
            <name>TestSinglyLinkedList.pdb</name>
            <length>1945600 b</length>
            <type>pdb</type>
        </file>
    </dir>
    </dir>
    )";

    if (validateXML(xmlData))
		cout << "XML is valid" << endl;
	else
		cout << "XML is invalid" << endl;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
