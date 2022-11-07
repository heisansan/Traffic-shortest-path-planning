#include <stdio.h>
#include <stdlib.h>
#define MVNum 50    //��󶥵���
#define Maxint 35000//�����ֵ 
enum boolean{FALSE,TRUE};//����boolean�������ͣ�����ȡֵ������false��true��false���Ե�����0ʹ�ã�true���Ե�����1ʹ�á� 
typedef char VertexType;
typedef int Adjmatrix;
typedef struct 
{
    VertexType vexs[MVNum];     //�������飬���ͼٶ�Ϊchar��
    Adjmatrix arcs[MVNum][MVNum];     //�ڽӾ��󣬼ٶ�Ϊint��
}MGraph;
int D1[MVNum],p1[MVNum];
int D[MVNum][MVNum],p[MVNum][MVNum];

//�����ڽӾ����ʾ����������ͼG
//n��e��ʾͼ�ĵ�ǰ�������ͱ���
void CreateMGraph(MGraph *G,int n,int e)
{
    int i,j,k,w;
    for(i=1;i<=n;i++)   //���붥����Ϣ
        G->vexs[i]=(char)i;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            G->arcs[i][j]=Maxint;   //��ʼ���ڽӾ���ʹ����֮��·����Ȩ�ض�������������������ֵ35000 
    printf("��������%d��·����:\n������i���յ����j��·������w��\n",e);
    for(k=1;k<=e;k++)
    {
        //����e���ߣ������ڽӾ���
        scanf("%d,%d,%d",&i,&j,&w);
        G->arcs[i][j]=w;//�ı�i������j����֮���·����Ȩ�� 
    }
    printf("����ͼ�Ĵ洢�ṹ������ϣ� \n");
}

//dijkstra
//�����������
int Dijkstra(MGraph *G,int v1,int n)
{
    //��Dijikstra�㷨������ͼG��v1���� �� ��������v �����·��p[v] ���� ȨD[v]
    //S[v]Ϊ�� ���ҽ��� v����s���� ����Ĵ�v1��v�����·��
    int D2[MVNum],p2[MVNum];
    int v,i,w,min;
    enum boolean S[MVNum];
    for(v=1;v<=n;v++)
    {
        //��ʼ�� S �� D
        S[v]=FALSE;          //�ÿ����·���յ㼯
        D2[v]=G->arcs[v1][v];      //�ó�ʼ�����·��ֵ 
        if(D2[v]<Maxint) //����˴� Ȩֵ < �����ֵ 
            p2[v]=v1;             //v1�ǵ�ǰ����˫�ף�
        else
            p2[v]=0;              //v��ǰ��
    }
    D2[v1]=0;    //S����ʼʱֻ��Դ�㣬Դ�㵽Դ��ľ���Ϊ0
    S[v1]=TRUE;  //��ʼѭ����ÿ�����V1��ĳ����������·��������V�ӵ�S��
    for (i=2;i<n;i++)
    {
        //����n-1������
        min=Maxint;//��ʼ�� 
        for(w=1;w<=n;w++)
            if(!S[w] && D2[w]<min)
            {
                //����v1����Ķ���w�������丳��v�����븳��min
                v=w;
                min=D2[w];
            }
            S[v]=TRUE;
            for(w=1;w<=n;w++)
                if(!S[w] && (D2[v] + G->arcs[v][w] < D2[w]))//�����˸����Ķ��� 
                {
                    D2[w]=D2[v]+G->arcs[v][w];
                    p2[w]=v;
                }
    }
    printf("·������ ·��\n");
    for(i=1;i<=n;i++)
    {
        printf("%5d",D2[i]);
        printf("%5d",i);
        v=p2[i];
        while(v!=0)
        {
            printf("<-%d",v);
            v=p2[v];
        }
        printf("\n");
    }
    int a=1,cost=1,sum1=1;
	while(a != 0)
	{
		printf("\n\n*******************1-1********************\n");
	    printf("--------------���Լ�����ѯ----------------\n");
	   	printf("     1.�Ӹó��е����ص��������\n");
	    printf("     2.�Ӹó��е����ص����ʱ��\n");
	    printf("     0.����\n");
	    printf("-----------------------------------------\n");
	    printf("��ѡ��");
	    scanf("%d",&a);
	    if(a == 1)
	    {
		    printf("\n-----------------------------------------\n");
		    printf("������ÿ 1 ·�̳������軨�ѵĳ���(Ԫ)��");
		    scanf("%d",&cost);
		    printf("\n·������   ·��   ������ѣ�Ԫ��\n");
		    for(i=1;i<=n;i++)
		    {
		        printf("%5d",D2[i]);
		        printf("%5d",i);
		        v=p2[i];
		        while(v!=0)
		        {
		            printf("<-%d",v);
		            v=p2[v];
		        }
		        if(D2[i] != Maxint) 
				{
			        sum1=cost*D2[i]; 
			        printf("%5d",sum1);
			        printf("\n");
				}
				else
				{
					printf("û��ͨ�еĵ�·"); 
				}
			} 
		}
	    else if(a == 2)
	    {
		    printf("\n-----------------------------------------\n");
		    printf("������ÿ 1 ·�̳������軨�ѵ�ʱ�䣨min����");
		    scanf("%d",&cost);
		    printf("\n·������  ·��   ���ʱ��(min)\n");
		    for(i=1;i<=n;i++)
		    {
		        printf("%5d",D2[i]);
		        printf("%5d",i);
		        v=p2[i];
		        while(v!=0)
		        {
		            printf("<-%d",v);
		            v=p2[v];
		        }
		        if(D2[i] != Maxint) 
				{
			        sum1=cost*D2[i]; 
			        printf("%5d",sum1);
			        printf("\n");
				}
				else
				{
					printf("����û��ͨ�еĵ�·"); 
				}
			}
		}
		else  break;
	}
}

