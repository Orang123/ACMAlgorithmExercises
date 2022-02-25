#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<string>
#define N 2100
using namespace std;
//ac 250ms ��С�߸���
/*
����:����m������Ϊn"01"��,ĳЩ������'*',�����Ĵ����Խ�
'*'����Ϊ'0'��'1'��ʾ��2����,�ظ��Ĵ�ֻ��һ������,����
Ҫ�������еĴ�,���������ֻ��һλ��ͬ,������������1�β���
ͬʱ����,����ÿ�β���ֻ������һ����,����Ҫ�������еĴ�����
��Ҫ���ٴβ���.
eg:������*01 100 011���Ա�ʾΪ001 101 100 011,����*01�Ǳ�ʾ����
001��101.
����:http://poj.org/problem?id=2724
˼·:����Ԥ�������еĴ�,����'*'�Ĵ�����Ϊ'0'��'1'2����,set<string>����,
����'*'�Ĵ�ֱ�Ӳ���set����,���������չ���ظ�����,�������д���������i��j,
ֻ��һλ��ͬ,����i��j֮���˫���,��ô��i�ʹ�jһ����һ������������1һ����
ż����1,����һ����������ż�����ڵ�һ����һ��ֻ��1������,��Ϊ��2������1�ĸ�������
ż����������,������������ȫ��ͬ,����2�������ٻ���2λ��ͬ,����i��j֮�佨��
��������һ����ż-��-ż-������,���㽻��Ⱦɫ��,����ʵ�����������Ӧ��Ҳ���������,
��˹���������ͼһ���Ƕ���ͼ,������ͼ�е�ÿ���ߴ������һ�ο���������2����,
��ʵ�ʰ���һ����ѡ����2����i,j�����,���������i�����ű�ĵ�k,����ʱi�Ѿ���������,
��Ϊ���������ʣ�µĴ�k,����ѡ������ʣ�µı�i-k����,ֻ����ʣ����Ǹ���������Ĵ�.
��������ת��Ϊ��ѡ�񾡿����ٵı߸������еĵ�,��˾���������ͼ�е���С�߸���.
����ͼ����С�߸���=������-��С���㸲��=������-���ƥ��.

ע��:
1.����ʵ�ʹ��ɵ�ͼ���ܻẬ�й�����,Ҳ���ǿ��ܲ�������С�߸���,��Ϊ��������Զ
û�б��ܸ��ǵ�,������ֻ���ñ߱�ʾ�������������,���ڹ�����ҲֻҪ��������һ�μ���,
����С�߸���=������-���ƥ��,����������ȷ��.
2.string������ѭ����ֵ����,string������char�ַ�����,����Ϊһ�����忴����,ÿ�ζ���O(n)
����һ��ԭ�ַ���,��TLEҪ�����û��ַ�Ĵ���,����ֻ�踴�Ƶ�ַ��ֱ������string����.

*/

int n,m,cnt,head[N],vis[N],match[N],ans;
vector<string> node;//node��¼��չ�����в��ظ��Ĵ�
vector<int> G[N];
set<string> s;

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
//����ע��stringֵ���ݻ�TLE,��Ϊÿ�ζ���O(n)��ֵһ���ַ���,������һ��ĸ��Ӷ�
//��ȡ���ô��ݻ��ߵ�ַָ�봫��,���������踴�������ַ���
int judge(int x,int y){
    int num=0;
    for(int i=0;i<n;i++){
        if(node[x][i]!=node[y][i])
            num++;
    }
    return num == 1;
}

void init(){
    cnt=ans=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    s.clear();
    node.clear();
    for(int i=1;i<N;i++) G[i].clear();
}

