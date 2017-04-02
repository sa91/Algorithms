#include<stdio.h>
int Heap[1000006],size;
// 1 indexed Max-Heap 
void swap(int i){
  //swap i and i/2 element (i.e swap child with parent)
	int t;
  t=Heap[i];
	Heap[i]=Heap[(i>>1)];
	Heap[(i>>1)]=t;
}
void push(int index){
  int i=index;
	while( i>1 && Heap[(i>>1)]<Heap[i]){
		swap(i);  //swap child with parent
		i=(i>>1);
	}
}
int top(){
  return Heap[1];
}
void rem(int x,int size)  
{
  if(x>size) return;
  //copying the last element on x
  Heap[x]=Heap[size];
  // decreasing size
  --size;
  // cheacking if parent is valid
  push(x); 
	// checking if child is valid
  int i=2*x;  //index of child
	while(i<=size){
		if(i+1<=size && Heap[i+1]>Heap[i])
			i++;
		if(Heap[i]>Heap[(i>>1)])
			swap(i); //swap child with parent
		else
			break;
		i=(i<<1);
	}
}
int main()
{
  int n;scanf("%d",&n);
  size=0;
  while(n--)
  {
    int t;scanf("%d",&t);
    if(t==1)
    {
      int v;scanf("%d",&v);
      Heap[++size] = v;
      push(size);
    }
    else if(t==2)
    {
      int v;scanf("%d",&v);
      rem(v,size);
    }
    else {
      printf("%d\n",top());
    }
  }
  return 0;
}
