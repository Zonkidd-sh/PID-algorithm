#include<stdio.h>
#include<stdlib.h>

struct _pid{
    float SetSpeed;            //定义设定值
    float ActualSpeed;        //定义实际值
    float err;                //定义偏差值
    float err_next;            //定义上一个偏差值
    float err_last;            //定义最上前的偏差值
    float Kp,Ki,Kd;            //定义比例、积分、微分系数
    float integral;
    float voltage;
    float umax;
    float umin;
}pid;

void PID_init(){
    printf("PID init begin \n");
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.4;
    pid.Ki=0.2;         //增加了积分系数
    pid.Kd=0.2;
    pid.umax=400;
    pid.umin=-200;
    printf("PID init end  \n");
}

float PID_realize(float speed){
    float index;
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;

    if(abs(pid.err)>200)        //变积分 过程
    {
        index = 0.0;
    }else if(abs(pid.err) < 180){
        index = 1.0;
        pid.integral+=pid.err;
    }else{
        index = (200-abs(pid.err))/20;
        pid.integral += pid.err;
    }

    pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);

    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
}

int main(){
    PID_init();
    int count=0;
    while(count<1000)
    {
        float speed=PID_realize(200.0);
        printf("%f\n",speed);
        count++;
    }
    return 0;
}
