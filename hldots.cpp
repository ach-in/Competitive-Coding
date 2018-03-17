/*
Problem-https://www.codechef.com/problems/HLDOTS
Author-Kushagra Juneja
*/

#include <iostream>
#include <cmath>
#include <vector>
#define mod 19101995
#define ll long long int
using namespace std ;
vector<int> adj[100005] ;
vector<int> adj2[100005] ;
bool visited[100005]={false} ;
int hld[100005][75] ;
int answer(int a , int b)
{
    if(b<0)
    {
        return 0 ;
    }
    if(hld[a][b]!=-1)
    {
        return hld[a][b] ;
    }
    int s= adj[a][0] ;
    if(s==0)
    {
        return 1 ;
    }
    if(s==1)
    {
        int by = adj[a][1] ;
        hld[a][b]= answer(by , b) ;
        return hld[a][b] ;
    }
    ll counter=0 ;
    for(int i=1 ; i<=s ; i++)
    {
        ll res=1 ;
        res=(res*answer(adj[a][i],b))%mod ;
        for(int j=1 ; j<=s ; j++)
        {
            if(j!=i)
            res=(res*answer(adj[a][j],b-1))%mod ;
        }
        counter=(counter+res)%mod ;
    }
    hld[a][b]=counter ;
    return counter ;
}
void dfs(int a)
{
    visited[a]=true ;
    int s=adj2[a][0] ;
    for(int i=1 ; i<=s ; i++)
    {
        if(!visited[adj2[a][i]])
        {
            adj[a].push_back(adj2[a][i]) ;
            adj[a][0]++ ;
            dfs(adj2[a][i]) ;
        }
    }
    return ;
}
int main()
{
    int n ;
    cin >> n ;
    int a, b  ;
    for(int i=1 ; i<=n ; i++)
    {
        adj2[i].push_back(0) ;
        adj[i].push_back(0) ;
    }
    for(int i=0 ; i<n-1;  i++)
    {
        cin >> a >> b ;
        adj2[a].push_back(b) ;
        adj2[b].push_back(a) ;
        adj2[b][0]++ ; adj2[a][0]++ ;
    }
    int logari=log2(n) ;
    for(int i=1 ; i<=n ; i++)
    {
        for(int j=1 ; j<75 ; j++)
        {
            hld[i][j]=-1 ;
        }
    }
    dfs(1) ;
    cout << answer(1,logari) ;
    return 0 ;
}