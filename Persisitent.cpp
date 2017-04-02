//Satyam Pandey :: Kamehameha //
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
#define new_node(A,C,LP,LI,RI) A.CNT=C, A.LUP=LP A.LID=LI, A.RID=RI

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
const int N=int(3e7);
int IDX=0;
int A[200005];
II SA[200005];
int M[200005];
map<int,int> RM;
int HEAD[200005];
int HH[200005];
struct node{
  int CNT,LUP,LID,RID;
  node(int C=0,int LP=-1,int LI=-1,int RI=-1): 
    CNT(C),LUP(LP),LID(LI),RID(RI){}
};
node NODES[N];
void insrt(int H,int L,int R,int POS) //H=new head number;
{
  //trace(H,L,R,POS,A[POS]);
  if(NODES[H].LUP != A[POS]){
    NODES[H].LUP=A[POS];
    NODES[H].CNT+=1;
  }
  if(L==R) return ;
  int M=(L+R)/2;
  if(POS>M)
  {
    if(NODES[H].RID!=-1) NODES[IDX+1]=NODES[NODES[H].RID];
    NODES[H].RID=++IDX;
    insrt(NODES[H].RID,M+1,R,POS);
  }
  else
  {
    if(NODES[H].LID!=-1) NODES[IDX+1]=NODES[NODES[H].LID];
    NODES[H].LID=++IDX;
    insrt(NODES[H].LID,L,M,POS);
  }
}
int qry(int H,int l,int r,int qb,int qe)
{
  //trace(H,l,r,qb,qe);
  if(H==-1) return 0;
  int m=(l+r)/2;
  if(qb>r||qe<l) return 0;
  if(qb<=l && qe>=r)
    return NODES[H].CNT;
  else
    return (qry(NODES[H].LID,l,m,qb,qe)+qry(NODES[H].RID,m+1,r,qb,qe));
}
int query(int L,int R,int qb,int qe,int k,int n)
{
  //trace(L,R,qb,qe,k,n);
  if(L==R) return L;
  int M=(L+R)/2;
  int BMID=qry(HEAD[M],1,n,qb,qe);
  int BST=qry(HEAD[L-1],1,n,qb,qe);
  int BEND=qry(HEAD[R],1,n,qb,qe); 
 // trace(BMID,BST,BEND);
  if(BEND-BST<k) return 0;
  if(BMID-BST>=k)
    return query(L,M,qb,qe,k,n);
  else 
    return query(M+1,R,qb,qe,k-(BMID-BST),n);
}
int main()
{
  int n,q,i;
  si(n);si(q);
  IDX=0;
//  trace(NODES[100].CNT,NODES[100].LUP,NODES[100].LID,NODES[100].RID);
  for(i=1;i<=n;i++) {
    si(A[i]);
    SA[i]=MP(A[i],i);
  }
  sort(SA+1,SA+(n+1));
  int MXCC=0;
  for(i=1;i<=n;)
  {
    M[++MXCC]=SA[i].F;
    RM[SA[i].F]=MXCC;
    while(i<=n && SA[i].F==M[MXCC]) i++;
  }
  HEAD[0]=-1,HH[0]=0,M[0]=-1;
  for(i=1;i<=n;i++)
  {
    NODES[++IDX]=NODES[HH[i-1]];
    HH[i]=IDX;
    HEAD[RM[SA[i].F]]=IDX;
    insrt(HH[i],1,n,SA[i].S);
  }
  int ans=0,v;
  LL a,b,c,d,l,r,k;
  while(q--)
  {
    sll(a);sll(b);sll(c);sll(d);sll(k);
    l=((a*max(ans,0))+b)%n+1;
    r=((c*max(ans,0))+d)%n+1;
    if(l>r) swap(l,r);
    v=query(1,MXCC,l,r,k,n);
    ans=M[v];
    dout(ans);
  }
  return 0;
}
