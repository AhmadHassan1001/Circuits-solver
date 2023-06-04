
#include<bits/stdc++.h>
#include "D:\Circuits-solver\linear_algebra.cpp"
using namespace std;
int main(int argc, char const *argv[])
{
    test();
    cout<<"######## Circuits solver #############";
    cout<<"Enter the number of nodes:";
    int n;
    cin>>n;
    vector<vector<pair<double,int>>>comps(n+1,vector<pair<double,int>>(n+1,{0,0}));
    int cmnd=0;
    
    do{
        cout<<"Choose action:\n";
        cout<<"1-Add 2-nodes component\n";
        cout<<"2-Add single-node component\n";
        cout<<"3-solve\n";
        cin>>cmnd;
        if(cmnd==1){
            cout<<"Select two different nodes number less than"<<n+1<<"\n";
            cout<<"Node a:";
            int a;
            cin>>a;
            cout<<"Node b:";
            int b;
            cin>>b;
            if(a==b){
                cout<<"a shouldn't equal b";
                continue;
            }
            if(comps[a][b].first!=0){
                cout<<"this branch has a component already";
                continue;
            }

            cout<<"Choose component:\n";
            cout<<"1- Battery\n";
            cout<<"2- Resistor\n";
            int comp=0;
            cin>>comp;
            if(comp==1){
                comps[a][b].first=comps[b][a].first=1;
                cout<<"Value of battery in V such that negative terminal is at node a:";
                cin>>comps[a][b].second;
                comps[b][a].second=-comps[a][b].second;
            }else if(comp==2){
                comps[a][b].first=comps[b][a].first=2;
                cout<<"Value of resistor in ohm:";
                cin>>comps[a][b].second;
                comps[b][a].second=comps[a][b].second;

            }



        }

    }while(cmnd!=3);

    cout<<"Solving as ground at node 1:";
    
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

