/*
����:ժ������
����n*m��ƴͼ����Ƭ��Ҫ���ж��Ƿ������һ��n*m�ľ��Σ�������Ƭ��F��ʾƽ�棬
I��ʾ���棬O��ʾ͹�棬���ھ��Σ���Ե�߱���ΪƽF�� �����ڲ��ı�ֻ������IO��OI
����ʽ����������������ַ���4���ַ���˳ʱ�뷽��ֱ��ʾ��Ƭ�Ķ������Ҳࡢ�ײ�����ࡣ
��������Щ��Ƭ�ܷ�ƴ��һ������ƴ�Ź���ľ��Ρ�
ע��:ÿ��ƴͼ��Ƭ�ߴ綼����ͬ��,����ʱ���ϸ���˳ʱ�뷽��ı�ʶ�İ�͹�ܷ��õ�,ֻ��һ�ַ��÷�ʽ.
0<n,m<=6.
����:https://www.luogu.com.cn/problem/UVA519
˼·:��Ҫö��n*m�ľ����ڲ�ÿ��λ��(x,y)���ܷ�����Щ��Ƭ,ʵ�ʾ���ö�پ����ڲ�������Ƭ����
��ȫ����,ֻ����һ���������ƴ�չ���ͷ���.
����ʱ��Ҫ���ǺϷ���Ե����.
1.�ڷ���ʱ��Ҫ���ǵ��ǵ�ǰλ��(x,y),����ǿ�����Ե�������ײ�����ˡ��Ҷ�,���豣֤�ⲿ��Ϊ'F'.
2.���(x,y)�ھ����ڲ�,��Ҫ��֤�䶥������һ��(x-1,y)�ĵײ�����IO��OI�����,�Լ��������(x,y-1)��
�Ҷ�����IO��OI����Բ���.����(x,y)�ײ����Ҳ಻����'F'ƽ��.

һ����֦�Ż��Ƕ��ڵ�ǰλ��(x,y)���֮ǰ�Ѿ����ù���ͬ����Ƭ,�Ͳ����ظ�����,��Ϊ����ֻ������ظ�
������,�����Ҫ���������а����ֵ���������� �����ô��������֦����.
��ö��ȫ����֮ǰҪ��֤Fƽ����Ŀ�����ܳ�(n+m)*2,�Լ�IO��ĿҪ��Ȳ�����Գɹ�,����ֱ�����NO.
*/
//ac 10ms qsort �Զ�ά���鰴�ֵ�������
//�����ֵ���Ͷ���ͬλ���ظ���Ƭ�����ػ�TLE
//�ʱ�临�Ӷ�36!,��ʵ����Ϊ��check���ظ�Ԫ�ص��ж� ���ӶȲ�û����ô��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,cnt,Icnt,Ocnt,Fcnt,mp[6][6],vis[N];
char block[N][5];//ע�ⳤ������Ҫ����Ϊ5,Ҫ��֤�ܷ������һ��'\0'������,���������ͬλ�� �ظ���Ƭ���� ���ж�ʧ����TLE

int cmp(const void*a, const void*b) {
	return strcmp((char*)a, (char*)b);
}

int check(int x,int y,int i){
    if(!x && block[i][0]!='F')//���� ������ƽ��
        return 0;
    if(x == n-1 && block[i][2]!='F')//�ײ� ������ƽ��
        return 0;
    if(x != n-1 && block[i][2] == 'F')//�����ڲ� �ײ�������ƽ��
        return 0;
    if(!y && block[i][3]!='F')//��� ������ƽ��
        return 0;
    if(y == m-1 && block[i][1]!='F')//�Ҷ� ������ƽ��
        return 0;
    if(y != m-1 && block[i][1] == 'F')//�����ڲ� �Ҷ˲�����ƽ��
        return 0;
    if(x>0 && block[i][0]+block[mp[x-1][y]][2]!='I'+'O')//���Ƕ��� ����IO��OI���
        return 0;
    if(y>0 && block[i][3]+block[mp[x][y-1]][1]!='I'+'O')//������� ����IO��OI���
        return 0;
    return 1;
}

