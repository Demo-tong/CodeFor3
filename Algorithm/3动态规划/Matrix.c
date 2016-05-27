//������˵�����ֵ
#include <stdio.h>
#define n 4
//�������˺���
void MatrixChain(int *p,int m[n+1][n+1],int s[n+1][n+1])	//m�����¼��С�˵Ĵ�����s�����¼�Ͽ���λ��
{
	int r,i,j,t,k;
	for(i=0;i<=n;i++)
		for(j=0;j<=i;j++)
		{	m[i][j] = 0;
			s[i][j] = 0;
		}
	for(r=2;r<=n;r++)	//r��ʾ���˾���ĸ���
	{
		for(i=1;i<=n-r+1;i++)
		{
			j = i+r-1;
			m[i][j] = m[i][i]+m[i+1][j]+p[i-1]*p[i]*p[j];	//m[i][j]��ʾ��Ai��Aj��˵���С�˵Ĵ���
			s[i][j] = i;	//s[i][j]��ʾ��Ai��Aj�ĶϿ���λ��
			for(k = i+1;k<j;k++)
			{
				t = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(m[i][j]>t)
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
	
}
int main(void)
{
	int m[n+1][n+1],s[n+1][n+1],p[n+1],i,j;
	printf("please input %d p:\n",n+1);
	for(i=0;i<n+1;i++)
		scanf("%d",p+i);
/*	for(i=0;i<n+1;i++)
		printf("%d ",p[i]);
	printf("\n");*/
	MatrixChain(p,m,s);
	printf("s����Ϊ��\n");
	for(i=1;i<=n;i++)
	{	for(j=1;j<=n;j++)
			printf("%-8d",s[i][j]);
		printf("\n");
	}
	printf("m����Ϊ��\n");
	for(i=1;i<=n;i++)
	{	for(j=1;j<=n;j++)
			printf("%-8d",m[i][j]);
		printf("\n");
	}
	return 0;
}
