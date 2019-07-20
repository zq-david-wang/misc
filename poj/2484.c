#include<stdio.h>

char dp[1000001];
char *names[] = {
    "Bob",
    "Alice"
};
int main() {
    dp[0] = 0;
    dp[1] = 1; dp[2] = 1;
    int i, j; for (i=3; i<=1000000; i++) {
        dp[i] = 0;
        if (dp[i-1]==0||dp[i-2]==0) dp[i] = 1;
        else {
            for (j=1; j<i-1; j++) {
                if (((dp[j]+dp[i-j-1])&1)==0) {
                    dp[i] = 1;
                    break;
                }
                if (j<i-2 && ((dp[j]+dp[i-j-2])&1)==0) {
                    dp[i] = 1;
                    break;
                }
            }
        }
    }
    while(1) {
        scanf("%d", &i);
        if (i==0) break;
        if (dp[i-1]==0 || dp[i-2]==0) printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}
