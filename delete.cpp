#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
void del_tokenizer(string user_command);
void deleter(string current_db,string table);
vector<string> delete_data;
void del_main(std::string current_db,std::string user_command){
    //cout<<user_command<<endl;
      
      del_tokenizer(user_command);
// cout<<"delete from : "<<delete_data[0]<<endl;
// cout<<"delete : " <<delete_data[1]<<endl;
// cout<<"condition head: "<<delete_data[2]<<endl;
// cout<<"condition value : "<<delete_data[3]<<endl;

 deleter(current_db,delete_data[0]);

}

// delete name from data where name=saif
//delete name from data where name=saif
void del_tokenizer(string user_command){

int pos=user_command.find(" ");//position for first space
int pos2=user_command.find(" ",pos+1);//position for second space 

string to_delete=user_command.substr(pos+1,pos2 - (pos+1));

int pos3=user_command.find(" ",pos2+1);//position of third space
int pos4=user_command.find(" ",pos3+1);//position of forth space

string delete_from=user_command.substr(pos3+1,pos4 - (pos3+1));

int pos5=user_command.find(" ",pos4+1);
string condition= user_command.substr(pos5+1,(user_command.length() - (pos5+1)));

int epos=condition.find("=");

string condition_head=condition.substr(0,epos);
string condition_val=condition.substr(epos+1,(condition.length()-(epos+1)));



delete_data={delete_from,to_delete,condition_head,condition_val};
}


void deleter(string current_db,string table){

    try{
       string path="db//"+current_db+"//"+table+".txt";
    fstream file;
    file.open(path,ios::in);
    if (!file.is_open())
    {
        cout<<"Error opening file ... dataselector/select.cpp"<<endl;
        return;
    }
    vector<string> filedata;
    string line;
    if(getline(file,line)){
         filedata.push_back(line);
    while (getline(file,line))
    {
      filedata.push_back(line);
    }
    //reading table data

    string meta=filedata[0];

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
    vector<string> data;


    for (int i = 0; i < commas.size() - 1; i++)
    {
       data.push_back(str.substr(commas[i]+1,commas[i+1]-(commas[i]+1)) );
    }
vector<vector<string>> user_data(filedata.size());
for (int i = 0; i < data.size(); i++)
{
    user_data[0].push_back(data[i]);
}
for (int i = 1; i < filedata.size(); i++)
{
    string row=filedata[i];
    //cout<<row<<endl;
    vector<int> commas;
    commas.push_back(-1);
    int pos=row.find(",");
    while(pos != std::string::npos){
        commas.push_back(pos);
        pos=row.find(",",pos+1);
    }
    commas.push_back(filedata[i].length());
    
    for (int j = 0; j < commas.size()-1; j++)
    {
        user_data[i].push_back(row.substr(commas[j]+1,commas[j+1] - (commas[j]+1)));
    }
}
cout<<setw(50)<<"Previous data : "<<endl;
for (int i = 0; i < user_data.size(); i++)
{
    for (int j = 0; j < user_data[0].size(); j++)
    {
        cout<<setw(15)<<user_data[i][j];
    }
    cout<<endl;
}
cout<<setw(50)<<"------ "<<endl;

int del_id=0;

for (int i = 0; i < user_data[0].size(); i++)
{
    if (user_data[0][i] == delete_data[1] )
    {
       del_id=i;
    }else{
        if (i == user_data[0].size())
        {
            cout<<"Data not found"<<endl;
            return;
        }
        continue;
    }
    
}


int condition_id=0;

for (int i = 0; i < user_data[0].size(); i++)
{
    if (user_data[0][i] == delete_data[2] )
    {
       condition_id=i;
    }else{
        if (i == user_data[0].size())
        {
            cout<<"Data not found"<<endl;
            return;
        }
        continue;
    }
    
}

for (int i = 1; i < user_data.size(); i++)
{
    for (int j = 0; j < user_data[0].size(); j++)
    {
        if ((user_data[i][j] == delete_data[3]) && j == condition_id )
        {
            // cout<<user_data[i][j]<<endl;
            // cout<<update_data[4]<<endl;
             user_data[i][del_id] = "";
        }else{
            continue;
        }
        
    }
    cout<<endl;
}

cout<<setw(50)<<"updated data : "<<endl;
for (int i = 0; i < user_data.size(); i++)
{
    for (int j = 0; j < user_data[0].size(); j++)
    {
        cout<<setw(15)<<user_data[i][j];
    }
    cout<<endl;
}
cout<<setw(50)<<"------ "<<endl;

file.close();
//writing back updated data to table 

file.open(path,ios::out);
if(!file.is_open()){
    cout<<"error openning file .... update.cpp/205"<<endl;
    return;
}
        string start="<metadata>";
            string end="</metadata>";
            string seprator=",";
for (int i = 0; i < user_data.size(); i++)
{
    for (int j = 0; j < user_data[0].size(); j++)
    {
        if(i==0 && j==0){
          file<<start;
          file<<user_data[i][j];   
          file<<seprator;
        }else if(i==0 && j==user_data[0].size() -1){
           file<<user_data[i][j];
           file<<end;
        //    file<<endl;  
        }else if (j != user_data[0].size() -1)
        {
            file<<user_data[i][j];
            file<<seprator;
        }else{
            file<<user_data[i][j];
            // file<<endl;
        }

    }
    file<<endl;
}

file.close();


}
    }catch(...){
        cout<<"invalid command"<<endl;
        return;
    }

}