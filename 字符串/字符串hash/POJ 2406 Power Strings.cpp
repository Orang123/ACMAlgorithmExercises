/*
����:����һ���ַ���,����������ַ������ɶ��ٸ���ͬ���Ӵ����ɵ�,
Ҫ���Ӵ�����������.��Щ�Ӵ�֮�䲻�����ص�,��λ�ò����н���,����
�Ƿָ��Ҹպý���������.
����:
����һ����,����һ���ظ����ص��Ӵ�,�ظ����������ֵ,
Ҳ���Ǵ���Сѭ����,��С����.
�ַ������Ȳ��ᳬ��10^6
����:http://poj.org/problem?id=2406
˼·:next�����ѭ���ڴ�������һ������.��������ժ��https://blog.csdn.net/wangcong9614/article/details/47271539
����Ϊlen���ַ�������Сѭ���ڵĳ�����len-next[len]�����ǰ�����Ϊs��
��ô���len%s==0��Ҳ�����ַ�������������ѭ���ڳ��ȣ���˵������ַ�������ȫѭ���ģ�
Ҳ��������abcabc��ababab���������ô�ڱ����У�����ַ�������ȫѭ����ϵģ�����ֻ
Ҫ���len/s��ok�ˡ����len%s!=0��˵���ַ���������ȫѭ����ϵģ�����abcdab��abcabce������
�������1�ͺ��ˡ�
����aabaabaa,next[8]=5,8%(8-5)!=0,ʵ�������������ͬǰ��׺��aabaa(ǰ׺�±귶Χ0~4)
aabaa(��׺�±귶Χ3~7),����3~4������λ�õ��Ӵ�"aa"���ص���,�������������ָ����Ӵ�,
Ҳ���ǲ�������ѭ����,��ô����len��������(len-next[len])�����,������������Ϊһ������
��ѭ����,���1.

ע��j-nxt[j]��������ѭ���ڵĳ���,j/(j-nxt[j])������ѭ������.
��j-nxt[tp],nxt[tp]<nxt[j],j-nxt[tp]��õĲ������ѭ����,ѭ���ڽϴ�,ѭ����������.
*/
//ac 392ms �ַ���hash
#include<cstdio>
#include<cstring>
#define p 233
#define N 1000100
typedef unsigned long long ull;
ull h[N],powr[N];
char s[N];
int len;
bool check(int x,ull hVal){
    for(int i=x;i<=len-x;i+=x){
        if(h[i+x]-h[i]*powr[x] != hVal)
            return false;
    }
    return true;
}
int main(){
    powr[0]=1;
    for(int i=1;i<N;i++)
        powr[i]=powr[i-1]*p;
    while(scanf("%s",s+1) && strcmp(s+1,".")!=0){
        len=strlen(s+1);
        h[0]=0;
        for(int i=1;i<N;i++)
            h[i]=h[i-1]*p+(s[i]-'a'+1);
        for(int i=1;i<=len;i++){
            if(len % i == 0 && check(i,h[i])){
                printf("%d\n",len/i);
                break;
            }
        }
    }
    return 0;
}

/*
//ac 125ms �±��0��ʼ next����Ӧ�������Сѭ���� kmp
#include<cstdio>
#include<cstring>
#define N 1000010

int next[N],len;
char str[N];

void getNext(){
    len=strlen(str);
    int i=-1,j=0;
    next[0]=-1;
    while(j<len){
        if(i == -1 || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    while(scanf("%s",str) && str[0]!='.'){
        getNext();
        if(len%(len-next[len]) == 0)
            printf("%d\n",len/(len-next[len]));
        else
            printf("1\n");
    }
    return 0;
}
*/

/*
//ac 110ms �±��1��ʼ
#include<cstdio>
#include<cstring>
#define N 1000010

int next[N],len;
char str[N];

void getNext(){
    len=strlen(str+1);
    int i=0,j=1;
    next[1]=0;
    while(j<=len){
        if(!i || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    while(scanf("%s",str+1) && str[1]!='.'){
        getNext();
        if(len%(len+1-next[len+1]) == 0)
            printf("%d\n",len/(len+1-next[len+1]));
        else
            printf("1\n");
    }
    return 0;
}
*/
