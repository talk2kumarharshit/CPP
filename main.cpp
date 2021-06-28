#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

int count, mprice;
class book;

class movie
{
    private:
        int id;
        char name[30], time[30];
        float price;
    public:
        friend class book;
        movie()
        {
            id = 0;
            strcpy(name, "no name");
            price = 0;
        }
        void setdata();
        void showdata();
        int storedata();
        void updatedata(char*);
        void deletedata(char*);
        void searchdata(char*);
        void viewdata();

        int getprice()
        {
            mprice = price;
        }

};

class book
{
    char mname[30], pname[30], btime[6], mobile[15];
    int  qty, bprice;

    public:
        friend class movie;
        book()
        {
            qty = 0, mprice = 0, bprice = 0;
            strcpy(mname, "no name");
            strcpy(mobile, "no name");
            strcpy(pname, "no name");
        }
        void setbooking();
        void showbooking();
        int storebooking();
        void viewbooking();
};

void movie :: setdata()
{
    cout<<"\t\tEnter The Id: ";
    cin>>id;
    cin.ignore();
    cout<<"\t\tEnter The Movie Name: ";
    cin.getline(name,29);
    cout<<"\t\tEnter The Movie Timing(hh:min)(seperated by comma): ";
    cin.getline(time,29);
    cout<<"\t\tEnter Price: ";
    cin>>price;
}

void movie :: showdata()
{
    cout<<"\t\t"<<id<<")  "<<name<<"\t\t\t"<<time<<"\t\t\t\t"<<price<<" Rs\n";
    cout<<"\t\t------------------------------------------------------------------------";
}

int movie :: storedata()
{
    if(id==0 && price == 0)
    {
        cout<<"Data Not Initialize"<<endl;
        return 0;
    }
    ofstream fout;
    fout.open("Mov.txt", ios::app);
    fout.write((char*)this, sizeof(*this));
    fout.close();
    cout<<"\n\t\tData Upload Successfully ! "<<endl;
    cout<<"\tPress any key to continue!!!";
    getch();
    return 0;
}

void movie :: updatedata(char* t)
{
    fstream file;
    count = 0;
    file.open("Mov.txt", ios::in|ios::out|ios::ate);
    file.seekg(0);
    file.read((char*)this, sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(t,name))
        {
            setdata();
           file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this, sizeof(*this));
            count++;
        }
        file.read((char*)this, sizeof(*this));
    }
    if(count!=0)
        cout<<"\n\t\tMovie Data Updated Successfully\n";
    else
        cout<<"\n\t\tMovie Not Found\n";
    count = 0;
    file.close();
    cout<<"\tPress any key to continue!!!";
    getch();
}

void movie :: deletedata(char* t)
{
    ifstream fin;
    ofstream fout;
    count = 0;
    fin.open("Mov.txt",ios::in);
    if(!fin)
        cout<<"\n\tFile Not Found\n\n";
    else
    {
        fout.open("Temp.txt", ios::out);
        fin.read((char*)this, sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(name, t))
            {

                fout.write((char*)this, sizeof(*this));
                count++;
            }
            else
                count = 0;
            fin.read((char*)this, sizeof(*this));
        }
        if(count>0)
        cout<<"\n\t\tMovie Not Found \n";
        else
        cout<<"\n\t\tMovie Deleted Successfully\n";
        count = 0;
        fin.close();
        fout.close();
        remove("Mov.txt");
        rename("Temp.txt", "Mov.txt");
    }
    cout<<"\tPress any key to continue!!!";
    getch();
}

void movie :: viewdata()
{
    ifstream fin;
    fin.open("Mov.txt",ios::in|ios::binary);
    if(!fin)
        cout<<"\n\tFile Not Found\n\n";
    else
    {
        fin.read((char*)this, sizeof(*this));
        while(!fin.eof())
        {
            showdata();
            cout<<endl;
            fin.read((char*)this, sizeof(*this));
        }

        fin.close();
    }
    cout<<"\tPress any key to continue!!!";
    getch();
}

void movie::searchdata(char* t)
{
    ifstream fin;
    count =0;
    fin.open("Mov.txt", ios::in);
    if(!fin)
        cout<<"\n\t\tFile Not Found"<<endl;
    else
    {
        fin.read((char*)this, sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,this->name))
            {
                cout<<"\n\t\tYou Search For:\n\t";
                showdata();
                mprice = getprice();
                count++;
            }
            fin.read((char*)this, sizeof(*this));
        }
    }
    if(count == 0)
        cout<<"\n\t\tMovie Not Available";
    getch();
}
char dte[25];
void book::setbooking()
{
    movie m;
    cout<<"\n\t\tEnter The Movie Name You Want To Book: ";
    cin.ignore();
    cin.getline(mname,29);
    m.searchdata(mname);
    if(count!=0)
    {
        cout<<"\n\t\tEnter The Customer Name: ";
        cin.getline(pname, 29);
        cout<<"\t\tEnter The Customer Mobile Number: ";
        cin.getline(mobile, 11);
        cout<<"\t\tEnter The Desired Movie Time: ";
        cin>>btime;
        cout<<"\t\tEnter The No. Of Ticket: ";
        cin>>qty;
        bprice = mprice*qty;
         time_t now = time(0);
        // convert now to string form
        char* dt = ctime(&now);
        strcpy(dte,dt);
    }
}

void book::showbooking()
{
    cout<<"\n\t\tCUSTOMER NAME - "<<pname;
    cout<<"\n\t\tMOVIE NAME - "<<mname;
    cout<<"\n\t\tMobile No. - "<<mobile;
    cout<<"\n\t\tMOVIE TIME - "<<btime;
    cout<<"\n\t\tNO. OF TICKET - "<<qty;
    cout<<"\n\t\tTOTAL PRICE - "<<bprice;
    cout<<"\n\t\tBooking date and time  - "<<dte;
    cout<<"\n\t\t---------------------------";
}

