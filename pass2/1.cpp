#include<bits/stdc++.h>
using namespace std;
struct LIT_TAB
{
	char lit[10];
	int address;
};
struct IC
{
	int lc;
	char type_of_mn[5];
	int opcode_of_mn;
	char type_of_op1[5];
	int opcode_of_op1;
	char type_of_op2[5];
	int opcode_of_op2;
};
struct machine_c
{
	int LC;
	int mnemonic_opcode;
	int op1_opcode;
	int address_op2;
};

int main()
{
	struct LIT_TAB lt[10];
	struct machine_c m[20];
	struct IC ic[30];
	int n1,n2,count=0,mtp=0;
	char fname[20],str[100];
	FILE *fp;
	char s1[6]="\0",s2[6]="\0",s3[6]="\0",s4[6]="\0",s5[6]="\0",s6[6]="\0",s7[6]="\0";
	cout<<"\nHow many entries in Literal Table ?";										//literal table input
	cin>>n1;
	for(int i=0;i<n1;i++)
	{
		cout<<"\nEnter literal:";
		cin>>lt[i].lit;
		cout<<"\nEnter the address:";
		cin>>lt[i].address;
		//ltp++;
	}
	cout<<"\nLiteral Table is :"<<endl;
	cout<<"Index\t\tLiteral\t\taddress";
	for(int i=0;i<n1;i++)
	{
		cout<<"\n"<<i<<"\t\t"<<lt[i].lit<<"\t\t"<<lt[i].address;
	}
	cout<<"\nEnter input file name";
	cin>>fname;
	fp=fopen(fname,"r");
	while(fgets(str,100,fp))
	{
		sscanf(str,"%s %s %s %s %s %s %s",s1,s2,s3,s4,s5,s6,s7);
		if(atoi(s1)!=0)								//LC 
		{
			m[mtp].LC=atoi(s1);
		}
		if(strcmp(s2,"AD")==0)			//if there is start ignore
		{
			break;
		}
		if(strcmp(s2,"IS")==0)
		{
			m[mtp].mnemonic_opcode=atoi(s3);
		}
		if(strcmp(s4,"R")==0 || strcmp(s4,"CC")==0) 
		{
			m[mtp].op1_opcode=atoi(s5);
		}
		if(strcmp(s6,"L")==0)			//any literal
		{
			int A=atoi(s7);
			m[mtp].address_op2=lt[A].address;
		}
		mtp++;
	}
	
	/*for(int i=0;i<n2;i++)
	{
		//cout<<"hi";
		if(ic[i].lc!=0)								//LC 
		{
			m[i].LC=ic[i].lc;
		}
		if(strcmp(ic[i].type_of_mn,"AD")==0)			//if there is start ignore
		{
			break;//i=i-1;
		}
		if(strcmp(ic[i].type_of_mn,"IS")==0)		//mnemonic is there
		{
			m[i].mnemonic_opcode=ic[i].opcode_of_mn;
		}
		if(strcmp(ic[i].type_of_op1,"R")==0 || strcmp(ic[i].type_of_op1,"CC")==0 )			//if operand 1
		{
			m[i].op1_opcode=ic[i].opcode_of_op1;
		}
		if(strcmp(ic[i].type_of_op2,"L")==0)			//any literal
		{
			int A=ic[i].opcode_of_op2;
			m[i].address_op2=lt[A].address;				//copy of adrress of literal
		}
		count++;
	}*/
	cout<<"\nMachine code:"<<endl;
	cout<<"\nLC\t\tObject\t\tCode\t\tAddress"<<endl;
	for(int i=0;i<mtp;i++)
	{
		cout<<m[i].LC<<"\t"<<"+"<<m[i].mnemonic_opcode<<"\t"<<m[i].op1_opcode<<"\t"<<m[i].address_op2<<endl;
	}
	return 0;
}
