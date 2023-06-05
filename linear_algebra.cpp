#include <bits/stdc++.h>
using namespace std;

bool comp(vector<double> &a, vector<double> &b)
{
    int pivot_a = 0, pivot_b = 0;
    for (; pivot_a < a.size(); pivot_a++)
    {
        if (a[pivot_a])
            break;
    }
    for (; pivot_b < b.size(); pivot_b++)
    {
        if (b[pivot_b])
            break;
    }
    return pivot_a < pivot_b;
}
void sortMatrix(vector<vector<double>> &mat)
{
    sort(mat.begin(), mat.end(), comp);
}

void rowOperation(vector<vector<double>> &mat, double cof, int row1, int row2)
{ /// row2=cof*row1+row2
    for (int i = 0; i < mat[row2].size(); i++)
    {
        mat[row2][i] += cof * mat[row1][i];
    }
}
int get_pivot(vector<double> &row)
{
    int pivot = 0;
    for (; pivot < row.size(); pivot++)
    {
        if (row[pivot])
            break;
    }
    return pivot;
}


void reduce(vector<vector<double>> &mat){
    for(int i=0;i<mat.size();i++){
        int pivot = get_pivot(mat[i]);
        if(pivot==mat[i].size())continue;
        for(int j=mat[i].size()-1;j>=0;j--)mat[i][j]/=mat[i][pivot];
    }
    sortMatrix(mat);
}
void solveMatrix(vector<vector<double>> &mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        int pivot = get_pivot(mat[i]);
        // cout <<"index"<<i<<"pvot="<< pivot << '\n';
        if (pivot != mat[i].size())
        {
            for (int j = 0; j < mat.size(); j++)
            {
                if (i == j || !mat[j][pivot])
                    continue;
                // cout << i << "--->" << j << '\n';
                rowOperation(mat, -mat[j][pivot] / mat[i][pivot], i, j);

                // for (int i = 0; i < mat.size(); i++)
                // {
                //     for (int j = 0; j < mat[i].size(); j++)
                //         cout << mat[i][j] << ' ';

                //     cout << '\n';
                // }
            }
        }
    }
    cout<<"solved\n";
    
    reduce(mat);
    cout<<"reduced\n";
}

void test()
{

    vector<vector<double>>   mat{{2, 1, 3, 1},
                                 {1,0,1, 2},
                                 {2,1,1, 3}};

    int n = 4;
    for (int i = 0; i < 3; i++)
    {
        // for (int j = 0; j < n; j++)
            // cout << mat[i][j] << ' ';
        // cout << '\n';
    }
    solveMatrix(mat);
    // reduce(mat);
    for (int i = 0; i < 3; i++)
    {
        // for (int j = 0; j < n; j++)
            // cout << mat[i][j] << ' ';

        // cout << '\n';
    }
}