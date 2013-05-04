//
// This program was written to complement the output generated
// by Tom Krcha's DrawScript CS6 Illustrator Plugin. DrawScript
// can generate Processing (www.processing.org) code from Illustrator
// shapes among other frameworks (see https://github.com/tomkrcha/drawscript).
//
// I tried his plugin with a file with a large number of shapes and, while
// it took a very long time, it did produce Processing-based output which
// I saved to a file to load into Processing. Because Processing is
// Java-based, I ran into Java's 64k limit for a single method. This quick
// program converts DrawScript's Processing output into separate 
// functions, splitting at fill().
//
// This program assumes the DrawScript output has been saved to a file
// which is passed in as an argument; a new version of the file with 
// _new appended to the name will be created.
//
// This program is in the public domain and can be used for any purpose.
// Enjoy.
// 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        cout << argv[0] << " <file>" << endl;
        return 1;
    }
    
    string fileName(argv[1]);
    ifstream theFile(fileName);

    vector<string> funcNames;
    int funcCount = 0;

    ofstream theNewFile(fileName + "_new");
    
    string tempLine;
    bool inFun = false;
    while (getline(theFile, tempLine))
    {
        if (tempLine.substr(0, 4) == "fill")
        {
            inFun = true;
            
            ++funcCount;
            stringstream newFuncName;
            newFuncName << "fun";
            newFuncName << funcCount;
            newFuncName << "()";
            funcNames.push_back(newFuncName.str());
            
            theNewFile << "void " << newFuncName.str() << " {" << endl;
        }
        else if (tempLine.length() == 0 && inFun)
        {
            theNewFile << "}" << endl;
            
            inFun = false;
        }
        
        theNewFile << tempLine << endl;
    }

    theNewFile << endl;
    theNewFile << "void allfun() {" << endl;
    for (std::vector<string>::iterator it = funcNames.begin(); it != funcNames.end(); ++it)
    {
        theNewFile << *it << ";" << endl;
        
    }
   
    theNewFile << "}" << endl;
    
    std::cout << "All Done!\n";
    return 0;
}

