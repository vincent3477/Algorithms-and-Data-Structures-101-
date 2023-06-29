/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA8 
* WordFrequency.cpp 
* This file will take one input file and find the frequency of each and every words found in the file and put all the resulting frequences of each word into an outfile.
*********************************************************************************/ 

#include <iostream>
#include <fstream>
#include <string.h>
#include "Dictionary.h"
using namespace std;

int main (int argc, char *argv[]){
    if(argc == 3){
    	ifstream inFile;
        ofstream outFile;

	inFile.open(argv[1]);
	if(!inFile.is_open()){
	    cout << "Could not open input file.\n";
	    return(EXIT_FAILURE);
	}
	
	outFile.open(argv[2]);
	if(!outFile.is_open()){
	    cout << "Could not open output file.\n";
	    return(EXIT_FAILURE);
	}
	
        //outFile = fopen(argv[2],"w");
        
        
        string instring = "";
        string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()_%-=+0123456789";
        size_t begin, end, length;
        string token;
        
        Dictionary d = Dictionary();
        string lastval = "";
        while(getline(inFile,instring)){
            
            //fgets(instring,4096,inFile);
            length = instring.length();
            int i = 0;
            while(instring[i] != '\0'){
                instring[i] = tolower(instring[i]);
                i++;
            }
            
            begin = min(instring.find_first_not_of(delim,0),length);
            end =  min(instring.find_first_of(delim,begin),length);
            token = instring.substr(begin,end-begin);
            
            while(token != ""){
            
                
                
            	
                

                if (d.contains(token)){
                    d.setValue(token, d.getValue(token) + 1);
                }
                else{
                    d.setValue(token, 1);
                }
                
                begin = min(instring.find_first_not_of(delim,end+1),length);
                end =  min(instring.find_first_of(delim,begin),length);
                token = instring.substr(begin,end-begin);
                
            }
            
            
            //cout << "fetching " << instring << "\n";
        }
        
        outFile << d << endl << endl;
        
       
        inFile.close();
        outFile.close();
    }
}
