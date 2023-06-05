#include <bits/stdc++.h>
#include "D:\Circuits-solver\linear_algebra.cpp"
// using namespace std;
vector<int> vis, super_nodes;
vector<vector<pair<int, double>>> circuit;
void get_super(int cr)
{
    // cout<<"cr"<<cr<<'\n';
    vis[cr] = 1;
    super_nodes.push_back(cr);
    for (int i = 0; i < circuit[cr].size(); i++)
    {

        // cout<<"to"<<i<<'\n';
        if (i != cr && circuit[cr][i].first == 1 && !vis[i])
        {
            // cout<<"to'"<<i<<'\n';
            get_super(i);
        }
    }
}

vector<double> get_current_equation(vector<int> &nodes)
{
    vector<double> equation(circuit[0].size());
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 1; j < circuit.size(); j++)
        {
            if (circuit[nodes[i]][j].first == 2)
            {
                equation[nodes[i] - 1] += 1 / circuit[nodes[i]][j].second;
                equation[j - 1] += -1 / circuit[nodes[i]][j].second;
            }
        }
    }
    return equation;
}
vector<vector<double>> get_volt_equations(vector<int> &nodes)
{
    vector<vector<double>> equations;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 1; j < circuit.size(); j++)
        {
            if (circuit[nodes[i]][j].first == 1)
            {
                vector<double> equation(circuit[0].size());
                equation[nodes[i] - 1] += -1;
                equation[j - 1] += 1;
                equation[circuit[0].size() - 1] = circuit[nodes[i]][j].second;
                equations.push_back(equation);
            }
        }
    }
    return equations;
}

vector<double> solveCircuit(vector<vector<pair<int, double>>> &comps, int n)
{
    circuit = comps;
    vis = vector<int>(n + 5);
    vector<vector<double>> matrix;
    for (int i = 1; i <= n; i++)
    {
        if (comps[i][i].first == 3)
        {
            vector<double> ground_equation(circuit[0].size());
            ground_equation[i - 1] = 1;
            matrix.push_back(ground_equation); /// ground at node i
        }
    }
    if (matrix.size() == 0)
    {
        // cout << "size:" << matrix.size() << '\n';
        vector<double> ground_equation(circuit[0].size());
        ground_equation[0] = 1;
        matrix.push_back(ground_equation); /// ground at node 1
    }
    // cout << "size:" << matrix.size() << '\n';
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            super_nodes = vector<int>();
            // cout << "getting super\n";
            get_super(i);
            // cout << "gor super\n";
            // for (int j = 0; j < super_nodes.size(); j++)
            //     cout << super_nodes[j] << ' ';
            // cout << '\n';

            vector<double> equation = get_current_equation(super_nodes);
            matrix.push_back(equation);
            // cout<<"gor current equation\n";
            // for(int j=0;j<equation.size();j++)cout<<equation[j]<<' ';
            // cout<<'\n';
            vector<vector<double>> equations = get_volt_equations(super_nodes);
            matrix.insert(matrix.end(), equations.begin(), equations.end());
            // cout<<"gor volt equations\n";
            // for(int j=0;j<equations.size();j++){
            //     for(int k=0;k<equations[j].size();k++){
            //         cout<<equations[j][k]<<' ';
            //     }
            //     cout<<'\n';
            // }
            // cout<<'\n';
        }
    }

    // cout << "Matrix:" << '\n';
    // for (int i = 0; i < matrix.size(); i++)
    // {
    //     for (int j = 0; j < matrix[i].size(); j++)
    //         cout << matrix[i][j] << ' ';
    //     cout << '\n';
    // }
    solveMatrix(matrix);
    // cout << "Matrix:" << '\n';
    // for (int i = 0; i < matrix.size(); i++)
    // {
    //     for (int j = 0; j < matrix[i].size(); j++)
    //         cout << matrix[i][j] << ' ';
    //     cout << '\n';
    // }
    // cout << "answering\n"
    //      << n;
    vector<double> answer(n);
    // cout << "answering\n"
    //      << n;
    // // for(int i=0;i<n;i++)answer.push_back(0);
    // cout << "answering\n"
    //      << matrix.size();
    for (int i = 0; i < matrix.size(); i++)
    {
        // cout << i << '\n';
        int pivot = get_pivot(matrix[i]);
        // cout << pivot << '\n';
        if (pivot == matrix[i].size())
            continue;
        answer[pivot] = matrix[i][n];
    }
    // cout << "answwered\n";
    return answer;
}

