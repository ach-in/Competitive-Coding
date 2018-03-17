/*
Problem-https://www.codechef.com/problems/SORTING
Author-Kushagra Juneja
*/

#include <bits/stdc++.h>
#define n_max 2000005
 
using namespace std ;
 
struct node
{
    int left , right , val ;
};
 
int n ; int arr[n_max] ; int position[n_max] ;
int root[n_max] ;
 
node nodes[n_max] ;
int tot=1 ;
 
int create_node()
{
    nodes[tot].left=nodes[tot].right=nodes[tot].val=0 ;
    return tot++ ;
}
 
int update(int pos , int l , int r , int p1)
{
    if(l>r || p1<l || r<p1) return pos ;
    int k=create_node() ;
    if(l==r){
        nodes[k].left=nodes[pos].left ; nodes[k].right=nodes[pos].right ;
        nodes[k].val=nodes[pos].val+1 ; return k ;
    }
    nodes[k].left=update(nodes[pos].left , l , (l+r)/2 , p1) ;
    nodes[k].right=update(nodes[pos].right , (l+r)/2+1 , r , p1) ;
    nodes[k].val= nodes[nodes[k].left].val+nodes[nodes[k].right].val ;
    return k ;
}
 
int query(int pos1 , int pos2 , int l , int r , int p1) // returns index of position in the original array
{
    assert(l<=r && p1<=nodes[pos2].val-nodes[pos1].val) ;
    if(l==r) return l ;
    int l1=nodes[pos1].left ; int l2=nodes[pos2].left ;
    int num= nodes[l2].val-nodes[l1].val ;
    if(num>=p1){
        return query(l1 , l2 , l , (l+r)/2 , p1) ;
    }
    else return query(nodes[pos1].right , nodes[pos2].right , (l+r)/2+1 , r , p1-num) ;
}
 
int solve(int l , int r)
{
    if(l==r || l==r+1) return 0 ;
    int mid=(r-l)/2+1 ;
    int sum=r-l+1 ;
    int posi=query(root[l-1] , root[r] , 1 , n , mid) ;
    sum+=solve(l , arr[posi]-1) ;
    sum+=solve(arr[posi]+1 , r) ;
    return sum ;
}
 
int main()
{
    scanf("%d",&n) ;
    for(int i=1 ; i<=n ; i++){
        scanf("%d",&arr[i]) ;
        position[arr[i]]=i ;
    }
    for(int i=1 ; i<=n ; i++){
        root[i]=update(root[i-1] , 1 , n , position[i]) ;
    }
    printf("%d\n",solve(1 , n)) ;
    return 0 ;
}
 