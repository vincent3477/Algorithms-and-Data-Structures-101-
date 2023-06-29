/********************************************************************************* 
* Vincent Siu, vsiu2
* 2023 Spring CSE101 PA8 
* Order.cpp 
* This file will take one input file and sort the words based on the alphabetical order and the order in which they were found and put the results into an output file.
*********************************************************************************/ 

#include <iostream>
#include <string.h>
#include "Dictionary.h"
using namespace std;
int main (int argc, char *argv[]){
    if(argc == 3){
    	FILE *inFile;
        FILE *outFile;


        inFile = fopen(argv[1],"r");
        outFile = fopen(argv[2],"w");
        
        
        char instring[4096] = "";
        
        Dictionary d = Dictionary();
        int line = 0;
        string lastval = "";
        while(!feof(inFile)){
            //cout << "fetching " << line << "\n";
            fscanf(inFile,"%s",instring);
            line++;
            d.setValue(instring,line);
            lastval = instring;
            
        }
        
        d.setValue(lastval,line-1);
        //cout << "done fetching\n";

       // char * alpha = d.to_string().c_str();
        //string byLine = d.pre_string();
        fputs(d.to_string().c_str(),outFile);
        fprintf(outFile,"\n");
        //cout << "done printing one part\n";
        fputs(d.pre_string().c_str(),outFile);
        //cout << "done printing the other part\n";
        fclose(inFile);
        fclose(outFile);
    }
    else{
        throw std::invalid_argument("You did not enter two arguements.\n");
    }
		
}

