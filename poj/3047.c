#include<stdio.h>

char *weekdays[] = {
    "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"
};

int ycount(int y) {
    if ((y%4)==0) {
        if ((y%400)==0) return 366;
        if ((y%100)==0) return 365;
        return 366;
    }
    return 365;
}

int months[13] = {
    0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
}; 
int mcount(int y, int m) {
    if (m!=2) return months[m];
    if ((y%4)==0) {
        if ((y%400)==0) return 29;
        if ((y%100)==0) return 28;
        return 29;
    }
    return 28;
}
int calc(int y, int m, int d) {
    int days = 0;
    int i;
    for (i=1800; i<y; i++){
        days+= ycount(i);
    }
    for (i=1; i<m; i++) days += mcount(y, i);
    days += d;
    return days;
}
int main() {
    int y, m, d;
    scanf("%d %d %d", &y, &m, &d);
    int c1 = calc(1900, 1, 1);
    int c2 = calc(y, m, d);
    int s = (c2 -c1+70000) %7;
    printf("%s\n", weekdays[s]);
    return 0;
}
