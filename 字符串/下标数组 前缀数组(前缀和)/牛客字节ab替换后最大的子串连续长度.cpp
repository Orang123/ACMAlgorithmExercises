/**
    有一个仅包含’a’和’b’两种字符的字符串s，长度为n，每次操作可以把一个字符做一次转换（把一个’a’设置为’b’，或者把一个’b’置成’a’)；
    但是操作的次数有上限m，问在有限的操作数范围内，能够得到最大连续的相同字符的子串的长度是多少。
 * 利用前缀和数组
 * 例如：
 * n=10,m=1,s=baabaabaab
 *   b a a b a a b a a b
 *   0 1 2 3 4 5 6 7 8 9
 *
 *   将 b-->a
 *   b 的前缀和数组为
 *          sums={ 0, 3, 6, 9, 10}//10 为字符串长度
 *   计算长度分别为:
 *          3  6-0-1=5   9-3-1=5  10-6-1=3
 *     ==>>max = max{ max, sums[i]-sum[i-m-1]-1}
 */
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
using namespace std;
int arra[50005];
int arrb[50005];
int main(){
    //vector<int> arra;
    //vector<int> arrb;
    string a;
    int n,m;
    scanf("%d%d",&n,&m);
    cin >>a;
    int cnta=0,cntb=0,index1=0,index2=0;
    for(int i=0;i<n;i++){
        if(a[i]=='a'){
            cnta++;
            arra[index1++]=i;
            //arra.push_back(i);//将a的下标保存下来
        }
        else{
            cntb++;
            arrb[index2++]=i;
           // arrb.push_back(i);//将b的下标保存下来
        }
    }
    if(cnta<=m||cntb<=m){
        printf("%d",n);
    }
    else{
        /*for(vector<int>::iterator it=arra.begin();it!=arra.end();it++)
            printf("%d ",*it);
    putchar('\n');
        for(vector<int>::iterator it=arrb.begin();it!=arrb.end();it++)
            printf("%d ",*it);
            putchar('\n');*/
        //arra.push_back(n);//这里要把字符串最后一个字符的位置下标放进去，在算最后一个字符a变换为b时这个字符右边的b会跟它连成一个连续得到子串
        arra[index1++]=n;
        int max1=arra[m];//这里因为下标为0的位置最左边没有字符所以不需要做插，直接取地m+1个位置的a做变换的下标就是已经连成子串的个数
        //printf("max1:");
        for(int i=m+1;i<index1;i++){//循环选取最大的,这里取的是m个子串，其实有点贪心的思维，直接就取最大的次数
            max1=max(max1,arra[i]-arra[i-m-1]-1);//arra[i]-arra[i-m-1]-1表示在arra中取m个a来连续的实际数组位置是有间隔的,i-m-1代表要将最左边得到a移动,实际计算的时候左右两边多延展了一个a字符，因为中间变换成b后,两边会连起来构成一个子串
            //printf("%d ",max1);
        }
        //putchar('\n');
        //arrb.push_back(n);
        int max2=arrb[m];
        //printf("max2:");
        for(int i=m+1;i<index2;i++){
            max2=max(max2,arrb[i]-arrb[i-m-1]-1);
            //printf("test:%d\n",arrb[i]-arrb[i-m-1]-1);
            //printf("%d ",max2);
        }
        printf("%d",max1>max2?max1:max2);
    }
    return 0;
}
