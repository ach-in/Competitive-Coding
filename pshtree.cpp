/*
Problem-https://www.codechef.com/JULY17/problems/PSHTTR
Author-Kushagra Juneja
*/

#include<bits/stdc++.h>
#define n_max 100005
 
using namespace std ;
 
struct edge
{
    int u,v,cost,id ;
};
vector<edge> edges ;
int n,m;
vector<int> adj[n_max] ;
int ctr ;
int enter[n_max]; int exiter[n_max] ;
int euler[n_max] ; int pa[n_max] ;
int ans[n_max] ;
 
void dfs(int node,int par)
{
    ctr++ ;
    enter[node]=ctr ;
    pa[node]=par ;
    for(int i=0 ; i<adj[node].size() ; i++){
        if(adj[node][i]!=par){
            dfs(adj[node][i],node) ;
        }
    }
    exiter[node]=ctr ;
}
 
bool compare(edge a, edge b){ return a.cost<b.cost ; }
 
void upd(int pos, int val)
{
    while(pos<=n+1){
        euler[pos]^=val ;
        pos+=pos&(-pos) ;
    }
}
 
int que(int pos)
{
    int ans=0 ;
    while(pos>0){
        ans^=euler[pos] ;
        pos-=pos&(-pos) ;
    }
    return ans ;
}
 
int main()
{
    int t ;
    scanf("%d",&t) ;
    while(t--){
       scanf("%d",&n) ;
       for(int i=0 ; i<=n+3 ; i++){
            adj[i].clear() ;
            euler[i]=0 ;
            pa[i]=0 ;
       }
       ctr=0 ;
       edges.clear() ;
       for(int i=1 ; i<n ; i++){
            int a,b,c ;
            scanf("%d %d %d",&a,&b,&c) ;
            adj[a].push_back(b) ;
            adj[b].push_back(a) ;
            edges.push_back(edge{a,b,c,0}) ;
       }
       dfs(1,0) ;
       int m ;
       scanf("%d",&m) ;
       vector<edge> query ;
       for(int i=0 ; i<m ; i++){
            int u,v,k ;
            scanf("%d %d %d",&u,&v,&k) ;
            query.push_back(edge{u,v,k,i}) ;
       }
       sort(query.begin(),query.end(),compare) ;
       sort(edges.begin(),edges.end(),compare) ;
       int ptr=0 ;
       for(int i=0 ; i<query.size() ; i++){
            while((ptr<n-1) && edges[ptr].cost<=query[i].cost){
                int parent=edges[ptr].u ;
                int child=edges[ptr].v ;
                if(pa[parent]==child){
                    swap(parent,child) ;
                }
                upd(enter[child],edges[ptr].cost);
                upd(exiter[child]+1,edges[ptr].cost);
                ptr++ ;
            }
            ans[query[i].id]=que(enter[query[i].u])^que(enter[query[i].v]) ;
       }
       for(int i=0 ; i<m ; i++){
            printf("%d\n",ans[i]) ;
       }
    }
    return 0 ;
}
 