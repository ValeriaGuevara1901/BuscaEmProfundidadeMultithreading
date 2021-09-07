/*
DEFINIÇÕES PADRÕES
*/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

#define BRANCO 0
#define AMARELO 1 
#define VERMELHO 2


typedef struct adjacencia{ // aresta
    int vertice; // vertice do destino
    TIPOPESO peso; // peso associado a aresta que leva ao vertice de destino
    struct adjacencia *prox; // o proximo elemento na lista de adjacencia
} ADJACENCIA;

typedef struct vertice{
    /*Dados armazenados vao aqui */
    ADJACENCIA *cab; // possui apaenas a cabeca na lista de adjacencia
}VERTICE;


/*
O NOSSO GRAFO, é uma estrutura que guarda numero de vertices e arestas
*/
typedef struct grafo{
    int vertices; // numero de vertice total do grafo
    int arestas; // numero de arestas total do grafo
    VERTICE *adj; // arranjo de vertices na estrutura
} GRAFO;

void visitaP(GRAFO *g, int u, int *cor){
    cor[u] = AMARELO; // visitar um no marca como amarelo
    ADJACENCIA *v = g->adj[u].cab; // visita adjacencia
    while(v){ // então visitamos sua adjacencia, aresta u e v recursivamente
        if(cor[v->vertice]==BRANCO) // se a cor for branca eu visito
            visitaP(g, v->vertice, cor); // veja que visito chamando a função de novo, ou seja, recursivo
        v = v->prox;
    }
    cor[u] = VERMELHO;
}

void profundida(GRAFO *g){
    int cor[g->vertices]; // crio um vetor com arranjo de cores (o valor tem que bater com o grafo)

    int u;
    for(u=0; u < g->vertices ; u++){ // inicialmente todos os vertices são brancos
        cor[u] = BRANCO;
    }
    for(u=0; u < g->vertices; u++){ 
        if(cor[u]== BRANCO) // se for branco visita todos em profundida
        visitaP(g, u, cor); // repare que é recursivo, visita até o final depois volta

    }
}

/* 
CRIAR O GRAFO
*/
GRAFO *criaGrafo(int v){
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE*)malloc(v*sizeof(VERTICE)); // arranjo com o numero de vertices desejados
    // inicializamos cada elemento do arranjo numa lista com null
    int i;
    for (i=0; i<v; i++)
        g->adj[i].cab = NULL;
    return(g);
}

/* 
CRIAR A ADJACÊNCIA
ponta da seta
*/
ADJACENCIA *criaAdj(int v, int peso){
    // aloca espaço para um nó(vertice) na lista de adjacencia
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    // abasteço com o vertice alvo da adjacencia
    temp->vertice = v;
    // e o peso da aresta
    temp->peso = peso;
    // fazemos desse um nó isolado e criamos
    temp->prox = NULL; // falta criar a aresta
    return(temp);
}

/* 
CRIA ARESTA
a aresta só é criada quando a adicionamos
uma adjacencia à lista de um vértice
*/
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    if(!gr) return (false); // se o grafo for nulo 
    if ((vf<0) || (vf >= gr->vertices)) // se o nó invalido
        return (false);
    if ((vi<0) || (vi >= gr->vertices))
        return (false);
    ADJACENCIA *novo = criaAdj(vf, p); // criamos uma adjacencia na memoria  
    novo->prox = gr->adj[vi].cab; // inserimos no inicio da lista de adjacencia
    gr->adj[vi].cab = novo; // passou a ser a cabeça da nova lista
    gr->arestas++;
    return (true);
}


/* 
IMPRIMIR GRAFO
*/
void imprime(GRAFO *gr){
    printf("Vértices: %d. \nArestas: %d\n", gr->vertices, gr->arestas); // cabeçalho geral
    for (int i = 0; i < gr->vertices; i++){ // para cada vertice no grafo
        printf("v%d: ", i);
        // mostramos sua lista de adjacencia
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad){ // enquanto o ponteiro não for null
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");// passa para o segundo elemento
    }

}

int main(){
    GRAFO *gr = criaGrafo(5);
    criaAresta(gr, 0, 1,2);
    criaAresta(gr, 1, 2, 4);
    criaAresta(gr, 2, 0, 12);
    criaAresta(gr, 2, 4, 40);
    criaAresta(gr, 3, 1, 3);
    criaAresta(gr, 4, 3, 8);

    imprime(gr);
    return 0;
}