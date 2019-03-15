#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


#define MAXN 100                 //MAXN表示X集合和Y集合顶点个数的最大值
int nx,ny;                                       //x和y集合中顶点的个数
int adj_matrix[MAXN][MAXN];                //邻接矩阵，g[i][j]为1表示有连接
int cx[MAXN],cy[MAXN];        //cx[i],表示最终求得的最大匹配中，与x集合中元素Xi匹配的集合Y中顶点的索引
                                                        //cy[i],表示最终求得的最大匹配中，与y集合中元素Yi匹配的集合X中顶点的索引

//DFS算法中记录顶点访问状态的数据mk[i]=0表示未访问过，为1表示访问过
int mk[MAXN];

//从集合X中的定顶点u出发，用深度有限的策略寻找增广路
//这种增广路只能是当前的匹配数增加1
int path(int u,vector<vector<bool> > adj_matrix){
	
    for(int v=0;v<ny;++v){      //考虑所有Yi顶点v
        if(adj_matrix[u][v] && !mk[v]){     //Y中顶点v与u邻接，且没有访问过
            mk[v]=1;                        //访问v

            //如果v没有匹配，则直接将v匹配给u，如果v已经匹配了，但是从cy[v],也就是从v之前已经匹配的x出发，找到一条增广路，但是这里记住这里v已经记录访问过了
            //如果第一个条件成立，则不会递归调用
            if(cy[v]==-1 || path(cy[v],adj_matrix)){
                cx[u]=v;         //把Y中v匹配给X中u
                cy[v]=u;            //把X中u匹配给Y中v
                return 1;
            }
        }
    }
    return 0;                        //如果不存在从u出发的增广路，则返回0
}

int maxMatch(vector<vector<bool> > adj_matrix){        //求二分图最大匹配的匈牙利算法

    int res=0;
    memset(cx,-1,sizeof(cx));        //从0匹配开始增广，将cx和xy各元素都初始化为-1
    memset(cy,-1,sizeof(cy));
    for(int i=0;i<nx;++i){
        if(cx[i]==-1){                                    //从X集合中每个没有匹配的点出发开始寻找增广路
            memset(mk,0,sizeof(mk));
            res+=path(i,adj_matrix);
        }
    }
    return res;
}

vector<vector<bool> > ReadData() {
	int num_left, num_right;
	cin >> num_left >> num_right;
	vector<vector<bool> > adj_matrix(num_left, vector<bool>(num_right));
	for (int i = 0; i < num_left; ++i)
	  for (int j = 0; j < num_right; ++j) {
	    int bit;
	    cin >> bit;
	    adj_matrix[i][j] = (bit == 1);
	  }
	return adj_matrix;
}
int main() {

    /*adj_matrix[0][0]=1; adj_matrix[0][1]=1; adj_matrix[0][2]=0; adj_matrix[0][3]=1;
    adj_matrix[1][0]=0; adj_matrix[1][1]=1; adj_matrix[1][2]=0; adj_matrix[1][3]=0;
    adj_matrix[2][0]=0; adj_matrix[2][1]=0; adj_matrix[2][2]=0; adj_matrix[2][3]=0;
    
	for (int i = 0; i < nx; ++i)
	  for (int j = 0; j < ny; ++j) {
	    
	    
	    cout<<adj_matrix[i][j]<<endl;
	  }
    */
    vector<vector<bool> > adj_matrix = ReadData();
    nx = adj_matrix.size();
    ny = adj_matrix[0].size();
    int num= maxMatch(adj_matrix);
    //cout<<"num="<<num<<endl;
    for(int num=0;num<nx;++num){
    	if (cx[num]+1)
    	{
    		cout<<cx[num]+1<<' ';
		}
        else
        {
        	cout<<-1<<' ';
		}
    }

    return 0;
}

