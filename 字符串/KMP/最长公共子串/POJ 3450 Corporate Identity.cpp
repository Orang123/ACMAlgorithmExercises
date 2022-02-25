/*
����:
n���Ĵ���������ǵ�������Ӵ����������������Ӵ����������IDENTITY LOST����
������ڶ��������Ӵ���������ֵ�����С����һ����
n<=4000,ÿ��������<=200.
����:http://poj.org/problem?id=3450
˼·:ö�ٵ�һ�����ĸ�����׺ȥ�����മƥ��,�����С��ƥ�䳤��,
�ڸ�����Сƥ�䳤����ȡ����ƥ�䳤��,�������һ��,��ȡ�ֵ����С��.

�Լ�������д�˸�������󳤶ȵ�����,����pos��һ����������˸������35,��֪��ԭ��
*/
//ac 422ms ö�ٵ�һ�����ĸ����Ӵ��ֱ��ʣ�µĴ���ʼƥ��,��¼��С�Ĺ����Ӵ�,���ڸ��������Ӵ����������
//ʱ�临�Ӷ�O(200*4000*200)=1.6*10^8 �������Ǻܺ�ʱ��,��Ҳ����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,plen,ans;
char s[N][M];

void getNext(char *p){
    plen=strlen(p);
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
            cnt=max(cnt,j);//��¼����ƥ�䳤��
        }
        else
            j=nxt[j];
    }
    return cnt;
}

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=0;i<n;i++)
            scanf("%s",s[i]);
        len=strlen(s[0]);
        //O(200*4000*200)=1.6*10^8 �������Ǻܺ�ʱ��,��Ҳ����
        for(int i=0;i<len;i++){//��һ������λ��i��ʼ�ĺ�׺
            tp=INF;
            for(int j=1;j<n;j++)//s[0]+i��Ϊģʽ��ȥ��������ƥ�� ����С����ƥ�䳤��,���ǵ�ǰ�����Ӵ�
                tp=min(tp,kmp(s[j],s[0]+i));
            if(tp>ans || (tp == ans && strcmp(s[0]+i,s[0]+pos)<0)){
                ans=tp;//��¼�����Ӵ�����
                pos=i;//��¼��׺��ʼ��λ��
            }
        }
        if(ans){
            for(int i=pos;i<pos+ans;i++)
                printf("%c",s[0][i]);
        }
        else//�����ڹ����Ӵ�
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}

/*
//ac 438ms ���ճ��ȴ�С��������,ѡ�񳤶���С���Ӵ���Ϊģʽ���������ı���ƥ��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,plen,ans;
struct S{
	char str[M];
	int len;
	bool operator <(const S &x)const{
		return len<x.len;//���ճ��ȴ�С��������
	}
}s[N];

void getNext(char *p){
    plen=strlen(p);
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p){
    getNext(p);
    slen=strlen(s);
    int i=0,j=0,cnt=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
            cnt=max(cnt,j);
        }
        else
            j=nxt[j];
    }
    return cnt;
}

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=0;i<n;i++){
            scanf("%s",s[i].str);
        	s[i].len=strlen(s[i].str);
		}
		sort(s,s+n);
        for(int i=0;i<s[0].len;i++){
            tp=INF;
            for(int j=1;j<n;j++)
                tp=min(tp,kmp(s[j].str,s[0].str+i));
            if(tp>ans || (tp == ans && strcmp(s[0].str+i,s[0].str+pos)<0)){
                ans=tp;
                pos=i;
            }
        }
        if(ans){
            for(int i=pos;i<pos+ans;i++)
                printf("%c",s[0].str[i]);
        }
        else
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}
*/

/*
//ac 360ms strstr���� ö�ٵ�һ�����������Ӵ�
//strstr(str1,str2) ���������ж��ַ���str2�Ƿ���str1���Ӵ���
//����ǣ���ú�������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL��
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,len,ans;
char s[N][M],str[M];

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        ans=0;
        for(int i=0;i<n;i++)
            scanf("%s",s[i]);
        len=strlen(s[0]);
        for(int i=0;i<len;i++){//ö�ٵ�һ�����ĳ�ʼλ��
        	int k=0;
        	for(int j=i;j<len;j++){//ö�ٵ�һ�����Ľ���λ��j
        		str[k++]=s[0][j];
        		str[k]='\0';
        		int flag=0;
        		for(int j=1;j<n;j++){//�ж����മ�Ƿ����str
        			if(!strstr(s[j],str)){//�������һ��������������Ӵ�str,��˵��str����������Ӵ�
        				flag=1;
        				break;
					}
				}
				if(!flag && (k>ans || (k == ans && strcmp(str,s[0]+pos)<0))){
        			ans=k;
        			pos=i;
				}
			}
        }
        if(ans){
            for(int i=pos;i<pos+ans;i++)
                printf("%c",s[0][i]);
        }
        else
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}
*/

/*
//�ο�����:https://blog.csdn.net/kalilili/article/details/43868029
//���Լ�д�Ķ��ִ� �е�����
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 4100
#define M 210
#define INF 0x3f3f3f3f
using namespace std;

int n,nxt[M],len,slen,pos;
char s[N][M];

void getNext(char *p,int plen){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int kmp(char *s,char *p,int plen){
    getNext(p,plen);
    slen=strlen(s);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=nxt[j];
    }
    return j == plen;
}

int check(int mid){
	int flag1,flag2=0;
	pos=-1;
	printf("len-mid=%d\n",len-mid);
	for(int i=0;i<=len-mid;i++){
		flag1=0;
		for(int j=1;j<n;j++){
			if(!kmp(s[j],s[0]+i,mid)){
				flag1=1;
				break;
			}
		}
		if(!flag1 && (pos == -1 || strcmp(s[0]+i,s[0]+pos))){
			pos=i;
			printf("pos=%d\n",pos);//��֪ΪΪʲô��һ������ ���һ��pos��Ī������35������
			flag2=1;
		}
	}
	return flag2;
}

int main(){
    int tp,pos;
    while(scanf("%d",&n) && n){
        for(int i=0;i<n;i++)
            scanf("%s",s[i]);
        len=strlen(s[0]);
        int l=0,r=len,mid;
        while(l<r){
        	mid=(l+r)/2;
        	//printf("mid=%d\n",mid);
        	if(check(mid))
        		l=mid+1;
        	else
        		r=mid;
		}
		printf("pos=%d\n",pos);
        if(mid){
            for(int i=pos;i<pos+mid;i++)
                printf("%c",s[0][i]);
        }
        else//�����ڹ����Ӵ�
            printf("IDENTITY LOST");
        printf("\n");
    }
    return 0;
}
*/