int main(){
    int pos;
    string str,s1,s2;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            cin >> str;
            pos=str.find('*');
            if(pos!=-1){//��str��ǰ���봮��'*'�򷵻ص���'*'����λ���±�,���򷵻�-1
                s1=s2=str.substr(0);//s1��s2Ϊstr�ĸ��ƴ�
                //string s1(str),s2(str);
                s1[pos]='0';//�޸�s1��ǰ'*'Ϊ'0'
                s2[pos]='1';//�޸�s1��ǰ'*'Ϊ'1'
                if(s.find(s1) == s.end()){//���s�в���s1,���ص���s�����һ��Ԫ�صĵ�����
                    s.insert(s1);//s�в���s1
                    node.push_back(s1);//��¼���в��ظ���
                }
                if(s.find(s2) == s.end()){
                    s.insert(s2);//s�в���s2
                    node.push_back(s2);
                }
            }
            else{//str����'*'
                if(s.find(str) == s.end()){
                    s.insert(str);//s�в�������չλ��str
                    node.push_back(str);
                }
            }
        }
        int len=node.size();
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++){
                if(judge(i,j)){//�жϴ�i�ʹ�j �Ƿ�ֻ��һλ��ͬ
                    G[i+1].push_back(j+1);//����˫���
                    G[j+1].push_back(i+1);
                }
            }
        }
        for(int i=1;i<=len;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",len-ans/2);//��С�߸���=������-���ƥ�� ��Ϊ���������е�������ͼansҪ��2
    }
    return 0;
}

/*
//ac 235ms string���ô���
//ac 219 stringָ���ַ����
#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<string>
#define N 2100
using namespace std;

int n,m,cnt,head[N],vis[N],match[N],ans;
vector<string> node;//node��¼��չ�����в��ظ��Ĵ�
vector<int> G[N];
set<string> s;

int dfs(int u){
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v] || dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
//����ע�ⲻҪֵ����string������Ϊ����,��TLE
int judge(string &x,string &y){//ָ���ַ���� judge(string *x,string *y)
    int num=0;
    for(int i=0;i<n;i++){
        if(x[i]!=y[i])//ָ���ַ���� if((*x)[i]!=(*y)[i])
            num++;
    }
    return num == 1;
}

void init(){
    cnt=ans=0;
    memset(match,0,sizeof(match));
    memset(head,-1,sizeof(head));
    s.clear();
    node.clear();
    for(int i=1;i<N;i++) G[i].clear();
}

int main(){
    int pos;
    string str,s1,s2;
    while(scanf("%d%d",&n,&m) && n+m){
        init();
        while(m--){
            cin >> str;
            pos=str.find('*');
            if(pos!=-1){//��str��ǰ���봮��'*'�򷵻ص���'*'����λ���±�,���򷵻�-1
                s1=s2=str.substr(0);//s1��s2Ϊstr�ĸ��ƴ�
                //string s1(str),s2(str);
                s1[pos]='0';//�޸�s1��ǰ'*'Ϊ'0'
                s2[pos]='1';//�޸�s1��ǰ'*'Ϊ'1'
                if(s.find(s1) == s.end()){//���s�в���s1,���ص���s�����һ��Ԫ�صĵ�����
                    s.insert(s1);//s�в���s1
                    node.push_back(s1);//��¼���в��ظ���
                }
                if(s.find(s2) == s.end()){
                    s.insert(s2);//s�в���s2
                    node.push_back(s2);
                }
            }
            else{//str����'*'
                if(s.find(str) == s.end()){
                    s.insert(str);//s�в�������չλ��str
                    node.push_back(str);
                }
            }
        }
        int len=node.size();
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++){
                //ָ���ַ���� judge(&node[i],&node[j])
                if(judge(node[i],node[j])){//�жϴ�i�ʹ�j �Ƿ�ֻ��һλ��ͬ ���ܴ���string��Ϊ��ʽ���� �� TLE
                    G[i+1].push_back(j+1);//����˫���
                    G[j+1].push_back(i+1);
                }
            }
        }
        for(int i=1;i<=len;i++){
            memset(vis,0,sizeof(vis));
            if(dfs(i)) ans++;
        }
        printf("%d\n",len-ans/2);//��С�߸���=������-���ƥ�� ��Ϊ���������е�������ͼansҪ��2
    }
    return 0;
}
*/
