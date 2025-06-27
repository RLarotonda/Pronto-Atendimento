SIMULADOR PRONTO-SOCORRO
===========================================================

Autores: Rafael Larotonda e Luana Cosmo
Disciplina: Algoritmo e Banco de Dados
Instituição: UNICENTRO
Professor(a): Luciane Agner
Data: 27 de junho de 2025

-----------------------------------------------------------
1. DESCRIÇÃO DO SIMULADOR
-----------------------------------------------------------
O Simulador Pronto-Socorro é uma aplicação em C++ que modela o fluxo de pacientes em um ambiente hospitalar. Ele gerencia a chegada de pacientes, a triagem e o atendimento médico, priorizando os casos mais urgentes para otimizar o fluxo de atendimento.

O simulador opera em Unidades de Tempo (UTs), onde a cada UT os eventos (chegadas, triagem, atendimento) são processados, permitindo visualizar a dinâmica de um pronto-socorro ao longo do tempo.

-----------------------------------------------------------
2. COMO EXECUTAR O SIMULADOR
-----------------------------------------------------------

1.  **Baixe ou clone** os arquivos do projeto (`Projeto02.cpp`, `Fila.h`, `FilaPrioridadesLE.h`).
2.  **Abra seu terminal** ou prompt de comando.
3.  **Navegue até o diretório** onde os arquivos estão salvos.
4.  **Compile o projeto** usando um compilador C++ (como o g++):
    ```bash
    g++ Projeto02.cpp -o pronto_socorro
    ```
    *Certifique-se de que todos os arquivos `.h` estejam no mesmo diretório.*
5.  **Execute o simulador:**
    ```bash
    ./pronto_socorro
    ```
6.  **Interaja com o console** para definir o tempo de simulação e adicionar pacientes.

-----------------------------------------------------------
3. CONCEITOS DE ALGORITMO E ESTRUTURAS DE DADOS APLICADOS
-----------------------------------------------------------

✔ **Filas Simples (FIFO)**:
- Implementada em `Fila.h` para a fila de triagem, onde pacientes aguardam em ordem de chegada.

✔ **Filas de Prioridade**:
- Implementada em `FilaPrioridadesLE.h` para a fila de atendimento, garantindo que pacientes com prioridade mais alta (menor valor numérico) sejam atendidos primeiro.

✔ **Listas Encadeadas**:
- As implementações das filas (`Fila.h` e `FilaPrioridadesLE.h`) são baseadas em listas encadeadas, utilizando nós (`struct noTriagem` e `struct noAtendimento`) e ponteiros para gerenciar a ordem e conexão dos elementos.

✔ **Gerenciamento Dinâmico de Memória**:
- Uso de `new` e `delete` para alocação e desalocação de nós nas filas, evitando vazamentos de memória.

✔ **Modularização e Funções**:
- O código é bem dividido em funções específicas (`chegadaPacientesAutomatico`, `chegadaPacienteManual`, `gerenciarTriagem`, `gerenciarAtendimento`, etc.), promovendo a reutilização de código e a legibilidade.

✔ **Parâmetros por Referência**:
- Utilização de parâmetros por referência (`&`) em funções como `gerenciarAtendimento` para permitir a modificação de variáveis de estado diretamente, como `emAtendimento` e `tempoRestante`.

✔ **Include Guards**:
- Uso de `#ifndef`, `#define` e `#endif` nos arquivos `.h` para prevenir múltiplas inclusões e erros de compilação.

-----------------------------------------------------------
4. FUNCIONALIDADES CRIATIVAS / DESTAQUES
-----------------------------------------------------------

✔ **Simulação em Duas Fases**:
- O simulador opera com uma `Fase de Chegadas` (com pacientes automáticos e manuais) e uma `Fase de Atendimento Final`, onde o programa para de gerar novos pacientes e foca em esvaziar todas as filas, garantindo o atendimento completo.

✔ **Triagem Instantânea**:
- Uma decisão de design que torna a triagem imediata. Pacientes que saem da fila de triagem têm sua prioridade definida e são inseridos instantaneamente na fila de atendimento na mesma UT.

✔ **Diferencia
