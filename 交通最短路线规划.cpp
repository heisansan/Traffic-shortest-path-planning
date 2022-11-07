#include <stdio.h>
#include <stdlib.h>
#define MVNum 50    //最大顶点数
#define Maxint 35000//最大数值 
enum boolean{FALSE,TRUE};//定义boolean这种类型，它的取值可以是false和true。false可以当常量0使用，true可以当常量1使用。 
typedef char VertexType;
typedef int Adjmatrix;
typedef struct 
{
    VertexType vexs[MVNum];     //顶点数组，类型假定为char型
    Adjmatrix arcs[MVNum][MVNum];     //邻接矩阵，假定为int型
}MGraph;
int D1[MVNum],p1[MVNum];
int D[MVNum][MVNum],p[MVNum][MVNum];

//采用邻接矩阵表示法构造有向图G
//n，e表示图的当前顶点数和边数
void CreateMGraph(MGraph *G,int n,int e)
{
    int i,j,k,w;
    for(i=1;i<=n;i++)   //输入顶点信息
        G->vexs[i]=(char)i;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            G->arcs[i][j]=Maxint;   //初始化邻接矩阵，使顶点之间路径的权重都是上面所定义的最大数值35000 
    printf("请输入这%d条路径的:\n起点城市i，终点城市j，路径长度w：\n",e);
    for(k=1;k<=e;k++)
    {
        //读入e条边，建立邻接矩阵
        scanf("%d,%d,%d",&i,&j,&w);
        G->arcs[i][j]=w;//改变i顶点与j顶点之间的路径的权重 
    }
    printf("有向图的存储结构建立完毕！ \n");
}

//dijkstra
//广度优先搜索
int Dijkstra(MGraph *G,int v1,int n)
{
    //用Dijikstra算法求有向图G的v1顶点 到 其他顶点v 的最短路径p[v] 及其 权D[v]
    //S[v]为真 当且仅当 v属于s，及 以求的从v1到v的最短路径
    int D2[MVNum],p2[MVNum];
    int v,i,w,min;
    enum boolean S[MVNum];
    for(v=1;v<=n;v++)
    {
        //初始化 S 和 D
        S[v]=FALSE;          //置空最短路径终点集
        D2[v]=G->arcs[v1][v];      //置初始的最短路径值 
        if(D2[v]<Maxint) //如果此处 权值 < 最大数值 
            p2[v]=v1;             //v1是的前趋（双亲）
        else
            p2[v]=0;              //v无前趋
    }
    D2[v1]=0;    //S集初始时只有源点，源点到源点的距离为0
    S[v1]=TRUE;  //开始循环，每次求的V1到某个顶点的最短路径，并把V加到S集
    for (i=2;i<n;i++)
    {
        //其余n-1个顶点
        min=Maxint;//初始化 
        for(w=1;w<=n;w++)
            if(!S[w] && D2[w]<min)
            {
                //找离v1最近的顶点w，并将其赋给v，距离赋给min
                v=w;
                min=D2[w];
            }
            S[v]=TRUE;
            for(w=1;w<=n;w++)
                if(!S[w] && (D2[v] + G->arcs[v][w] < D2[w]))//发现了更近的顶点 
                {
                    D2[w]=D2[v]+G->arcs[v][w];
                    p2[w]=v;
                }
    }
    printf("路径长度 路径\n");
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
	    printf("--------------可以继续查询----------------\n");
	   	printf("     1.从该城市到各地的最低消费\n");
	    printf("     2.从该城市到各地的最短时间\n");
	    printf("     0.返回\n");
	    printf("-----------------------------------------\n");
	    printf("请选择：");
	    scanf("%d",&a);
	    if(a == 1)
	    {
		    printf("\n-----------------------------------------\n");
		    printf("请输入每 1 路程长度所需花费的车费(元)：");
		    scanf("%d",&cost);
		    printf("\n路径长度   路径   最低消费（元）\n");
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
					printf("没有通行的道路"); 
				}
			} 
		}
	    else if(a == 2)
	    {
		    printf("\n-----------------------------------------\n");
		    printf("请输入每 1 路程长度所需花费的时间（min）：");
		    scanf("%d",&cost);
		    printf("\n路径长度  路径   最短时间(min)\n");
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
					printf("这里没有通行的道路"); 
				}
			}
		}
		else  break;
	}
}

