/*
 * =====================================================================================
 *
 *       Filename:  3299.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月20日 21时17分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<math.h>

int main() {
    char b[8], m;
    double t, d, h;
    double v_e, v_h;
    while(1) {
        scanf("%s", b);
        if (b[0] == 'E') break;
        m = 0;
        if (b[0] == 'T') { 
            scanf("%lf", &t);
            m |= 1;
        } else if (b[0] == 'D') {
            scanf("%lf", &d);
            m |= 2;
        } else {
            scanf("%lf", &h);
            m |= 4;
        }
        scanf("%s", b);
        if (b[0] == 'T') { 
            scanf("%lf", &t);
            m |= 1;
        } else if (b[0] == 'D') {
            scanf("%lf", &d);
            m |= 2;
        } else {
            scanf("%lf", &h);
            m |= 4;
        }
        if (m==3) {
            // h
            v_e = 6.11*exp(5417.7530*((1/273.16) - (1/(d+273.16))));
            v_h = 0.5555*(v_e-10.0);
            h = t+v_h;
        } else if (m==5) {
            // d
            v_h = h-t;
            v_e = v_h/0.5555+10.0;
            d = 1/ ((1/273.16) - (log(v_e/6.11) / 5417.7530)) - 273.16;
        } else {
            // t
            v_e = 6.11*exp(5417.7530*((1/273.16) - (1/(d+273.16))));
            v_h = 0.5555*(v_e-10.0);
            t = h-v_h;
        }
        printf("T %.1f D %.1f H %.1f\n", t, d, h);
    }
    return 0;
}

