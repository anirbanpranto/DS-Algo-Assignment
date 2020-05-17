#include <iostream>
#include <fstream>

/*
Employee Task Delete
*/

using namespace std;

struct Node{
    string data;
    Node *next;
    Node *prev;
};

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
        double salary;
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

void NormalEmployee();
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
                emp.toDo(task);
            }
            userfile.close();
            int op = 1;
            while(op != 7){
                cout<<"\nWhat do you want to do?"<<endl;
                cout<<"1. Add ToDo"<<endl;
                cout<<"2. View ToDo"<<endl;
                cout<<"3. Delete ToDo"<<endl;
                cout<<"4. Edit Task"<<endl;
                cout<<"5. See details"<<endl;
                cout<<"6. Task Transfer"<<endl;
                cout<<"7. Exit"<<endl;
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
                    getline(cin,New);
                    cout<<"What is the new task : ";
                    getline(cin, Old);
                    emp.editTodo(Old, New);
                }
                else if(op == 5){
                    emp.setname(name);
                    emp.setpost(post);
                    cout<<"Name : "<<emp.getname()<<endl;
                    cout<<"Post : "<<emp.getpost()<<endl;
                }
                else if(op == 6){
                    //task transfer
                }
            }
            userfile.open(login);
            if(userfile.is_open()){
                userfile<<name<<endl;
                userfile<<post<<endl;
                string bro = emp.TODO.Pop();
                while(bro != "no"){
                    userfile<<bro<<endl;
                    bro = emp.TODO.Pop();
                }
            }
            else{
                cout<<"An error occured"<<endl;
            }
            userfile.close();
            NormalEmployee();
        }
        else{
            cout<<"User not found or incorrect credentials"<<endl;
            LoginEmp();
        }
}

void mainScr(){
    int op;
    cout<<"\nWelcome! Type 1 to proceed Type 0 to exit."<<endl;
    cout<<"Ans : ";
    cin>>op;
    if(op == 1) NormalEmployee();
    else if(op == 0) return;
    else mainScr();
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
    else if(op == 2);
    else if(op == 3){
        mainScr();
    }
}

int main()
{
    mainScr();
    cout<<"Thank You!"<<endl;
    return 0;
}
