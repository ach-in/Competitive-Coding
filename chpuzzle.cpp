/*
Problem-https://www.codechef.com/FEB15/problems/CHPUZZLE
Author-Kushagra Juneja
*/

#include<cstdio>
#include<vector>
#include<algorithm>
#define inf 100000000
#define ll long long int
using namespace std ;
int answer[1005][1005] ;
int answer2[1005][1005] ;
struct info
{
   int number ; int difx ; int dify ;
};
struct cell
{
    int x ; int y ;
};
bool compare (info a , info b)
{
    return a.dify<b.dify || (a.dify==b.dify && a.difx<b.difx ) ;
}
bool compare1 (info a , info b)
{
    return a.difx<b.difx || (a.difx==b.difx && a.dify<b.dify)  ;
}
vector<cell> adj[200005] ;
info arr2[200005] ;
info arr[200005] ;
inline void update(int pos , int x , int y)
{
    x-- ; y-- ;
    int s=adj[pos].size() ;
    for(int i=1 ; i<s ; i++)
    {
        int x1=adj[pos][i].x ;
        int y1=adj[pos][i].y ;
        answer[x1+x][y1+y]=pos ;
    }
    return  ;
}
inline void update2(int pos , int x , int y)
{
    x-- ; y-- ;
    int s=adj[pos].size() ;
    for(int i=1 ; i<s ; i++)
    {
        int x1=adj[pos][i].x ;
        int y1=adj[pos][i].y ;
        answer2[x1+x][y1+y]=pos ;
    }
    return  ;
}
int main()
{
    int w , h , k ;
    scanf("%d %d %d", &h ,&w , &k) ;
    for(int i=1 ; i<=k ;i++)
    {
        int a ;
        scanf("%d",&a) ;
        cell pr ;
        pr.x=a ;pr.y=0 ;
        adj[i].push_back(pr) ;
        int c , d ;
        int maxix=(-1)*inf ;
        int minix=inf ;
        int maxiy=(-1)*inf ;
        int miniy=inf ;
        for(int j=1 ; j<=a ;j++)
        {
            scanf("%d %d",&c , &d) ;
            if(d<minix)
                minix=d ;
            if(d>maxix)
                maxix=d ;
            if(c<miniy)
                miniy=c ;
            if(c>maxiy)
                maxiy=c ;
            pr.x=d ;pr.y=c ;
            adj[i].push_back(pr) ;
        }
        arr[i].number=i ;
        arr[i].difx=maxix-minix+1 ;
        arr[i].dify=maxiy-miniy+1 ;
    }
    sort(arr+1 , arr+k+1, compare) ;
    int counter=1 ;
    int y=1 ;
    while(counter<=k)
    {
        int x=1 ;
        int maxi= 0;
        while(true)
        {
            if(counter>k)
            {
                break ;
            }
            if(x+arr[counter].difx>w+1 || y+arr[counter].dify>h+1)
            {
                break ;
            }
            if(arr[counter].dify>maxi)
                maxi=arr[counter].dify ;
            update(arr[counter].number ,x ,y ) ;
            x+=arr[counter].difx ;
            counter++ ;
        }
        y+=maxi ;
        if(y+arr[counter].dify>h+1)
        {
            break ;
        }
    }
    ll sum1 =0 ;
    for(int i=1 ; i<=h ; i++)
    {
        for(int j=1 ; j<=w ; j++)
        {
            if(answer[j][i]!=0)
            {
                sum1++ ;
            }
        }
    }
    sort(arr+1 , arr+k+1, compare1) ;
    counter=1 ;
    int x=1 ;
    while(counter<=k)
    {
        int y=1 ;
        int maxi= 0;
        while(true)
        {
            if(counter>k)
            {
                break ;
            }
            if(x+arr[counter].difx>w+1 || y+arr[counter].dify>h+1)
            {
                break ;
            }
            if(arr[counter].difx>maxi)
                maxi=arr[counter].difx ;
            update2(arr[counter].number ,x ,y ) ;
            y+=arr[counter].dify ;
            counter++ ;
        }
        x+=maxi ;
        if(x+arr[counter].difx>w+1)
        {
            break ;
        }
    }
    ll sum2 =0 ;
    for(int i=1 ; i<=h ; i++)
    {
        for(int j=1 ; j<=w ; j++)
        {
            if(answer2[j][i]!=0)
            {
                sum2++ ;
            }
        }
    }
    for(int i=1 ; i<=h ; i++)
    {
        for(int j=1 ; j<=w ; j++)
        {
 
                printf("%d ",answer2[j][i]) ;
            
        }
        printf("\n") ;
    }
 
    return 0 ;
}