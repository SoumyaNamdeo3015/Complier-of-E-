/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#include<iostream>
//Write your code below this line

//floor(x/y) and y!=0
int __div__(int x, int y){
    if(x%y ==0){ return x/y; }
    else if(x*y<0 && x%y!=0){ return (x/y) -1;}
    return x/y;
}

EPPCompiler::EPPCompiler(){}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
}

void EPPCompiler::compile(vector<vector<string>> code){

}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string>v;
    return v;
}

void EPPCompiler::write_to_file(vector<string>commands){
    ofstream myfile(output_file);
    int sz = commands.size();
    for(int i=0;i<sz;i++){
        string CommandString = commands[i];
        myfile << CommandString << endl;
    }   
    cout << output_file <<" created!" << endl;
    myfile.close();
}

EPPCompiler::~EPPCompiler(){
  //there's nothing to be deleted :(
}

int main(){
  EPPCompiler epp("outputfile1.txt",100);
  vector<string>commands{"output file created successfully!","//this is a comment"};
 epp.write_to_file(commands);
  return 0;
}