int dfs(int cur){
    if(cur == cnt)
        return 1;
    int x=cur/m,y=cur%m;
    char tp[5]={0};//���ﲻ��ʼ�� ��wa
    for(int i=0;i<cnt;i++){
        if(!vis[i] && strcmp(tp,block[i]) && check(x,y,i)){//strcmp(tp,block[i].str)�ж� ��ǰλ��(x,y)�Ƿ��Ѿ��ظ����ù���Ƭ
            vis[i]=1;
            strcpy(tp,block[i]);
            //memcpy(tp,block[i],sizeof(tp));//ac
            mp[x][y]=i;
            if(dfs(cur+1))
                return 1;
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        cnt=n*m;
        Icnt=Ocnt=Fcnt=0;
        for(int i=0;i<cnt;i++){
            scanf("%s",block[i]);
            for(int j=0;j<4;j++){
                if(block[i][j] == 'I')
                    Icnt++;
                else if(block[i][j] == 'O')
                    Ocnt++;
                else
                    Fcnt++;
            }
        }
        if(Icnt != Ocnt || Fcnt!=(n+m)*2){
            printf("NO\n");
            continue;
        }
        qsort(block, cnt, sizeof(block[0]), cmp);
        if(dfs(0))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*
//ac 10ms �ýṹ���block�ֵ�������,ע�������� ������д�жϺ���,������strcmp���������re
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,cnt,Icnt,Ocnt,Fcnt,mp[6][6],vis[N];
struct Block{
    char str[5];
    bool operator <(const Block & x)const{
        //return strcmp(str,x.str);//����д��RE
    	for(int i=0;i<4;i++){
    		if(str[i]!=x.str[i])
    			return str[i]<x.str[i];
		}
		return 1;
    }
}block[N];

int check(int x,int y,int i){
    if(!x && block[i].str[0]!='F')//���� ������ƽ��
        return 0;
    if(x == n-1 && block[i].str[2]!='F')//�ײ� ������ƽ��
        return 0;
    if(x != n-1 && block[i].str[2] == 'F')//�����ڲ� �ײ�������ƽ��
        return 0;
    if(!y && block[i].str[3]!='F')//��� ������ƽ��
        return 0;
    if(y == m-1 && block[i].str[1]!='F')//�Ҷ� ������ƽ��
        return 0;
    if(y != m-1 && block[i].str[1] == 'F')//�����ڲ� �Ҷ˲�����ƽ��
        return 0;
    if(x>0 && block[i].str[0]+block[mp[x-1][y]].str[2]!='I'+'O')//���Ƕ��� ����IO��OI���
        return 0;
    if(y>0 && block[i].str[3]+block[mp[x][y-1]].str[1]!='I'+'O')//������� ����IO��OI���
        return 0;
    return 1;
}

int dfs(int cur){
    if(cur == cnt)
        return 1;
    int x=cur/m,y=cur%m;
    char tp[5]={0};
    for(int i=0;i<cnt;i++){
        if(!vis[i] && strcmp(tp,block[i].str) && check(x,y,i)){//strcmp(tp,block[i].str)�ж� ��ǰλ��(x,y)�Ƿ��Ѿ��ظ����ù���Ƭ
            vis[i]=1;
            //strcpy(tp,block[i].str);//ac
            memcpy(tp,block[i].str,sizeof(tp));//ac
            mp[x][y]=i;
            if(dfs(cur+1))
                return 1;
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        cnt=n*m;
        Icnt=Ocnt=Fcnt=0;
        for(int i=0;i<cnt;i++){
            scanf("%s",block[i].str);
            for(int j=0;j<4;j++){
                if(block[i].str[j] == 'I')
                    Icnt++;
                else if(block[i].str[j] == 'O')
                    Ocnt++;
                else
                    Fcnt++;
            }
        }
        if(Icnt != Ocnt || Fcnt!=(n+m)*2){
            printf("NO\n");
            continue;
        }
        sort(block,block+cnt);
        if(dfs(0))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
*/
