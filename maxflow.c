#include<stdio.h>
#include<string.h>
void print(int *a,int n);
void pt(int n);
void prt(int a[][205],int n);

//////////////////MAXFLOW//////////////////////////////////////
#define inf 305
int sink; 
//note: 
//source =0 && sink you have to set;
//cap[i][j]: capacity of flow from i to j.
	typedef struct n {
		int ver;
		int mfw;
		int from;
	}node;
node a[205];
int wfrm[205],cap[205][205]={0},v[205],p[205];
void swap(int i)
{
	node t;
	p[a[(i>>1)].ver]=i;
	p[a[i].ver]=(i>>1);
	t=a[i];
	a[i]=a[(i>>1)];
	a[(i>>1)]=t;
}
void push(int i)
{
	while( i>1 && a[(i>>1)].mfw<a[i].mfw)
	{
		swap(i);
		i=(i>>1);
	}
}
void top(int size)
{
	int i=2;
	while(i<size)
	{
		if(i+1<size && a[i+1].mfw>a[i].mfw)
			i++;
		if(a[i].mfw>a[(i>>1)].mfw)
			swap(i);
		else
			break;
		i=(i<<1);
	}
}
int pfs(int size)
{
	int j=2;
	int cver,mfw,from,newmflw,i,prev,pcap;
	a[1].ver=0;
	for(i=0;i<=size;i++){
		v[i]=0;
		p[i]=0;
	}
	a[1].mfw=inf;
	a[1].from=-1;
	pcap=0;
	while(j>0)
	{
		cver=a[1].ver;
		wfrm[a[1].ver]=a[1].from;
		mfw=a[1].mfw;
		v[a[1].ver]=1;
		a[1]=a[j-1];
		p[a[j-1].ver]=1;
		j--;
		top(j);
		//	printf("cver:%d\n",cver);
		if(cver==sink)
		{
			pcap=mfw;
			break;
		}
		for(i=0;i<=size;i++)
		{
			if(cap[cver][i]>0 && v[i]!=1)
			{
				if(mfw<cap[cver][i])
					newmflw=mfw;
				else
					newmflw=cap[cver][i];
				if(p[i]!=0 && newmflw>a[p[i]].mfw)
				{
					a[p[i]].mfw=newmflw;
					a[p[i]].from=cver;
					push(p[i]);
				}
				else if(p[i]==0)
				{
					a[j].ver=i;
					a[j].mfw=newmflw;
					a[j].from=cver;
					p[i]=j;
					push(j);
					j++;
				}
			}
		}
		//	printf("heap\n");
		//	pt(a,j);
		//		printf("pos\n");
		//		print(p,size+1);
	}
	i=sink;
	//	printf("wfrm\n");
	//	print(wfrm,size+1);
	if(pcap>0)
	{
		while(wfrm[i]!=-1)
		{
			prev=wfrm[i];
			cap[prev][i]-=pcap;
			cap[i][prev]+=pcap;
			i=prev;
		}
	}
	//	prt(cap,size+1);
	return pcap;
}
///////////////////////////////////////END///////////////////////

////printfunc///////////////////:-
void print(int *a,int n){
	int i;
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	printf("\n");
}
void pt(int n){
	int i;
	for(i=0;i<n;i++)
		printf("%d:%d ",a[i].ver,a[i].mfw);
	printf("\n");
	printf("\n");
}
void prt(int a[][205],int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	printf("\n");
}
int main()
{
	int i,j,sum1=0,sum2=0,n,m,p,q,c,sum;
	scanf("%d %d",&n,&m);
	sink=(2*n)+1;
	for(i=1;i<n+1;i++){
		scanf("%d",&cap[0][i]);
		cap[i][n+i]=inf;
		sum1+=cap[0][i];
	}
	for(j=n+1;j<=(2*n);j++){
		scanf("%d",&cap[j][sink]);
		sum2+=cap[j][sink];
	}
	for(i=1;i<=m;i++)
	{
		scanf("%d %d",&p,&q);
		cap[p][n+q]=inf;
		cap[q][n+p]=inf;
	}
	if(sum1!=sum2){
		printf("NO\n");
		return 0;
	}
	sum=0;
	while((c=pfs(sink))!=0)
	{	sum+=c;
	}
	if(sum==sum1)
	{		printf("YES\n");
		for(j=1;j<=n;j++){
			for(i=n+1;i<=(2*n);i++)
				printf("%d ",cap[i][j]);
			printf("\n");		
		}
	}
	else
		printf("NO\n");

	return 0;
}
