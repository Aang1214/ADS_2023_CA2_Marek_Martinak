
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
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
    string tag = "";
    string y = "";
    int p;
    int i = 0;
    int t = 0;
    int filecheck = 0;
    bool first = true;


    if (validateXML(xml))
    {    
        while (i < xml.length())
        { // it goes through the whole string
            if (xml[i] == '<') { 
                    string tag = "";
                    i++;
                    while (xml[i] != '>') {
                        tag += xml[i];
                        i++;
                    }

                    if (tag == "name")
                    {
                        t = i + 1;
                        while (xml[t] != '<')
                        {
                            y += xml[t];
                            t++;

                        }
                        D->name = y;
                        i = t;
                        y = "";
                    }
                    else if (tag == "length") {
                        t = i + 1;
                        while (xml[t] != '<')
                        {
                            y += xml[t];
                            t++;
                        }
                        D->length = y;
                        i = t;
                        y = "";
                    }
                    else if (tag == "type") {
                        t = i + 1;
                        while (xml[t] != '<')
                        {
                            y += xml[t];
                            t++;
                        }
                        D->type = y;
                        i = t;
                        y = "";
                    }
                    else if (tag == "dir") {
                        D = new DataMemory(dir);
                        if (first)
                        {
                            tree = Tree<DataMemory*>(D);
                            first = false;
                        }
                        //iter.item() = D; if first(root)
                        else
                        {
                            iter.appendChild(D);
                            iter.childEnd();
                            iter.down();
                        }
                         //else
                        
                        y = "";
                    }
                    else if (tag == "/dir") {

                        //if first dont do this & firts = false
                        iter.up();
                        y = "";
                    }
                    else if (tag == "file") {
                        D = new DataMemory(file);
                        iter.appendChild(D);
                        iter.childEnd();
                        y = "";
                    }

                    
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




/*int BreathFirstSearch(Tree<string>& tree) {
    return 0;
}*/

void displayTree(TreeIterator<DataMemory*> iter, string indent)
{
   // if (iter.node != nullptr && iter.node->data != nullptr && iter.node->data->name != "")
    //{
        cout << indent << iter.node->data->name;
    //}
    if (iter.childValid())
    {
        cout << "(" << endl;

        while (iter.childValid())
        {
            TreeIterator<DataMemory*> iter2(iter.childIter.currentNode->data);
            displayTree(iter2, "\t" + indent);
            iter.childForth();
        }
        cout << indent << ")";
    }
    cout << endl;
}

void E_displayTreeWithSize(TreeIterator<DataMemory*> iter, string indent)
{
    cout << indent << iter.node->data->name;
    if (iter.childValid())
    {
        cout << "(" << endl;

        while (iter.childValid())
        {
            TreeIterator<DataMemory*> iter2(iter.childIter.currentNode->data);
            cout << indent << iter.childIter.currentNode->data->data->name;
            if (iter.node->data->type == "file")
            {
               
                cout << " " << iter.childIter.currentNode->data->data->length;
			}
            cout << endl;
            
            iter.childForth();
        }
        cout << indent << ")";
    }
    cout << endl;
}

int A_countItems(Tree<DataMemory*>& tree) {
    
    return tree.count() - 1;
}


int B_MemoryBFA(Tree<DataMemory*>& tree) {
	queue<Tree<DataMemory*>*> queueIt;
    int count = 0;
    queueIt.push(&tree);
    while (!queueIt.empty()) {
		DListIterator<Tree<DataMemory*>*> iter = queueIt.front()->children->getIterator();
        while (iter.isValid()) {
			queueIt.push(iter.item());
			iter.advance();
		}
        count = stoi(queueIt.front()->data->length);
		queueIt.pop();

	}
    return count;
}

void C_PruneTheTree(Tree<DataMemory*>& tree) {
	TreeIterator<DataMemory*> iter(&tree);
    while (iter.childValid()) {
        if (iter.node->data->type == "file") {
			
		}
		iter.childForth();
	}
}
void D_FindGivenFolder(Tree<DataMemory*>& tree, string folderName) {
	TreeIterator<DataMemory*> iter(&tree);
    while (iter.childValid()) {
        if (iter.node->data->name == folderName) {
			cout << "Folder found" << endl;
			return;
		}
		iter.childForth();
	}
	
}
void printBFS(Tree<DataMemory*>* tree)
{
    queue<Tree<DataMemory*>*> queue;
    queue.push(tree);
    while (!queue.empty())
    {
        DListIterator<Tree<DataMemory*>*> iter(queue.front()->children->getIterator());
        while (iter.isValid())
        {
            queue.push(iter.item());
            iter.advance();
        }
        cout << queue.front()->data->name << "\t ";
        queue.pop();

    }


}

Tree<DataMemory*> MyTree()
{
    DataMemory* test = new DataMemory("ADS_Single_LinkedList_Exercises","", "", dir);
    Tree<DataMemory*>* root = new Tree<DataMemory*>(test);
    TreeIterator<DataMemory*> iter(root);
    iter.appendChild(new DataMemory(".git", "", "", dir));
    iter.down();
    iter.appendChild(new DataMemory("config", "353 b", "config",file));
    iter.appendChild(new DataMemory("config", "73 b", "config", file));
    iter.appendChild(new DataMemory("config", "23 b", "config", file));
    iter.root();
    printBFS(root);
    cout << root->count();
    return *root;

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

    
    string emptyString = "";
    string fileName = "../x64/Debug/File.xml";
    Tree<DataMemory*> tree(nullptr);
    ifstream* fileStream = new ifstream("../x64/Debug/File.xml");
    string xml = xmlToString(fileStream);
    createTree(tree, fileName);
    TreeIterator<DataMemory*> iter = TreeIterator<DataMemory*>(&tree);
    displayTree(iter, "");
    cout << endl;
    cout << "Number of files: " << A_countItems(tree) << endl;
    cout << endl;
    D_FindGivenFolder(tree, "Debug");
    cout << endl;
    MyTree();

    Tree<DataMemory*> treee = MyTree();
    cout << endl;
    cout << endl;
    E_displayTreeWithSize(iter, "");
    cout << endl;
    cout << "Number of files: " << A_countItems(treee) << endl;
    cout << endl;
    //cout << "Memory used: " << B_MemoryBFA(treee) << endl;
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
