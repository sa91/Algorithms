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
const int N=int(1e6);
int  LCST[4*N],LSZ[4*N],LCED[4*N];
int SZ[N],POS[N],CED[N],HV[N],CST[N],P[N];
VI G[N];
int T;
bool DONE[N];
/////In hld  the key concept is to notice dfss////
void dfs(int x,int pre)
{
  SZ[x]=1;P[x]=pre;
	for(auto i:G[x] )
		if(i!=pre){
			dfs(i,x);
      SZ[x]+=SZ[i];
			if(SZ[i]>SZ[HV[x]])   
				HV[x]=i;	
		}	
}
void dfs2(int x,int pre)
{
  trace(x,pre);
	//starting postion of subtree of x//
  POS[x]=T++;CST[x]=x;
	while(HV[x]){
    trace(HV[x],x);
    CST[HV[x]]=CST[x];
    x=HV[x];
    POS[x]=T++;
  }
  CED[x]=x;
  while(x!=CST[x]){
    CED[P[x]]=CED[x];x=P[x];
	  for(auto i:G[x])
		  if(i!=P[x] && i!=HV[x])
			  dfs2(i,x);
  }
}
/// for Lazy  updates on *A ///
void modify(int *A,int k,int l,int r)
{
	if(l!=r){
    A[2*k]+=A[k];
    A[(2*k)+1]+=A[k];
    A[k]=0;
  }
}
void updt(int *A,int k,int l,int r,int qb,int qe,int ch) 
{
	int m=((l+r)/2);
	if(A[k]) modify(A,k,l,r);
	if(qe<l || qb>r) return ;
	if(qb<=l && r<=qe){
		A[k]+=ch;
		return ;
	}
	updt(A,(2*k),l,m,qb,qe,ch);
  updt(A,((2*k)+1),m+1,r,qb,qe,ch);
}
int qry(int *A,int k,int l,int r,int q)
{
  int m=(l+r)/2;
  if(l==r) return A[k];
  if(A[k]) modify(A,k,l,r);
  if(q>m) return qry(A,(2*k)+1,m+1,r,q);
  else return qry(A,(2*k),l,m,q);
}
int solve(int A,int n)
{
  int CEDA=qry(LCED,1,1,n,POS[A]);
  int CSTA=qry(LCST,1,1,n,POS[A]);
  if(POS[CEDA]>POS[A]){
    updt(LCST,1,1,n,POS[A]+1,POS[CEDA],HV[A]-CSTA);
    updt(LCED,1,1,n,POS[CSTA],POS[A],P[A]-CEDA);
  }
  int szA=qry(LSZ,1,1,n,POS[A]);
  trace(szA,A,POS[A]);
	while(1)
  {
    CSTA=qry(LCST,1,1,n,POS[A]);
    trace(CSTA);
    updt(LSZ,1,1,n,POS[CSTA],POS[A],-szA);
    A=CSTA;
    if(DONE[P[A]]) break;
    A=P[A];
	}
  int ret=qry(LSZ,1,1,n,POS[A])+szA;
  return ret;
}
int main()
{
  DONE[0]=1;
	int a,b,n,i,q,v;si(n);
	for(i=1;i<n;i++)
	{
		scanf("%d %d",&a,&b);
		G[a].PB(b);
		G[b].PB(a);
	}
  T=1;
	dfs(1,0);
	dfs2(1,0);
  for(i=1;i<=n;i++)
  {
    updt(LSZ,1,1,n,POS[i],POS[i],SZ[i]);
    updt(LCED,1,1,n,POS[i],POS[i],CED[i]);
    updt(LCST,1,1,n,POS[i],POS[i],CST[i]);
    trace(i,POS[i],SZ[i],CED[i],CST[i]);
  }
	scanf("%d",&q);
  int ans=0;
	for(i=0;i<q;i++){
		si(v);
    v=ans^v;
    ans=solve(v,n);
    DONE[v]=1;
    dout(ans);
	}
	return 0;
}

