#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std;
struct select_query_struct{
    string command_name;//what is the command
    string selector;//what to select
    string clause;//from
    string identifier;//table name
    string condition_clause;//where
    string condition;//condition
}typedef select_query;

void dataselector(string current_db,select_query obj);
void select_query_tokenizer(string data,select_query &obj);

void  select_main(std::string current_db,std::string user_command){
select_query  user_select_query;
select_query_tokenizer(user_command,user_select_query);
// cout<<"Command Name : "<<(!user_select_query.command_name.empty()? user_select_query.command_name : "Null")<<endl;
// cout<<"Selector : "<<(!user_select_query.selector.empty()? user_select_query.selector: "Null")<<endl;
// cout<<"clause: "<<(!user_select_query.clause.empty()? user_select_query.clause: "Null")<<endl;
// cout<<"Identifier : "<<(!user_select_query.identifier.empty()? user_select_query.identifier : "Null")<<endl;
// cout<<"Condition_clause : "<<(!user_select_query.condition_clause.empty()? user_select_query.condition_clause : "Null")<<endl;
// cout<<"Condition : "<<(!user_select_query.condition.empty()? user_select_query.condition: "Null")<<endl;
    dataselector(current_db,user_select_query);

}


void select_query_tokenizer(std::string data,select_query &obj){
vector<int> spacesIndex;

//finding all occurances of space in query
int pos=data.find(' ');
while(pos != std::string::npos){
    spacesIndex.push_back(pos);
   // cout<<"\nPOS : "<<pos;
pos = data.find(' ',pos+1);
}


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

void dataselector(string current_db,select_query obj ){
    string path="db//"+current_db+"//"+obj.identifier+".txt";
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

if(obj.selector == "*"  &&  (obj.condition_clause == "" && obj.condition == "")){
for (int i = 0; i < user_data.size(); i++)
{
    for (int j = 0; j < user_data[0].size(); j++)
    {
        cout<<setw(15)<<user_data[i][j];
    }
    cout<<endl;
}
}else if(obj.selector != "*" &&  obj.condition_clause=="" && obj.condition == ""){
    string d_head=obj.selector;
    int id=0;
    for(int i=0;i<user_data[0].size();i++){
        if(user_data[0][i]==d_head){
           id = i;
           break;
        }else{
            continue;
        }
    }
    for (int i = 0; i < user_data.size(); i++)
{
        cout<<setw(15)<<user_data[i][id];
        cout<<endl;
}
}else if (obj.selector != "*" &&  obj.condition_clause!="" && obj.condition != ""){
string to_Select=obj.selector;
string cond_head;
string cond;
int pos=obj.condition.find("=");
cond_head=obj.condition.substr(0,pos);
cond= obj.condition.substr(pos+1,((obj.condition.length()) -  (pos+1 )));
//finding data index
 string d_head=obj.selector;
    int data_id=0;
    for(int i=0;i<user_data[0].size();i++){
        if(user_data[0][i]==d_head){
           data_id = i;
           break;
        }else{
            continue;
        }
    }

    int cond_id=0;
    for(int i=0;i<user_data[0].size();i++){
        if(user_data[0][i]==cond_head){
           cond_id = i;
           break;
        }else{
            continue;
        }
    }

   cout<<setw(15)<<user_data[0][data_id]<<endl;
   for (int i = 1; i < user_data.size(); i++)
{
   if(user_data[i][cond_id] == cond){
     cout<<setw(15)<<user_data[i][data_id]<<endl;
   }
}

}else if( obj.selector == "*" &&  obj.condition_clause!="" && obj.condition != ""){
   string to_Select=obj.selector;
string cond_head;
string cond;
int pos=obj.condition.find("=");
cond_head=obj.condition.substr(0,pos);
cond= obj.condition.substr(pos+1,((obj.condition.length()) -  (pos+1 )));
//finding data index
 string d_head=obj.selector;
    int data_id=0;
    for(int i=0;i<user_data[0].size();i++){
        if(user_data[0][i]==d_head){
           data_id = i;
           break;
        }else{
            continue;
        }
    }

    int cond_id=0;
    for(int i=0;i<user_data[0].size();i++){
        if(user_data[0][i]==cond_head){
           cond_id = i;
           break;
        }else{
            continue;
        }
    }

for (int i = 0; i < user_data.size(); i++)
{
    int flag=0;
    for (int j = 0; j < user_data[0].size(); j++)
    {
    
            if( i == 0){
        cout<<setw(15)<<user_data[i][j];
        flag=1;
        }else if(user_data[i][cond_id] == cond){
        cout<<setw(15)<<user_data[i][j];
         flag=1;
        }else{
            flag=0; 
            continue;
        }
        
    }
    if(flag){
        cout<<endl;
    }
}
}
}else{
    cout<<"Table is empty"<<endl;
}
    
}