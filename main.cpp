#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Node of a linked list
struct Node{
    string data;
    Node *next;
    Node *prev;
};

//For the company database
struct User{
    //holdup
    string name;
    string login;
};

//Array to store information in the Company Database
vector<struct User> v;

//function headers
void mainScr();
void LoginEmp();
void NormalEmployee();
void RegEmp();
void bsort(vector<struct User> &);
string bsearch(string);
void transfer_task(string, string);

//2 classes with Delete, Push, Edit, View, Pop 
class Stack{
    public:
        Node *head = NULL;
        void Push(string data){
            Node *temp = new Node();
            temp->next = head;
            temp->data = data;
            head = temp;
        }
        string Pop(){
            if(head != NULL){
                string num;
                Node *temp = new Node();
                temp = head;
                head = head->next;
                num = temp->data;
                delete temp;
                return num;
            }
            else{
                return "no";
            }
        }
        
        //Linear Search (Algorithm 3)
        void Delete(string item){
            bool ok = false;
            Node *temp = head;
            if(head == NULL){
                cout<<"NO Tasks are due"<<endl;
            }
            else if(head->data == item){
                string del = Pop();
                ok = true;
            }
            else{
                Node *prev = head;
                while(temp != NULL){
                    if(temp->data == item){
                        Node *del = new Node();
                        del = temp;
                        prev->next = temp->next;
                        ok = true;
                        delete del;
                        break;
                    }
                    prev = temp;
                    temp = temp->next;
                }
            }
            if(ok) cout<<"Done!"<<endl;
            else cout<<"Task does not exist!"<<endl;
        }
        
        //Linear Search (Algorithm 3)
        void Edit(string item, string New){
            bool ok = false;
            Node *temp = head;
            while(temp != NULL){
                    if(temp->data == item){
                        temp->data = New;
                        ok = true;
                        break;
                    }
                    temp = temp->next;
            }
            if(ok) cout<<"Done!"<<endl;
            else cout<<"Task does not exist!"<<endl;
        }

        void ShowData(){
            Node *temp = new Node();
            temp = this->head;
            int i = 0;
            cout<<"List of available tasks : "<<endl;
            while(temp != NULL){
                cout<<++i<<". "<<temp->data<<endl;
                temp = temp->next;
            }
        }
};

class Employee{
    private:
        string name;
        string post;
        int task;
    public:
        Stack TODO;
        void toDo(string task){
            this->TODO.Push(task);
        }
        void editTodo(string old, string New){
            this->TODO.Edit(old,New);
        }
        void seeToDo(){
            this->TODO.ShowData();
        }
        void deleteToDo(string task){
            this->TODO.Delete(task);
        }
        void setname(string name){
            this->name = name;
        }
        void setpost(string post){
            this->post = post;
        }
        string getname(){
            return this->name;
        }
        string getpost(){
            return this->post;
        }
};

//swap algorithm
void swap(User &a, User &b){
    User temp = a;
    a = b;
    b = temp;
}

//Bubble Sort(Algorithm 1)
void bsort(vector<User> &v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.size()-1; j++){
            if(v[j].name > v[j+1].name){
                swap(v[j],v[j+1]);
            }
        }
    }
}

//Binary search(Algorithm 2)
string bsearch(string name){
    bsort(v);
    int first = 0;
    int last = v.size()-1;
    int mid;
    bool found = false;
    while(!found && first<=last){
        mid = (first+last)/2;
        if(v[mid].name == name){
            found = !found;
            break;
        }
        else{
            if(name<v[mid].name){
                last = mid - 1;
            }
            else{
                first = mid + 1;
            }
        }
    }
    if(found) return v[mid].login;
    else return "None";
}

//Transfering Tasks among employees
void transfer_task(string item, string user){
    cout<<endl;
    string log = bsearch(user);
    if(log == "None"){
        cout<<"No such user"<<endl;
        return;
    }
    else{
        fstream user;
        user.open(log.c_str());
        vector<string> info;
        string data;
        while(getline(user,data)){
            info.push_back(data);
        }
        info.push_back(item);
        for(auto it:info){
            cout<<it<<endl;
        }
        user.close();
        user.open(log.c_str());
        for(auto it:info){
            user<<it<<endl;
        }
        user.close();
    }
}

int main()
{
    mainScr();
    cout<<"Thank You!"<<endl;
    return 0;
}

