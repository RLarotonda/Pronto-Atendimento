#ifndef FILA_H
#define FILA_H

#include <iostream>
using namespace std;

struct noTriagem {
    int info;
    string nome;
    noTriagem *link;
};

noTriagem *inicializaFila() { 
    return NULL; 
}

noTriagem *insereFila(noTriagem *L, int x, const string& nome) {
    noTriagem *N = new noTriagem;
    N->info = x;
    N->nome = nome;
    N->link = NULL;

    if (!L) return N;

    noTriagem *P = L;
    while (P->link) P = P->link;
    P->link = N;
    return L;
}

noTriagem *removeFila(noTriagem *L, int *n, string& nome) {
    if (L) {
        *n = L->info;
        nome = L->nome;
        noTriagem *AUX = L;
        L = L->link;
        delete AUX;
    } else {
        *n = 0;
        nome = "";
    }
    return L;
}

void imprimeFila(noTriagem *L) {
    cout << "\nFila de Triagem: ";
    while (L != NULL) {
        cout << "[" << L->nome << " - Senha: " << L->info << "] ";
        L = L->link;
    }
    cout << endl;
}

#endif