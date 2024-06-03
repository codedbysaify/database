#include<iostream>
#include<sys/stat.h>
//#include "create.h"
#include "structures.h"
#include <direct.h>

using namespace std;
void create_main(string user_command){
    
  create_database obj;
    int si=user_command.find(" ");
    int flag=user_command.find(" ",si+1);
    if(flag == std::string::npos){
    obj.command = user_command.substr(0,si);
    obj.databasename = user_command.substr(si+1,((user_command.length())-(si+1)));
   //cout<<"create.cpp : \n command : " <<obj.command <<endl <<"Database name : " <<obj.databasename;
  string directory="db//" + obj.databasename;
 int status = mkdir(directory.c_str());
 if(status < 0 ){
    cout<<"Error creating a folder";
 }else{
    cout<<"DataBase created succefully ...\n";
 }
   } else  {
    cout<<"Invalid command";
   }
}
