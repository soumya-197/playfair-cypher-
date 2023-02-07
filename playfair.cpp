#include <iostream>
using namespace std;
#include <string>

string str,key;
char keyT[5][5];
int rowcol[4]; //contains row,col of digraph 

void lowerCase(string x){
    if(x=="k"){
        for(int i=0;i<key.length();i++){
            if(key[i]>64 && key[i]<91){
                key[i]=key[i]+32;
            }
        }
    }
    else{
        for(int i=0;i<str.length();i++){
            if(str[i]>64 && str[i]<91){
                str[i]=str[i]+32;
            }
        }
    }
}

void removeSpace(string x){
   if(x=="k"){
        int count=0;
        for(int i=0;i<key.length();i++){
            if(key[i]==' '){
                key.erase(i,1);
            }
        }
    }
    else{
        int count=0;
        for(int i=0;i<str.length();i++){
            if(str[i]==' '){
                str.erase(i,1);
            }
        }
    } 
}

void addZ(){
    string s="z";
    if(str.length()%2 != 0){
        str.insert(str.length(),s);
    }
}

void addX(){
    string s="x";
    for(int i=0;i<str.length()-1;i++){
        if(str[i]==str[i+1]){
            str.insert(i+1,s);
        }
    }
}

void keyTable(){
    // storing count of alphabet
    int dict[26]={0};
    dict['j'-97]=1; //j is not included in table 
    for(int i=0;i<key.length();i++){
        if(key[i]!='j'){
            dict[key[i]-97]=2;
        }
    }
    int row=0,col=0;
    for(int i=0;i<key.length();i++){
        if(dict[key[i]-97]==2){
            dict[key[i]-97]--;
            keyT[row][col]=key[i];
            col++;
            if(col==5){
                row++;
                col=0;
            }
        }
    }
    for(int i=0;i<26;i++){
        if(dict[i]==0){
            keyT[row][col]=(char)(i+97);
            col++;
            if(col==5){
                row++;
                col=0;
            }
        }
    }
}

void findCell(char a,char b){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(keyT[i][j]==a){
                rowcol[0]=i;
                rowcol[1]=j;
            }
            else if(keyT[i][j]==b){
                rowcol[2]=i;
                rowcol[3]=j;
            }
        }
    }
}

void encrypt(){
    for(int i=0;i<str.length();i=i+2){
        if(str[i]=='j'){
            str[i]='i';
        }
        else if(str[i+1]=='j'){
            str[i+1]='i';
        }
        findCell(str[i],str[i+1]);

        if(rowcol[0]==rowcol[2]){
            str[i]=keyT[rowcol[0]][(rowcol[1]+1)%5];
            str[i+1]=keyT[rowcol[0]][(rowcol[3]+1)%5];
        }
        else if(rowcol[1]==rowcol[3]){
            str[i]=keyT[(rowcol[0]+1)%5][rowcol[1]];
            str[i+1]=keyT[(rowcol[2]+1)%5][rowcol[1]];
        }
        else{
            str[i]=keyT[rowcol[0]][rowcol[3]];
            str[i+1]=keyT[rowcol[2]][rowcol[1]];
        }
    }
}

void playfairCipher(){
    lowerCase("k");
    lowerCase("s");
    removeSpace("k");
    removeSpace("s");
    addZ();
    addX();
    keyTable();
    encrypt();
}

int main(){
    key = "Monarchy";
    cout<<"Enter Plain text : ";
    getline(cin,str);
    playfairCipher();
    cout<<"Encrypted text : "<<str<<endl;
    return 0;
}