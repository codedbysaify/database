#include<iostream>
#include"createTable.h"
#include<dirent.h>
#include<sys/types.h>
#include <vector>
#include<cstring>
#include<fstream>
#include<string>
using namespace std;
string Checker(string db_name,string table);
int CreateTable(string table_name,string current_db);

//create_table student("name","class","enrollement")

void createTable_main(string user_command,string current_db){
int pos=user_command.find(" ");
int obr_pos=user_command.find("(");
int cbr_pos=user_command.find(")");
vector<string> tabel_heads;

int col_pos=user_command.find("\"");
vector <int> colons;


string table_name = user_command.substr(pos+1 ,(obr_pos - (pos+1)));
while (col_pos != std::string::npos)
{
    colons.push_back(col_pos);
    col_pos = user_command.find("\"",col_pos+1);
}

cout<<"Table Name : "<<table_name<<endl;
for(int i =0 ; i<colons.size();i++){
    cout<<colons[i]<<endl;
}
for(int i =0 ; i<colons.size();i+=2){
    cout<<user_command.substr(colons[i]+1,((colons[i+1])-(colons[i]+1)) )<<endl;
    //cout<<colons[i]<<endl;
}

            // if (  Checker(current_db,table_name) == "not found")
            // {
            //     CreateTable(table_name,current_db);
            // }
           
}

string Checker(string db_name,string table){
    string fpath="db//"+db_name + "//";
const char*path=fpath.c_str();
DIR* dir=opendir(path);
if (dir ==  nullptr ){
    cout<<"unable to open folder : createTable - 17"<<endl;
    return "error finding the folder";
}
vector <string> entries;
struct dirent * entry;
while ((entry =  readdir(dir)) != nullptr){
//cout<<entry -> d_name<<endl;    
if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0 ){
    continue;
    }
entries.push_back(entry->d_name);
}

if (entries.size() != 0)
{
string res;
int i=0;
do
{
  res= entries[i] == (table + ".txt") ? "found" : "not found";
  ++i;
} while (i < entries.size());
closedir(dir);  
return res;
}else{
    closedir(dir); 
    return "not found";
}
}

int CreateTable(string table_name,string current_db){
string path = "db//" + current_db + "//" + table_name + ".txt";

fstream table;

table.open(path ,ios::out );
if(!table.is_open()){
    cout<<"error creating table - CreateTable 68"<<endl;
    return 0;
}else{
    cout<<"Created Table succesfully..";
    return 1;
}
table.close();
}