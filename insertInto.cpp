#include<iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include<vector>
using namespace std;
void insertData(string current_db,string tabel,vector<string> data);
int tableChecker(string db,string table);
int validation(string current_db,string table);
vector<string> dataParser(string user_command);

void insertInto_main(std::string current_db,string user_command){
    int opos=user_command.find("o");
    int obr_pos=user_command.find("(");
    string table_name=user_command.substr(opos+2,((obr_pos)-(opos+2)));
    if(tableChecker(current_db,table_name)){
     vector<string> data= dataParser(user_command);
     int sze=validation(current_db,table_name);
     if (data.size() == sze)
     {
    insertData(current_db,table_name,data);
     }else{
        cout<<"Error in data length"<<endl;
        return;
     }
     
    }else{
        cout<<"Table not found"<<endl;
        return;
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

int validation(string current_db,string table){
    string path="db//"+current_db+"//"+table+".txt";
    fstream file;
  file.open(path,ios::in);
  if(!file.is_open()){
    cout<<"error opening file .... insertinto/validation"<<endl;
    return -1;
  }
  string line;
  if (getline(file,line))
  {
   // cout<<line<<endl;
   int gr_pos=line.find(">");
  int ls_pos=line.find("<",gr_pos+1);
  string str=line.substr(gr_pos+1,ls_pos-(gr_pos+1));
  vector<int> commas;
  commas.push_back(-1);
    int cm_pos=str.find(",");
    while (cm_pos != std::string::npos)
    {
        commas.push_back(cm_pos);
        cm_pos=str.find(",",cm_pos+1);
    }
    commas.push_back(str.length());
    vector<string> data;
    for (int i = 0; i < commas.size() - 1; i++)
    {
       data.push_back(str.substr(commas[i]+1,commas[i+1]-(commas[i]+1)) );
    }
      return data.size();
  }

  
  return 0;
}