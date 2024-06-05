//>g++ -std=c++17 main.cpp create.cpp createTable.cpp insertInto.cpp select.cpp update.cpp delete.cpp info.cpp -o main.exe
//checking c++ standard
    //cout << __cplusplus << std::endl;
#include<iostream>
#include<iomanip>
#include<windows.h>
#include<string>
#include<vector>
#include "create.h"
#include "createTable.h"
#include "insert.h"
#include "sel.h"
#include "update.h"
#include "del.h"
#include "info.h"
using namespace std;
int screenWidth;
std::string current_database;
int screenWidthCalculator();

int main(){
    {
screenWidth=screenWidthCalculator();
  string data="MY  DATABASE";
  cout<<setw(50)<<data;
    }
string userInput;
do{
cout<<"\n>>";
getline(cin,userInput);
//cout<<"userInput: "<<userInput;
if(!userInput.empty()){
int fsi=userInput.find(' ');//first space index of user input
string command=userInput.substr(0,fsi);
if (command == "select")
{

select_main(current_database,userInput);
}
else if (command == "create_table"){

createTable_main(userInput,current_database);

}else if(command == "insert"){
    insertInto_main(current_database,userInput);
}else if(command == "create"){

create_main(userInput);

}else if(command == "use"){

int pos=userInput.find(" ");
int flag=userInput.find(" ",pos+1);
if(flag == std::string::npos){
current_database = userInput.substr(pos+1,(userInput.length()-( pos+1)));
cout<<"Current database in use : "<<current_database;

}
}else if(command == "update"){
     update_main(current_database,userInput);
}else if(command == "delete"){
    del_main(current_database,userInput);
}else if(command == "databaseinfo"){
    database_info(current_database);
}else if(command == "tableinfo"){
 table_info(current_database,userInput);
}
else{
    if(userInput != "exit"){
    cout<<"Invalid input!!!";//Add custom error classes
    }
}
}else{
    cout<<"INPUT is Empty"; //implement cpp defualt error control classes
}


} while(userInput != "exit");
    return 0;
}

int screenWidthCalculator(){
//checking screen width 

HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo(hconsole,&csbi)){
int left=csbi.srWindow.Left;
int right=csbi.srWindow.Right;
int width = (right-left)+1;
return width;
}else{
    cout<<"ERROR READING SCREEN BUFFER DATA";
    return 0;
}
}



