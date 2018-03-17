/*
Problem - https://www.codechef.com/FEB15/problems/DEVLOCK
Aithor-Kushagra Juneja
*/

#include<cstdio>
#include<vector>
#define ll long long int
#define mod 998244353
using namespace std ;
ll check[105] ;
ll counter[105] ;
ll arr[15005][55][4] ;// 0-final 1-pow 2-temp 3-base
ll n ,  p  , mm ;
ll pow(ll a)
{
    if(a==0)
    {
        return 1%p ;
    }
    if(a==1)
    {
        return 10%p ;
    }
    ll w=pow(a/2) ;
    if(a%2==0)
    {
        return (w*w)%p ;
    }
    else
    {
        return (w*w*10)%p ;
    }
}
void multiply(ll rem  , ll pos1 , ll pos2)//multiply pos1 and pos2 and store in pos1
{
    for(int i=0 ; i<=mm+3 ; i++)
    {
        for(int j=0 ; j<p+3 ; j++)
        {
            arr[i][j][2]=0 ;
        }
    }
    for(int i=0 ; i<=mm ; i++)
    {
        ll reman=(i*rem)%p ;
        for(int k=0 ; k<=i ; k++)
        {
            arr[i][reman][2]=(arr[i][reman][2]+arr[k][(k*rem)%p][pos1]*arr[i-k][((i-k)*rem)%p][pos2])%mod ;
        }
    }
    for(int i=0 ; i<=mm+3 ; i++)
    {
        for(int j=0 ; j<p+3 ; j++)
        {
            arr[i][j][pos1]=arr[i][j][2] ;
        }
    }
}
void power(ll num ,ll  rem)
{
    if(num==1)
    {
        return ;
    }
    else
    {
        power(num/2 , rem) ;
        multiply( rem , 1 , 1 ) ;
        if(num%2==1)
        {
            multiply(rem ,1 , 3 ) ;
        }
    }
    return ;
}
inline void calculate(ll num , ll rem )
{
    for(int i=0 ; i<=mm+3 ; i++)
    {
        for(int j=0 ; j<=p+3 ; j++)
        {
            arr[i][j][1]=0 ;
            arr[i][j][3]=0 ;
        }
    }
    for(int i=0 ; i<10 ; i++)
    {
        arr[i][(i*rem)%p][1]=1 ;
        arr[i][(i*rem)%p][3]=1 ;
    }
    power(num , rem) ;
    return ;
}
void  multiplication(ll rem)
{
    for(int i=0 ; i<=mm ; i++)
    {
        for(int j=0;  j<p ; j++)
        {
            arr[i][j][2]=0 ;
        }
    }
    for(int i=0 ; i<=mm ; i++)
    {
        for(int j=0 ; j<p ; j++)//calculate arr[i][j][0]
        {
            for(int k1=0 ; k1<=i ; k1++)
            {
                ll p1=(k1*rem)%p , p2 ;
                if(p1<=j)
                {
                   p2=j-p1 ;
                }
                else
                {
                    p2=j+p-p1 ;
                }
                arr[i][j][2]=(arr[i][j][2]+ arr[i-k1][p2][0]*arr[k1][p1][1]  )%mod ;
 
            }
 
        }
    }
    for(int i=0 ; i<=mm ; i++)
    {
        for(int j=0;  j<p ; j++)
        {
            arr[i][j][0]=arr[i][j][2] ;
        }
    }
    return ;
}
int main()
{
    scanf("%lld %lld %lld", &n , &p , &mm) ;
    for(int i=0 ; i<105 ; i++)
    {
        check[i]=-1 ;
    }
    ll start , period ;
    for(int i=0 ; ;i++)
    {
        ll as = pow(i) ;
        if(check[as]==-1)
        {
            check[as]=i ;
            counter[as]++ ;
        }
        else
        {
            start=i ;//repetition starts from this point
            period=i-check[as] ;
            break ; // length of period
        }
    }
    ll power=(n-start)/period ;
    for(int i=start ; i<start+period ; i++)
    {
        ll as = pow(i) ;
        counter[as]+=power ;
    }
    int node1=start+power*period ;//start of phase 2
    int node2=n-1 ;//end of phase 2
    for(int i=node1 ; i<=node2 ; i++)
    {
        ll as=pow(i) ;
        counter[as]++ ;
    }
    bool bread=false ;
    for(int i=0 ; i<p ; i++)
    {
        if(counter[i]==0)
        {
            continue ;
        }
        calculate(counter[i],i) ;
        if(bread)
       {
           multiplication(i) ;
       }
       else
       {
           bread=true ;
           for(int j=0 ; j<=mm ; j++)
           {
               for(int k=0 ; k<p ; k++)
               {
                   arr[j][k][0]=arr[j][k][1] ;
               }
           }
       }
    }
    for(int i=1 ; i<=mm ; i++)
    {
        arr[i][0][0]=(arr[i][0][0]+arr[i-1][0][0])%mod ;
    }
    for(int i=0 ; i<=mm ; i++)
    {
        printf("%lld ",arr[i][0][0]) ;
    }
    return 0 ;
}