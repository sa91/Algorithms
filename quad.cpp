//solution of  qudratic equation ::https://www.codechef.com/JULY09/problems/E4///
#include<iostream>
#include<cstdio>
#include<algorithm>
#define M(x) ((x)%p)
using namespace std;
typedef long long int ll;
ll p;
ll pwm(ll v,int in)
{
	ll x=v;v=1;
	while(in>0)
	{
		if((in&1)==1)
			v=M(v*x);
		in=(in>>1);
		x=M(x*x);
	}
	return v;
}
ll sqrt(ll a)
{
	ll r=0,s=p-1,n,m,x,b,g,coff,t;
	if(pwm(a,((p-1)>>1))==p-1)
		return -1;
	while((s&1)==0){       //generating s and r////
		s=(s>>1);
		r++;
	}
	for(ll i=2;i<p;i++)
		if(pwm(i,((p-1)>>1))==p-1){        //finding n//
			n=i;
			break;
		}
	b=pwm(a,s);
	g=pwm(n,s);
	x=pwm(a,((s+1)>>1));
	while(r>0)
	{
		t=b;
		for(m=0;m<r;m++){
			if(M(t)==1)
				break;
			t=M(t*t);
		}
		if(m>0)
		{
			coff=pwm(g,(1<<(r-(m+1))));
			x=M(x*coff);
			g=M(coff*coff);
			b=M(b*g);
		}
		r=m;
	}
	return x;
}


///////////////////////////////////////////////////////////
///note do not use this variable again////
void ren(ll &a,ll &b,ll q)
{
	ll temp;
	temp=b;
	b=(a-(b*q));
	a=temp;
}
ll gcd(ll a,ll b)
{
	ll olds=1,s=0,t=1,oldt=0;
	ll q;
	while(b!=0)
	{
		q=a/b;
		ren(a,b,q);
		ren(olds,s,q);
		ren(oldt,t,q);
		oldt=M(oldt);
	}
	return oldt;
} 
int main()
{
	ll a,q,test,b,c,sqr1,sqr2,ans1,ans2,oldt;
	scanf("%lld",&test);
	while(test--)
	{
		scanf("%lld %lld %lld %lld",&a,&b,&c,&p);
		if(p==2){
			int cnt=0;
			if(M(a+b+c)==0) cnt+=2;
			if(c==0) cnt++;
			if(cnt==3) printf("2 0 1\n");
			else if(cnt==1) printf("1 0\n");
			else if(cnt==2) printf("1 1\n");
			else printf("0\n ");
			continue;
		}
		q=M(M(b*b)-M(4*a*c)+p);
		if(b==0 && c==0){
			printf("1 0\n");
			continue;
		}
		if(q==0)
			sqr1=0;
		else
			sqr1=sqrt(q);
		sqr2=p-sqr1;
		if(sqr1==-1){
			printf("0\n");
			continue;
		}
		//		printf("%lld %lld\n",sqr1,sqr2);
		oldt=gcd(p,M(2*a));
		if(oldt<0)
			oldt+=p*((oldt/p)+1);
		oldt=M(oldt);
		//		printf("%lld\n",oldt);
		ans1=M(oldt*M(sqr1+p-b));
		ans2=M(oldt*M(sqr2+p-b));
		if(ans1<ans2)
			printf("2 %lld %lld\n",ans1,ans2);	
		else if(ans2<ans1)
			printf("2 %lld %lld\n",ans2,ans1);	
		else
			printf("1 %lld\n",ans1);	

	}
	return 0;
}
