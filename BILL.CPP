#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<iomanip.h>
//function declaration.................................
int getNewFcode();
void Food_addrecord();
void Food_search();
void Food_modify();
void Food_delete();
void Food_report();
void Foodmenu();
void Password();
long getNewbillno();
int Find(int code, char nm[], int &pr);
void Bill_create();
void Bill_report();
void Billmenu();


class Food
{
		int Fcode;
		char Fname[30];
		char Ftype[30];
		int Price;
		int Qty;
	public:
		Food();
		void Fenter();
		void Fdisplay();
		void Fupdate();
		void Fshow();
		void setFcode(int n)
		{
			Fcode = n;
		}

		int getFcode()
		{
			return Fcode;
		}

		char* getFname()
		{
			return Fname;
		}
		char* getFtype()
		{
			return Ftype;
		}
		int getPrice()
		{
			return Price;
		}
};

Food :: Food()
{
	Fcode = 0;
	strcpy(Fname, "None");
	strcpy(Ftype, "None");
	Price = 0;
	Qty = 0;
}

void Food:: Fenter()
{
	cout<<"\n\t    Food Entry Details   ";
	cout<<"\n\t-------------------------";
	cout<<"\n\t Food Code \t: "<<Fcode;
	cout<<"\n\t Food Name \t: ";
	gets(Fname);
	cout<<"\t Food Type \t: ";
	gets(Ftype);
	cout<<"\t Price \t\t: ";
	cin>>Price;
	cout<<"\t Quantity \t: ";
	cin>>Qty;
}

void Food:: Fdisplay()
{
	cout<<"\n\t       Food Details      ";
	cout<<"\n\t-------------------------";
	cout<<"\n\t Food Code \t: "<<Fcode;
	cout<<"\n\t Food Name \t: "<<Fname;
	cout<<"\n\t Food Type \t: "<<Ftype;
	cout<<"\n\t Price \t\t: "<<Price;
	cout<<"\n\t Quantity \t: "<<Qty;
}

void Food:: Fupdate()
{
	cout<<"\n\t   Food Entry Details    ";
	cout<<"\n\t-------------------------";
	cout<<"\n\t Food Code \t: "<<Fcode;
	cout<<"\n\t Food Name \t: "<<Fname;
	cout<<"\n\t Food Type \t: "<<Ftype;
	cout<<"\n\t Price \t\t: ";
	cin>>Price;
	cout<<"\t Quantity \t: ";
	cin>>Qty;
}

void Food::Fshow()
{
	cout<<"\n"<<setw(8)<<Fcode<<setw(25)<<Fname<<setw(20)<<Ftype
		<<setw(10)<<Price<<setw(10)<<Qty;
}

int getNewFcode()
{
	int code;
	fstream F("Food.dat",ios::in|ios::binary);
	Food obj;

	F.seekg(0,ios::end);


	if(F.tellg() > 0)
	{

		F.seekg(F.tellg() - sizeof(obj));


		F.read((char*)&obj, sizeof(obj));

		code = obj.getFcode() + 1;
	}
	else
	{

		code = 101;
	}
	F.close();
	return code;
}


void Food_addrecord()
{
	Food s;
	fstream F;
	F.open("Food.dat",ios::app|ios::binary);
	int code = getNewFcode();
	s.setFcode(code);
	s.Fenter();
	F.write((char*)&s, sizeof(s));
	F.close();
}


void Food_search()
{
	Food s;
	fstream f;
	f.open("Food.dat",ios::in|ios::binary);
	char name[30];
	int found=0;
	cout<<"\n\t Enter Food name to be searched : ";
	gets(name);
	while(f.read((char*)&s, sizeof(s)))
	{
		if(strcmpi(name, s.getFname())==0)
		{
			s.Fdisplay();
			found=1;
		}
	}
	f.close();
	if(found==0)
		cout<<"\n\t Record Not Found !!!! ";
}

void Food_modify()
{
	fstream F;
	Food s;
	int code, found=0;
	F.open("Food.dat",ios::in|ios::out|ios::binary);
	cout<<"\n\t Enter Food Code : ";
	cin>>code;
	while(F.read((char*)&s, sizeof(s)) && (!found))
	{
		if(code == s.getFcode())
		{
			s.Fdisplay();
			found=1;
			s.Fupdate();
			F.seekp(F.tellg() - sizeof(s));
			F.write((char*)&s,sizeof(s));
		}
	}
	F.close();
	if(found==0)
		cout<<"\n\t Record Not Found !!!! ";
}

