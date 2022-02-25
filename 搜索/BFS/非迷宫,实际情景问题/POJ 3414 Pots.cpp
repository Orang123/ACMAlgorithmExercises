/*
//题意摘自网上
题意:有二个水壶1 2,对水壶有三种操作:
1)FILL(i),将i水壶的水填满.
2)DROP(i),将水壶i中的水全部倒掉.
3)POUR(i,j)将水壶i中的水倒到水壶j中，要么把i水壶倒完为止,要么把j水壶倒满为止.
问进行多少步操作,并且怎么操作,输出操作的步骤,两个水壶中的水可以达到C这个水量.
如果不可能则输出"impossible".初始时两个水壶是空的,没有水.
1<=A,B,C<=100.C<=max(A,B).
链接:http://poj.org/problem?id=3414
思路:和HDU 1495 非常可乐一样,bfs 状态设计为1 2两水壶的水量,
状态标记设置为vis[tp.A][tp.B]=0/1表示1水壶水量为tp.A,2水壶水量为tp.B,
这个状态是否已经到达过.操作步骤也放入State状态里,用vector<string>存储.
*/
//ac 16ms bfs+倒水状态转移
//时间复杂度O(n*n)=10000 vis[110][110]
#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#include<string>
#include<vector>
#define N 110
using namespace std;

int A,B,C,vis[N][N];
struct State{
    int A,B,s;
    State(int A=0,int B=0,int s=0):A(A),B(B),s(s){}
    vector<string> path;
};
vector<string>::iterator it;

int bfs(){
    queue<State> Q;
    State tp,next;
    vis[0][0]=1;
    Q.push(State(0,0,0));
    while(!Q.empty()){
        tp=Q.front();
        if(tp.A == C || tp.B == C){
            printf("%d\n",tp.s);
            for(it=tp.path.begin();it!=tp.path.end();it++)
                cout << *it << endl;
            return 1;
        }
        Q.pop();
        next.s=tp.s+1;
        //将1水壶倒满
        if(tp.A != A){
            next.A=A;
            next.B=tp.B;
            //将之前操作步骤复制到next下一状态中
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("FILL(1)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
        //将2水壶倒满
        if(tp.B != B){
            next.A=tp.A;
            next.B=B;
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("FILL(2)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
        //将1水壶倒空
        if(tp.A){
            next.A=0;
            next.B=tp.B;
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("DROP(1)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
        //将2水壶倒空
        if(tp.B){
            next.A=tp.A;
            next.B=0;
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("DROP(2)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
        //将1水壶水往2水壶倒
        if(tp.A && tp.B<B){
            if(tp.A<=B-tp.B){
                next.A=0;
                next.B=tp.B+tp.A;
            }
            else{
                next.A=tp.A-(B-tp.B);
                next.B=B;
            }
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("POUR(1,2)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
        //将2水壶水往1水壶倒
        if(tp.B && tp.A<A){
            if(tp.B<=A-tp.A){
                next.A=tp.A+tp.B;
                next.B=0;
            }
            else{
                next.A=A;
                next.B=tp.B-(A-tp.A);
            }
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("POUR(2,1)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
    }
    return 0;
}

int main(){
    int ans;
    memset(vis,0,sizeof(vis));
    scanf("%d%d%d",&A,&B,&C);
    ans=bfs();
    if(!ans)
        printf("impossible\n");
    return 0;
}
