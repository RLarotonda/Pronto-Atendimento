#ifndef FILA_PRIORIDADES_LE_H
#define FILA_PRIORIDADES_LE_H

#include <iostream>
using namespace std;

struct noAtendimento {
    int info;
    int prior;
    string nome;
    noAtendimento *link;
};


noAtendimento *insereFP(noAtendimento *A, int valor, int prioridade, const string& nome) {
    noAtendimento *N = new noAtendimento;
    N->info = valor;
    N->prior = prioridade;
    N->nome = nome;
    N->link = NULL;

    if (A == NULL || prioridade < A->prior) { 
        N->link = A;
        return N;
    }

    noAtendimento *P = A;
    while (P->link != NULL && prioridade >= P->link->prior) { 
        P = P->link;
    }

    N->link = P->link;
    P->link = N;
    return A;
}

noAtendimento *removeFP(noAtendimento *A, int *n, int *prioridade, string& nome) {
    if (A != NULL) {
        *n = A->info;
        *prioridade = A->prior;
        nome = A->nome;
        noAtendimento *AUX = A;
        A = A->link;
        delete AUX;
    }
    return A;
}

void exibe(noAtendimento *A) {
    noAtendimento *P = A;
    cout << " ";
    while (P != NULL) {
        cout << "[" << P->nome << " | Senha:" << P->info << " | P:" << P->prior << "] ";
        P = P->link;
    }
    cout << endl;
}

#endif