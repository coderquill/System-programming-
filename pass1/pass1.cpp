#include<bits/stdc++.h>
using namespace std;
typedef struct mot				//structure for MOT
{
	char mne[10];
	char type[10];
	int opcode;
	int length;
}mot;
mot temp;
int LC;
mot m[13]=
{
	{"STOP","IS",00,1},
	{"ADD","IS",01,1},
	{"SUB","IS",02,1},
	{"MULT","IS",03,1},
	{"MOVER","IS",04,1},
	{"MOVE","IS",05,1},
	{"BC","IS",9,1},
	{"READ","IS",11,1}
};
typedef struct REG					//structure for Reg
{
	char reg[5];
	char type[3];
	int opcode;
}REG;
REG temp1;
REG R[5]=
{
	{"AREG","R",00},
	{"BREG","R",01},
	{"CREG","R",02},
	{"DREG","R",03}
};
typedef struct CC				//structure for Condition code
{
	char cc[5];
	char type[3];
	int opcode;
}CC;
CC temp2;
CC C[7]=
{
	{"LT","CC",00},
	{"GT","CC",01},
	{"LE","CC",02},
	{"GE","CC",03},
	{"NE","CC",04},
	{"EQ","CC",05}
};
struct SYM_TAB					//structure for symbol table
{
	char symbol[20];
	int address;
};
struct LIT_TAB					//structure for literal table
{
	char literal[20];
	int address;
};
 struct IC						//structure for intermediate code table
{
	int L_C;
	char m_type[4];
	int m_code;
	char type_of_ope_1[4];
	int add_of_op_1;
	char type_of_ope_2[4];
	int add_of_op_2;
};	
struct pool_tab
{
	int pool_p;
};
int search_mot(char str1[10])			//searching in MOT
{
	int i;
	for(i=0;i<12;i++)
	{
		if(strcmp(m[i].mne,str1)==0)
		{
			strcpy(temp.mne,m[i].mne);
			strcpy(temp.type,m[i].type);
			temp.opcode=m[i].opcode;
			temp.length=m[i].length;
			return 1;
		}
	}
	return 0;
}

int search_reg(char str1[10])						//searching for REG
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcmp(R[i].reg,str1)==0)
		{
			strcpy(temp1.reg,R[i].reg);
			strcpy(temp1.type,R[i].type);
			temp1.opcode=R[i].opcode;
			return 1;
		}
	}
	return 0;
}
int search_cc(char str1[10])						//searching for Condition code
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcmp(C[i].cc,str1)==0)
		{
			strcpy(temp2.cc,C[i].cc);
			strcpy(temp2.type,C[i].type);
			temp2.opcode=C[i].opcode;
			return 1;
		}
	}
	return 0;
}	

