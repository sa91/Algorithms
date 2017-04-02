#include<stdio.h>
#define maxn 200004
#define mod 1000000007
typedef long long int ll;
ll  lazy[5*maxn]={0};
ll seg[5*maxn]={0};
int val[maxn]={0};
int n;
         ////////////////variable part od seg tree////////////////
#define trv 0//trv is the trivial value on empty selection in the given query//

/////////////////function of seg tree////////////////
ll func(ll p,ll q){
	ll r=(p+q)%mod;
	return r;
}
	 //////modification related(case specific)/////////
/////////////////structure of modification information/////////
typedef struct md{
	ll A,B,C,i2,i,i0;
}modifications;
modifications m[5*maxn];

////////initialise modification array m//////////
ll init(int k,ll l,ll r ){
	m[k].A=0;
	m[k].B=0;
	m[k].C=0;
	m[k].i=((((r-l)+1)*(l+r))/2)%mod;;
	m[k].i0=(r-l)+1;
	if(l<r)
		m[k].i2=func(init(2*k,l,(l+r)/2),init((2*k)+1,((l+r)/2)+1,r));
	else
		m[k].i2=(l*l)%mod;
	return m[k].i2;		
}

/////modify function holds , how to modify value at the pos//////

ll B,C;//required for modification(case specific)///
void modify(int k,int lz)
{
	if(lz==0)						//////lz indicats whwther its lazy update or normal update////
	{
		m[k].A=m[k].A+1;
		m[k].B=(m[k].B+B)%mod;
		m[k].C=(m[k].C+C)%mod;	
	}
	seg[k]=(((((seg[k]+((m[k].i2*m[k].A)%mod))%mod)+((m[k].i*m[k].B)%mod))%mod)+((m[k].i0*m[k].C)%mod))%mod;
	if((2*k)+1<=5*n)
	{
	lazy[(2*k)]=1;
	lazy[(2*k)+1]=1;
	m[2*k].A=(m[2*k].A+m[k].A)%mod;;
	m[(2*k)+1].A=(m[(2*k)+1].A+m[k].A)%mod;;
	m[2*k].B=(m[2*k].B+m[k].B)%mod;;
	m[(2*k)+1].B=(m[(2*k)+1].B+m[k].B)%mod;;
	m[2*k].C=(m[2*k].C+m[k].C)%mod;;
	m[(2*k)+1].C=(m[(2*k)+1].C+m[k].C)%mod;;
	}
	m[k].A=0;
	m[k].B=0;
	m[k].C=0;
} 
  //////////////////modification over/////////////////////////
        ///////////////////variable part over ////////////////////////

     ////////////////////////working (FIXED)//////////////////////
/////crt creates  seg tree///////////////////
ll crt(int k,int l,int r)
{
	if(l==r)
		return seg[k]=val[l];
	int m=((l+r)>>1);
	seg[k]=func(crt((2*k),l,m),crt((2*k)+1,m+1,r));
	return seg[k];
}

////////updt updates the range in seg tree///////
ll updt(int k,int l,int r,ll qb,ll qe)
{
	int m=(l+r)/2;
	if(lazy[k]==1)
	{
		lazy[k]=0;
		modify(k,1);
	}
	if(qb>r||qe<l)
		return seg[k];
	if(qb<=l && qe>=r)
		modify(k,0);
	else	
		seg[k]=func(updt(2*k,l,m,qb,qe),updt((2*k)+1,m+1,r,qb,qe));
	return seg[k];
}

/////qry return anser of the query///////////
ll qry(int k,int l,int r,ll qb,ll qe)
{
	int m=(l+r)/2;
	if(lazy[k]==1)
	{
		lazy[k]=0;
		modify(k,1);
	}
	if(qb>r||qe<l)
		return trv;
	if(qb<=l && qe>=r)
		return seg[k];
	else
		return func(qry((2*k),l,m,qb,qe),qry((2*k)+1,m+1,r,qb,qe));
}

int main()
{
	ll c,x,y;
	int i,q;
	scanf("%d %d",&n,&q);
	for(i=1;i<=n;i++)
		val[i]=0;
	crt(1,1,n);
	init(1,1,n);
	for(i=0;i<q;i++)
	{
		scanf("%lld %lld %lld",&c,&x,&y); 
		////c==1:-update else query ////
		if(c==1)
		{
			B=((3+mod)-(2*x))%mod;	///B,C are case specific///////
			C=((x-1)*(x-2))%mod;
			updt(1,1,n,x,y);
		}
		else
			{
			printf("%lld\n",qry(1,1,n,x,y));
			}
	}
	return 0;
}
