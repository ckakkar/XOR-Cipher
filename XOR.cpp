#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
using namespace std;

#define MSG_LENGTH 8

class cipher
{
private:
    char key[MSG_LENGTH]={'1','1','1','1','0','0','1','0'};
    unsigned char original;
    unsigned char encoded;
    unsigned char decoded;
public:
    cipher();    

    void getInput();
    unsigned char cipherWithKey(unsigned char tmp);
    void printCipher(const unsigned char &k) const;
    unsigned char stringToBinary(char xx[]);
    unsigned char scrambler(unsigned char o);

    unsigned char getEncoding() const;
    unsigned char getDecoding() const;

    bool encoder();
    bool decoder();
    char* unsig2char(unsigned char k) const;
    bool compare() const;

    friend ostream& operator<<(ostream& out,const cipher c);
};
cipher::cipher() //rather from encoder I would prefer to call my getInput() from the constructor
{
    getInput();
}
void cipher::getInput() //it'll get the original input from the user as a binary string
{
    char* arr=new char[MSG_LENGTH+1];
    string s;
    label:
    cout<<"enter the user-input original string: ";//string size-anything,
    cin>>s;                                        //for string size less than 8, automatic 0s will 
    int size=s.length();                           //generated and for greater than 8 the least significant  
                                                   //will be dropped
    for(int i=0;i<size;i++)
    {
        int num=+s[i];
        if(num!=48 && num!=49)
        {
            cerr<<"Please enter binary string consisting of 1's and 0's only!!"<<endl;
            goto label;
        }
    }
    for(int i=0;i<MSG_LENGTH-size;i++)
    {
        arr[i]='0';
    }
    for(int i=MSG_LENGTH-size;i<MSG_LENGTH;i++)
    {
        arr[i]=s[i-(MSG_LENGTH-size)];
    }
    arr[MSG_LENGTH]='\0';

    this->original=stringToBinary(arr);
}
unsigned char cipher::cipherWithKey(unsigned char tmp) //this'll return a char (un)ciphered with
{                                                      //the given KEY
    char* arr=unsig2char(tmp);
    char* new_arr=new char[MSG_LENGTH+1];

    for(int i=0;i<MSG_LENGTH;i++)
    {
        if((arr[i]=='1' && this->key[i]=='1') || (arr[i]=='0' && this->key[i]=='0'))
            new_arr[i]='0';
        else
            new_arr[i]='1';
    }
    new_arr[MSG_LENGTH]='\0';
    unsigned char ch=stringToBinary(new_arr);
    return ch;
}
void cipher::printCipher(const unsigned char &k) const //This'll simply just print the "1-0" string
{
    char* arr=unsig2char(k);
    for(int i=0;i<MSG_LENGTH;i++)
    {
        cout<<arr[i];
    }
}
unsigned char cipher::stringToBinary(char xx[])  //this a basic binary to decimal
{                                                //converter 
    int sum=0,power=0;
    for(int i=MSG_LENGTH-1;i>=0;i--)
    {
        if(xx[i]=='1')
            sum+=pow(2,power);
        power++;
    }
    unsigned char ch=sum;
    delete []xx;
    return ch;
}
unsigned char cipher::scrambler(unsigned char o)  //This one scrambles the string according to the 
{                                                 //given algorithm 
    char* arr=unsig2char(o);
    for(int i=0;i<MSG_LENGTH-1;i+=2)
    {
        char temp=arr[i];
        arr[i]=arr[i+1];
        arr[i+1]=temp;
    }
    unsigned char ch=stringToBinary(arr);

    return ch;
}
unsigned char cipher::getEncoding() const  //Simple getter fuctions
{
    return this->encoded;
}
unsigned char cipher::getDecoding() const   //Simple getter fuction 
{
    return this->decoded;
}
bool cipher::encoder()    //updates the encoded-member fuction 
{
    unsigned char crypt=cipherWithKey(this->original);
    unsigned char enc=scrambler(crypt);
    this->encoded=enc;

    return true;
}
bool cipher::decoder()     //updates the decoded-member function 
{
    unsigned char decrypt=scrambler(this->encoded);
    unsigned char dec=cipherWithKey(decrypt);
    this->decoded=dec;

    return true;
}
char* cipher::unsig2char(unsigned char k) const //This function takes in a unsigned char  
{                                               //returns char* 
    int num=+k;
    char* a=new char[MSG_LENGTH+1];
    for(int i=MSG_LENGTH-1;i>=0;i--)
    {
        if(num%2==1)
            a[i]='1';
        else
            a[i]='0';
        num/=2;
    }
    a[MSG_LENGTH]='\0';

    return a;
}
bool cipher::compare() const   //This fuction compares the orginal and the 
{                              //decoded string 
    char* orig=unsig2char(this->original);
    char* deco=unsig2char(this->decoded);

    for(int i=0;i<MSG_LENGTH;i++)
    {
        if(orig[i]!=deco[i])
            return false;
    }

    return true;
}
ostream& operator<<(ostream& out,const cipher ck) //a friend fuction that out puts the 
{                                                 //result of our cipher
    out<<"\noriginal: ";
    ck.printCipher(ck.original);
    out<<"\nencoded: ";
    ck.printCipher(ck.encoded);
    out<<"\ndecoded: ";
    ck.printCipher(ck.decoded);
    out<<endl;

    return out;
}

int main()
{
    cipher ck;      // main function as given in the labv assingmnet 
    assert(ck.encoder());
    assert(ck.decoder());

    cout<<ck<<endl;

    if(ck.compare())
        cout<<">> Test passed.\n";
    else
        cout<<">> Test failed.\n";

    return 0;
}