int main()
{
	
	char s1[6]="\0",s2[6]="\0",s3[6]="\0",s4[6]="\0";
	struct SYM_TAB st[20];
	struct LIT_TAB lt[20];
	struct IC ic[30];
	struct pool_tab p[5];
	ofstream pass1;							//for output
	int stp=0,ltp=0,icp=0,ptp=0,k,j,count=0,flagl=0;;
	
	FILE *fp;
	char str[100],fname[100];
	cout<<"\nEnter file name::"<<endl;					//filename input
	cin>>fname;
	fp=fopen(fname,"r");
	
	for(int i=0;i<10;i++)						//initialize literal table
	{
		lt[i].address=-1;
	}
	for(int i=0;i<10;i++)						//initialize symbol table
	{
		st[i].address=-1;
	}
	while(fgets(str,100,fp))
	{
		
		sscanf(str,"%s %s %s %s",s1,s2,s3,s4);			//Tokanizing
		if(strcmp(s2,"START")==0)
		{
			if(strcmp(s3,"-")!=0)
			{
				LC=atoi(s3);				//stored in LC
			}
			strcpy(ic[icp].m_type,"AD");
			ic[icp].m_code=00;
			strcpy(ic[icp].type_of_ope_1,"-");
			ic[icp].add_of_op_1=0;
			strcpy(ic[icp].type_of_ope_2,"C");
			ic[icp].add_of_op_2=LC;
			ic[icp].L_C=0;
			icp++;
		}
		if(strcmp(s2,"ORIGIN")==0)				//handle ORIGIN
		{
			//cout<<"hi";
			if(strcmp(s3,"-")!=0)
			{
				LC=atoi(s3);				//stored in LC
			}
			strcpy(ic[icp].m_type,"AD");
			ic[icp].m_code=04;
			strcpy(ic[icp].type_of_ope_1,"-");
			ic[icp].add_of_op_1=0;
			strcpy(ic[icp].type_of_ope_2,"C");
			ic[icp].add_of_op_2=LC;
			ic[icp].L_C=0;
			icp++;
		}
		
		else if(search_mot(s2)==1)
		{
			strcpy(ic[icp].m_type,temp.type);		//menimonic copy to IC
			ic[icp].m_code=temp.opcode;
			//cout<<s2;
			if(s1[0]!='-')					//lable copyied to symtab
			{
				strcpy(st[stp].symbol,s1);
				st[stp].address=LC;
				stp++;
			}
			if(search_reg(s3)==1)				//operand 1 check is REG
			{	
				strcpy(ic[icp].type_of_ope_1,temp1.type);
				ic[icp].add_of_op_1=temp1.opcode;
			}
			else if(search_cc(s3)==1)			//operand 1 check is condition code
			{	
				strcpy(ic[icp].type_of_ope_1,temp2.type);
				ic[icp].add_of_op_1=temp2.opcode;
			}
			else
			{
				strcpy(ic[icp].type_of_ope_1,"-");
				ic[icp].add_of_op_1=0;
			}
			if(strcmp(s4,"-")!=0)
			{
				if(s4[0]=='=')					//operand 2 is literal
				{
					if(ltp==0)					
					{
						strcpy(lt[ltp].literal,s4);		//copy literal
						lt[ltp].address=-1;
						strcpy(ic[icp].type_of_ope_2,"L");
						ic[icp].add_of_op_2=ltp;
						ltp++;
					}
					else if(ltp!=	0)					//checking repeatation
					{
						int A=ltp, flag=0;
						
						for(int i=0;i<A;i++)
						{
							if(strcmp(lt[i].literal,s4)==0 )
							{
								//cout<<"hi";
								strcpy(ic[icp].type_of_ope_2,"L");
								ic[icp].add_of_op_2=i;
								flag=1;
								break;
							}
						}
						if(flag==0 || flagl==1)
						{
							strcpy(lt[ltp].literal,s4);		//copy literal
							lt[ltp].address=-1;
							strcpy(ic[icp].type_of_ope_2,"L");
							ic[icp].add_of_op_2=ltp;
							p[ptp].pool_p=ltp;
							ltp++;	
							//ptp++;
						}
							
					}
									
				}
				else if(s4[0]!='=')					//copy this symbol
				{
					if(stp==0)					
					{
						strcpy(st[stp].symbol,s4);		//copy symbol
						st[stp].address=-1;
						strcpy(ic[icp].type_of_ope_2,"S");
						ic[icp].add_of_op_2=stp;
						stp++;
					}
					else if(stp!=0)					//checking repeatation
					{
						int A=stp,flag=0;
						for(int i=0;i<A;i++)
						{
							if(strcmp(st[i].symbol,s4)==0)
							{
								//cout<<"hi";
								strcpy(ic[icp].type_of_ope_2,"S");
								ic[icp].add_of_op_2=i;
								flag=1;
								break;
							}
						}
						if(flag==0)
						{
							strcpy(st[stp].symbol,s4);		//copy symbol
							st[stp].address=-1;
							strcpy(ic[icp].type_of_ope_2,"S");
							ic[icp].add_of_op_2=stp;
							stp++;	
						}
					}
				}
				
			}
			else
			{
				strcpy(ic[icp].type_of_ope_2,"-");
				ic[icp].add_of_op_2=0;
			}
			ic[icp].L_C=LC;
			icp++;	
			LC=LC+temp.length;					//LC + size of mnemonic
		}
		if(strcmp(s2,"LTORG")==0)					//LTORG handling
		{
			strcpy(ic[icp].m_type,"AD");
			ic[icp].m_code=03;
			//cout<<LC;
			p[ptp].pool_p=0;
			//ptp++;
			flagl=1;
			
			if(ltp!=0)
			{
				for(int i=ptp;i<ltp;i++ && flagl==1)
				{
					lt[i].address=LC;
					strcpy(ic[icp].m_type,"AD");
					ic[icp].m_code=03;
					strcpy(ic[icp].type_of_ope_1,"-");
					ic[icp].add_of_op_1=0;
					strcpy(ic[icp].type_of_ope_2,lt[i].literal);
					ic[icp].add_of_op_2=0;
					ic[icp].L_C=LC;
					icp++;
					LC++;
				}
			}	
			ptp++;
		}
					
		if(strcmp(s2,"END")==0)					//LTORG handling
		{
			strcpy(ic[icp].m_type,"AD");
			ic[icp].m_code=02;
			if(ltp!=0)
			{
				for(int i=ptp+1;i<ltp;i++)
				{
					lt[i].address=LC;
					strcpy(ic[icp].m_type,"AD");
					ic[icp].m_code=02;
					strcpy(ic[icp].type_of_ope_1,"-");
					ic[icp].add_of_op_1=0;
					strcpy(ic[icp].type_of_ope_2,lt[i].literal);
					ic[icp].add_of_op_2=0;
					ic[icp].L_C=LC;
					icp++;
				}
			}	
		}
		
		if(strcmp(s2,"DC")==0)						//process DC forward references
		{
			int A=stp;
			for(int i=0;i<A;i++)
			{
				if(strcmp(st[i].symbol,s1)==0)
				{
					st[i].address=LC;
				}
			}
			strcpy(ic[icp].m_type,"DL");
			ic[icp].m_code=0;
			strcpy(ic[icp].type_of_ope_1,"-");
			ic[icp].add_of_op_1=0;
			strcpy(ic[icp].type_of_ope_2,"C");
			ic[icp].add_of_op_2=atoi(s3);
			ic[icp].L_C=LC;
			icp++;
			LC++;
		}
		if(strcmp(s2,"DS")==0)
		{
			int A=stp;
			for(int i=0;i<A;i++)
			{
				if(strcmp(st[i].symbol,s1)==0)
				{
					st[i].address=LC;
				}
			}
			strcpy(ic[icp].m_type,"DL");
			ic[icp].m_code=1;
			strcpy(ic[icp].type_of_ope_1,"-");
			ic[icp].add_of_op_1=0;
			strcpy(ic[icp].type_of_ope_2,"-");
			ic[icp].add_of_op_2=0;
			ic[icp].L_C=LC;
			icp++;
			LC=LC+atoi(s3);
		}
		if(strcmp(s2,"EQU")==0)
		{
			int eq;
			strcpy(ic[icp].m_type,"AD");
			ic[icp].m_code=05;
			ic[icp].L_C=LC;
			
			for(int i=0;i<stp;i++)
			{
				if(strcmp(st[i].symbol,s3)==0)
				{
					eq=st[i].address;
					strcpy(ic[icp].type_of_ope_1,"S");
					ic[icp].add_of_op_1=i;
					
				}
			}
			if(s1[0]!='-')					//lable copyied to symtab
			{
				strcpy(st[stp].symbol,s1);
				st[stp].address=LC+eq;
				stp++;
			}
			strcpy(ic[icp].type_of_ope_2,"-");
			ic[icp].add_of_op_2=0;
			icp++;
			LC++;
		}				
		count++;
		//cout<<count;
	}
	cout<<"\nSymbol table is :";
	cout<<"\nINDEX\t\tSYMBOL\t\tADDRESS";
	cout<<"\n--------------------------------------------------\n";
	for(int i=0;i<stp;i++)
	{
		cout<<i<<"\t\t"<<st[i].symbol<<"\t\t"<<st[i].address<<endl;
	}
	cout<<"\nLiteral table is :";
	cout<<"\nINDEX\t\tLITERAL\t\tADDRESS";
	cout<<"\n--------------------------------------------------\n";
	for(int i=0;i<ltp;i++)
	{
		cout<<i<<"\t\t"<<lt[i].literal<<"\t\t"<<lt[i].address<<endl;
	}
	cout<<"\nPool table is :";
	cout<<"\nIndex";
	cout<<"\n--------------------------------------------------\n";
	for(int i=0;i<ptp+1;i++)
	{
		cout<<p[i].pool_p<<endl;
	}
	pass1.open("Intermediate_code.txt");
	pass1<<"\nIntermediate Code table is :";
	pass1<<"\nADDRESS(LC)\t\tMENIMONIC OPCODE\tOPERAND 1\tOPERAND 2";
	pass1<<"\n---------------------------------------------------------------------------------------\n";
	for(int i=0;i<count+1;i++)
	{
		pass1<<ic[i].L_C<<"\t\t\t("<<ic[i].m_type<<" , "<<ic[i].m_code<<")\t\t("<<ic[i].type_of_ope_1<<" , "<<ic[i].add_of_op_1<<")\t\t("<<ic[i].type_of_ope_2<<" , "<<ic[i].add_of_op_2<<")"<<endl;
	}
	return 0;
}
/*
Enter file name::
ass1.txt

Symbol table is :
INDEX		SYMBOL		ADDRESS
--------------------------------------------------
0		N		205
1		AGAIN		102
2		B		206
3		F		305

Literal table is :
INDEX		LITERAL		ADDRESS
--------------------------------------------------
0		='5'		200
1		='1'		201
2		='5'		207

Pool table is :
Index
--------------------------------------------------
0
2



Intermediate Code table is :
ADDRESS(LC)		MENIMONIC OPCODE	OPERAND 1	OPERAND 2
---------------------------------------------------------------------------------------
0			(AD , 0)		(- , 0)		(C , 100)
100			(IS , 11)		(- , 0)		(S , 0)
101			(IS , 4)		(R , 1)		(L , 0)
102			(IS , 3)		(R , 1)		(L , 1)
103			(IS , 4)		(R , 2)		(S , 2)
104			(IS , 9)		(CC , 2)		(S , 1)
0			(AD , 4)		(- , 0)		(C , 200)
200			(AD , 3)		(- , 0)		(='5' , 0)
201			(AD , 3)		(- , 0)		(='1' , 0)
202			(IS , 4)		(R , 1)		(L , 2)
203			(AD , 5)		(S , 1)		(- , 0)
204			(IS , 0)		(- , 0)		(- , 0)
205			(DL , 0)		(- , 0)		(C , 1)
206			(DL , 1)		(- , 0)		(- , 0)
207			(AD , 2)		(- , 0)		(='5' , 0)
*/
