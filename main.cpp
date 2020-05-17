#include <iostream>
#include <fstream>
#include <vector>
#include <map>
/*
Employee Task Delete
*/
using namespace std;

struct Node{
    string data;
    Node *next;
    Node *prev;
};

void mainScr();
void binarySearch(map<string, int> w);
void findmax(map<string, int> &v);
void findMin(map<string, int> &v);
map<string, int> worker;
void LoginEmp();
void NormalEmployee();
void RegEmp();

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

int main()
{
    mainScr();
    cout<<"Thank You!"<<endl;
    return 0;
}

void LoginEmp(){
        string usr,pwd, login= "";
        Employee emp;
        cout<<"Username : ";
        cin>>usr;
        cout<<"Password : ";
        cin>>pwd;
        login = usr+pwd;
        fstream userfile;
        userfile.open(login);
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
            int op = 1;
            while(op != 6){
                cout<<"\nWhat do you want to do?"<<endl;
                cout<<"1. Add ToDo"<<endl;
                cout<<"2. View ToDo"<<endl;
                cout<<"3. Delete ToDo"<<endl;
                cout<<"4. Edit Task"<<endl;
                cout<<"5. See details"<<endl;
                cout<<"6. Exit"<<endl;
                cout<<"Ans : ";
                cin>>op;
                cin.ignore(100,'\n');
                if(op==1){
                    string random;
                    cout<<"Add Todo : ";
                    getline(cin,random);
                    emp.toDo(random);
                }
                else if(op == 2){
                    emp.seeToDo();
                }
                else if(op == 3){
                    string random;
                    cout<<"What task do you want to delete : ";
                    getline(cin,random);
                    emp.deleteToDo(random);
                }
                else if(op == 4){
                    string New, Old;
                    cout<<"What task do you want to edit : ";
                    getline(cin,Old);
                    cout<<"What is the new task : ";
                    getline(cin, New);
                    emp.editTodo(Old, New);
                }
                else if(op == 5){
                    emp.setname(name);
                    emp.setpost(post);
                    cout<<"Name : "<<emp.getname()<<endl;
                    cout<<"Post : "<<emp.getpost()<<endl;
                }
                else{
                    break;
                }
            }
            userfile.open(login);
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
            NormalEmployee();
        }
        else if(login == "00"){
            NormalEmployee();
        }
        else{
            cout<<"User not found or incorrect credentials"<<endl;
            LoginEmp();
        }
}

void HighPerf(){
//
}
void LowPerf(){
//
}

void mainScr(){
    int op;
    cout<<"\nWelcome! Type 1 to proceed Type 0 to exit."<<endl;
    cout<<"Also! You can see who has got more work done and evaluate performance of others!\n";
    cout<<"Press 3 to see most working person and 4 to see least working person\n";
    cout<<"Ans : ";
    cin>>op;
    cin.ignore(100,'\n');
    if(op == 1) NormalEmployee();
    else if(op == 2) HighPerf();
    else if(op == 3) LowPerf();
    else if(op == 0) return;
    else mainScr();
}

void RegEmp(){
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
    ofstream MyFile(login);
    ofstream outfile;
    cout<<"Done! Press any key to continue"<<endl;
    MyFile<<name<<endl;
    MyFile<<post<<endl;
    outfile.open("database.txt", ios_base::app);
    outfile<<name<<" "<<0<<endl;
    outfile.close();
    getchar();
    mainScr();
}

void NormalEmployee(){
    int op;
    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"Ans : ";
    cin>>op;
    cin.ignore(100,'\n');
    if(op == 1) LoginEmp();
    else if(op == 2) RegEmp();
    else if(op == 3){
        mainScr();
    }
}
