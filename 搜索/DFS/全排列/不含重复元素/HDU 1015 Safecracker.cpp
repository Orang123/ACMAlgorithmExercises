/*
题意:就是给定一个目标值target,再给你一个备选字符串(5~12个字符)，
要你在这个字符串里选5个出来，满足题中给定的等式:
v - w^2 + x^3 - y^4 + z^5 = target，并且你选择的这5个字符组成的
字符串必须是所有可能情况中按字典序最大的情况。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1015
思路:虽然是从给定字符串中选取5个字符,但是因为实际5个字符对应的
v、w、x、y、z可以不同,实际问题转化成了 选取5个数构成的所有排列.
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
char a[26], b[5];
int target;
bool visit[26],flag;
bool solve(int v, int w, int x, int y, int z){
    if (v - w*w + x*x*x - y*y*y*y + z*z*z*z*z == target)
        return true;
    else
        return false;
}
bool DFS(int len,int num){
    if (num == 5){
        if (solve(b[0] - 64, b[1] - 64, b[2] - 64, b[3] - 64, b[4] - 64)){//64是'A'的ASCII码
            flag=true;
            return true;
        }
        else return false;
    }
    else{
        for (int i = 0; i < len; i++){
            if (!visit[i]){
                visit[i] = true;
                b[num] = a[i];
                if (DFS(len, num + 1)) return true;
                visit[i] = false;
            }
        }
    }
    if(flag) return true;
    else return false;
}
int main(){
    int len;
    while (scanf("%d %s", &target, a), target || strcmp(a, "END")){
        len = strlen(a);
        memset(visit, false, sizeof(visit)*len);
        flag=false;
        sort(a, a + len,greater<char>());
        if (DFS(len, 0)) puts(b);
        else puts("no solution");
    }
    return 0;
}