//Login session of an employee
void LoginEmp(){
        cout<<endl;
        string usr,pwd, login= "";
        Employee emp;
        cout<<"Write 00 for both username and password to return to previous screen."<<endl;
        cout<<"Username : ";
        getline(cin,usr);
        cout<<"Password : ";
        getline(cin,pwd);
        login = usr+pwd;
        if(login == "0000") return;
        fstream userfile;
        userfile.open(login.c_str());
        if(userfile.is_open()){
            string task;
            string name;
            string post;
            getline(userfile, name);
            getline(userfile, post);
            while(!userfile.eof()){
                getline(userfile, task);
                if(task == "") ;//
                else emp.toDo(task);
            }
            userfile.close();
            string op = "";
            while(true){
                cout<<"\nWhat do you want to do?"<<endl;
                cout<<"1. Add ToDo"<<endl;
                cout<<"2. View ToDo"<<endl;
                cout<<"3. Delete ToDo"<<endl;
                cout<<"4. Edit Task"<<endl;
                cout<<"5. See details"<<endl;
                cout<<"6. Transfer Task(Session Closes after you perform it)"<<endl;
                cout<<"7. Exit"<<endl;
                cout<<"Ans : ";
                getline(cin,op);
                if(op=="1"){
                    string random;
                    cout<<"Add Todo : ";
                    getline(cin,random);
                    emp.toDo(random);
                }
                else if(op == "2"){
                    emp.seeToDo();
                }
                else if(op == "3"){
                    string random;
                    cout<<"What task do you want to delete : ";
                    getline(cin,random);
                    emp.deleteToDo(random);
                }
                else if(op == "4"){
                    string New, Old;
                    cout<<"What task do you want to edit : ";
                    getline(cin,Old);
                    cout<<"What is the new task : ";
                    getline(cin, New);
                    emp.editTodo(Old, New);
                }
                else if(op == "5"){
                    emp.setname(name);
                    emp.setpost(post);
                    cout<<"Name : "<<emp.getname()<<endl;
                    cout<<"Post : "<<emp.getpost()<<endl;
                }
                else if(op == "6"){
                    string trans, receipant;
                    cout<<"Which task do you want to transfer :";
                    getline(cin,trans);
                    cout<<"Who do you want to transfer it to : ";
                    getline(cin,receipant);
                    transfer_task(trans,receipant);
                }
                else if(op == "7"){
                    break;
                }
                else{
                    continue;
                }
            }
            userfile.open(login.c_str());
            if(userfile.is_open()){
                userfile<<name<<"\n";
                userfile<<post<<"\n";
                string bro = emp.TODO.Pop();
                while(bro != "no"){
                    userfile<<"\n"<<bro;
                    bro = emp.TODO.Pop();
                }
            }
            else{
                cout<<"An error occured"<<endl;
            }
            userfile.close();
            LoginEmp();
        }
        else if(login == "00"){
            NormalEmployee();
        }
        else{
            cout<<"User not found or incorrect credentials"<<endl;
            LoginEmp();
        }
}

//Main screen/Start screen
void mainScr(){
    string op;
    cout<<"\nWelcome! Type 1 to proceed Type 0 to exit."<<endl;
    cout<<"Ans : ";
    getline(cin,op);
    if(op == "1") NormalEmployee();
    else if(op == "0") exit;
    else mainScr();
}

//Employee Registration
void RegEmp(){
    cout<<endl;
    string name, post, username, pass, login;
    cout<<"Name : ";
    getline(cin,name);
    cout<<"Post : ";
    getline(cin,post);
    cout<<"Username : ";
    getline(cin,username);
    cout<<"Password : ";
    getline(cin,pass);
    login = username+pass;
    ofstream MyFile(login.c_str());
    MyFile<<name<<endl;
    MyFile<<post<<endl;
    User dummy;
    dummy.name = name;
    dummy.login = login;
    v.push_back(dummy);
    ofstream init("data");
    for(auto it:v){
        init<<it.name<<" "<<it.login<<endl;
    }
    cout<<"Done! Press any key to continue"<<endl;
    getchar();
    mainScr();
}

//Options
void NormalEmployee(){
    cout<<endl;
    ifstream init("data");
    string data;
    string log;
    while(init>>data>>log){
        User dummy;
        dummy.name = data;
        dummy.login = log;
        v.push_back(dummy);
    }
    string op;
    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"Ans : ";
    getline(cin,op);
    if(op == "1") LoginEmp();
    else if(op == "2") RegEmp();
    else if(op == "3") return;
    NormalEmployee();
}
