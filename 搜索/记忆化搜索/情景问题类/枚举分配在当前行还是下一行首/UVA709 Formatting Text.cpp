/*
����:ժ������
���¶��䳤�����Ƴ���Ϊn��Ȼ���ڸ���һƪ���£������ɸ����ʣ��Կ��н�����
����Ҫ����������ʹ�����µ�badnessԽС��badness�ļ��㷽�������һ��ֻ��
һ�����ʵĻ��������ʵĳ���С��n����badness ����500������Ϊ0��
��һ���ж�����ʣ�ÿ��������֮���badness = ��c - 1) ^ 2 (cΪ�������ʵĿո�������
Ҫ��ÿ�п��Ƴ�����n������ǰһ�����ʶ�ͷ����һ�����ʶ�β��һ�����ε�������⣩��
n<=80,��������һ�γ�������Ϊ10000.
����:https://www.luogu.com.cn/problem/UVA709
˼·:��Ϊ���µĹ淶�����һ���ж������,��ôһ������ͷβ���붼�е����νӲ���.
Ҳ����˵������Ҫ��������֮��ļ�� ʹ������ӵ����һ�������ܸպ���������,����
�����ļ�϶����ǲ�ȷ����,������˵����֮��ļ�϶ԽСԽ��,�п���ǰ�浥�ʳ��ȶ��϶�,
�����϶�Ƚ�С,���һ�����ʳ��Ƚϳ�,��Ҫ�����һ������ǡ��������β��,֮��ļ�϶��
��ͻ�Ƚϴ�,���badness�ͻ�ϴ�,���ǿ��Կ��ǽ�ǰ�泤�Ƚ�С�ĵ��ʼ�϶�����Ĵ�һ��,
ʹ�ýϴ󳤶ȵ�����ǡ�÷�������һ��,���Һͺ��浥�ʵļ�϶���ܵ����ý�С,���������
badness�����,��֮��õ�����ǲ���ȷ����,��Ҫö�����м�϶�����Ŀ�����,�������������,
���ڵ�i�����ʷ�����ĳһ�е�j��λ�����״̬ �ںܶ������϶����»��ظ�����,�����ص���
����.��Ҫ�������¼����.��ֹ״̬���ǽ����е��ʶ��������ʱ.

��˼��仯����.dp[i][j]��ʾ��i�����ʷ�����ĳһ��,��֮ǰ�Ѿ�������j��λ��ʱ,��i������
����������е��ʷ���ʱ���ܲ�������Сbadness.
path[i][j]=p��¼��i�������ڵ�j+1��λ�ú�������Ŀո���ռ�����һ��λ��Ϊp.
path[i][j]=0,�����i�����ʺ�û�е���β����,����������з���.

//�ϺõĲ��ͽ���:https://www.cnblogs.com/scau20110726/archive/2012/10/01/2709458.html
*/
//ac 10ms ���仯����
//dp[i][j]��ʾ��i�����ʷ�����ĳһ��,��֮ǰ�Ѿ�������j��λ��ʱ,��i�����ʰ������
//���е��ʷ���ʱ���ܲ�������Сbadness.
//path[i][j]=p��¼��i�������ڵ�j+1��λ�ú�������Ŀո���ռ�����һ��λ��Ϊp.
//path[i][j]=0,�����i�����ʺ�û�е���β����,����������з���.
//ʱ�临�Ӷ�O(cnt*80*80)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10005
#define INF 0x3f3f3f3f
using namespace std;

int n,len[N],cnt,dp[N][85],path[N][85];
char str[N],word[N][85];

