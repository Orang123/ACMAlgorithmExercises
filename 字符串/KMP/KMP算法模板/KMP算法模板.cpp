/*
����:
KMP�㷨��һ�ָĽ����ַ���ƥ���㷨����D.E.Knuth��J.H.Morris��V.R.Pratt
��1977�귢��������ǳ���Ϊ��Ŭ�ء�Ī��˹�������ز��������KMP�㷨��.
һ������Ϊslen���ı���s,��һ������Ϊplen��ģʽ��p,����Ҫ����ı���s
�Ƿ����ģʽ��p,�����������һ������ƥ���λ��,�����������-1.
����next�����kmpƥ����ʱ�临�Ӷ�ΪO(slen+plen) �ռ临�Ӷ�O(slen+plen)

��ض���:
1.ǰ׺:������λ�ַ���������ĩλ�ַ����Ӵ�.
2.��׺:����ĩλ�ַ�����������λ�ַ����Ӵ�.
3.���ͬǰ��׺(�����ǰ��׺):ģʽ��p��ĳ�������Ӵ���ǰ׺�ͺ�׺��ͬ����Ӵ�.
����next����Ķ��� �ǽ����������±��0��ʼ,��ʼֵΪ-1�����
4.next���鶨��:���ı���s��ģʽ��p��ƥ��ʱ,ģʽ��pҪ���˵�����λ���±�.
5.next[i]:��ֵ = ��i+1λ�ַ�ǰ��iλ�ַ����ɵ��Ӵ������ͬǰ��׺�ĳ���,�����ǰ׺��׺�����ܵ���������,����Ҫ�����һ�����һ���ַ�.
Ҳ�ǵ�ģʽ��p[i]ʧ��ʱ,ģʽ��p��Ҫ���»��˵�λ��.
˵��:next�����ֵ�͵���ģʽ���Ӵ����ͬǰ��׺����ֵ����һλ,���ʼ��һ��ֵΪ-1.

����㷨ʱ�ο�����:
https://blog.csdn.net/v_july_v/article/details/7041827#t10  v_JULY_v����д�ķǳ���ϸ,ǿ���Ƽ�
https://blog.csdn.net/yyzsir/article/details/89462339
https://blog.csdn.net/dark_cy/article/details/88698736
*/
//����next�����kmpƥ����ʱ�临�Ӷ�ΪO(slen+plen)
#include<cstdio>
#include<cstring>
#define N 1100
using namespace std;

int next[N],slen,plen;
char s[N],p[N];

//��ͨnext����
//ʱ�临�Ӷ�O(plen)
void getNext(){
    next[0]=-1;
    int i=-1,j=0;
    //ģʽ��pֻ�жϵ������ڶ�λ,��Ϊÿ��i == -1 �� p[i] == p[j]ʱ,next[++j]=++i j���ټ�һλ
    //ģʽ�������һλ�жϵ���ǰj-1λ�����ͬǰ��׺�ĳ���
    while(j<plen-1){
        /*
        i == -1��ʾ:
        ֮ǰ����������ͬǰ��׺�Ѿ�����������,��Ҫ
        ���¿�ʼ�����µ����ͬǰ��׺,��ʼ״̬���Ϊ-1,
        ��ʾ֮ǰ��������ͬǰ��׺.
        p[i] == p[j]��ʾ,���ͬǰ��׺���ȿ����ټ�1,
        ��:next[j+1]=next[j]+1
        */
        if(i == -1 || p[i] == p[j]){
            i++;//i++ j++ ��������ж����ͬǰ��׺�Ƿ�������
            j++;
            next[j]=i;//ǰj���ַ����ɵ��Ӵ����ǰ��׺�ĳ���Ϊi,��Ϊ�±��0��ʼ,�����±��Ѿ���j+1���ַ���
        }
        else//p[i]!=p[j]ʱ,���ǽ�ģʽ������,���ǳ��Ƚ϶̵����ͬǰ��׺�Ƿ��п���ƥ������.
            i=next[i];
    }
}

//�Ż��汾next����,next[j]��¼��λ�õ��ַ����Ǻ͵�ǰ��jλ�ַ���ͬ
//ʱ�临�Ӷ�O(plen)
//�Ż������next�������ǰ��׺��ͬ,next��ֵҲ��ͬ,
//eg:abcabcabc ��Ӧ�Ż�next��ֵ: -1 0 0 -1 0 0 -1 0 0
//abcabcabc δ�Ż�next��ֵ: -1 0 0 0 1 2 3 4 5
//ע��:�Ż���next���鲻����������й�ѭ���ڵ�����,��Ϊnext[i]����ʾ��,
//�����Ѿ�����0~i-1�����ͬǰ��׺�ĳ�����,���Ǳ�ʾ��һ��ƥ��λ��
void betterNext(){
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j]){
            i++;
            j++;
            //���ͬǰ��׺��һλ�������ͬ,ֱ�Ӽ�¼����
            if(p[i]!=p[j])
                next[j]=i;
            /*
            �����һλ��ͬ,��next[j]��¼ ǰ׺�� ǰiλ��Ӧ�����ͬǰ��׺��λ��,��next[i]
            p[next[i]]��¼��λ���ַ�һ����p[i]�ǲ�ͬ��,��Ϊiһ��С��j,�Ѿ�ͳ�ƹ���next����
            һ�����Ż����˵�.
            */
            else
                next[j]=next[i];
        }
        else//p[i]!=p[j] ���ǽ�ģʽ������,���ǳ��Ƚ϶̵����ͬǰ��׺�Ƿ��п���ƥ������.
            i=next[i];
    }
}

