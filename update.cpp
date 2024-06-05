#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;
void tokenizer(string command);
void table_reader(string curernt_db,string table);
//update update_data name=saif where name=saiiif

vector<string>update_data;


void update_main(std::string current_db,std::string user_command){
    //cout<<user_command<<endl;
     tokenizer(user_command);
//      cout<<"Table : " <<update_data[0]<<endl;
// cout<<"update heading : "<<update_data[1]<<endl;
// cout<<"update value : "<<update_data[2]<<endl;
// cout<<"condition heading : "<<update_data[3]<<endl;
// cout<<"condition value : "<<update_data[4]<<endl;
table_reader(current_db,update_data[0]);


}


void tokenizer(string command){

int pos=command.find(" ");//position of first space
int pos2=command.find(" ",pos+1);//position of second space

string table=command.substr(pos+1,pos2-(pos+1));

int pos3=command.find(" ",pos2+1);//third space position
string upstate=command.substr(pos2+1,pos3-(pos2+1));

if(command.substr(pos2+1,pos3-(pos2+1)).find("=") == std::string::npos){
    cout<<"invalid command"<<endl;
    return;
}
int epos=upstate.find("=");
string update_head=upstate.substr(0,epos);
string update_val=upstate.substr(epos+1,upstate.length() - (epos+1));

int pos4=command.find(" ",pos3+1);
string condition=command.substr(pos4+1,command.length()-(pos4+1));
int cepos=condition.find("=");
string condition_head=condition.substr(0,cepos);
string condition_value=condition.substr(cepos+1,condition.length() - (cepos+1));

// cout<<"Table :" <<table<<endl;
// cout<<"update heading : "<<update_head<<endl;
// cout<<"update value : "<<update_val<<endl;
// cout<<"condition heading : "<<condition_head<<endl;
// cout<<"condition value : "<<condition_value<<endl;
 update_data={table,update_head,update_val,condition_head,condition_value}; 

}

void table_reader(string current_db,string table){
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

int update_id=0;

for (int i = 0; i < user_data[0].size(); i++)
{
    if (user_data[0][i] == update_data[1] )
    {
       update_id=i;
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
    if (user_data[0][i] == update_data[3] )
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
        if ((user_data[i][j] == update_data[4]) && j == condition_id )
        {
            // cout<<user_data[i][j]<<endl;
            // cout<<update_data[4]<<endl;
             user_data[i][update_id] = update_data[2];
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

}