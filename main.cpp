/* 
 * File:   main.cpp
 * Author: noemurr
 *
 * Created on 18 agosto 2015, 12.30
 * 
 * goal of program: the program will cript a file 
 *                  with method of trasposition with key.
 */

#include <cstdlib>
#include <string>
#include <fstream>
#include "functions/functions.h"
#include <time.h>

using namespace std;

int main(int argc, char** argv) {
    if(argc == 1){
        cout << "usage: "<<argv[0]<<" c/d path_input_file path_output_file key\n";
        return END_FAILED;
    }
    // dichiarazione dei file.
    FILE* inFile;
    FILE* outFile;
    
    // apertura dei file.
    inFile = fopen(argv[2], "rb");
    
    if(!inFile){
        cout<<"error opening input file\n";
        return END_FAILED;
    
    }
    
    outFile = fopen(argv[3], "wb");
    
    // controlli sulla avvenuta apertura dei file con successo:
    if(!outFile){
        cout<<"error opening output file\n";
        return END_FAILED;
    
    }

       
    if(argv[1][0] == 'c'){
        clock_t start,end;
        start = clock();
        // preparazione output
        cout << "\nOperation: encryption;";
        cout << "\nKey: "<< argv[4] << ";\n";
        cout << "\nInput file:\n\tpath: " << argv[2] << ";\n\tsize: " << file_size(inFile) / 1024 << "kB (" << file_size(inFile) << "B);\n\nbeginning encryption: \n";
        if(cript(inFile,outFile,argv[4],strlen(argv[4]))){
            cout << "\nOutput file:\n\tpath: " << argv[3] << ";\n\tsize: " << file_size(outFile) / 1024 << "kB (" << file_size(outFile) << "B);";
            end = clock();
            cout << "\nfile crypted in " << double(end-start)/CLOCKS_PER_SEC << " seconds;";
            cout << endl << "\n------------------------ENCRYPTION COMPLETE-----------------------------\n";
            fclose(inFile);
            fclose(outFile);
            return END_SUCCESS;
        }
        else{
            return END_FAILED;
        }
    }
    else if(argv[1][0] == 'd'){
        clock_t start,end;
        start = clock();
        // preparazione output
        cout << "\nOperation: decryption;";
        cout << "\nKey: "<< argv[4] << ";\n";
        cout << "\nInput file:\n\tpath: " << argv[2] << ";\n\tsize: " << file_size(inFile) / 1024 << "kB (" << file_size(inFile) << "B);\n\nbeginning decryption: \n";
        if(decript(inFile,outFile,argv[4],strlen(argv[4]))){
            cout << "\nOutput file:\n\tpath: " << argv[3] << ";\n\tsize: " << file_size(outFile) / 1024 << "kB (" << file_size(outFile) << "B);";
            end = clock();
            cout << "\nfile decrypted in " << double(end-start)/CLOCKS_PER_SEC << " seconds;";
            cout << endl << "\n------------------------DECRYPTION COMPLETE-----------------------------\n";
            fclose(inFile);
            fclose(outFile);
            return END_SUCCESS;
        }
        else{
            cout << endl << "\n------------------------DECRYPTION FAILED-----------------------------\n";
            return END_FAILED;
        }
    }
    else{
        cout << "option '" << argv[1] <<"' not recognized\n";
    }
    return 0;
}

