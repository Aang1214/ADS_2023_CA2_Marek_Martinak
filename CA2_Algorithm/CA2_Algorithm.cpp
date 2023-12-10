
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include "DList.h" 
#include "Tree.h" 
#include "TreeIterator.h" 
#include "MyStack.h"
#include "DListIterator.h"
#include "DListNode.h"

using namespace std;



bool validateXML(const string& xml) {
    Tree<string> *tree = new Tree<string>("text");
    TreeIterator<string> iter(tree);
    MyStack<string> *file = new MyStack<string>;
    string nextTag = "dir";
    string prevTag = "";
    int i = 0;
    while ( i < xml.length()) { // it goes through the whole string
        if (xml[i] == '<') { // if it finds a tag

            if (xml[i + 1] == '/') { // if it is a closing tag
				string tag = ""; 
				i += 2;

                while (xml[i] != '>') { // it goes through the "tag"
					tag += xml[i];
					i++;
				}

                if (tag != file->top()) { // if the closing tag is not the same as the last opening tag
					return false;
				}
				file->pop(); // if it is the same, it pops the last opening tag
			}
            
            else {
				string tag = "";
				i++;
                while (xml[i] != '>') {
					tag += xml[i];
					i++;
				}
                
                if (tag == nextTag || nextTag == "dir/file") {
                    if (tag == "dir" || tag == "file")
                    {
                        nextTag = "name";
                    }
                    else if (prevTag == "dir")
                    {
                        nextTag = "dir/file";

                    }

                    else if(prevTag == "file") 
                    {
                            nextTag = "length";
                    }
                    else if (prevTag == "name") {
                        nextTag = "type";
                    }
                    
                    else if (prevTag == "length") {
                        nextTag = "dir/file";
                    }
                
                }
                else {
					return false;
                }
                /*if (tag == "dir" || tag == "file" && prevTag != "dir") {
                   		nextTag = "name";
                }

                else if (tag == nextTag) {
                    if (prevTag == "file") {
                        nextTag = "length";
                    }
                    else if (prevTag == "name") {
                        nextTag = "type";
                    }
                }
                
                else {
                    return false;
                }*/
                prevTag = tag;

				file->push(tag); // if it is an opening tag, it pushes it to the stack

			}
		}
		i++;
    }
    iter.root();
}


string xmlToString(ifstream* fileStream) {
	string fileInString;
	string line;
    if (fileStream) {
        while (getline(*fileStream, line))
        {
			fileInString += line;
            cout << line << endl;
		}
	}
    else {
		cout << "File not found";
	}
	fileStream->close();
	return fileInString;
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

   

    ifstream* fileStream = new ifstream("../x64/Debug/File.xml");
    string xml = xmlToString(fileStream);
    

    if (validateXML(xml))
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