int dfs(int i,int j){
    if(dp[i][j]!=-1)//dp��ʼ״̬Ҫ����Ϊ-1,��ΪINF����Ҳ�� �����Ϲ淶��״̬,Ҳ��һ���Ϸ�����ֵ,�п���ĳ�ֵ��������޷�ʹ�� ���һ������ǡ������β��
        return dp[i][j];
    dp[i][j]=INF;//��ʼֵ�����
    if(i == cnt+1){//����cnt�������Ѿ��������
        if(!j)//���һ������ǡ���������һ��β��,�Ϸ�״̬ ����0,������badness.
            return dp[i][j]=0;
        else//���Ϸ�״̬,���һ������δ�ܽ��� ���һ��β��,����INF ��Ϊ���Ϸ���ֵ���
            return dp[i][j];
    }
    int res;
    //��i�����ʵ���ռһ��,badnessΪ500
    if(!j){
        dp[i][j]=dfs(i+1,0)+500;
        path[i][j]=0;
    }
    //��i������ �ڵ�ǰ��j��λ�ú�β��պ�ռ����ǰ��,b�����������badness,badness�Ѿ���֮ǰ�ļ�϶�������
    if(j+len[i] == n){//���кϷ�״̬,���һ������һ���ǽ������һ�е�β����
        dp[i][j]=dfs(i+1,0);
        path[i][j]=0;
    }
    else{//��i�����ʵ�ǰ�е�j��λ�ú���,������ռ����ǰ��
        int k=j+len[i]+1;//��i��������ռ��λ��+����һ���ո�
        for(int p=k;p<n;p++){//ö��i+1�����ʺ͵�i������֮��ļ�϶
            if(p+len[i+1]>n)//��ǰ�в��ܱ���i������ռ��,Ҳ���ò��µ�i+1������ʱ����,�Ѿ����ڲ��Ϸ�״̬ ������ö�ٸ����϶
                break;
            int c=p-k;//������֮���badnessΪ(�ո���-1)��ƽ��
            res=dfs(i+1,p);
            if(dp[i][j]>res+c*c){
                dp[i][j]=res+c*c;
                path[i][j]=p;//��¼��i�������ڵ�j+1��λ�ú�������Ŀո���ռ�����һ��λ��Ϊp
            }
        }
    }
    return dp[i][j];
}

void print(int i,int j){
    while(i<=cnt){
        printf("%s",word[i]);
        if(path[i][j] == 0)//path[i][j]Ϊ0����,��i�������Ǳ������һ������,û�е���β��,������з�
            printf("\n");
        else{
            //�����i�����ʺ�Ŀո���,����Ϊpath[i][j]-j-len[i],int k=j+len[i]+1;
            for(int k=1;k<=path[i][j]-j-len[i];k++)
                printf(" ");
        }
        j=path[i][j];//����Ҫ�ȼ�¼����j,�ٸ���i,�ȸ���i��,path[i][j]�Ѿ�����֮ǰ��path[i][j]��
        i++;
    }
    printf("\n");//ÿ�����������һ������.
}

int main(){
    while(scanf("%d",&n) && n){
        cnt=0;
        memset(dp,-1,sizeof(dp));
        getchar();
        while(gets(str) && str[0]!='\0'){
            for(int i=0;str[i]!='\0';){
                sscanf(str+i,"%s",word[++cnt]);
                len[cnt]=strlen(word[cnt]);
                i+=len[cnt];
                while(str[i] == ' ') i++;
            }
        }
        dfs(1,0);
        print(1,0);
    }
    return 0;
}

