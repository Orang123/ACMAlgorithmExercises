/*
����:ժ������
����һ����p,�ҳ���p���Ӵ�,�ô�����p��ǰ׺Ҳ��p�ĺ�׺��
��С����������з���Ҫ��Ĵ��ĳ��ȡ�
plen<=4*10^5.
����:http://poj.org/problem?id=2752
˼·:ժ�Բ���:https://blog.csdn.net/niushuai666/article/details/6968507
next����ĶԳ���.
�����Ҳ��next�����һ��Ӧ�á�
��Ȼ����ģʽ��ƥ�䣬����Ҫ�����ģʽ����next���顣���ǵ�һ����
Ȼ�����ǿ�ʼ������ô��next��������ɲ���ǰ׺��׺��ƥ�䡣
���ǻ����������Ǹ��ַ���Ϊ������˵��һ�¡�
  �±�   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
  ģʽ�� a  b  a  b  c  a  b  a  b  a  b  a  b  c  a  b  a  b
 next[i] -1 0  0  1  2  0  1  2  3  4  3  4  3  4  5  6  7  8  9
1����i = lenʱ��next[len] = next[18] = 9��˵�������ַ���ǰ9���ַ��ͺ�9���ַ���ͬ������9������Ҫ��ġ�
2��next[9] = 4��˵����0-8��ǰ4���ַ��ͺ�4���ַ���ͬ����Ϊ��1����ǰ9���ַ��ͺ�9���ַ���ͬ�����ԣ�S��
��0-3����5-8����0-3�ֵ���9-12,5-8�ֵ���14-17�����Խ����0-3����14-17����4Ҳ����������ġ�
3��next[4]=2��ͬ2�����ǿ��Եõ�2Ҳ����������ġ�
4��next[2]=0������û����ͬ��ǰ׺�ͺ�׺�ˣ���ʱ�����Ѿ��ҵ������S��������ǰ׺�ͺ�׺��
5���������2,4,9,18.
���ԣ����ǿ����Ƶ������Ľ��ۣ�����next[i]��=0�ģ�����ģʽ����ǰ׺�ͺ�׺��ͬ���ַ�����
*/

//ac 516ms �ַ���hash
#include<cstdio>
#include<cstring>
#define p 233 //1000007Ҳ��
#define N 400100
typedef unsigned long long ull;
ull h[N],powr[N];
char s[N];
int main(){
    int len;
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1)!=EOF){
        len=strlen(s+1);
        h[0]=0;
        for(int i=1;i<=len;i++)
            h[i]=h[i-1]*p+(s[i]-'A'+1);
        for(int i=1;i<=len;i++)
            if(h[i] == h[len]-h[len-i]*powr[i])
                printf("%d ",i);
        printf("\n");
    }
    return 0;
}

/*
//ac 719ms kmp
#include<cstdio>
#include<cstring>
#include<vector>
#define N 400010
using namespace std;

int plen,nxt[N];
char p[N];
vector<int> ans;

void getNext(){
    plen=strlen(p);
    nxt[0]=-1;
    int i=-1,j=0;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    while(scanf("%s",p)!=EOF){
        ans.clear();
        getNext();
        ans.push_back(plen);
        for(int i=plen;nxt[i];i=nxt[i])
            ans.push_back(nxt[i]);
        for(int i=ans.size()-1;i>=0;i--){
            printf("%d",ans[i]);
            if(i)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
*/
