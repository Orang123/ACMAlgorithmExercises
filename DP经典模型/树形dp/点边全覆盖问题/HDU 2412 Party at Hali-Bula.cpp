#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<cstring>
#include<string>
using namespace std;
/*
����:һЩԱ���μ��ɶ�,����Ա�����ܺ������ϰ�����,�������Զ����˲μ�,����������Ƿ�Ψһ��
����:http://acm.hdu.edu.cn/showproblem.php?pid=2412
˼·:
dp[root][0]����root��㲻�� only[root][0]root��㲻���ķ����Ƿ�Ψһ 1����Ψһ,0����Ψһ
dp[root][1]����root����� only[root][1]root������ķ����Ƿ�Ψһ
*/

vector <int> tree[205];
map<string,int> mp;
int dp[205][2],only[205][2];
void dfs(int root){
    int son;
    for(int i=0;i<tree[root].size();i++){
        son=tree[root][i];
        dfs(son);
        //Ա�����ϰ�һ��������,Ա������,�ϰ�����ɲ���.
        dp[root][0]+=max(dp[son][0],dp[son][1]);
        dp[root][1]+=dp[son][0];//�ϰ���,Ա��һ������.
        /*������ת�Ʒֿ�����only[root][0] only[root][1]
        ��Ա������Ա������������,��Ա�����ķ�����Ψһ;
        ��Ա��������Ա����������,��Ա�������ķ�����Ψһ;
        ����Ա�����Ͳ�������һ��,��˵���ϰ岻���ķ�����Ψһ;
        ��Ա���Ĳ�Ψһ��ȥ�Ƶ��ϰ�Ĳ�Ψһ��.���ȿ�ʼһ����Ա�����Ͳ�����ȵ��µ��ϰ岻���Ĳ�Ψһ��.
        */
        if((dp[son][1]>dp[son][0]&&!only[son][1])||(dp[son][1]<dp[son][0]&&!only[son][0])||(dp[son][0]==dp[son][1]))
            only[root][0]=0;
        //Ա�������ķ�����Ψһ,���ϰ����ķ���Ҳ��Ψһ.��Ϊ�ϰ�����,Ա��һ��������.
        if(!only[son][0])
            only[root][1]=0;
    }
}
int main(){
    int n,index;
    char str1[10],str2[10];
    while(scanf("%d",&n)&&n){
        index=1;
        for(int i=1;i<=n;i++)//��ѭ����ʼ��
            for(int j=0;j<2;j++)
                only[i][0]=only[i][1]=1;
        for(int i=0;i<205;i++)
            tree[i].clear();
        mp.clear();
        scanf("%s",str1);
        mp[str1]=index++;//�����ϰ� �ǽڵ�1
        for(int i=1;i<n;i++){
            scanf("%s%s",str1,str2);//str2 ��str1���ϰ�
            if(!mp[str2]) mp[str2]=index++;//��map��string��Ӧת��Ϊint�Ľڵ���
            if(!mp[str1]) mp[str1]=index++;
            tree[mp[str2]].push_back(mp[str1]);//���������
        }
        for(int i=1;i<index;i++){
            dp[i][0]=0;
            dp[i][1]=1;
        }
        dfs(1);
        if(dp[1][1]>dp[1][0]&&only[1][1]==1)
            printf("%d Yes\n",dp[1][1]);
        else if(dp[1][1]<dp[1][0]&&only[1][0]==1)
            printf("%d Yes\n",dp[1][0]);
        else{
            printf("%d No\n",max(dp[1][0],dp[1][1]));
        }
    }
    return 0;
}