/*
//����dp
//����̬�滮��Ҫ�ļ�����̫��,��̫��д,����ȷ����ʼ״̬
//��������Ķ�̬�滮ģ��(����dp,����,��λdp,״ѹdp)���鶼��dfs�ݹ�ķ�ʽ���仯���������,����д�����ȽϺ�д,���,���˼·�϶��ǲ���.
//ժ�Բ���:https://blog.csdn.net/u012997373/article/details/38844073
#include <cstdio>
#include <cstring>

const int N = 10005;
const int M = 85;
const int INF = 0x3f3f3f3f;

int L, n;
int dp[N][M];
int p[N][M];//·��
char str[N];
char word[N][M];
int l[N];//���ʳ���

int Min (const int a, const int b) { return a < b ? a: b; }

void handle () {��������

	int j = 0;
	bool flag = 0;
	for (int i = 0; i <= strlen (str); i++) {

		if (str[i] != ' ' && str[i] != '\0') {
			word[n][j++] = str[i];
			flag = 1;
		} else {
			if (flag) {
				word[n][j] = '\0';
				l[n++] = j;
				j = 0;
				flag = 0;
			}
		}
	}
}

void printf_ans (int x, int y) {//���·��

	if (x == n + 1)
		return;
	if (!p[x][y] && !y) {//����һ�в�Ҫ����ո�ֱ�ӻس�
		printf ("%s", word[x - 1]);
	} else {

		printf ("%s", word[x - 1]);
		if (x != n) {
			for (int i = y + l[x - 1]; i < p[x][y]; i++)
				printf (" ");
		}
	}

	if (!p[x][y] || x == n)
		printf ("\n");
	printf_ans(x + 1, p[x][y]);
}

int main () {

	int tmp;
	while (scanf ("%d%*c", &L), L) {

		n = 0;
		while (gets(str) && str[0] != '\0') {

			handle();
		}
		//init
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= L; j++) {
				dp[i][j] = INF;
				p[i][j] = L + 1;
			}
		dp[n][0] = 500;
		p[n][0] = 0;
		dp[n][L - l[n - 1]] = 0;

		for (int i = n - 1; i >= 1; i--) {
			for (int j = 0; j <= L - l[i]; j++) {

				if (dp[i + 1][j] == INF)
					continue;
				if (!j) {

					if (dp[i + 1][j] <= dp[i][L - l[i - 1]]) {//�������������е����
						dp[i][L - l[i - 1]] = dp[i + 1][j];
						p[i][L - l[i - 1]] = j;
					}
					tmp = (l[i - 1] == L) ? 0: 500;
					if (dp[i + 1][j] + tmp <= dp[i][0]) {//����һ��
						dp[i][0] = dp[i + 1][j] + tmp;
						p[i][0] = j;
					}

				} else {

					for (int k = 0; k < j - l[i - 1]; k++) {//�м��пո�����

						tmp = j - l[i - 1] - k - 1;
						if (dp[i + 1][j] + tmp * tmp < dp[i][k]) {

							dp[i][k] = dp[i + 1][j] + tmp * tmp;
							p[i][k] = j;
						} else if (dp[i + 1][j] + tmp * tmp == dp[i][k]) {

							if (p[i][k] > k)//���������Խӵ��ʵĻ�����ô�Ͳ�Ҫ����һ��
								p[i][k] = Min (p[i][k], j);//ʹ��ǰ��Ŀո�����
							else
								p[i][k] = j;
						}
					}
				}
			}
		}

		printf_ans(1, 0);
		printf ("\n");
	}
	return 0;
}
*/

/*
//ac 0ms ����dp
//ժ�Բ���:https://blog.csdn.net/mobius_strip/article/details/22175897
// a+b = c, aa + bb = aa + (c-a)(c-a) = cc + 2aa - 2ac,��ֵ�� 2a = c
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

typedef struct dnode
{
	char word[85];
	int  length;
}data;
data D[10005];

int sumL[10005];
int F[10005];
int E[10005];

void output( int i, int width, int max )
{
	if ( i < max ) {
		if ( E[i] > i+1 ) {
			//����ÿ���о���Ŀո�ֲ�
			int sblack = width-sumL[E[i]-1]+sumL[i-1];
			int eblack = sblack/(E[i]-1-i);
			int nshort = (eblack+1)*(E[i]-1-i)-sblack;
			int count = 0;
			printf("%s",D[i].word);
			for ( int j = i+1 ; j < E[i] ; ++ j ) {
				for ( int k = 0 ; k < eblack ; ++ k )
					printf(" ");
				if ( ++ count > nshort ) printf(" ");
				printf("%s",D[j].word);
			}printf("\n");
		}else printf("%s\n",D[i].word);//�Լ�����һ��
		output( E[i], width, max );
	}
}

int main()
{
	int width,temp;
	while ( scanf("%d",&width) && width ) {
		getchar();
		int count = 1;
		while ( (temp = getchar()) != '\n' ) {
			do {
				ungetc( temp, stdin );
				scanf("%s",D[count].word);
				D[count].length = strlen(D[count].word);
				count ++;
			}while ( (temp = getchar()) != '\n' );
		}

		sumL[0] = 0;
		for ( int i = 1 ; i < count ; ++ i )
			sumL[i] = sumL[i-1]+D[i].length;

		F[count] = 0;
		for ( int i = count-1 ; i > 0 ; -- i ) {
			F[i] = F[i+1] + 500;
			E[i] = i+1;
			for ( int j = i+1 ; j < count && sumL[j]-sumL[i-1]+j-i <= width ; ++ j ) {
				//����ÿ���о���Ŀո�ֲ�
				int sblack = width-sumL[j]+sumL[i-1];
				int eblack = sblack/(j-i);
				int nshort = (eblack+1)*(j-i)-sblack;
				int add = (j-i-nshort)*eblack*eblack+nshort*(eblack-1)*(eblack-1);//���д���
				if ( F[i] >= F[j+1] + add ) {
					F[i] = F[j+1] + add;
					E[i] = j+1;
				}
			}
		}

		output( 1, width, count );
		printf("\n");
	}
	return 0;
}
*/
