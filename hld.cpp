//this is the code of epic tree(Hacker rank epiccode june challenge) using HLD(IMPORTANTLY) with segtree///
/////First HLD code///////////

//#include<std/c++.h>
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#define maxn 100064
#define mod 10009
#define pb push_back
#define M(x) ((x)%mod)
//vector iterator def///
using namespace std;
typedef struct t{
	int lz,a,b;
}tii;
tii st[4*maxn];
int sz[maxn]={0},S[maxn],E[maxn],hv[maxn]={0},dad[maxn],p[maxn],d[maxn],t[maxn];
vector <int> g[maxn];
int n,T,s;
void prt(int *a,int n)
{
	int i;
	for( i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
void print(int n)
{
	for(int i=1;i<30;i++)
			printf("%d.) lz:%d a:%d b:%d\n",i,st[i].lz,st[i].a,st[i].b);
		printf("\n");
}
/////here hld is the key concept notice dfss////
void dfs(int x,int pre)
{
	sz[x]=1;
	int a;
	vector <int> :: iterator it;
	 for( it = g[x].begin(); it != g[x].end(); ++it )
	 {
		a=*it;
//		printf("%d\n",a);
		if(a!=pre){
			p[a]=x;
			d[a]=d[x]+1;
			dfs(a,x);
			sz[x]+=sz[a];
			if(sz[a]>sz[hv[x]])   //sz[0]=0 imp//
				hv[x]=a;	
		}
	}
}
void dfs2(int x,int pre)
{
	t[s]=(t[s-1]+sz[x])%mod;
	S[x]=s++;  //starting postion of tree //
	if(hv[x]!=0){
		dad[hv[x]]=dad[x];
		dfs2(hv[x],x);
	}
	int a;
	vector <int> :: iterator it;
	for(it=g[x].begin();it!=g[x].end();it++){
		a=*it;
		if(a!=pre && a!=hv[x]){
			dad[a]=a;
			dfs2(a,x);
		}
	}
	E[x]=s;		
}
int LCA(int a,int b)
{
	while(dad[a]!=dad[b]){
		if(d[dad[a]]>d[dad[b]])
			a=p[dad[a]];
		else
			b=p[dad[b]];
	}
	return d[a]<d[b]? a : b;
}
void up1(int k,int l,int r)
{
	st[k].a=M(st[k].a+M(((r-l)+1)*st[k].lz));
	st[k].b=M(st[k].b+M((t[r]-t[l-1]+mod)*st[k].lz));
	if(k<=2*n){
		st[(2*k)].lz=M(st[(2*k)].lz+st[k].lz);
		st[(2*k)+1].lz=M(st[(2*k)+1].lz+st[k].lz);
	}
	st[k].lz=0;
}
void upd(int k,int l,int r,int qb,int qe)
{
	int m=((l+r)/2);
	if(st[k].lz!=0)
	 up1(k,l,r);
	if(qe<l || qb>r) 
		return ;
	if(qb<=l && r<=qe){
		st[k].lz=M(st[k].lz+T);
		up1(k,l,r);
		return ;
	}
	upd((2*k),l,m,qb,qe);upd(((2*k)+1),m+1,r,qb,qe);
	st[k].a=M(st[(2*k)].a+st[((2*k)+1)].a);
	st[k].b=M(st[(2*k)].b+st[((2*k)+1)].b);
}
void callupd(int lca,int a)
{
	while(dad[lca]!=dad[a]){
		upd(1,1,n,S[dad[a]],S[a]);
		a=p[dad[a]];	
	}
	upd(1,1,n,S[lca],S[a]);
}
int sum(int k,int l,int r,int qb,int qe,int ch)
{
	int m=((l+r)/2);
	if(st[k].lz!=0)
		up1(k,l,r);
	if(qe<l || qb>r)
		return 0;
	if(qb<=l  && qe>=r){
		if(ch==1)
			return st[k].a;
		return st[k].b;
	}
	return M(sum((2*k),l,m,qb,qe,ch)+sum(((2*k)+1),m+1,r,qb,qe,ch));
}
int fnsum(int lca,int a)
{
	int s=0;
	while(dad[lca]!=dad[a]){
		s=M(s+sum(1,1,n,S[dad[a]],S[a],1));
		a=p[dad[a]];	
	}
	s=M(s+sum(1,1,n,S[lca],S[a],1));
	return s;
}
int main()
{
	int a,b,c,i,q,j,ans;
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		scanf("%d %d",&a,&b);
		g[a].pb(b);
		g[b].pb(a);
	}
	d[1]=0;
	dfs(1,-1);
	dad[1]=1;
	s=1;
	dfs2(1,-1);
	scanf("%d",&q);
	for(i=0;i<q;i++)
	{
		scanf("%d %d",&j,&a);
		if(j==1)
		{
			scanf("%d %d",&b,&T);
			c=LCA(a,b);
			callupd(c,a);
			callupd(c,b);
			T=mod-T;
			upd(1,1,n,S[c],S[c]);
		}
		else{
			if(a!=1)
			ans=M(fnsum(1,p[a])*M(sz[a]));
			else
				ans=0;
			ans=M(ans+sum(1,1,n,S[a],E[a]-1,2));
			printf("%d\n",ans);
		}
	}
	return 0;
}
