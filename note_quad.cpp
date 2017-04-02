//solves a^2=x(mod p)
LL root_of_x(LL x) 
{
	LL r=0,s=p-1,n,m,x,b,g,coff,t;
	if(powermod(a,((p-1)>>1),p)==p-1)//calcute (a^((p-1)/2))%p;
		return -1;
	while((s&1)==0)       //generating s and r////
		s=(s>>1);r++; 
	for(LL i=2;i<p;i++)
		if(powermod(i,((p-1)>>1))==p-1){        //finding n//
			n=i;break;	}
	b=powermod(a,s,p);g=powermod(n,s,p);x=pwm(a,((s+1)>>1));
	while(r>0)
	{
		t=b;
		for(m=0;m<r;m++){
			if(M(t)==1) break;
			t=M(t*t);}
		if(m>0){
			coff=powermod(g,(1<<(r-(m+1))));	x=M(x*coff);
			g=M(coff*coff);b=M(b*g);
		}r=m;
	}	return x;
}
//NOTE :return -1 ,root of x do not exist
