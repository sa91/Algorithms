#include<stdio.h>
////////////incresing seq//////////////////

int lst[100005]={0};///////last of each list/////////
int list[100005]; ////////list iun which icresing seq has to be found///////
int bns(int r,int k)
{
	int l=0,m;
	while(l<r){
		m=(l+r)/2;
		if(lst[m]<k)
			l=m+1;
		else
			r=m;
	}
	if(lst[l]<k)
		l++;
	return l;
}
int n;
int fincsq()////here returns length of largest inc. sequence (lar)///
{
	int k,lar,i;
	lar=0;
	for(i=0;i<n;i++){
		k=bns(lar,list[i]);
		lst[k]=list[i];
		if(k>lar)
			lar++;
	}
	return lar;
}
/////////////done////////////////////////
int main()
{
	int i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",&list[i]);
	printf("%d\n",fincsq());
	return 0;
}

