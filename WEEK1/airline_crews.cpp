#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


#define MAXN 100                
int nx,ny;                                      
int adj_matrix[MAXN][MAXN];               
int cx[MAXN],cy[MAXN];        
                                                        


int mk[MAXN];


int path(int u,vector<vector<bool> > adj_matrix){
	
    for(int v=0;v<ny;++v){     
        if(adj_matrix[u][v] && !mk[v]){     
            mk[v]=1;                      

           
            if(cy[v]==-1 || path(cy[v],adj_matrix)){
                cx[u]=v;         
                cy[v]=u;            
                return 1;
            }
        }
    }
    return 0;                        
}

int maxMatch(vector<vector<bool> > adj_matrix){       

    int res=0;
    memset(cx,-1,sizeof(cx));        
    memset(cy,-1,sizeof(cy));
    for(int i=0;i<nx;++i){
        if(cx[i]==-1){                                  
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

