#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream outFile;
    outFile.open("address.txt");
    for(int i=1; i<1024; i++)
    {
        if(i<9)
        {
            outFile<<i<<"  :  "<<2048+i-1<<endl;
        }
        else
        {
            outFile<<i<< " :  "<<2055+2*(i-8)-1<<endl;
        }
    }
}