#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 1000
/*���帴������*/
typedef struct{
double real;
double img;
}complex;

complex x[N], *W; /*��������,�任��*/
int size_x=0;      /*�������еĴ�С���ڱ������н���2�Ĵ���*/
double PI;         /*Բ����*/

void fft();     /*���ٸ���Ҷ�任*/
void ifft();
void initW();   /*��ʼ���任��*/
void change(); /*��ַ*/
void add(complex ,complex ,complex *); /*�����ӷ�*/
void mul(complex ,complex ,complex *); /*�����˷�*/
void sub(complex ,complex ,complex *); /*��������*/
void divi(complex ,complex ,complex *);/*��������*/
void output();

int main(){
int i,method;                             /*������*/
system("cls");
PI=atan(1)*4;
printf("Please input the size of x:\n");
scanf("%d",&size_x);
printf("Please input the data in x[N]:\n");
for(i=0;i<size_x;i++)
   scanf("%lf%lf",&x[i].real,&x[i].img);
initW();
printf("Use FFT(0) or IFFT(1)?\n");
scanf("%d",&method);
if(method==0)
   fft();
else
   ifft();
output();
return 0;
}

/*���ٸ���Ҷ�任*/
void fft(){
int i=0,j=0,k=0,l=0;
complex up,down,product;
change();
for(i=0;i< log(size_x)/log(2) ;i++){   /*һ����������*/
   l=1<<i;
   for(j=0;j<size_x;j+= 2*l ){             /*һ���������*/
    for(k=0;k<l;k++){        /*һ����������*/
      mul(x[j+k+l],W[size_x*k/2/l],&product);
      add(x[j+k],product,&up);
      sub(x[j+k],product,&down);
      x[j+k]=up;
      x[j+k+l]=down;
    }
   }
}
}

/*���ٸ���Ҷ��任*/
void ifft(){
int i=0,j=0,k=0,l=size_x;
complex up,down;
for(i=0;i< (int)( log(size_x)/log(2) );i++){   /*һ����������*/
   l/=2;
   for(j=0;j<size_x;j+= 2*l ){             /*һ���������*/
    for(k=0;k<l;k++){        /*һ����������*/
     add(x[j+k],x[j+k+l],&up);
     up.real/=2;up.img/=2;
     sub(x[j+k],x[j+k+l],&down);
     down.real/=2;down.img/=2;
     divi(down,W[size_x*k/2/l],&down);
     x[j+k]=up;
     x[j+k+l]=down;
    }
   }
}
change();
}

/*��ʼ���任��*/
void initW(){
int i;
W=(complex *)malloc(sizeof(complex) * size_x);
for(i=0;i<size_x;i++){
   W[i].real=cos(2*PI/size_x*i);
   W[i].img=-1*sin(2*PI/size_x*i);
}
}

/*��ַ���㣬��x(n)��λ����*/
void change(){
complex temp;
unsigned short i=0,j=0,k=0;
double t;
for(i=0;i<size_x;i++){
   k=i;j=0;
   t=(log(size_x)/log(2));
   while( (t--)>0 ){
    j=j<<1;
    j|=(k & 1);
    k=k>>1;
   }
   if(j>i){
    temp=x[i];
    x[i]=x[j];
    x[j]=temp;
   }
}
}

/*�������Ҷ�任�Ľ��*/
void output(){
int i;
printf("The result are as follows\n");
for(i=0;i<size_x;i++){
   printf("%.4f",x[i].real);
   if(x[i].img>=0.0001)printf("+%.4fj\n",x[i].img);
   else if(fabs(x[i].img)<0.0001)printf("\n");
   else printf("%.4fj\n",x[i].img);
}
}
void add(complex a,complex b,complex *c){
c->real=a.real+b.real;
c->img=a.img+b.img;
}

void mul(complex a,complex b,complex *c){
c->real=a.real*b.real - a.img*b.img;
c->img=a.real*b.img + a.img*b.real;
}
void sub(complex a,complex b,complex *c){
c->real=a.real-b.real;
c->img=a.img-b.img;
}
void divi(complex a,complex b,complex *c){
c->real=( a.real*b.real+a.img*b.img )/( b.real*b.real+b.img*b.img);
c->img=( a.img*b.real-a.real*b.img)/(b.real*b.real+b.img*b.img);
}
 
