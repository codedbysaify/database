#include<iostream>
#include<sys/stat.h>
#include<iomanip>
#include<vector>
#include<string>
#include<dirent.h>
#include<cstring>
#include<fstream>
using namespace std;
void table_info(std::string current_db,std::string user_command);
void database_info(std::string current_db){
string fpath="db//"+current_db+"//";
const char * path=fpath.c_str();
DIR * dir=opendir(path);
if (dir == nullptr)
{
    cout<<"Error openening directory ...info.cpp"<<endl;
}
dirent * entry;
cout<<setw(50)<<"Tables list "<<endl;
while ((entry = readdir(dir)) != nullptr)
{
    if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0 ){
    continue;
    }
    cout<<setw(50)<<entry->d_name<<endl;
}
closedir(dir); 
}
void table_info(std::string current_db,std::string user_command){

int pos=user_command.find(" ");
string table=user_command.substr(pos+1,(user_command.length() - (pos+1)));
  string path="db//"+current_db+"//"+table+".txt";
    fstream file;
    file.open(path,ios::in);
    if (!file.is_open())
    {
        cout<<"Error opening file ... dataselector/select.cpp"<<endl;
        return;
    }
    string meta;
    if(getline(file,meta)){
      //   filedata.push_back(line);
    }
 file.close();
 
    int gr_pos=meta.find(">");
  int ls_pos=meta.find("<",gr_pos+1);
  string str=meta.substr(gr_pos+1,ls_pos-(gr_pos+1));
  vector<int> commas;
  commas.push_back(-1);
    int cm_pos=str.find(",");
    while (cm_pos != std::string::npos)
    {
        commas.push_back(cm_pos);
        cm_pos=str.find(",",cm_pos+1);
    }
    commas.push_back(str.length());
    //vector<string> data;
     cout<<setw(50)<< "Columns"<<endl;
    for (int i = 0; i < commas.size() - 1; i++)
    {
    //    data.push_back(str.substr(commas[i]+1,commas[i+1]-(commas[i]+1)) );
     cout<<setw(50)<<str.substr(commas[i]+1,commas[i+1]-(commas[i]+1))<<endl;
         
    }

}