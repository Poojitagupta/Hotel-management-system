#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>
using namespace std;
//MARK:- Interface Functions Here =>
# define total_rooms 100
void intro() {
	cout<<"C++ Project On Hotel Management System";
}

void head() {
	system("cls");
	cout<<"XYZ Group of Hotels";
}

//MARK:- Hotel Class Here =>

class hotel {
	private:
			int room_no;
			char name[30];
			char address[50];
			char phone[15];
			int days;
			float fare;
	public:
			void main_menu();		//to display the main menu
			void add();				//to book a room
			void display(); 		//to display the customer record
			void rooms();			//to display allotted rooms
			void edit();			//to edit the customer record
			int check(int);	     	//to check room status
			void modify(int);		//to modify the record
			void delete_rec(int);   //to delete the record
};

void hotel::main_menu() {
	int choice;
	while(choice!=5) {
	    system("cls");
		head();
		cout<<"\nMAIN MENU ";
		cout<<"\n1.Book A Room";
		cout<<"\n2.Customer Record";
		cout<<"\n3.Rooms Allotted";
		cout<<"\n4.Edit Record";
		cout<<"\n5.Exit";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		switch(choice) {
			case 1:	add();
					break;
			case 2: display();
					break;
			case 3: rooms();
					break;
			case 4:	edit();
					break;
			case 5: break;
			default: {
				cout<<"\nWrong choice.....!!!";
				cout<<"\nPress any key to continue....!!";
				getch();
			}
		}
	}
}

void hotel::add() {
	system("cls");
	head();
	int r,flag;
	ofstream fout("Record.txt",ios::app);
	cout<<"\nAvailable rooms:";
	cout<<"\n";
	for(int i=1;i<=total_rooms;i++){
		if(!check(i)){
			cout<<i<<", ";
		}
	}
	cout<<"\n";
	cout<<"\n Enter Customer Details";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	
	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else {
		room_no=r;
		cout<<" Name: ";
		cin>>name;
        cin.ignore();
		cout<<" Address: ";
		cin>>address;
        cin.ignore();
		cout<<" Phone No: ";
		cin>>phone;
        cin.ignore();
		cout<<" No of Days to Checkout: ";
		cin>>days;
		fare=days*900;						//900 is currently set as the
											//default price per day
		fout.write((char*)this,sizeof(hotel));
		cout<<"\n Room is booked...!!!";
	}

	cout<<"\n Press any key to continue.....!!";
	getch();
	fout.close();
}

void hotel::display() {
	system("cls");
	head();
	ifstream fin("Record.dat",ios::in);
	int r;
	cout<<"\nOccupied rooms:";
	cout<<"\n";
	for(int i=1;i<=total_rooms;i++){
		if(check(i)){
			cout<<i<<", ";
		}
	}
	cout<<"\n";
	cout<<"\n Enter room no: ";
	cin>>r;
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
	    system("cls");
			head();
			cout<<"\n Customer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			cout<<"\n Days: "<<days;
			cout<<"\n Total Fare: "<<fare;
		}
	}
	cout<<"\n\n Press any key to continue....!!";
	getch();
	fin.close();
}

void hotel::rooms() {
	system("cls");
	head();
	ifstream fin("Record.dat",ios::in);
	cout<<"\nList Of Rooms Allotted";
	cout<<"\n----------------------";
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		cout<<"\n Room no: "<<room_no<<"\n Name: "<<name;
		cout<<"\n Address: "<<address<<"\n Phone: "<<phone;
		cout<<"\n Days: "<<days<<"\n Total: "<<fare;
		cout<<"\n**********************************";
	}
	cout<<"\nPress any key to continue.....!!";
	getch();
	fin.close();
}

void hotel::edit() {
	system("cls");
	head();
	int choice,r;
	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;

	system("cls");
	head();
	cout<<"\n Enter room no: " ;
	cin>>r;
	switch(choice) {
		case 1:	modify(r);
				break;
		case 2:	delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}


int hotel::check(int r) {
	int flag=0;
	ifstream fin("Record.dat",ios::in);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			flag=1;
			break;
		}
	}

	fin.close();
	return(flag);
}

void hotel::modify(int r) {
	system("cls");
	head();
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);
	while(!file.eof()) {
		pos=file.tellg();
		file.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n Name: ";
			cin>>name;
            cin.ignore();
			cout<<" Address: ";
			cin>>address;
            cin.ignore();
			cout<<" Phone no: ";
			cin>>phone;
            cin.ignore();
			cout<<" Days: ";
			cin>>days;
			fare=days*900;
			file.seekg(pos);
			file.write((char*)this,sizeof(hotel));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
}

void hotel::delete_rec(int r) {
	system("cls");
	head();
	int flag=0;
	char ch;
	ifstream fin("Record.dat",ios::in);
	ofstream fout("temp.dat",ios::out);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone No: "<<phone;
			cout<<"\n Days: "<<days;
			cout<<"\n Total Fare: "<<fare;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;
			if(ch=='n')
				fout.write((char*)this,sizeof(hotel));
			flag=1;
			break;
		}
		else
			fout.write((char*)this,sizeof(hotel));
	}

	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else {
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
}

//MARK:- Main() Function Here =>

int main() {
	hotel h;
	system("cls");
	intro();
	cout<<"\nPress any key to continue....!!";

	getch();
	system("cls");
	head();
	char id[5],pass[7];
	cout<<"\nusername => ";
	cin>>id;
	cout<<"\npassword => ";
	cin>>pass;
	cout<<"\n\n\t";
	cout<<"\t";
	if(strcmp(id,"admin")==0&&strcmp(pass,"******")==0)
		cout<<"\n!!!Login Successfull!!!";
	else {
		cout<<"\n!!!INVALID CREDENTIALS!!!";
		getch();
		exit(-1);
	}
	system("cls");
	h.main_menu();
	getch();
	
	return 0;
} 