//floyd(���������㷨)
//ʹ��n*n��ά���鴢��·����Ϣ
//D[i][j]����¼ÿһ�Զ������̾���
void Floyd(MGraph *G,  int n)
{
    int i, j, k;
    //����ÿһ�Զ���֮���·������
    for(i=1;i<=n;j++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                if(G->arcs[i][j]!=Maxint)//����������������·�� 
                    p[i][j]=j;
                else//�����������·���� 
                    p[i][j]=0;
                D[i][j]=G->arcs[i][j];    
            }

    //k=1ʱֻ������1�Ŷ��������ת
    //k=2ʱֻ������1�ź�2�Ŷ��������ת
    //k=3......
    for(k=1;k<=n;k++)
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                //�������i��k ���� k��j�ľ��� С�� iֱ�ӵ�j���� --- i��j�ľ��� �辭��k������ת�������·�� 
                if(D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j]=D[i][k]+D[k][j];
                    p[i][j]=p[i][k];
                }
            }
    }
}

int main()
{    
    MGraph *G;
    int n,e,v,w,k;//v�����   w���յ�
    int xz=1; //ѡ�� 
    G=(MGraph *)malloc(sizeof(MGraph));     //��ʼ��ͼ
    printf("\n*******************��������ͼ********************\n\n");
    printf("������и�����·;���� n,e :");
    scanf("%d,%d",&n,&e);
    CreateMGraph(G,n,e);    //��������ͼ�ṹ
    while(xz!=0)
    {
    	printf("\n\n\n*****************���˵�********************\n");
    	printf("-----------------------------------------\n");
        printf("        ��ͨ���·�߹滮--���н�ͨ��ѯ    \n");
        printf("-----------------------------------------\n");
        printf("     1.���һ�����е��������е����·����\n");
        printf("     2.������������������Ҫ�����·��\n");
        printf("     0.�˳�����\n");
        printf("-----------------------------------------\n");
        printf("��ѡ��");
        scanf("%d",&xz);
		printf("\n-----------------------------------------\n");
        if(xz==1)//����Դ����� 
        {
            printf("��Դ·��������������v����ţ�");
            scanf("%d",&v);
            Dijkstra(G,v,n);
        }
        if(xz==2)           //����һ�Զ�������·��
        {
            Floyd(G,n);     
            printf("������㣺");
            scanf("%d",&v);
            printf("�����յ㣺");
            scanf("%d",&w);
            k=p[v][w];     //kΪv�ĺ�̽��
            if(k==0)
            {
                printf("����%d �� ����%d ��·����\n",v,w);
            }
			else
            {
                printf("�ӳ���%d �� ����%d �����·���ǣ�%d",v,w,v);
            }
            while(k!=w)
            {
                printf("-->%d",k);
                k=p[k][w];
            }
            printf("--%d",w);
            printf(" ·�����ȣ�%d\n",D[v][w]);
            int b=1,cost=1;
			int sum2,sum22;
			sum2 = D[v][w];
            while(b!=0)
			{
				printf("\n\n*******************2-1********************\n");
			    printf("--------------���Լ�����ѯ----------------\n");
			   	printf("       1.�������������������������\n");
			    printf("       2.�������������������ѵ����ʱ��\n");
			    printf("       0.����\n");
			    printf("-----------------------------------------\n");
				printf("��ѡ��"); 
			    scanf("%d",&b);
			    if(b == 1)
				{
					printf("\n-----------------------------------------\n");
				    printf("������ÿ 1 ·�̳������軨�ѵĳ���(Ԫ)��");
				    scanf("%d",&cost);
		            sum2=cost*D[v][w];
		            sum22=sum2*2;
					printf("���̳��ѣ�%d  �����ܳ���: %d \n",sum2,sum22);
				} 
				else if(b == 2)
				{
					printf("\n-----------------------------------------\n");
				    printf("������ÿ 1 ·�̳������軨�ѵ�ʱ��(����)��");
				    scanf("%d",&cost);
		            sum2=cost*D[v][w];
		            sum22=sum2*2;
					printf("���̻���ʱ�䣺%d ����  ��������ʱ��: %d ����\n",sum2,sum22);
					int c=1;
					while(c != 0)
					{
						printf("\n\n*******************2-2********************\n");
						printf("--------------���Լ�����ѯ----------------\n");
				  	 	printf("       1.�������������Сʱ\n");
				 	   	printf("       2.�г̼���\n");
					    printf("       0.����\n");
				 	    printf("-----------------------------------------\n");
						printf("��ѡ��");
						scanf("%d",&c);
						int h,min,h1,min1,h2,min2;
						h1=sum2/60;
						min1=sum2%60;
						if(c == 1)
						{	
							printf("\n���̵ķ���תСʱת�������%d ���� = %d Сʱ %d ����\n",sum2,h1,min1);
							sum22=sum2*2;
							h2=sum22/60;
							min2=sum22%60;
							printf("�����ķ���תСʱת�������%d ���� = %d Сʱ %d ����\n",sum22,h2,min2);
						}
						else if(c == 2)
						{
							printf("�����������������ʱ�䣨xx:xx����");
							scanf("%d:%d",&h,&min);
							h=h+h1;
							min=min+min1;
							printf("����Ԥ�Ƶ���ʱ��Ϊ��");
							for(;min >= 60;min=min-60)
							{
								h=h+1;
							}
							for(;h >= 24;h=h-24)
							{
								printf("�����");
							}
							printf("%2d:%2d\n",h,min);
						}
						else break;
					}
				}
				else  break; 
      		}
			        
    	}
	}
	printf("���������·��");
}
