//
//  main.cpp
//  Tree
//
//  Created by Ahmed Latif on 2/11/17.
//  Copyright © 2017 Ahmed Latif. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "BST.h"


using namespace std;
int main(int argc, const char * argv[]) {
    try{
        
        
        
        string fileName = argv[1];
        ifstream inputFile;
        
        inputFile.open(fileName.c_str());
        
        if(!inputFile)
        {
            cout << "\nThe file name you have entered is incorrect.\n";
            
        }
        else
        {
            cout << "file opened" << endl;
            BST<string> bst;
            
            bool terminate = false;
            //while loop
            while(!inputFile.eof() && !terminate)
            {
                string command;
                getline(inputFile, command);
                
                if (command[0] == '#')
                {
                
                    if(command[1] == 'L')
                    {
                        stringstream ss;
                        ss << command;
                        
                        string fileName;
                        ss >> fileName >> fileName;

                        bst.loadFile(fileName);
                    }
                    
                    else if(command[1] == 'A')
                    {
                        stringstream ss;
                        ss << command;
                        
                        string value;
                        ss >> value >> value;
                        
                        cout << "Adding value: " << value << endl;
                        bst.insert(value);
                    }
                    
                    else if(command[1] == 'D')
                    {
                        stringstream ss;
                        ss << command;
                        
                        string value;
                        ss >> value >> value;
                        
                        cout << "Deleting value " << value << endl;
                        bst.Delete(value);
                    }
                    
                    else if(command[1] == 'E')
                    {
                        cout << "Clearing BST " << endl;
                        bst.clear();
                    }
                    
                    else if(command[1] == 'P')
                    {
                         if(command[2] == 'I')
                        {
                            cout << "Printing In Order: " << endl;
                            bst.printInOrder();
                            cout << endl;
                        }
                        else if(command[2] == 'P')
                        {
                            cout << "Printing Post Order: " << endl;
                            bst.printPostOrder();
                            cout << endl;
                            
                        }
                        else if(command[2] == 'E')
                        {
                            cout << "Printing Pre Order: " << endl;
                            bst.printPreOrder();
                            cout << endl;
                        }
                    }
                    else if(command[1] == 'H')
                    {
                        cout << "Height: ";
                        bst.printHeight();
                    }
                    else if(command[1] == 'T')
                    {
                        terminate = true;
                        cout << "Goodbye" << endl;
                    }
                }
                
            }
        }
    }
    catch(...)
    {
        cout << "ERROR - unknown error has occurred" << endl;
    }
    
    return 0;
}