void Food_delete()
{
	fstream F1,F2;
	Food s;
	int code, found=0;
	char ans;
	F1.open("Food.dat",ios::in|ios::binary);
	F2.open("Temp.dat",ios::out|ios::binary);
	cout<<"\n\t Enter Food Code : ";
	cin>>code;
	while(F1.read((char*)&s, sizeof(s)))
	{
		if(code != s.getFcode())
			F2.write((char*)&s, sizeof(s));
		else
		{
			found=1;
			s.Fdisplay();
			cout<<"\n\t Are you sure you want to delete this record (y/n) ? ";
			cin>>ans;
			if(ans=='n')
				F2.write((char*)&s, sizeof(s));
			else
				cout<<"\n\t Record Deleted Successfully ";
		}
	}
	F1.close();
	F2.close();

	F1.open("Temp.dat",ios::in|ios::binary);
	F2.open("Food.dat",ios::out|ios::binary);
	while(F1.read((char*)&s,sizeof(s)))
	{
		F2.write((char*)&s,sizeof(s));
	}
	F1.close();
	F2.close();

	if(found==0)
		cout<<"\n\t Record Not Found !!!! ";
}

void Food_report()
{
	fstream F;
	Food s;
	F.open("Food.dat",ios::in|ios::binary);
	cout<<"\n---------------------------------------------"
		<<"---------------------------------";
	cout<<"\n"<<setw(8)<<"Code"<<setw(25)<<"Food Name"<<setw(20)<<"Type"
		<<setw(10)<<"Price"<<setw(10)<<"Qty";
		cout<<"\n---------------------------------------------"
		<<"---------------------------------";
	while(F.read((char*)&s,sizeof(s)))
	{
		s.Fshow();
	}
	cout<<"\n---------------------------------------------"
		<<"---------------------------------";

	F.close();
}

void Foodmenu()
{
	int ch;
	do
	{
		clrscr();
		cout<<"\n\t Food Menu ";
		cout<<"\n\t-----------";
		cout<<"\n\t 1. Add a new dish record to the menu ";
		cout<<"\n\t 2. Search an existing dish's record ";
		cout<<"\n\t 3. Modify a dish's record ";
		cout<<"\n\t 4. Delete a dish's record ";
		cout<<"\n\t 5. See the menu ";
		cout<<"\n\t 6. Exit ";
		cout<<"\n\t Enter Choice [1-6] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: Food_addrecord(); break;
			case 2: Food_search(); break;
			case 3: Food_modify(); break;
			case 4: Food_delete(); break;
			case 5: Food_report(); break;
			case 6: cout<<"\n\t Exit .."; break;
			default:cout<<"\n\t Invalid Choice ";
		}
		getch();
	}while(ch != 6);
}

void Password()
{
	char pass[10];
	apass:
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t     Enter Password : ";
	cin>>pass;
	if(strcmp(pass,"admin")==0)
	{
		cout<<"\n\t\t\t     Login Successful.";
		getch();
		Foodmenu();
	}
	else
	{
		cout<<"\n\t Login Fail ..... Password is wrong. ";
		goto apass;


	}
}


class Billing
{
		long billno;
		char cname[30];
		char mobile[15];
		int fcode[10];
		char fname[10][30];
		int price[10];
		int qty[10];
		int index;
		long total;
	public:
		Billing();
		void Benter();
		void Bdisplay();
		void Bshow();
		long getbillno()
		{
			return billno;
		}
		void setbillno(long n)
		{
			billno = n;
		}
		char* getcname()
		{
			return cname;
		}
		void Update(int code, char fn[], int q, int pr, int i)
		{
			index=i;
			fcode[i] = code;
			strcpy(fname[i], fn);
			qty[i] = q;
			price[i] = pr;
			total += q*pr;
		}
}

Billing::Billing()
{
	billno = 0;
	strcpy(cname,"None");
	strcpy(mobile,"None");
	for(int i=0; i<10; i++)
	{
		fcode[i] = 0;
		strcpy(fname[i],NULL);
		price[i] = 0;
		qty[i]=0;
	}
	index=-1;
	total=0;
}

void Billing::Benter()
{
	cout<<"\n\t Billing Details Entry Form ";
	cout<<"\n\t****************************";
	cout<<"\n\t Bill No \t: "<<billno;
	cout<<"\n\t Name \t\t: ";
	gets(cname);
	cout<<"\t Mobile No. \t: ";
	gets(mobile);
}

