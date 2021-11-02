#include <stdio.h>
#include <string.h>
#define TAM_PILA 10

typedef struct
{
    char operadores[TAM_PILA];
    int tope;
    
}Pila;


void inicializaPila(Pila *p);
int apila(Pila *p, char operador);
int desapila(Pila *p);
void capturaOperacion(char op[21]);
void transformaPostfija(Pila *p, char operacion[21], int *i);

int main()
{
    Pila pila;
    int i = 0;
    char operacion[21];
    
    capturaOperacion(operacion);
    transformaPostfija(&pila,operacion,&i);
    /*while(pila.tope>0)
        desapila(&pila);
    printf("\n");*/
}

void transformaPostfija(Pila *p, char operacion[21], int *i)
{
    
    if ((operacion[*i]>=65 && operacion[*i]<=90) || (operacion[*i]>=97 && operacion[*i]<=122)) //ASCII 65-90=A-Z / 97-122=a-z
    {
        printf("%c",operacion[*i]);
        (*i)++;
        transformaPostfija(p,operacion,i);
    }
    else if (operacion[*i]=='(')
    {
        apila(p,operacion[*i]);
        (*i)++;
        transformaPostfija(p,operacion,i);
    }
    else if (operacion[*i]=='*' || operacion[*i]=='/')
    {
        if (p->operadores[p->tope]=='*' || p->operadores[p->tope]=='/')
        {
            desapila(p);
            transformaPostfija(p,operacion,i);
        }
        apila(p,operacion[*i]);
        (*i)++;
        transformaPostfija(p,operacion,i);
    }
    else if (operacion[*i]=='+' || operacion[*i]=='-')
    {
        if(p->operadores[p->tope]=='*' || p->operadores[p->tope]=='/')
        {
            desapila(p);
            transformaPostfija(p,operacion,i);
        }
        else if(p->operadores[p->tope]=='+' || p->operadores[p->tope]=='-')
        {
            desapila(p);
            transformaPostfija(p,operacion,i);
        }
        apila(p,operacion[*i]);
        (*i)++;
        transformaPostfija(p,operacion,i);
    }
    else if(operacion[*i]==')')
    {
        do
        {
            desapila(p);
        }while (p->operadores[p->tope]!='(');
        (*i)++;
        transformaPostfija(p,operacion,i);
    }
    else if(operacion[*i]==' ')
    {
        while(p->tope>0)
            desapila(p);
        printf("\n");
    }
}

void capturaOperacion(char op[21])
{
    
    printf("Ingresa la operación infija que se desea transformar a postfija\n");
    printf("\t-no use espacios\n");
    printf("\t-max 20 caracteres\n");
    scanf("%s",&op[0]);
    fflush(stdin);
    op[strlen(op)+1]=' ';
}

int apila(Pila *p, char operador)
{
    int pudoApilar = 0;

    if(p->tope < TAM_PILA - 1)
    {
        p->tope++;
        p->operadores[p->tope] = operador;
        
        pudoApilar = 1;
    }
    
    return pudoApilar;
}

int desapila(Pila *p)
{
    int pudoDesapilar = 0;
    
    if(p->tope > -1)
    {
        if (p->operadores[p->tope]!='(')
        printf("%c",p->operadores[p->tope]);
        p->tope--;
        pudoDesapilar = 1;
    }
     
    return pudoDesapilar;
}

void inicializaPila(Pila *p)
{
    p->tope = -1;
}
