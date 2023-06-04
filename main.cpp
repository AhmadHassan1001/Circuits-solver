
#include<bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    cout<<"######## Circuits solver #############";
    cout<<"Enter the number of nodes:";
    int n;
    cin>>n;

    int cmnd=0;
    
    do{
        cout<<"Choose action:\n";
        cout<<"1-Add 2-nodes component\n";
        cout<<"2-Add single-node component\n";
        cout<<"3-solve\n";
        cin>>cmnd;

    }while(cmnd!=3);


    //TODO: OUTPUT all VOLTS
    do{
        cout<<"Choose what you wanT:\n";
        cout<<"1-Get current\n";
        cout<<"2-Get voltage difference\n";
        cout<<"3-Exit\n";
        cin>>cmnd;

    }while(cmnd!=3);

    cout<<"Finished\n";


    return 0;
}

