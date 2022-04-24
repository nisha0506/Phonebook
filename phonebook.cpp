#include<fstream>
#include<iostream>
#include<cstdio>
#include<conio.h>
using namespace std;
void menu();
void AddNumber();
void DisplayRecords();
void SearchBySrNo();
void deleteRecord();
void modifyRecord();
class PhoneBook
{
    int srno;
    std::string name;
    std::string mobile;
    std::string email;
    std::string group;
public:
    int getSrNo()
    {
        return srno;
    }
    void storeData()
    {
        std::cout<<"\n...........Create New Phone Record...........\n";
        cout<<"Enter Serial Number: ";
        cin>>srno;
        cin.ignore();
        cout<<"Enter Record Name: ";
        getline(cin,name);
        cout<<"Enter Mobile Number: ";
        getline(cin,mobile);
        cout<<"Enter E-mail ID: ";
        getline(cin,email);
        cout<<"Enter Record Group: ";
        getline(cin,group);
        cout<<endl;
    }
    void showData()
    {
        std::cout<<"\n...........Phone Record...........\n";
        cout<<"Sr. No.: "<<srno<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Mobile No.: "<<mobile<<endl;
        cout<<"Email ID: "<<email<<endl;
        cout<<"Group: "<<group<<endl;
    }
}b;
void AddNumber()
{
    ofstream fout;
    fout.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    b.storeData();
    fout.write((char*)&b,sizeof(b));
    fout.close();
    cout<<"\nRecord Saved to File.....\n";
}
void DisplayRecords()
{
    ifstream fin;
    fin.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    while(fin.read((char*)&b,sizeof(b)))
    {
        b.showData();
    }
    fin.close();
    cout<<"\nReading of Data File Competed.....\n";
}
void SearchBySrNo()
{
    ifstream fin;
    int n, flag=0;
    fin.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    cout<<"Enter Serial Number of Record To Display: ";
    cin>>n;
    while(fin.read((char*)&b,sizeof(b)))
    {
        if(n==b.getSrNo())
        {
            b.showData();
            flag++;
            cout<<"\n\n.....Record Found and Displayed.....\n";
        }
    }
    fin.close();
    if(flag==0)
        cout<<"\nThe Record of  Serial Number "<<n<<" is not in file.....\n";
    cout<<"\nReading of Data File Completed.....\n";
}
void deleteRecord()
{
    ifstream fin;
    ofstream fout;
    int n, flag=0;
    fin.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    fout.open("temp.dat",ios::out|ios::binary);
    cout<<"Enter Serial Number of Record to be Delete: ";
    cin>>n;
    while(fin.read((char*)&b,sizeof(b)))
    {
        if(n==b.getSrNo())
        {
            cout<<"\nThe Following record is deleted.....\n";
            b.showData();
            flag++;
        }
        else
        {
            fout.write((char*)&b,sizeof(b));
        }
    }
    fin.close();
    fout.close();
    if(flag==0)
        cout<<"\nThe Record of  Serial Number "<<n<<" is not in file.....\n";
    cout<<"\nReading of Data File Completed.....\n";
    remove("PhoneBook.dat");
    rename("temp.dat","PhoneBook.dat");
}
void modifyRecord()
{
    fstream fio;
    int n, flag=0, pos;
    fio.open("PhoneBook.dat",ios::out|ios::binary|ios::in);
    cout<<"Enter Serial Number of Record To Modify: ";
    cin>>n;
    while(fio.read((char*)&b,sizeof(b)))
    {
       pos=fio.tellg();
       if(n==b.getSrNo())
        {
            cout<<"The following record will be modified.....\n";
            b.showData();
            flag++;
            cout<<"\nRe-Enter the new details.....\n";
            b.storeData();
            fio.seekg(pos-sizeof(b));
            fio.write((char*)&b,sizeof(b));
            cout<<"\n.....Data Modified Successfully.....\n";
        }
    }
    fio.close();
    if(flag==0)
       cout<<"\nThe Record of Serial Number "<<n<<" is not in file.....\n";
    cout<<"\nReading of Data File Completed.....\n";
}
void clrscr()
{
    system("cls");
}
void menu()
{
    int ch;
    do {
        clrscr();
        cout<<"......................................\n";
        cout<<"        Phone Book Management          \n";
        cout<<"......................................\n";
        cout<<":::::::::::::::Program Menu::::::::::::::::\n";
        cout<<"0. Exit\n";
        cout<<"1. Save New Phone Record\n";
        cout<<"2. Display All Saved Records\n";
        cout<<"3. Search Specific Record\n";
        cout<<"4. Delete Specific Record\n";
        cout<<"5. Modify Existing Record\n";
        cout<<"Enter Your Choice: ";
        cin>>ch;
        clrscr();
        switch(ch)
        {
            case 1: AddNumber(); break;
            case 2: DisplayRecords();break;
            case 3: SearchBySrNo(); break;
            case 4: deleteRecord(); break;
            case 5: modifyRecord(); break;
        }
        getch();
    }while(ch);
}
int main()
{
    menu();
}
