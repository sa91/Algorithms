//This code is for 588E - Duff in the Army
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI >  VVI;
typedef long long int   LL;
typedef unsigned long long int ULL;

#define pb push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))
#define LET(x,a) __typeof(a) x(a)
#define tr(container, it) for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++) 

#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
//Works for forward as well as backward iteration

#define gu getchar
#define pu putchar
#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)

#define DRT() int t; si(t); while(t--)

#define PlUSWRAP(index,n) index = (index+1)%n   //index++; if(index>=n) index=0
#define MINUSWRAP(index,n) index = (index + n -1)%n   //index--; if(index<0) index=n-1
#define ROUNDOFFINT(d) d = (int)((double)d + 0.5) //Round off d to nearest integer

#define FLUSHN while(gu()!='\n')
#define FLUSHS while(gu()!=' ')

#define TRACE

#ifdef TRACE
#define trace1(x)                cerr << #x << ": " << x << endl;
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << endl;
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << endl;
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << endl;
#define trace5(a, b, c, d, e)    cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl;
#define trace6(a, b, c, d, e, f) cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " << #f << ": " << f << endl;

#else

#define trace1(x)
#define trace2(x, y)
#define trace3(x, y, z)
#define trace4(a, b, c, d)
#define trace5(a, b, c, d, e)
#define trace6(a, b, c, d, e, f)

#endif

#define m(x) ((x)%mod);
#define mod (1e9)+7
const int  maxn=(int)(1e5)+15;

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);
typedef struct cen{
	vector <VI> vs;
	map <int,int> M;
}cnn;
cnn C[maxn];
int p[maxn];
int d[maxn];
VI G[maxn];
int sz[maxn];
int dfs(int x,int pre)
{
	sz[x]=1;
	for(auto i:G[x])
	{
		if(i!=pre)
			sz[x]+=dfs(i,x);
	}
	return sz[x];
}
int chc(set <int> &s,int v)
{
	s.insert(v);
	if(s.size()>10){
		int t=*(--s.end());
		s.erase(t);
		if(t==v)
			return 1;
	}
	return 0;
}
void dfs1(int x,int pre,cnn &Cn)
{
//	trace2(x,pre);
if(x!=pre){
int q=Cn.M[x]=Cn.vs.size();
VI v;Cn.vs.pb(v);
int r=0,i=0,j=0;
int k=Cn.M[pre];
int l=Cn.vs[k].size();
int m=C[x].vs[0].size();
	while(r<10 && j<l && i<m)
	{
		if(C[x].vs[0][i]<Cn.vs[k][j]){
			Cn.vs[q].pb(C[x].vs[0][i++]);r++;
		}
		else
			Cn.vs[q].pb(Cn.vs[k][j++]),r++;
	}
	while(r<10 && i<m)
			Cn.vs[q].pb(C[x].vs[0][i++]),r++;
	while(r<10 && j<l)
			Cn.vs[q].pb(Cn.vs[k][j++]),r++;
}
	for(auto i:G[x])
	{
		if(i!=pre && p[i]==0)	
			dfs1(i,x,Cn);
	}
}
void finc(int pc,int s,int x)
{
		for(auto i:G[x])
		{
			if(sz[i]>s/2 && p[i]==0)
			{
				sz[x]-=sz[i];
				sz[i]+=sz[x];
				finc(pc,s,i);
				return;
			}
		}
		C[x].M[x]=0;
		p[x]=pc;
		d[x]=d[pc]+1;
		dfs1(x,x,C[x]);
/*		for(auto j:C[x].M)
		{
			trace1(j.S);
			for(auto i:C[x].vs[j.S])
				trace3(i,x,j.S);
		}
	*/
		for(auto i:G[x])
			if(p[i]==0)
				finc(x,sz[i],i);
}
set <int> aux;
int arr[25];
int main()
{
	int n,m,q,u,v,a,i,j,r;
	si(n);si(m);si(q);
	for(i=1;i<=n;i++){
		VI v;C[i].vs.pb(v);
	}
	for(i=1;i<n;i++)
	{
		si(u);si(v);
		G[u].pb(v);
		G[v].pb(u);
	}
	for(i=1;i<=m;i++)
	{
		si(u);
		if(C[u].vs[0].size()<10)
			C[u].vs[0].pb(i);
	}
	int u1,v1;
	dfs(1,0);
	finc(maxn-1,n,1);
/*	for(i=1;i<=n;i++)
		printf("%d ",sz[i]);
	cout<<"\n";
	for(i=1;i<=n;i++)
		printf("%d ",p[i]);
	cout<<"\n";
	for(i=1;i<=n;i++)
		printf("%d ",d[i]);
	cout<<"\n";
	*/
	while(q--)
	{
		si(u1);si(v1),si(a);
		u=u1;v=v1;
		if(d[u]<d[v])
			swap(u,v);
		while(d[u]!=d[v])
			u=p[u];
		while(u!=v)
			u=p[u],v=p[v];
		aux.clear();
		for(auto i:C[u].vs[C[u].M[v1]])
			if(chc(aux,i))
				break;
		for(auto i:C[u].vs[C[u].M[u1]])
			if(chc(aux,i))
				break;
		int nm=min((int)aux.size(),a);
		printf("%d ",nm);
		int r=0;
		for(auto i:aux){
			printf("%d ",i);r++;
			if(r==nm)
				break;
		}
		printf("\n");
	}
	return 0;
}
