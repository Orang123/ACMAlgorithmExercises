/*
���� ���ժ�Բ���:https://blog.csdn.net/hjt_fathomless/article/details/52548842
����:����2������n��n<10^100����k��k<10000������������������������m
1��m��nλ����ͬ
2��m�ܱ�k����
3��������������ʱ��m��n����ͬλ�õĵط������ֲ�ͬ�ĸ�������
4��������������ʱ��mֵ��С
����:http://poj.org/problem?id=3373
˼·:����������뵽��ô����
dp[i][j][num]��ʾǰiλ�����ɵ�����j���ı���num�Σ����仯�����ͺá�
����num����Ƕ����أ�
����k��λ����m����ôn���ֻҪ�ı�mΪλ�Ϳ���%k==0�ˣ���Ϊn��mλ֮ǰ����%k���Եõ�һ����X����mλ���k-X�����ˣ�
����k���Ϊ10000�����ı�5λ���У�

���Ǻ��������"����k��λ����m����ôn���ֻҪ�ı�mΪλ�Ϳ���%k==0��".
*/
//ac 1579ms ���仯����
#include<cstdio>
#include<cstring>
const int N = 1e4 + 9;
int d[110][N][6], n, k,minn;
char s[110],ans[110];
void dfs(int pos,int pre,int num) {
    if(pos==n) {
        if(num<minn&&pre==0) {
            minn=num;
            strcpy(ans,s);
        }
        return;
    } else if(num<minn) {
        if(!d[pos][pre][num]) {
            d[pos][pre][num]=1;
            char t=s[pos];
            for(int i=0; i<=9; i++) {
                if(pos==0&&i==0)continue;
                s[pos]=i+'0';
                dfs(pos+1,(pre*10+i)%k,num+(i!=t-'0'));

            }
            s[pos]=t;
        }
    }
}
int main() {
    //freopen ("f.txt", "r", stdin);
    while (~scanf ("%s %d", s, &k) ) {
        n = strlen (s);
        memset(d,0,sizeof(d));
        minn=6;
        dfs (0, 0, 0);
        printf("%s\n",ans);
    }
    return 0;
}
