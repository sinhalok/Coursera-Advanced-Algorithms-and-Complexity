#include <iostream>
#include <queue>
#include<string.h>
using namespace std;
#define arraysize 201
int maxData = 0x7fffffff;
int capacity[arraysize][arraysize]; 
int flow[arraysize];                
int pre[arraysize];                
int n,m;
queue<int> myqueue;
int BFS(int src,int des)
{
    int i,j;
    while(!myqueue.empty())      
        myqueue.pop();
    for(i=1;i<m+1;++i)
    {
        pre[i]=-1;
    }
    pre[src]=0;
    flow[src]= maxData;
    myqueue.push(src);
    while(!myqueue.empty())
    {
        int index = myqueue.front();
        myqueue.pop();
        if(index == des)          
            break;
        for(i=1;i<m+1;++i)
        {
            if(i!=src && capacity[index][i]>0 && pre[i]==-1)
            {
                 pre[i] = index; 
                 flow[i] = min(capacity[index][i],flow[index]);   
                 myqueue.push(i);
            }
        }
    }
    if(pre[des]==-1)      
        return -1;
    else
        return flow[des];
}
int maxFlow(int src,int des)
{
    int increasement= 0;
    int sumflow = 0;
    while((increasement=BFS(src,des))!=-1)
    {
         int k = des;         
         while(k!=src)
         {
              int last = pre[k];
              capacity[last][k] -= increasement; 
              capacity[k][last] += increasement; 
              k = last;
         }
         sumflow += increasement;
    }
    return sumflow;
}




int main()
{
    int i,j;
    int start,end,ci;
    while(cin>>m>>n)
    {
        memset(capacity,0,sizeof(capacity));
        memset(flow,0,sizeof(flow));
        for(i=0;i<n;++i)
        {
            cin>>start>>end>>ci;
            if(start == end)               
               continue;
            capacity[start][end] +=ci;     
        }
        cout<<maxFlow(1,m)<<endl;
    }
    return 0;
}

