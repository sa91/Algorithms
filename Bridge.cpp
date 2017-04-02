//Kyokai no Kanata //
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> II;
typedef vector<II> VII;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef long long int LL;

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
#define TRACE

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
#define H(i,j) (((i)*(n+1))+(j))
#define EV(v)  (((v)/(n+1))*((v)%(n+1)))
const int N=int(2e6);
VI G[N];
int U[N],V[N],arr[N],vis[N],T=0,FB[2][N];
bool isbridge[N];
char buf[10];
int adj(int u,int e){
  return U[e]==u?V[e]:U[e];
}
void dfs(int u,int edge)
{
  vis[u]=1; arr[u]=++T;
  int low=arr[u];
  for(auto e:G[u])
  {
    if(e==edge) continue;
    int v=adj(u,e);
    if(!vis[v]) dfs(v,e);
    low=min(low,arr[v]);
  }
  if(low==arr[u] && edge!=-1) isbridge[edge]=true;
  arr[u]=low;
  return ;
}
int main()
{
  int n,qv,qf,w,dw,b,db;si(n);si(qv);si(qf);
  int ED=0,i,j;
  U[ED]=H(0,0);V[ED]=H(n,n);
  G[H(0,0)].PB(ED);
  G[H(n,n)].PB(ED);
  ED++;
  for(i=0;i<qv;i++)
  {
    si(b);si(w);si(db);si(dw);
    U[ED]=H(b,w);V[ED]=H(b+db,w+dw);
    G[U[ED]].PB(ED);
    G[V[ED]].PB(ED);
    ED++;
  }
  for(i=0;i<qf;i++)
  {
      scanf("%d %d %s",&b,&w,buf);
      if(buf[0]=='B') FB[0][H(b,w)]=1;
      else FB[1][H(b,w)]=1;
  }
  for(i=0;i<=n;i++)
    for(j=0;j<=n;j++)
    {
      if(!FB[1][H(i,j)] && j<n){
        U[ED]=H(i,j);V[ED]=H(i,j+1);
        G[U[ED]].PB(ED);
        G[V[ED]].PB(ED);
        ED++;
      }
      if(!FB[0][H(i,j)] && i<n){
        U[ED]=H(i,j);V[ED]=H(i+1,j);
        G[U[ED]].PB(ED);
        G[V[ED]].PB(ED);
        ED++;
      }
    }
 // for(i=0;i<ED;i++)
 //   printf("%d %d\n",U[i],V[i]);
  int ans=-1;
  for(i=0;i<=n;i++)
    for(j=0;j<=n;j++)
      if(!vis[H(i,j)])
      T=0,dfs(H(i,j),-1);
  for(i=0;i<ED;i++)
    if(isbridge[i]){
//      trace(U[i],V[i]);
      ans=max(ans,EV(V[i])+EV(U[i]));
    }
  dout(ans);
  return 0;
}

