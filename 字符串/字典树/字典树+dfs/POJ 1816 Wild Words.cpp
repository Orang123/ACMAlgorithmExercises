/*
����:ժ������
����n��ģʽ�������г���Сд��ĸ�⣬������һ���ַ���
*����ɿյ������ַ�����Ȼ���ٸ���m���ַ��������ж���
��ģʽ��������֮ƥ�䡣
˵��:'*'�ַ�����һ��Ҳ��ƥ��.
n<=100000,m<=100,ģʽ������<=6,�ı�������<=20.
����:http://poj.org/problem?id=1816
˼·:����'*'����Ҫö��ƥ���ı��������ַ�,����Ҫdfs����
ʵ��,�����ÿ��ģʽ�������ı���������һ��dfsƥ��,���ӶȺܴ�,
�϶���TLE,����ģʽ�����Ȳ�����6,��Щģʽ���ַ������ܹ�����ĳЩ
ģʽ����ǰ׺,��Ȼ���Խ����е�ģʽ��������һ���ֵ�����,����ƥ��ʱ
������ͬ��ǰ׺ʵ��ֻ������һ��,�������ص���ģʽ��Ҳ�������ӽڵ�
һֱ������ȥ,����ֻ����һ��.���ֱ�ӶԹ����õ��ֵ������ı�����ƥ��,
ֻ��һ��dfs����ͳ�Ƴ���������ƥ��������ģʽ�����.

��Ҫע��:
1.ģʽ���������ظ�,������ֵ�������ģʽ�����,Ҫ��һ��vector���ظ���ǰ׺
�ı��ȫ�ӽ�ȥ.
2.dfs����'*'��ö��,���Բ�ƥ��,�������п��ܵ���dfs�������ظ��ķ���,������ʱ
Ҫ�Ա������.
*/

/*
һ��dfsö�ٳ����ظ���ŵ�����
ģʽ��:*j*j
�ı���:jj��jjj
�����ı���jj,ģʽ��������'*'������ƥ��,���������ߵ��ֵ�����Ҷ�ӽڵ�ڶ���'j'.
���Ƕ����ı���jjj,ģʽ���е�����'*'��ȻҪ��һ���ǲ���ƥ���,���������ߵ��ֵ���
��Ҷ�ӽڵ�ڶ���'j',�������ƥ��,��ôʵ�ʾ���2�ַ���,Ҫô��һ��'*'��ƥ��,Ҫô
�ڶ���'*'��ƥ��.
*/

//ac 891ms
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 600010
using namespace std;

int n,m,tr[N][28],cnt,slen;
char s[30];
vector<int> wordId[N],ans;

int newNode(){
    cnt++;
    for(int i=0;i<28;i++)
        tr[cnt][i]=0;
    wordId[cnt].clear();
    return cnt;
}

int check(char x){
    if(x == '?')
        return 26;
    if(x == '*')
        return 27;
    return x-'a';
}

void insertWord(int id){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=check(s[i]);
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordId[rt].push_back(id);//ģʽ�������ظ�
}

void dfs(int rt,int i){
    //���'*'��ѡȡ�������ǰ�濼��,�����TLE,��֪ԭ��
    if(tr[rt][27]){//27 ����'*'�����
        //j=i����� ����'*'��һ���ַ�Ҳ��ƥ��,�����������ı���"the" ģʽ��"??e*"�����,
        //��������'*'��ʵ�ʾͿ��Բ�ƥ��,��"??e*"��Ȼ�ǿ������"the"��
        for(int j=i;j<=slen;j++)//ö��'*'����Դ�i��ʼ�ļ����ı����ַ�
            dfs(tr[rt][27],j);
    }
    //����ǰ�ֵ���ǰ׺����ģʽ��,�����ı���sƥ����� ���ɼ�¼ŷ�������.
    if(wordId[rt].size() && i == slen){
        for(int i=0;i<wordId[rt].size();i++)
            ans.push_back(wordId[rt][i]);
        return;
    }
    if(i == slen)//�ı����Ѿ�ƥ����,�ֵ�����ǰ׺��û�ܹ�������������ģʽ���ͷ���
        return;
    //������ĸ ���
    if(s[i]>='a' && s[i]<='z'){
        if(tr[rt][s[i]-'a'])
            dfs(tr[rt][s[i]-'a'],i+1);
    }
    //26 '?'�����
    if(tr[rt][26])
        dfs(tr[rt][26],i+1);
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        cnt=-1;
        newNode();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            insertWord(i);
        }
        while(m--){
            ans.clear();
            scanf("%s",s);
            slen=strlen(s);
            dfs(0,0);
            if(ans.size()){
                sort(ans.begin(),ans.end());
                printf("%d",ans[0]);
                for(int i=1;i<ans.size();i++){
                    if(ans[i]!=ans[i-1])//�ظ���Ų����
                        printf(" %d",ans[i]);
                }
                printf("\n");
            }
            else
                printf("Not match\n");
        }
    }
    return 0;
}
