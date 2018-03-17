/*
Problem-https://www.codechef.com/problems/GENETICS
Author-Kushagra Juneja
*/

#include <bits/stdc++.h>
#define ll long long int
#define n_max 20000030
#define count countern
 
using namespace std ;
 
struct node
{
    int arr[4] ;
    int l , r , val ;
    int cnt ;
    ll pr ;
};
 
int n=1 ;
node nodes[n_max] ; int answer[4] ;
int rooter[10005] ;
 
void upd(int root)
{
    int l= nodes[root].l ; int r=nodes[root].r ;
    nodes[root].cnt=1 ;
    for(int i=0 ; i<4 ;i++){
        nodes[root].arr[i]=0 ;
    }
    nodes[root].arr[nodes[root].val]++ ;
    if(l>0){
        nodes[root].cnt+=nodes[l].cnt ;
        for(int i=0 ; i<4 ; i++){
            nodes[root].arr[i]+=nodes[l].arr[i] ;
        }
    }
    if(r>0){
        nodes[root].cnt+=nodes[r].cnt ;
        for(int i=0 ; i<4 ; i++){
            nodes[root].arr[i]+=nodes[r].arr[i] ;
        }
    }
}
 
int copy_node(int pos)
{
    nodes[n].cnt=nodes[pos].cnt ;
    nodes[n].l=nodes[pos].l ; nodes[n].r=nodes[pos].r ;
    nodes[n].pr=nodes[pos].pr ;
    nodes[n].val=nodes[pos].val ;
    for(int i=0 ; i<4 ; i++){
        nodes[n].arr[i]=nodes[pos].arr[i] ;
    }
    return n++ ;
}
 
int create_node(int val)
{
    nodes[n].cnt=1 ;
    nodes[n].l=nodes[n].r=-1 ;
    nodes[n].val=val ;
    nodes[n].pr=rand() ;
    for(int i=0 ; i<4 ; i++){
        nodes[n].arr[i]=0 ;
    }
    nodes[n].arr[nodes[n].val]++ ;
    return n++ ;
}
 
pair<int , int> split(int root , int pos)
{
    if(root<0) return make_pair(-1 , -1) ;
    // less/equal   greater
    root=copy_node(root) ;
    int l=nodes[root].l ; int r=nodes[root].r ;
    int m = (l>=0) ? nodes[l].cnt : 0 ;
    if(pos<=m){
        pair<int , int> p = split(l , pos) ;
        nodes[root].l=p.second ;
        upd(root) ;
        return make_pair(p.first , root) ;
    }
 
    pair<int , int> p=split(r , pos-1-m) ;
    nodes[root].r=p.first ;
    upd(root) ;
    return make_pair(root , p.second) ;
}
 
int merge(int a , int b)
{
    if(a<0 && b<0) return -1 ;
    if(b<0 || nodes[a].pr>nodes[b].pr)
    {
        a=copy_node(a) ;
        nodes[a].r=merge(nodes[a].r , b) ;
        upd(a) ;
        return a ;
    }
    b=copy_node(b) ;
    nodes[b].l=merge(a, nodes[b].l) ;
    upd(b) ;
    return b ;
    assert(n<10000000) ;
}
 
int insert(int root , int pos , int val)
{
    pair<int , int> p=split(root , pos-1) ;
    int n=create_node(val) ;
    int x=merge(p.first , n) ;
    return merge(x , p.second) ;
}
 
int del(int root , int pos)
{
    pair<int , int > p=split(root , pos-1) ;
    pair<int , int > p2=split(p.second , 1) ;
    return merge(p.first , p2.second) ;
}
 
int change(int root , int pos , int val)
{
    int n=create_node(val) ;
    pair<int , int> p=split(root , pos-1) ;
    pair<int , int> p2=split(p.second , 1) ;
    int x= merge(p.first , n) ;
    return merge(x , p2.second) ;
}
 
int count(int root , int k1 , int k2)
{
    pair<int , int> p=split(root , k1-1) ;
    pair<int , int> p2=split(p.second , k2-k1+1) ;
    for(int i=0  ;i<4 ; i++){
        answer[i]=nodes[p2.first].arr[i] ;
    }
    int x=merge(p.first , p2.first) ;
    return merge(x , p2.second) ;
}
 
pair<int , int> cross(int root1 , int root2 , int k1 , int k2)
{
    pair<int , int> p=split(root1 , k1) ;
    pair<int , int> p2=split(root2 , k2) ;
    return make_pair(merge(p.first , p2.second) , merge(p2.first , p.second)) ;
}
 
char buf[30005] ;
 
int sizer()
{
    for(int i=0 ;  ; i++)
    {
        if(buf[i]=='\0') return i ;
    }
}
 
int main()
{
    int n , q ;
    scanf("%d",&n) ;
    int mapper[230] ;
    mapper['A']=0 ; mapper['G']=1 ; mapper['T']=2 ; mapper['C']=3 ;
    for(int i=1 ; i<=n ; i++)
    {
        if(i==1) rooter[i]=-1 ;
        else rooter[i]=rooter[i-1] ;
        scanf(" %s",buf) ;
        int s=sizer() ;
        for(int j=0 ; j<s ; j++)
        {
            rooter[i]=insert(rooter[i], j+1 , mapper[buf[j]]) ;
        }
    }
    scanf("%d",&q) ;
    for(int i=0 ; i<q ; i++)
    {
        scanf(" %s",buf) ;
        if(strcmp("MUTATE" , buf)==0){
            int a , b ; char c ;
            scanf("%d%d %c",&a , &b , &c) ;
            rooter[a]=change(rooter[a] , b , mapper[c]) ;
        }
        else if(strcmp("CROSS" , buf)==0){
            int l , r , k1 , k2 ;
            scanf("%d%d%d%d",&l ,&r ,&k1 ,&k2) ;
            pair<int , int> p=cross( rooter[l] , rooter[r] , k1 , k2) ;
            n++ ;
            rooter[n]=p.first ;
            n++ ;
            rooter[n]=p.second ;
        }
        else if(strcmp("COUNT" , buf)==0){
            int id , k1 , k2 ;
            scanf("%d%d%d",&id ,&k1 ,&k2) ;
            count(rooter[id] , k1 , k2) ;
            for(int i=0 ; i<4 ; i++){
                printf("%d ",answer[i]) ;
                printf("\n") ;
            }
        }
        else{
            assert(1==2) ;
        }
    }
    return 0 ;
}