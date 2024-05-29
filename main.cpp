//>g++ -std=c++17 main.cpp -o main.exe
//checking c++ standard
    //cout << __cplusplus << std::endl;
#include<iostream>
#include<iomanip>
#include<windows.h>
#include<string>
#include<vector>
using namespace std;
int screenWidth;
struct select_query_struct{
    string command_name;//what is the command
    string selector;//what to select
    string clause;//from
    string identifier;//table name
    string condition_clause;//where
    string condition;//condition
}typedef select_query;

void  manipulator(int spaces,char fillwith,string data);
int screenWidthCalculator();
void select_query_tokenizer(string data,select_query &obj);
int main(){
    {
screenWidth=screenWidthCalculator();
  string data="MY  DATABASE";
manipulator(30,' '," ");
manipulator(20,'~',data);
manipulator(10,'~'," ");
cout<<endl;
    }
string userInput;
select_query  user_select_query;
cout<<">>";
getline(cin,userInput);

//cout<<"userInput: "<<userInput;
if(!userInput.empty()){

int fsi=userInput.find(' ');//first space index of user input
string command=userInput.substr(0,fsi);
if (command == "select")
{
select_query_tokenizer(userInput,user_select_query);
cout<<"Command Name : "<<(!user_select_query.command_name.empty()? user_select_query.command_name : "Null")<<endl;
cout<<"Selector : "<<(!user_select_query.selector.empty()? user_select_query.selector: "Null")<<endl;
cout<<"clause: "<<(!user_select_query.clause.empty()? user_select_query.clause: "Null")<<endl;
cout<<"Identifier : "<<(!user_select_query.identifier.empty()? user_select_query.identifier : "Null")<<endl;
cout<<"Condition_clause : "<<(!user_select_query.condition_clause.empty()? user_select_query.condition_clause : "Null")<<endl;
cout<<"Condition : "<<(!user_select_query.condition.empty()? user_select_query.condition: "Null")<<endl;
}else{
    cout<<"Invalid input!!!";
}



}else{
    cout<<"INPUT is Empty"; //implement cpp defualt error control classes
}

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
void manipulator(int spaces,char fillwith,string data){
cout<<setfill(fillwith)<<setw(spaces)<<data;
return;
}

void select_query_tokenizer(string data, select_query &obj){
vector<int> spacesIndex;

//finding all occurances of space in query
int pos=data.find(' ');
while(pos != std::string::npos){
    spacesIndex.push_back(pos);
   // cout<<"\nPOS : "<<pos;
pos = data.find(' ',pos+1);
}

cout<<"Check : "<<spacesIndex[1] - (spacesIndex[0]+1)<<endl;


if(spacesIndex.size() == 3){
obj.command_name = data.substr(0,spacesIndex[0]); 
obj.selector = data.substr(spacesIndex[0]+1,(spacesIndex[1] - (spacesIndex[0]+1)));
obj.clause=data.substr(spacesIndex[1]+1,(spacesIndex[2] - (spacesIndex[1]+1)));
obj.identifier=data.substr(spacesIndex[2]+1,(data.length()-(spacesIndex[2]+1)));
obj.condition_clause="";
obj.condition="";
}else{
    obj.command_name = data.substr(0,spacesIndex[0]); 
obj.selector = data.substr(spacesIndex[0]+1,(spacesIndex[1] - (spacesIndex[0]+1)));
obj.clause=data.substr(spacesIndex[1]+1,(spacesIndex[2] - (spacesIndex[1]+1)));
obj.identifier=data.substr(spacesIndex[2]+1,(spacesIndex[3]-(spacesIndex[2]+1)));
obj.condition_clause=data.substr(spacesIndex[3]+1,(spacesIndex[4]-(spacesIndex[3]+1)));;
obj.condition=data.substr(spacesIndex[4]+1,(data.length()-(spacesIndex[4]+1)));
}

}





// for (int i = 0; i < spacesIndex.size(); i++)
// {
   
//    cout<<"\nSpace Index : "<<spacesIndex[i];
// }

//complete select query and start making create query


//6 8 13 22