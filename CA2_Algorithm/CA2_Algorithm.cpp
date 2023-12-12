
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
#include "MyCode.h"
using namespace std;



bool validateXML(string& xml) {
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
    return true;
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


void createTree(Tree<DataMemory*>& tree, string fileName) {
    ifstream* fileStream = new ifstream(fileName);
    string xml = xmlToString(fileStream);
    TreeIterator<DataMemory*> iter(&tree);
    DataMemory* D = new DataMemory(dir);
    string x = "";
    string y = "";
    int p;
    int i = 0;
    int t = 0;
    int filecheck = 0;

    if (validateXML(xml))
    {    
        while (i < xml.length())
        { // it goes through the whole string
            x += xml[i];
            
        
            if (x == "<name>")
                { 
                t = i + 1;
                while (xml[t] != '<')
                {
                    y += xml[t];
                    t++;
                    
                }
                D->name = y;
                i = t; 
                x = "";
				}
            else if (x == "<length>") {
                t = i + 1;
                while (xml[t] != '<')
                {
                    y += xml[t];
                    t++;
                }
                D->length = y;
                i = t;
                x = "";
            }
            else if (x == "<type>") {
                t = i + 1;
                while (xml[t] != '<')
                {
					y += xml[t];
					t++;
				}
				D->type = y;
                i = t;
                x = "";
            }
            else if (x == "<dir>") {
                D = new DataMemory(dir);
                //iter.item() = D; if first(root)
                iter.appendChild(D); //else
                iter.childEnd();
                iter.down();
                x = "";
			}


            else if (x == "</dir>") {
                //if first dont do this & firts = false
                iter.up();
                x = "";
            }
            else if (x == "<file>") {
                D = new DataMemory(file);
                iter.appendChild(D);
                iter.childEnd();
                x = "";
			}
            i++;
						
         }

        iter.root();

               
     }
    else 
    {
		cout << "XML is invalid" << endl;
	}
}


/*int countFiles(Tree<string>& tree) {
	TreeIterator<string> iter(&tree);
	int count = 0;
    while (iter.childValid()) {
        if (iter.item() == "file") {
			count++;
		}
		iter.advance();
	}
	return count;
}*/

/*int BreathFirstSearch(Tree<string>& tree) {
    return 0;
}*/

void displayTree(TreeIterator<DataMemory*> iter, string indent)
{
    cout << "There should be a line here " << endl;
    cout << indent << iter.item()->name << endl;
    while (iter.childValid()) {
        TreeIterator<DataMemory*> child(iter);
        child.down();
        displayTree(child, indent + "\t");
        iter.childForth();
    }
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

    
  
    string fileName = "../x64/Debug/File.xml";
    Tree<DataMemory*> tree(nullptr);
    ifstream* fileStream = new ifstream("../x64/Debug/File.xml");
    string xml = xmlToString(fileStream);
    createTree(tree, fileName);
    TreeIterator<DataMemory*> iter(&tree);
    displayTree(iter, "");

    return 0;
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
