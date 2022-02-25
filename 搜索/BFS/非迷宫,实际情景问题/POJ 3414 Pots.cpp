/*
//����ժ������
����:�ж���ˮ��1 2,��ˮ�������ֲ���:
1)FILL(i),��iˮ����ˮ����.
2)DROP(i),��ˮ��i�е�ˮȫ������.
3)POUR(i,j)��ˮ��i�е�ˮ����ˮ��j�У�Ҫô��iˮ������Ϊֹ,Ҫô��jˮ������Ϊֹ.
�ʽ��ж��ٲ�����,������ô����,��������Ĳ���,����ˮ���е�ˮ���ԴﵽC���ˮ��.
��������������"impossible".��ʼʱ����ˮ���ǿյ�,û��ˮ.
1<=A,B,C<=100.C<=max(A,B).
����:http://poj.org/problem?id=3414
˼·:��HDU 1495 �ǳ�����һ��,bfs ״̬���Ϊ1 2��ˮ����ˮ��,
״̬�������Ϊvis[tp.A][tp.B]=0/1��ʾ1ˮ��ˮ��Ϊtp.A,2ˮ��ˮ��Ϊtp.B,
���״̬�Ƿ��Ѿ������.��������Ҳ����State״̬��,��vector<string>�洢.
*/
//ac 16ms bfs+��ˮ״̬ת��
//ʱ�临�Ӷ�O(n*n)=10000 vis[110][110]
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
        //��1ˮ������
        if(tp.A != A){
            next.A=A;
            next.B=tp.B;
            //��֮ǰ�������踴�Ƶ�next��һ״̬��
            next.path.assign(tp.path.begin(),tp.path.end());
            next.path.push_back("FILL(1)");
            if(!vis[next.A][next.B]){
                vis[next.A][next.B]=1;
                Q.push(next);
            }
        }
        //��2ˮ������
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
        //��1ˮ������
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
        //��2ˮ������
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
        //��1ˮ��ˮ��2ˮ����
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
        //��2ˮ��ˮ��1ˮ����
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
