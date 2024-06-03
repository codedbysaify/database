#include<iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include<vector>
using namespace std;
void insertData(string current_db,string tabel,vector<string> data);
int tableChecker(string db,string table);
vector<string> dataParser(string user_command);

void insertInto_main(std::string current_db,string user_command){
    int opos=user_command.find("o");
    int obr_pos=user_command.find("(");
    string table_name=user_command.substr(opos+2,((obr_pos)-(opos+2)));
    cout<<tableChecker(current_db,table_name)<<endl;
    if(tableChecker(current_db,table_name)){
     vector<string> data= dataParser(user_command);
      insertData(current_db,table_name,data);
    }

}

int tableChecker(string db,string table){

    string fpath="db//"+db+"//";
  const char* path=fpath.c_str();
    DIR * dir=opendir(path);
    if (dir == nullptr)
    {
        cout<<"Internal database error.."<<endl;
        return -1;
    }
    dirent * entry;
    while ((entry=readdir(dir)) != nullptr)
    {
        if ((entry->d_name == ".") || (entry->d_name == ".."))
        {
            continue;
        }
        
        if (entry->d_name==table+".txt")
        {
            //cout<<entry->d_name<<endl;
            return 1;
           // cout<<"match found"<<endl;
        }
        
    }
    return 0;
    
    
}

void insertData(string current_db,string tabel,vector<string> data){
string path="db//"+current_db+"//"+tabel+".txt";
fstream table;
table.open(path,ios::app);
if(!table.is_open()){
    cout<<"internal database error ... InsertData"<<endl;
}
char newlinechar='\n';
char seprator=',';

for (int i = 0; i < data.size(); i++)
{
    if (i != data.size()-1)
    {
        table<<data[i];
        table<<seprator;
    }else{
      table<<data[i];  
    }
}
table<<newlinechar;
table.close();
}

vector<string> dataParser(string user_command){
    int obr_pos=user_command.find("(");
    int cbr_pos=user_command.find(")");
    vector<int> col_pos;
    int n=obr_pos;
    col_pos.push_back(n); 
    while (n != std::string::npos)
    {
        n=user_command.find(",",n+1);
        if(n != std::string::npos){
        col_pos.push_back(n);
        }
    }
    col_pos.push_back(cbr_pos);
  


    vector<string> data;
    for(int i=0;i<col_pos.size()-1;i++){
         
         int p1=(user_command.substr(col_pos[i]+1,1)) == "\"" ? (col_pos[i]+2) : (col_pos[i]+1);
         int p2=(user_command.substr(col_pos[i+1]-1,1))== "\"" ? (col_pos[i+1]-2):(col_pos[i+1]-1);
        data.push_back(user_command.substr(p1,(p2-p1)+1));

    }
    return data;

}