//�ı���S��ģʽ��P��ʼƥ��
//ʱ�临�Ӷ�O(slen)
int kmp(){
    int i=0,j=0;//S��P�±��0��ʼ
    while(i<slen && j<plen){
        /*
        j == -1,��ʾ֮ǰƥ����Ӵ��Ѿ�������ƥ����,ģʽ��P��Ҫ��ͷ��ʼ���ı���S����һλ��ʼ�����

        s[i]==p[j]ʱ �����Ƚ�S��P����һλ�ж��Ƿ����
        */
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        //s[i]!=p[j]ʱ,ģʽ��p��Ҫ���˵�next[j]λ�ü�����S[i]�Ƚ��Ƿ����,s[i] �Ƿ���� p[next[j]]
        //��Ϊs[i]��p[j]�����,��s[i]��p[j]֮ǰ����ͬ��һ��,�ٴ�ƥ��ʱ,ѡ��ģʽ����ͬ��ǰ׺��һ�κ�s[i]�Ƚ�
        //�൱��ģʽ��������j-next[j]λ
        else
            j=next[j];
    }
    if(j == plen)//ģʽ��ƥ�����
        return i-j+1;//����ģʽ��p���ı���s�е�һ��ƥ���λ��,�������±�+1
    else//�ı���s��δ�ҵ�ģʽ��p ����-1
        return -1;
}

//����next�����kmpƥ����ʱ�临�Ӷ�ΪO(slen+plen)

int main(){
    scanf("%s",s);//bacbababadababacambabacaddababacasdsd
    scanf("%s",p);//ababaca
    slen=strlen(s);//�ı���s����
    plen=strlen(p);//ģʽ��p����
    getNext();
    //betterNext();
    printf("%d",kmp());//11
    return 0;
}

/*
input
ababcabcacbab
abcac

bacbababadababacambabacaddababacasdsd
ababaca

output
6
11
*/

/*
//kmp �±��1��ʼ
#include<cstdio>
#include<cstring>
#define N 1100
using namespace std;

int next[N],slen,plen;
char s[N],p[N];

void getNext(){
    next[1]=0;
    int i=0,j=1;//�±��1��ʼ,��˲��Ϸ���ʼֵΪ0,������-1,���Ϸ���ʼֵ�ǵ�һ����ʼ�±��1.
    while(j<plen){
        if(!i || p[i] == p[j]){//���Ϸ�ֵΪi == 0
            i++;
            j++;
            next[j]=i;
        }
        else
            i=next[i];
    }
}

void betterNext(){
    next[1]=0;
    int i=0,j=1;
    while(j<plen){
        if(!i || p[i] == p[j]){
            i++;
            j++;
            if(p[i]!=p[j])
                next[j]=i;
            else
                next[j]=next[i];
        }
        else
            i=next[i];
    }
}

int kmp(){
    int i=1,j=1;
    while(i<=slen && j<=plen){
        if(!j || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j == plen+1)
        return i-j+1;
    else
        return -1;
}

int main(){
    scanf("%s",s+1);//�ı�����ģʽ���±궼��1��ʼ
    scanf("%s",p+1);
    slen=strlen(s+1);
    plen=strlen(p+1);
    //getNext();
    betterNext();
    printf("%d",kmp());
    return 0;
}
*/

/*
//��ͨ�ı���ƥ������
//ʱ�临�Ӷ�O(slen*plen)
#include<cstdio>
#include<cstring>
#define N 1100
using namespace std;

int slen,plen;
char s[N],p[N];

int match(){
    slen=strlen(s);
    plen=strlen(p);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(s[i] == p[j]){
            i++;
            j++;
        }
        else{//s[i]��p[j]�����ʱ,��ģʽ��p���ݵ�0,���¿�ʼ��֮ǰ�ı�����ʼ��Եĵ�һ��λ�õ���һλ�ÿ�ʼ�������
            i=i-j+1;//ע�����ﲻ��д��i-=j+1,����ʵ�ʵı����i=i-(j+1)=i-j-1 ����� ��ѭ��
            j=0;
        }
    }
    if(j == plen)
        return i-j+1;
    else
        return -1;
}

int main(){
    scanf("%s",s);
    scanf("%s",p);
    printf("%d",match());
    return 0;
}
*/