int book :: storebooking()
{
    if(mobile==0 && mprice == 0 && qty ==0 &&  bprice == 0)
    {
        cout<<"Data Not Initialize"<<endl;
        getch();
        return 0;
    }
    ofstream fout;
    fout.open("Book.txt", ios::app);
    fout.write((char*)this, sizeof(*this));
    fout.close();
    cout<<"\n\t\tTicket Booked Successfully ! "<<endl;
    cout<<"\tPress any key to continue!!!";
    getch();
    return 0;
}

void book :: viewbooking()
{
    ifstream fin;
    fin.open("Book.txt",ios::in|ios::binary);
    if(!fin)
        cout<<"\n\tFile Not Found\n\n";
    else
    {
        fin.read((char*)this, sizeof(*this));
        while(!fin.eof())
        {
            showbooking();
            cout<<endl;
           fin.read((char*)this, sizeof(*this));
        }
        fin.close();
    }
    cout<<"\tPress any key to continue!!!";
    getch();
}

void login()
{
    char id[15], pass[8],p;
    int i;
    system("cls");
    cout<<"\n\n\t\t---------------------------------";
    cout<<"\n\t       |  MOVIE TICKET BOOKING SYSTEM    |\n";
    cout<<"\t\t---------------------------------\n";
    cout<<"\nPlease Login to continue...";
    cout<<"\n\n\tUsername : ";
    cin>>id;
    cout<<"\n\tPassword : ";
    cin>>pass;

    if(strcmp(id,"harshit")==0 && strcmp(pass,"harshit")==0)
    {
        cout<<"\n\t\tWelcome To MOVIE TICKET BOOKING SYSTEM !!! \n\tPress any key to continue...";
        getch();
    }
    else
    {
        cout<<"\n\t\tID or Password Incorrect!!! Please try again...";
        getch();
        login();
    }
}

int menu()
{
        int choice;
        cout<<"\n\n\t\t---------------------------------";
        cout<<"\n\t       |  MOVIE TICKET BOOKING SYSTEM    |\n";
        cout<<"\t\t---------------------------------\n";

        cout<<"\n\t1. Insert Movie, Timing and Price "<<endl;
        cout<<"\t2. Edit Movie, Timing and Price "<<endl;
        cout<<"\t3. Delete Movie, Timing and Price "<<endl;
        cout<<"\t4. View All Movies "<<endl;
        cout<<"\t5. Book Ticket "<<endl;
        cout<<"\t6. View All Bookings "<<endl;
        cout<<"\t7. Exit From Application "<<endl;
        cout<<"\tEnter Your Choice: ";
        scanf("%d",&choice);
        return choice;
}

int main()
{
    char name[30], c;
    movie m1;
    book b1;
    login();
    while (1)
    {
        system("cls");
        time_t now = time(0);
        // convert now to string form
        char* dt = ctime(&now);
        cout<<"\n\n\t\t"<<dt;
        switch (menu())
        {

        case 1:
            m1.setdata();
            m1.showdata();
            m1.storedata();
            break;
        case 2:
            cout<<"\n\t\t"<<"id)  "<<"Movie Name"<<"\t\t\t"<<"Movie Time"<<"\t\t\t"<<"price"<<" (Rs)"<<endl;
            cout<<"\t\t--------------------------------------------------------------------------\n";
            m1.viewdata();
            cout<<"\n\t Enter The Movie Name To Update: ";
            cin.ignore();
            cin.getline(name,29);
            m1.updatedata(name);
            break;
        case 3:
           cout<<"\n\t\t"<<"id)  "<<"Movie Name"<<"\t\t\t"<<"Movie Time"<<"\t\t\t"<<"price"<<" (Rs)"<<endl;
            cout<<"\t\t--------------------------------------------------------------------------\n";
            m1.viewdata();
            cout<<"\n\t Enter The Movie Name To Delete: ";
            cin.ignore();
            cin.getline(name,29);
            m1.deletedata(name);
            break;
        case 4:
            cout<<"\n\t\t"<<"id)  "<<"Movie Name"<<"\t\t\t"<<"Movie Time"<<"\t\t\t"<<"price"<<" (Rs)"<<endl;
            cout<<"\t\t--------------------------------------------------------------------------\n";
            m1.viewdata();
            break;
        case 5:
            cout<<"\n\t\tThe Movies Available are:"<<endl;
            cout<<"\n\t\t"<<"id)  "<<"Movie Name"<<"\t\t\t"<<"Movie Time"<<"\t\t\t"<<"price"<<" (Rs)"<<endl;
            cout<<"\t\t--------------------------------------------------------------------------\n";
            m1.viewdata();
            b1.setbooking();
            if(count!=0)
            {
                cout<<"\n\t\tAre You Sure You Want To Book This Ticket (y/n): ";
                cin>>c;
                if(c=='y' || c=='Y')
                {
                    cout<<"\n\t\tBOOKING CONFIRM \n\t\tTHANK YOY FOR BOOKING \n\t\tHAVE A GOOD DAY.\n";
                    b1.showbooking();
                    b1.storebooking();
                }
            }
            break;
        case 6:
            b1.viewbooking();
            break;
        case 7:
            cout<<"\n\t\tThank You For Using This Application!!\n";
            exit(0);

        default:
            cout<<"\nInvalid Choice!!";
            getch();
            break;
        }
    }
    return 0;
}
