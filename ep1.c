//Nome: Davidson Vieira de Souza
// Nº usp : 12611668
#include <stdio.h>
#include <math.h>

// função para estabelecer o tipo de triangulo, avaliando seus lados
float tipoTriangulo(float L1, float l2, float l3)
{
    if (L1 == l2 && l2 == l3 && L1 == l3)
    {
        printf("Classificacao em funcao dos lados: equilatero \n");
    }
    else if (L1 == l2 || L1 == l3 || l2 == l3)
    {
        printf("Classificacao em funcao dos lados: isoceles\n");
    }
    else
    {
        printf("Classificacao em funcao dos lados: escaleno\n");
    }
}

//função para ver o tipo de triangulo, avaliando ele pelos seus angulos
float anguloTriangulo(float L1, float l2, float l3)
{
    int i;
    float maior, menor, meio;
    maior = -1;
    menor = 100000000;
    meio = -1;
    float k[3] = {L1, l2, l3};
    for (i = 0; i < 3; i++)
    {
        if (k[i] > maior)
        {
            maior = k[i];
        }
        else if (k[i] < menor)
        {
            menor = k[i];
        }
        else if (menor < k[i] < maior)
        {
            meio = k[i];
        }
    }
    if (L1 * L1 == l2 * l2 + l3 * l3 || l2 * l2 == L1 * L1 + l3 * l3 || l3 * l3 == L1 * L1 + l2 * l2)
    {
        printf("Classificacao em funcao dos angulos: RETO \n");
    }
    else if ((maior * maior) > (menor * menor) + (meio * meio))
    {
        printf("Classificacao em funcao dos angulos: OBTUSANGULO \n");
    }
    else if ((maior * maior) < (menor * menor) + (meio * meio))
    {
        printf("Classificacao em funcao dos angulos: ACUTANGULO \n");
    }
}

//função para calcular area do triangulo em função dos seus lados
// tendo que usar o teorema do radical de Heron para calcular a area em função somente de seus lados
float area(float L1, float l2, float l3)
{
    float a;
    a = sqrt(((L1 + l2 + l3) / 2) * (((L1 + l2 + l3) / 2) - L1) * (((L1 + l2 + l3) / 2) - l2) * (((L1 + l2 + l3) / 2) - l3));
    return printf("Area do triangulo:%.2f \n", a);
}

// função para ver se o trinângulo é valido ou não
float validade(float L1, float l2, float l3)
{
    if (L1 < l2 + l3 && l2 < L1 + l3 && l3 < L1 + l2)
    {
        printf("Medidas dos lados formam um triangulo VALIDO \n");
        tipoTriangulo(L1, l2, l3);
        anguloTriangulo(L1, l2, l3);
        area(L1, l2, l3);
    }
    else
    {
        printf("medidas dos lados formam um triangulo invalido");
    }
}
int main()
{
    float L1, l2, l3;
    printf("escolha os lados de um triangulo \n");
    scanf("%f", &L1);
    scanf("%f", &l2);
    scanf("%f", &l3);
    validade(L1, l2, l3);
    return 0;
}
