#include<iostream>
#include<vector>
#include <ctime>
using namespace std;
int n,mat[16][16],save_mat[16][16],vis[16],total_cost=0;
vector<int> best_path;
vector<int> temp_path;
int red_mat[16][16]={0};
int ini_mat[16][16]={0};
int upper_bound = 999;
int reduce(int from_city,int to_city,int mini)
{
    // cout<<"---------------------------------------"<<endl;
    // cout<<"from city is "<<from_city<<endl;
    // cout<<"to city is "<<to_city<<endl;
    // cout<<"---------------------------------------"<<endl;
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<n+1;j++)
        {
            if(i==1 && j==from_city)
            {
                red_mat[i][j]=100;
                continue;
            }
            if(i==from_city||j==to_city)red_mat[i][j]=100;
            else red_mat[i][j]=mat[i][j];
        }
    }
    //reduce row
    int r_cost=0;
    for(int i=1;i<n+1;i++)
    {
        int min=100,w_zero=0;
        for(int j=1;j<n+1;j++)
        {
            if (min==0)
            {
                w_zero=1;
                break;
            }
            if(red_mat[i][j]<min)min=red_mat[i][j];
        }
        if(w_zero||min==100)continue;
        else r_cost +=min;
        for(int j=1;j<n+1;j++)
        {
            if(red_mat[i][j]!=100)red_mat[i][j]-=min;
        }    
    }
    
    //reduce col
    int c_cost=0;
    for(int j=1;j<n+1;j++)
    {
        int min=100,w_zero=0;
        for(int i=1;i<n+1;i++)
        {
            if (min==0)
            {
                w_zero=1;
                break;
            }
            if(red_mat[i][j]<min)min=red_mat[i][j];
        }
        if(w_zero||min==100)continue;
        else c_cost +=min;
        for(int i=1;i<n+1;i++)
        {
            if(red_mat[i][j]!=100)red_mat[i][j]-=min;
        }    
    }
    if(r_cost+c_cost+mat[from_city][to_city]<=mini)
    {
        for(int i=1;i<n+1;i++)
        {
            //copy a mat 
            for(int j=1;j<n+1;j++)
            {
                save_mat[i][j]=red_mat[i][j];
                if(from_city==0&&to_city==0)
                {
                    ini_mat[i][j] = save_mat[i][j];
                    mat[i][j]=save_mat[i][j];//initial mat
                }
            }
        }
    }
    // cout<<"r_cost is "<<r_cost<<endl;
    // cout<<"c_cost is "<<c_cost<<endl;
    // cout<<"r_cost+c_cost+mat[from][to]"<<r_cost+c_cost+mat[from_city][to_city]<<endl;
    return r_cost+c_cost;

}
void find_least_cost_city(int cur_city,int level)
{
    if(level==n)
    {
        total_cost += (mat[cur_city][temp_path[0]]!=100)?mat[cur_city][1]:0;
        temp_path.push_back(1);
        if(upper_bound==999)
        {
            upper_bound=total_cost;
        }
        return;
    }
    int next_city,red,mini=999;
    for(int i =1;i<n+1;i++)
    {
        if(vis[i]==0)
        {
            red=reduce(cur_city,i,mini);
            if(red+mat[cur_city][i]<mini)
            {
                next_city = i;
                mini = red+mat[cur_city][i];

            }
        }
    }
    vis[next_city]=1;
    total_cost +=mini;
    for(int i=1;i<n+1;i++)
    {
        //copy a mat 
        for(int j=1;j<n+1;j++)mat[i][j]=save_mat[i][j];
    }
    // cout<<"next city is "<<next_city<<endl;
    // cout<<"the mat is now: "<<endl;
    // for(int i=1;i<n+1;i++)
    // {
    //     //copy a mat 
    //     for(int j=1;j<n+1;j++)
    //     {
    //         cout<<mat[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"the total cost is "<<total_cost<<endl;
    tmep_path.push_back(next_city);
    find_least_cost_city(next_city,level+1);
}
int main()
{
    clock_t start, end;
    double time;
    start = clock();
    cin>>n;
    for(int i = 1;i<n+1;i++)for(int j = 1;j<n+1;j++)cin>>mat[i][j];
    cout<<"The shortest Hamiltonian cycle:"<<endl;
    vis[1]=1;
    best_path.push_back(1);
    total_cost = reduce(0,0,999);   
    find_least_cost_city(1,1);
    for(int i=0;i<n+1;i++)cout<<best_path[i]<<" ";
    cout<<endl;
    end = clock();
    cout<<"Total cost:"<<total_cost<<endl;
    cout<<"Time:"<<double(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}