vector<vector<double>> solveCurrent(vector<vector<pair<int, double>>> &comps, int n, vector<double> volts)
{
    vector<vector<double>> currents(n + 1, vector<double>(n + 1, -1e9));

    // simple branches
    for (int i = 1; i < comps.size(); i++)
    {
        for (int j = 1; j < comps[i].size(); j++)
        {
            if (comps[i][j].first == 2)
            {
                currents[i][j] = (volts[i - 1] - volts[j - 1]) / comps[i][j].second;
                currents[j][i] = (volts[j - 1] - volts[i - 1]) / comps[i][j].second;
            }
        }
    }

    int flag = 0;
    do
    {
        flag = 0;
        // battary branches
        for (int i = 1; i < comps.size(); i++)
        {
            for (int j = 1; j < comps[i].size(); j++)
            {
                if (comps[i][j].first == 1&&currents[i][j]==-1e9)
                {
                    { // get current from node i

                        /// ensure it is valid
                        bool valid = true;
                        for (int k = 0; k < comps[i].size(); k++)
                        {
                            if (k != j && comps[i][k].first == 1 && currents[i][k] == -1e9)
                                valid = false;
                        }
                        if (valid)
                        {
                            currents[i][j] = 0;

                            for (int k = 0; k < comps[i].size(); k++)
                            {
                                if (k == j)
                                    continue;
                                if(comps[i][k].first==1||comps[i][k].first==2)
                                currents[i][j] -= currents[i][k];
                                flag = 1;
                            }
                        }
                            currents[j][i]=-currents[i][j];
                    }
                    if(!flag){ // get current from node j

                        /// ensure it is valid
                        bool valid = true;
                        for (int k = 0; k < comps[j].size(); k++)
                        {
                            if (k != j && comps[j][k].first == 1 && currents[j][k] == -1e9)
                                valid = false;
                        }
                        if (valid)
                        {
                            currents[j][i] = 0;

                            for (int k = 0; k < comps[j].size(); k++)
                            {
                                if (k == j)
                                    continue;
                                if(comps[i][k].first==1||comps[i][k].first==2)
                                currents[j][i] -= currents[j][k];
                                flag = 1;
                            }
                            currents[i][j]=-currents[j][i];
                        }
                    }
                }
            }
        }
    } while (flag);

    return currents;
}

void testCircuit()
{
    vector<vector<pair<int, double>>> comps{{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
                                            {{0, 0}, {0, 0}, {0, 0}, {2, 1}, {0, 0}, {2, 1}, {1, 0}},
                                            {{0, 0}, {0, 0}, {3, 0}, {2, 1}, {0, 0}, {0, 0}, {1, -5}},
                                            {{0, 0}, {2, 1}, {2, 1}, {0, 0}, {2, 1}, {0, 0}, {0, 0}},
                                            {{0, 0}, {0, 0}, {0, 0}, {2, 1}, {0, 0}, {1, -5}, {0, 0}},
                                            {{0, 0}, {2, 1}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
                                            {{0, 0}, {1, 0}, {1, 5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    cout << "solving..\n";
    int n=6;
    vector<double> answer = solveCircuit(comps, n);
    cout << "solved\n";
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << ' ';
    
    cout<<'\n';
    vector<vector<double> >answerCurrent= solveCurrent(comps,n,answer);
    for(int i=0;i<answerCurrent.size();i++){
        for(int j=0;j<answerCurrent[i].size();j++){
            cout<<answerCurrent[i][j]<<' ';
        }
        cout<<'\n';
    }



}