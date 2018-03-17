/*
Problem-https://www.codechef.com/APRIL15/problems/DIVLAND
Author-Kushagra Juneja
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <queue>
#include <utility>
 
#define inf 1000006
#define ll long long int
#define CPS CLOCKS_PER_SEC
 
using namespace std ;
 
 
struct edge
{
    int u , cost ;
};
 
 
int n , m ;
int best[inf] ; ll bestcost ;
int sub[inf] ; bool visited[inf] ;
ll curcost ; int countering=1 ; bool tree=0 ;
vector<edge> adj[inf] ; int compo[inf] ;
clock_t begin ; int parent[inf] ;
 
 
bool time()
{
    return ( ((float)(clock()- begin))/CPS < 0.95 ) ;
}
 
 
int dfs(int node)
{
    if(visited[node]) return 0 ;
    visited[node]=1 ; int counter=1 ;
    for(int i=0 ; i<adj[node].size() ; i++)
    {
        if(!visited[adj[node][i].u])
        {
            parent[adj[node][i].u]=node ;
            counter+=dfs(adj[node][i].u) ;
        }
    }
    sub[node]=counter ;
    compo[node]=countering ;
    return counter ;
}
 
void locate(int node)
{
    best[node]=1 ;
    for(int i=0 ; i<adj[node].size() ; i++)
    {
        if(adj[node][i].u!=parent[node])
        locate(adj[node][i].u) ;
    }
    return ;
}
 
 
priority_queue<pair<int , int> > q ;
 
 
void solve_tree()
{
   for(int i=0 ; i<n ; i++)
   {
       q.push(make_pair(sub[i],i)) ;
   }
   int l=n/2 ;
   while(!q.empty())
   {
       if(q.top().first>l) {
       q.pop() ; continue ;
      }
      else {
            if(best[q.top().second]) {q.pop() ;
                continue ;}
      l-=q.top().first ;
      locate(q.top().second) ;
      }
   }
   int a=rand()%n ;
   while(l>0)
   {
       while(best[a]!=0) a=rand()%n ;
       best[a]=1 ; l-- ;
   }
   return ;
}
 
 
 
void solver()
{
    int a , b ; int i ;
    int k=0 ;
    while(++k<15 && time())
    {
       curcost=bestcost ;
       a= rand()%n ;
       while(best[a]!=0) a=rand()%n ;
       b=rand()%n ;
       while(best[b]!=1) b=rand()%n ;
       for( i=0 ; i<adj[a].size() ; i++)
       {
           if(best[adj[a][i].u]==0) curcost+=adj[a][i].cost ;
           else {
            if(b!=adj[a][i].u) curcost-=adj[a][i].cost ;
           }
       }
       for( i=0  ;i<adj[b].size() ; i++)
       {
           if(best[adj[b][i].u]==1) curcost+=adj[b][i].cost ;
           else {
            if(a!=adj[b][i].u) curcost-=adj[a][i].cost ;
           }
       }
       if(curcost<bestcost) {
            swap(best[a],best[b]) ;
            bestcost=curcost ;
       }
    }
    return ;
}
 
 
inline void print()
{
    for(int i=0 ; i<n ; i++)
    {
        if(best[i]==1) printf("%d\n",i) ;
    }
    return ;
}
 
inline void initialise()
{
    for(int i=0 ; i<n/2 ; i++)
    {
        best[i]=1 ;
    }
    for(int i=0 ; i<n ; i++)
    {
        for(int j=0 ; j<adj[i].size() ; j++)
        {
            if(best[i]!=best[adj[i][j].u])
                bestcost+=adj[i][j].cost ;
        }
    }
    bestcost/=2 ;
    return ;
}
 
 
int main()
{
    begin=clock() ;
    scanf("%d %d",&n,&m) ;
    int a , b ,c ;
    for(int i=0 ; i<m ;  i++)
    {
        scanf("%d %d %d",&a,&b,&c) ;
        adj[a].push_back( (edge) {b,c} ) ;
        adj[b].push_back( (edge) {a,c}) ;
    }
    srand(12345) ;
    for(int i=0 ; i<n ; i++)
    {
        if(!visited[i]) {
                parent[i]=-1 ;
                dfs(i) ; countering++ ;
        }
    }
    if(countering==2 && m==n-1 ) tree=1 ;
    if(tree) solve_tree() ;
    else {
            initialise() ;
            solver() ;
    }
    print() ;
    return 0 ;
}