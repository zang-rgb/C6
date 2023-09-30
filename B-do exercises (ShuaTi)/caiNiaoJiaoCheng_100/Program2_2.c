/*
*题目：企业发放的奖金根据利润提成。

利润(I)低于或等于10万元时，奖金可提10%；
利润高于10万元，低于20万元时，低于10万元的部分按10%提成，高于10万元的部分，可提成7.5%；
20万到40万之间时，高于20万元的部分，可提成5%；
40万到60万之间时高于40万元的部分，可提成3%；
60万到100万之间时，高于60万元的部分，可提成1.5%；
高于100万元时，超过100万元的部分按1%提成。
从键盘输入当月利润I，求应发放奖金总数？

程序分析：请利用数轴来分界，定位。注意定义时需把奖金定义成双精度浮点(double)型。
*/
/*
利用 switch 的击穿现象 的计算方法
*/
#include <stdio.h>
#define SHIWAN 100000

int main(){
    double I;
    double B = 0.0;
    int flag;

    scanf("%lf",&I);
    flag = (int)(I/SHIWAN);
    flag = flag > 10 ? 10 : flag;
    
    switch(flag){
        case 10:
            B += (I-10*SHIWAN)*0.01;
            I = 10*SHIWAN;
        case 9:
        case 8:
        case 7:
        case 6:
            B += (I-6*SHIWAN)*0.015;
            I = 6*SHIWAN;
        case 5:
        case 4:
            B+= (I-4*SHIWAN)*0.03;
            I = 4*SHIWAN;
        case 3:
        case 2:
            B += (I-2*SHIWAN)*0.05;
            I = 2*SHIWAN;
        case 1:
            B += (I-1*SHIWAN)*0.075;
            I = 1*SHIWAN;
        case 0:
            B += I *0.1;
    }
    
    printf("%.2f\n",B);
    return 0;
}