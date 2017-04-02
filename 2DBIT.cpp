//solution for morgan stanley 2016 Matrix Inversions//
#include<bits/stdc++.h>
using namespace std;
#define N 1006
#define F first
#define S second
int BIT[N][N]; 
void update(int x, int y, int val,int n)
{
  int tmp;
    for (; x <= n; x += (x & -x))
    {
      tmp=y;
        for (; tmp <= n; tmp += (tmp & -tmp))
            BIT[x][tmp] += val;
    }
    return;
}
 
// A function to get sum from (0, 0) to (x, y)
int getSum(int x, int y)
{
    int sum = 0;
    int tmp; 
    for(; x > 0; x -= x&-x)
    {
       tmp=y;
        for(; tmp > 0; tmp -= tmp&-tmp)
            sum += BIT[x][tmp];
    }
    return sum;
}
int qry(int x1,int y1,int x2,int y2)
{
        int ans = getSum( x2, y2)-getSum(x2, y1-1)-
                  getSum( x1-1, y2)+getSum(x1-1, y1-1); 
       return ans;
}
pair <int,pair<int,int>> A[N*N];
 int main()
{
  int n,p=0;scanf("%d",&n);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
      scanf("%d",&A[p].F);A[p].S.F=i;A[p].S.S=j;
      p++;
    }
  sort(A,A+p);
  long long ANS=0;
  for(int i=0;i<p;i++)
  {
  //  cout<<A[i].F<<endl;
    ANS+=qry(A[i].S.F,A[i].S.S,n,n);
    update(A[i].S.F,A[i].S.S,1,n);
 // cout<<ANS<<endl;
  }
  cout<<ANS<<endl;
  return 0;
} 

