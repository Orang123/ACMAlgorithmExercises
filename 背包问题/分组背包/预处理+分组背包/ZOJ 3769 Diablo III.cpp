/*
����:��13��װ��,ÿ��װ��ֻ��ѡһ��,ÿ��װ����һ���˺�ֵ������,
�������ѡTwo-Handed�Ļ��Ͳ���ѡShield��Weapon,Finger����ѡ����.
��ʹ�������Դ���С��m�������,�˺���ֵ����Ƕ���.
����:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369730
˼·:��Ȼÿ��װ����λ���ֻ�ܷ�һ��ͬ���͵�װ��,��ôͬ�����͵�װ�����Էֵ�
һ������,Ӧ�÷��鱳����⼴��,����Two-Handed(˫��)��Ϊ��Shield(����)��Weapon(����)
�ǻ����,��˿��԰������ͻ��ܵ�����Ϊһ��˫��װ���Լ������ߺ�������ϳ�һ��˫��װ��
�ŵ�ͬһ����.��fingerѡ�񵥸���ָ���൱��ֻ��һֻ�ִ���ָ,�ѽ�ָ�����������Ҳ���൱
��˫�ֶ����˽�ָ,����ָ������ϵ�װ���ٷŵ�finger����.���鱳��ʱע��:����Ҫ��m����,
Ҳ����ת��ʱ���ڴ���m������ֻ��ȡm��Ϊ����,��j+t��m����Сֵ��Ϊת�ƺ������,
����״̬ת�Ʒ��̾���int tp=min(j+k.t,m);dp[i][tp]=max(dp[i][tp],dp[i-1][j]+k.d);
��Ҫע����ǲ����ù��������Ż�,��Ϊ��ʹ��������j����,��j=mʱ,j+k.t=tp,tp�Ծ�����Сֵm,
�����ٿ���ͬ���ڱ��װ��ʱ,dp[j]=dp[m],���dp[j]�Ѿ������˵�i���װ��,�������ڼ����ۼ�
��i���װ����,��˲����ù�������һά����ȥ��.
*/
//ac 359ms ��ά����ʵ�� ���ܹ��������Ż�
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define M 50010
using namespace std;

int n,m,dp[14][M];
char str[15][20]={"","Shield", "Weapon", "Two-Handed", "Finger","Head", "Shoulder", "Neck", "Torso", "Hand", "Wrist", "Waist", "Legs", "Feet"};
struct Node{
    int d,t;
    Node(int d=0,int t=0):d(d),t(t){}
};
vector<Node> G[14];

int check(char *x){
    for(int i=1;i<=13;i++){
        if(!strcmp(x,str[i]))
           return i;
    }
    return 0;
}

int main(){
    char x[20];
    int T,d,t,id;
    scanf("%d",&T);
    while(T--){
        for(int i=1;i<=13;i++)
            G[i].clear();
        memset(dp,-1,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%s%d%d",x,&d,&t);
            id=check(x);
            G[id].push_back(Node(d,t));
        }
        //��Weapon�����ŵ�Two-Handed˫��һ����
        for(Node &i : G[2])
            G[3].push_back(i);
        for(Node &i : G[1]){
            //��Shield���Ʒŵ�Two-Handed˫��һ����
            G[3].push_back(i);
            for(Node &j : G[2])
                //��Shield��Weapon�����װ���ŵ�Two-Handed˫��һ����
                G[3].push_back(Node(i.d+j.d,i.t+j.t));
        }
        int len=G[4].size();
        //��Finger��װ���������������Ϊһ��װ���ٷŵ�finger��
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++)
                G[4].push_back(Node(G[4][i].d+G[4][j].d,G[4][i].t+G[4][j].t));
        }
        dp[2][0]=0;
        //��ΪShield��Weapon����Two-Handed����,����ֱ�ӴӸ��º��Two-Handedװ���鿪ʼdp
        for(int i=3;i<=13;i++){
            for(int j=0;j<=m;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=m;j++){
                //���ӻ�TLE
                if(dp[i-1][j] == -1) continue;//�������뱣֤ǡ��װ�����ǺϷ�״̬
                for(Node &k : G[i]){
                    /*
                    ��Ҫע����ǲ����ù��������Ż�,��Ϊ��ʹ��������j����,��j=mʱ,j+k.t=tp,tp�Ծ�����Сֵm,
                    �����ٿ���ͬ���ڱ��װ��ʱ,dp[j]=dp[m],���dp[j]�Ѿ������˵�i���װ��,�������ڼ����ۼ�
                    ��i���װ����,��˲����ù�������һά����ȥ��.
                    */
                    int tp=min(j+k.t,m);//��������mʱ,ֻȡm
                    dp[i][tp]=max(dp[i][tp],dp[i-1][j]+k.d);
                }
            }
        }
        printf("%d\n",dp[13][m]);
    }
    return 0;
}
