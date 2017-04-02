#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef long long int ll; 
void print( ll *a,int n);
//////////////////suffix array sort//////////////////
#define maxn 5005
char str[5005];
int rank[maxn],pos[maxn],cnt[maxn],bh[maxn],b2h[maxn],next[maxn];
int cmp(const void *a,const void *b){
	const int* x=a;const  int* y=b;
	return (str[*x]-str[*y]);
}
int n;
void suffixsort()
{
	int i,j,k,h,pst,t;
	for(i=0;i<n;i++)
	{
		pos[i]=i;
		bh[i]=0;
		b2h[i]=0;
		cnt[i]=0;
	}
	qsort(pos,n,sizeof(int),cmp);
	bh[0]=1;
	for(i=1;i<n;i++)
		if(str[pos[i-1]]!=str[pos[i]])
			bh[i]=1;
	for(i=0;i<n;i++)
		rank[pos[i]]=i;
	for(h=1;h<n;h=(h<<1))
	{
		i=0,pst=0,j=0;
		for(i=0;i<n;i++)
		{
			if(bh[i]==1)
			{
				pst=i;
				next[j++]=i;
				b2h[i]=0;
			}
			rank[pos[i]]=pst;
			cnt[i]=0;
		}
		next[j++]=n;
		b2h[rank[n-h]]=1;
		cnt[rank[n-h]]++;
		int l=1;
		for(i=0;i<n;i=j)
		{
			for(j=i;j<next[l];j++)
			{
				t=pos[j]-h;
				if(t>=0)
				{
					rank[t]=(rank[t]+(cnt[rank[t]]++));
					b2h[rank[t]]=1;
				}
			}
			for(j=i;j<next[l];j++)
			{
				t=pos[j]-h;
				if(t>=0 && b2h[rank[t]]==1){
					for(k=rank[t]+1;!bh[k] && b2h[k]==1;b2h[k++]=0);
				}
			}
			l++;			
		}
		//	print(rank,n+1);
		//		print(b2h,n+1);
		for(i=0;i<n;i++){
			pos[rank[i]]=i;
			bh[i]=bh[i]|b2h[i];
		}
	}
	for(i=0;i<n;i++)
		rank[pos[i]]=i;
	return;
}
////////////////////////suffixsortdone/////////////////////

//////////////////lcparray///////////////////////
ll lcp[maxn];
void lcpi()
{
	///lcp[i]=lcp(Ai,Ai-1)/////////
	int i,j,h=0;
	for(i=0;i<n;i++)
	{
		if(rank[i]>0)
		{
			j=pos[rank[i]-1];
			while(i+h<n && j+h<n && str[i+h]==str[j+h])
				h++;
			lcp[rank[i]]=h;
			if(h>0)
				h--;
		}
	}
}
////////////////lcpcaldone/////////////////////////////
int main()
{
	int i;
	scanf("%d",&n);
		scanf("%s",str);
		suffixsort();
		for(i=0;i<n+1;i++)
			lcp[i]=0;
		lcpi();
		for(i=0;i<n;i++)
			printf("%s\n",str+pos[i]);
		print(lcp,n+1);
	return 0;
}
///////////////printfunc/////////////////////////////////
void print(ll *a,int n)
{ int i;
	for(i=0;i<n;i++)
		printf("%lld ",a[i]);
	printf("\n");
}