//floyd(费洛伊德算法)
//使用n*n二维数组储存路径信息
//D[i][j]：记录每一对顶点的最短距离
void Floyd(MGraph *G,  int n)
{
    int i, j, k;
    //储存每一对顶点之间的路径距离
    for(i=1;i<=n;j++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                if(G->arcs[i][j]!=Maxint)//如果这两个顶点间有路径 
                    p[i][j]=j;
                else//其他情况（无路径） 
                    p[i][j]=0;
                D[i][j]=G->arcs[i][j];    
            }

    //k=1时只允许经过1号顶点进行中转
    //k=2时只允许经过1号和2号顶点进行中转
    //k=3......
    for(k=1;k<=n;k++)
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                //如果顶点i到k 加上 k到j的距离 小于 i直接到j距离 --- i到j的距离 需经过k顶点中转才是最短路径 
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
    int n,e,v,w,k;//v：起点   w：终点
    int xz=1; //选择 
    G=(MGraph *)malloc(sizeof(MGraph));     //初始化图
    printf("\n*******************建立有向图********************\n\n");
    printf("输入城市个数和路途数量 n,e :");
    scanf("%d,%d",&n,&e);
    CreateMGraph(G,n,e);    //建立有向图结构
    while(xz!=0)
    {
    	printf("\n\n\n*****************主菜单********************\n");
    	printf("-----------------------------------------\n");
        printf("        交通最短路线规划--城市交通咨询    \n");
        printf("-----------------------------------------\n");
        printf("     1.求从一个城市到其他城市的最短路径；\n");
        printf("     2.求往返两个城市所需要的最短路径\n");
        printf("     0.退出程序\n");
        printf("-----------------------------------------\n");
        printf("请选择：");
        scanf("%d",&xz);
		printf("\n-----------------------------------------\n");
        if(xz==1)//单个源点出发 
        {
            printf("求单源路径，输入起点城市v的序号：");
            scanf("%d",&v);
            Dijkstra(G,v,n);
        }
        if(xz==2)           //任意一对顶点间最短路径
        {
            Floyd(G,n);     
            printf("输入起点：");
            scanf("%d",&v);
            printf("输入终点：");
            scanf("%d",&w);
            k=p[v][w];     //k为v的后继结点
            if(k==0)
            {
                printf("城市%d 到 城市%d 无路径！\n",v,w);
            }
			else
            {
                printf("从城市%d 到 城市%d 的最短路径是：%d",v,w,v);
            }
            while(k!=w)
            {
                printf("-->%d",k);
                k=p[k][w];
            }
            printf("--%d",w);
            printf(" 路径长度：%d\n",D[v][w]);
            int b=1,cost=1;
			int sum2,sum22;
			sum2 = D[v][w];
            while(b!=0)
			{
				printf("\n\n*******************2-1********************\n");
			    printf("--------------可以继续查询----------------\n");
			   	printf("       1.在这两个城市往返的最低消费\n");
			    printf("       2.在这两个城市往返花费的最短时间\n");
			    printf("       0.返回\n");
			    printf("-----------------------------------------\n");
				printf("请选择："); 
			    scanf("%d",&b);
			    if(b == 1)
				{
					printf("\n-----------------------------------------\n");
				    printf("请输入每 1 路程长度所需花费的车费(元)：");
				    scanf("%d",&cost);
		            sum2=cost*D[v][w];
		            sum22=sum2*2;
					printf("单程车费：%d  往返总车费: %d \n",sum2,sum22);
				} 
				else if(b == 2)
				{
					printf("\n-----------------------------------------\n");
				    printf("请输入每 1 路程长度所需花费的时间(分钟)：");
				    scanf("%d",&cost);
		            sum2=cost*D[v][w];
		            sum22=sum2*2;
					printf("单程花费时间：%d 分钟  往返花费时间: %d 分钟\n",sum2,sum22);
					int c=1;
					while(c != 0)
					{
						printf("\n\n*******************2-2********************\n");
						printf("--------------可以继续查询----------------\n");
				  	 	printf("       1.将分钟数换算成小时\n");
				 	   	printf("       2.行程计算\n");
					    printf("       0.返回\n");
				 	    printf("-----------------------------------------\n");
						printf("请选择：");
						scanf("%d",&c);
						int h,min,h1,min1,h2,min2;
						h1=sum2/60;
						min1=sum2%60;
						if(c == 1)
						{	
							printf("\n单程的分钟转小时转换结果：%d 分钟 = %d 小时 %d 分钟\n",sum2,h1,min1);
							sum22=sum2*2;
							h2=sum22/60;
							min2=sum22%60;
							printf("往返的分钟转小时转换结果：%d 分钟 = %d 小时 %d 分钟\n",sum22,h2,min2);
						}
						else if(c == 2)
						{
							printf("请输入您打算出发的时间（xx:xx）：");
							scanf("%d:%d",&h,&min);
							h=h+h1;
							min=min+min1;
							printf("您的预计到达时间为：");
							for(;min >= 60;min=min-60)
							{
								h=h+1;
							}
							for(;h >= 24;h=h-24)
							{
								printf("隔天的");
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
	printf("结束求最短路径");
}
