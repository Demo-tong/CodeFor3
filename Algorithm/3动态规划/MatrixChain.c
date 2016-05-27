#include<stdio.h>
void MatrixChain(int p[100], int n, int m[100][100], int s[100][100]){
	for(int i=1; i<=n; i++)	m[i][i] = 0;
	for(int r=2; r<=n; r++)
		for(int i=1; i<=n-r+1; i++){
			int j=i+r-1;
			m[i][j] = m[i+1][j]+p[i-1]*p[i]*[j];
			s[i][j] = i;
			for(int k=i+1; k<j; k++){
			int t = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
			if(t < m[i][j]){
					m[i][j] = t;
					s[i][j] = k;
			}
		}
	printf("min:%d", t);
	
}
void Traceback(int i, int j, int s[][]){
	if(i == j)	return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j]+1, j, s);
	printf("Multiply A%d,%d", i, s[i][j]);
	printf("and A%d,%d\n", s[i][j]+1, j);			}
void main(){
	int n;
	printf("请输入参与连乘的矩阵的个数：");
	scanf("%d", &n);

	int Ai[n], Aj[n], m[n][n], s[n][n];
	for(int i=1; i<n+1; i++){
		printf("A%的维数：", i);
		scanf("%d %d", Ai, Aj);
	}
	MatrixChain(Ai[1], n, m, s);
	Traceback(1, n, s);
}
