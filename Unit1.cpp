//---------------------------------------------------------------------------
#include <windows.h>
#include "Registry.hpp"
#include <vcl.h>
#pragma hdrstop
#include <iostream>
#include <string>
using namespace std;

//---------------------------------------------------------------------------
//http://www.cyberforum.ru/cpp-builder/thread159991.html
//http://citforum.ru/operating_systems/windows/registry_c/
#pragma argsused
int main(int argc, char* argv[])
{
string S;
string S2;
AnsiString Str;
AnsiString Str2;
string param;
char symb;
int pos=0;
TRegistry *reg=new TRegistry();
HKEY h ;
PBYTE pbBuff;
DWORD cBuff=0;
DWORD Type=0;

cout<<"Please, enter the file path"<<endl;
cin>>S;
//S="?????????\\HKEY_CURRENT_USER\\Console\\Git Bash"  ;
pos=S.find('\\',0);
S=S.erase(0,pos+1);
pos=S.find('\\',0);
S2=S.substr(0,pos);
symb=S2[S2.length()-1];
S=S.erase(0,pos+1);
pos=S.find('\\',0);

switch(symb){
 case 'T': {h=HKEY_CLASSES_ROOT; break;}
 case 'R': {h=HKEY_CURRENT_USER; break;}
 case 'E': {h=HKEY_LOCAL_MACHINE; break;}
 case 'S': {h=HKEY_USERS; break;}
 case 'G': {h=HKEY_CURRENT_CONFIG; break;}
}

while (pos!=-1)
{
 pos=S.find('\\',0);
 S2=S.substr(0,pos);
 if (RegOpenKeyEx(h,S2.c_str(),0,KEY_QUERY_VALUE,&h)==ERROR_SUCCESS)cout<<'s';
 S=S.erase(0,pos+1);
 pos=S.find('\\',0);
}
cout<<"Input the parameter"<<endl;
cin>>param;

if(RegOpenKeyEx(h,S.c_str(),0,KEY_QUERY_VALUE,&h)==ERROR_SUCCESS)
{
	if(RegQueryValueEx(h,param.c_str(),NULL,NULL,NULL,
&cBuff)==ERROR_SUCCESS)
	{
		if(cBuff>1)
		{
			if((pbBuff=new BYTE [cBuff])==NULL) abort();
			RegQueryValueEx(h,param.c_str(),NULL,&Type,pbBuff,&cBuff);
			register int i;
			PBYTE tmpBuff;
			if((tmpBuff=new  BYTE [cBuff])==NULL) abort();
			switch(Type)
			{
			case(REG_SZ):
				cout<<"Type of REG_SZ, data: "<<pbBuff;
				break;
			case(REG_MULTI_SZ):
				cout<<"Type of REG_MULTI_SZ, data:\n\t";
				for(i=0;i<cBuff-1;i++)
					pbBuff[i] ? cout<<pbBuff[i] : cout<<'\n'<<'\t';
				break;
			case(REG_EXPAND_SZ):
				cout<<"Type of REG_EXPAND_SZ, data: "<<pbBuff<<endl;
				if(ExpandEnvironmentStrings((PCHAR)pbBuff,
(PCHAR)tmpBuff,cBuff)!=0) cout<<tmpBuff;
				break;
                        case(REG_DWORD):
                                cout<<"Type of REG_DWORD, data: "<<pbBuff<<endl;
				if(ExpandEnvironmentStrings((PCHAR)pbBuff,
(PCHAR)tmpBuff,cBuff)!=0) cout<<tmpBuff;
				break;
			}
				
		}
		else {cout<<"Value is empty"<<endl;
                }
	}
	else {
        S="";
        S2="";
        reg->RootKey=h;

        cout<<"Imput name of Key";
        cin>>S;
        Str=S.c_str();
        reg->OpenKey(Str,true);

        cout<<"Imput name of parametre";
        cin>>S;
        Str=S.c_str();

        cout<<"Imput name of value";
        cin>>S2;
        Str2=S2.c_str();

        reg->WriteString(Str,Str2);
        reg->CloseKey();
        delete reg;
        }
}
else cout<<"Error in open"<<endl;
system("pause");

        return 0;
}
//---------------------------------------------------------------------------