void Billing::Bdisplay()
{
	cout<<"\n\t Bill Receipt ";
	cout<<"\n\t**************";
	cout<<"\n\t Bill No \t: "<<billno;
	cout<<"\n\t Name \t\t: "<<cname;
	cout<<"\n\t Mobile No. \t: "<<mobile;
		cout<<"\n---------------------------------------------"
		<<"---------------------------------";
	cout<<"\n"<<setw(10)<<"Code"<<setw(20)<<"Food Name"<<setw(10)
		 <<"Price"<<setw(10)<<"Quantity"<<setw(10)<<"Total";
		cout<<"\n---------------------------------------------"
		<<"---------------------------------";

	for(int i=0; i<=index; i++)
	{
		cout<<"\n"<<setw(10)<<fcode[i]<<setw(20)<<fname[i]
			<<setw(10)<<price[i]<<setw(10)<<qty[i]
			<<setw(10)<<price[i]*qty[i];
	}
	cout<<endl<<"\n Total Amount is Rs."<<total;
}

void Billing::Bshow()
{

	cout<<"\n"<<setw(10)<<billno<<setw(25)<<cname
		<<setw(15)<<mobile<<setw(10)<<total;
}

long getNewbillno()
{
	fstream F;
	Billing B;
	long bno;
	F.open("Bill_rest.dat",ios::in|ios::binary);
	F.seekg(0,ios::end);
	if(F.tellg() > 0)
	{
		F.seekg(F.tellg() - sizeof(B));
		F.read((char*)&B, sizeof(B));
		bno = B.getbillno() + 1;
	}
	else
	{
		bno = 1;
	}
	F.close();
	return bno;
}

int Find(int code, char nm[], int &pr)
{
	fstream F("food.dat",ios::in|ios::binary);
	Food s;
	int found=0;
	while(F.read((char*)&s, sizeof(s)))
	{
		if(code == s.getFcode())
		{
			found=1;
			strcpy(nm, s.getFname());
			pr = s.getPrice();
			break;
		}
	}
	F.close();
	return found;
}

void Bill_create()
{
	Billing B;
	fstream F;
	F.open("Bill_rest.dat",ios::app|ios::binary);
	long no = getNewbillno();
	B.setbillno(no);
	B.Benter();
	Food_report();
	int i=0, n,qty,status,price,code;
	char fname[30];
	cout<<"\n\t How Many Food Items Do You Want?[Max.10] : ";
	cin>>n;
	if(n>10)
		n=10;
	do
	{
		cout<<"\n Enter Food Code : ";
		cin>>code;
		status = Find(code,fname,price);
		if(status==1)
		{
			cout<<"\n\t Food Name : "<<fname;
			cout<<"\n\t Price is  : "<<price;
			cout<<"\n\t Enter Quantity : ";
			cin>>qty;
			B.Update(code, fname, qty, price,i);
			i++;
		}
		else
		{
			cout<<"\n\t Wrong Food Code !! Please Re-Enter ";
		}
	}while(i<n);
	B.Bdisplay();
	F.write((char*)&B,sizeof(B));
	F.close();
}

void Bill_report()
{
	fstream F("Bill_rest.dat",ios::in|ios::binary);
	Billing B;
	cout<<"\n--------------------------------------"
		<<"---------------------------------------";
	cout<<"\n"<<setw(10)<<"Bill no" <<setw(25)<<"Customer Name"
		<<setw(15)<<"Mobile No"<<setw(10)<<"Total";
	cout<<"\n--------------------------------------"
		<<"---------------------------------------";
	while(F.read((char*)&B, sizeof(B)))
	{
		B.Bshow();
	}
	cout<<"\n--------------------------------------"
		<<"---------------------------------------";
	F.close();
}

void Billmenu()
{
	int ch;
	do
	{
		clrscr();
		cout<<"\n\t Billing Menu ";
		cout<<"\n\t--------------";
		cout<<"\n\t 1. order food items. ";
		cout<<"\n\t 2. See a report of today's billings ";
		cout<<"\n\t 3. Exit ";
		cout<<"\n\t Enter Choice [1-3] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: Bill_create(); break;
			case 2: Bill_report(); break;
			case 3: cout<<"\n\t Exit ..."; break;
			default:cout<<"\n\t Invalid Choice !!!! "; break;
		}
		getch();
	}while(ch!=3);
}


void main()
{
	textbackground(WHITE);
	textcolor(BLACK);
	int ch;
	do
	{
		clrscr();
		cout<<"\n\t       ******************** ROYAL VEGA ******************** ";
		cout<<"\n\n\t\t\t      Welcome to Royal Vega  ";
		cout<<"\n\t------------------------------------------------------------------";
		cout<<"\n\n\t 1. Staff login ";
		cout<<"\n\t 2. Order Food";
		cout<<"\n\t 3. Exit ";
		cout<<"\n\n\t Enter Choice [1-3] : ";
		cin>>ch;
		switch(ch)
		{
			case 1: Password(); break;
			case 2: Billmenu(); break;
			case 3: cout<<"\n\t Exit ..."; break;
			default: cout<<"\n\t Invalid Choice !!!! "; break;
		}
		getch();
	}while(ch!=3);
}

