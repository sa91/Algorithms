//Snorlax//
#include<bits/stdc++.h>

using namespace std;
typedef long long int LL;
typedef pair<LL,LL> II;
typedef vector<II> VII;
typedef vector<int> VI;
typedef vector< VI > VVI;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

//#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr<<name<<" : "<<arg1<<endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
	const char* comma=strchr(names+1,',');
	cerr.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
///---- convex full------//
const int N=int(1e5)+50;
VII P;	    
II pivot;    			// II=pair<LL,LL>
II CH1[N],CH2[N];
inline void cmp_points(II &a,II b)
{
	if(a.S==b.S && a.F>b.F) {
		a=b;
		return ;
	}
	if(a.S>b.S) a=b;
}
int quadrant(II a)
{
	if(a.F>=0 && a.S>= 0)  return 1;
	if(a.F<0 && a.S>= 0)  return 2;
	if(a.F<0 && a.S<0)  	return 3;
	if(a.F>=0 && a.S<0)  return 4;
	return 0;
}
bool cmp(II a,II b){
	if(a==pivot) return 1;
	if(b==pivot) return 0;
	II AA=MP(a.F-pivot.F,a.S-pivot.S);
	II BB=MP(b.F-pivot.F,b.S-pivot.S);
	if(quadrant(AA)==quadrant(BB)) 
		return (((a.S-pivot.S)*(b.F-pivot.F))<((b.S-pivot.S)*(a.F-pivot.F)));
	return (quadrant(AA)<quadrant(BB));
}
LL crossproduct(II a,II b){
	return ((a.F*b.S)-(a.S*b.F));
}
int convexhull(VII &P,II *CH)     //returns size of convex full;
{
	int sz=P.size(),i;
	pivot=P[0];
	for(i=0;i<sz;i++) cmp_points(pivot,P[i]);
	sort(ALL(P),cmp);
	int j=2;
	CH[0]=P[0];CH[1]=P[1];
	for(i=2;i<sz;i++)
	{
		while(j>=2) {
			II v1=MP(CH[j-1].F-CH[j-2].F,CH[j-1].S-CH[j-2].S);
			II v2=MP(P[i].F-CH[j-1].F,P[i].S-CH[j-1].S);
			if(crossproduct(v1,v2)>0) break;
			j--;
		}CH[j++]=P[i];
	}
	return j;
}
///-----convex complete----///
int check(II a,II b,II c)
{
	if(a.F==c.F){
		if(b.F==a.F) return 1;
		return 0;
	}
	if(a.S==c.S){
		if(b.S==a.S) return 1;
		return 0;
	}
	if((c.F-a.F)*(b.S-a.S)==(c.S-a.S)*(b.F-a.F)) return 1;
	return 0;
}
int main()
{
	int i,j,n,m,b;si(m);
	for(i=0;i<m;i++){
		II a;sll(a.F);sll(a.S);
		P.PB(a);
	}
	b=convexhull(P,CH2);
	for(i=0;i<b;i++)
	{
    printf("%d %d\n",CH2[i].F,CH2[i].S);
	}
  return 0;
}
