
#include<bits/stdc++.h>
// #include "D:\Circuits-solver\linear_algebra.cpp"
#include "D:\Circuits-solver\circuits_analyser.cpp"
using namespace std;
int main(int argc, char const *argv[])
{
    // testCircuit();
    cout<<"######## Circuits solver #############";
    cout<<"Enter the number of nodes:";
    int n;
    cin>>n;
    vector<vector<pair<int,double>>>comps(n+1,vector<pair<int,double>>(n+1,{0,0}));
    int cmnd=0;
    
    do{
        cout<<"Choose action:\n";
        cout<<"1-Add 2-nodes component\n";
        cout<<"2-Add single-node component\n";
        cout<<"3-solve\n";
        cin>>cmnd;
        if(cmnd==1){
            cout<<"Select two different nodes number less than"<<n<<"\n";
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
    vector<double>volts=solveCircuit(comps,n);
    for(int i=0;i<volts.size();i++)cout<<"v"<<i+1<<"="<<volts[i]<<", ";
    cout<<'\n';
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

/**
 * 
3
1
1
2
1
5
1
2
3
2
2
1
3
1
2
3
3

*/