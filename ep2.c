// Nome: Davidson Vieira de Souza
// Nº USP: 12611668
#include<stdio.h>

//Sendo x a raiz quadrada aproximada do valor de n.
// funçao para calcular o modulo.
double mod(double n,double x){
    if(x*x<n){
        return (n-(x*x));
    }
    else{
        return (x*x)-n;
    }
}

//função que opera as aproximaões.
double aproxima(double n,double e,double x){
    double k,y;
    x=n/2;
    k=0;
    while(mod(n,x)>=e || mod(n,x)==0){
         if(x*x>n){
            while(x*x>n){
                x=x/2;
            }
        }
         if(x*x<n){
            while(x*x<n){
                x=(x/2)+x;
            }
        }
        k=k+1;
    }

 return(printf(" Numero de iteracoes:%lf \n\n Diferenca absoluta: %lf\n\n Raiz quadrada:%lf\n",k,mod(n,x),x));
}

int main(){
double n,e,x;

printf("Sendo n o valor o qual voce deseja calcular a raiz, e com e sendo a aproximacao :\n\n");

printf("digite um valor de n tal que n >=1\n");
scanf("%lf",&n);

printf("digite um valor de e tal que e > 0\n");
scanf("%lf",&e);

aproxima(n,e,x);


 return 0;
}
