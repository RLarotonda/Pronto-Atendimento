#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype> // Necessario para toupper()
#include "Fila.h"
#include "FilaPrioridadesLE.h"

using namespace std;

noTriagem* filaTriagem = NULL;
noAtendimento* filaAtendimento = NULL;

int senhaGlobal = 1; // Aumenta a cada entrada de paciente, tanto automatica quanto manual

string nomesExemplo[] = {
    "Carlos", "Ana", "João", "Mariana", "Pedro", "Beatriz", "Lucas", "Fernanda", "Luana", "Rafael"
}; // vetor para nomes aleatorios automaticos

void chegadaPacientesAutomatico() {
    string nome = nomesExemplo[rand() % 10]; // Escolhe um dos nomes do array nomeExemplo
    cout << "Paciente " << nome << " chegou com a senha " << senhaGlobal << " (automatico).\n";
    filaTriagem = insereFila(filaTriagem, senhaGlobal, nome);
    imprimeFila(filaTriagem);
    senhaGlobal++;
}

int obterPrioridade() {
    int escolha;
    cout << "\nO que o paciente está sentindo?\n";
    cout << "1. Parada cardíaca\n";
    cout << "2. Hemorragia\n";
    cout << "3. Febre alta\n";
    cout << "4. Fratura\n";
    cout << "5. Dor de cabeça\n";
    cout << "6. Resfriado\n";
    cout << "Opção: ";
    cin >> escolha;

    if (escolha == 1 || escolha == 2) return 0; // Prioridade 0 (Grave)
    if (escolha == 3 || escolha == 4) return 1; // Prioridade 1 (Média)
    return 2; // Prioridade 2 (Leve)
}

void chegadaPacienteManual() {
    string nomePaciente;
    cout << "Informe o nome do paciente: ";
    getline(cin, nomePaciente); 

    int prioridadeManual = obterPrioridade();

    cout << "Bem-vindo(a) " << nomePaciente << "! Sua senha de atendimento é: " << senhaGlobal << ". Aguarde pelo atendimento." << endl;
    
    filaAtendimento = insereFP(filaAtendimento, senhaGlobal, prioridadeManual, nomePaciente);
    cout << "Segundo os sintomas do paciente " << nomePaciente << " (Senha " << senhaGlobal << ") classificamos o grau como ";
    if (prioridadeManual == 0) cout << "GRAVE.\n";
    else if (prioridadeManual == 1) cout << "MÉDIA.\n";
    else cout << "LEVE.\n";
    cout << "Fila de Atendimento Atual: ";
    exibe(filaAtendimento);

    senhaGlobal++;
}

void gerenciarTriagem(int ut) {
    // Se houver pacientes na fila de triagem, processa um imediatamente
    if (filaTriagem != NULL) {
        int senhaTriagem;
        string nomeTriagem;
        filaTriagem = removeFila(filaTriagem, &senhaTriagem, nomeTriagem);
        cout << "Paciente " << nomeTriagem << " (Senha " << senhaTriagem << ") saiu da triagem na UT " << ut << ".\n";
        imprimeFila(filaTriagem); // Mostra a fila de triagem após a remoção

        // Para pacientes automáticos, a prioridade é aleatória
        int prioridadeGerada = rand() % 3; 
        
        filaAtendimento = insereFP(filaAtendimento, senhaTriagem, prioridadeGerada, nomeTriagem);
        
        cout << "Paciente " << nomeTriagem << " classificado automaticamente como ";
        if (prioridadeGerada == 0) cout << "GRAVE.\n";
        else if (prioridadeGerada == 1) cout << "MÉDIA.\n";
        else cout << "LEVE.\n";
        cout << "Fila de Atendimento Atual: ";
        exibe(filaAtendimento);
    }
}

void gerenciarAtendimento(int ut, bool& emAtendimento, int& senhaPacienteAtendimento, int& prioridadePacienteAtendimento, string& nomePacienteAtendimento, int& tempoRestante) {
    if (!emAtendimento && filaAtendimento != NULL) {
        filaAtendimento = removeFP(filaAtendimento, &senhaPacienteAtendimento, &prioridadePacienteAtendimento, nomePacienteAtendimento); 
        
        if (prioridadePacienteAtendimento == 0) { // Grave
            tempoRestante = 4;
        } else if (prioridadePacienteAtendimento == 1) { // Média
            tempoRestante = 2;
        } else { // prioridadePacienteAtendimento == 2 (Leve)
            tempoRestante = 1;
        }

        emAtendimento = true;
        cout << "Iniciando atendimento paciente " << nomePacienteAtendimento << " senha " << senhaPacienteAtendimento
             << " (Prioridade: " << prioridadePacienteAtendimento << ") na UT " << ut << "...\n";
    }

    if (emAtendimento) {
        tempoRestante--;
        cout << "Em atendimento: " << nomePacienteAtendimento << " senha " << senhaPacienteAtendimento
             << " (restam " << tempoRestante << " ut).\n";
        if (tempoRestante == 0) { // Quanto tempo restante acaba atendimento acaba
            cout << "Atendimento do paciente " << nomePacienteAtendimento << " senha " << senhaPacienteAtendimento << " finalizado na UT " << ut << ".\n";
            emAtendimento = false;
        }
    }
}

void atendimentoAutomatico(int totalUT) {
    int ut = 0;
    int tempoRestante = 0; // Usado para determinar demora do atendimento 4ut GRAVE, 2ut MEDIO  e 1ut LEVE
    int senhaPacienteAtendimento = 0;
    int prioridadePacienteAtendimento = 0;
    string nomePacienteAtendimento = "";
    bool emAtendimento = false;
    char pacienteUsuarioOpcao;

    cout << "\n>>> Iniciando simulação de atendimento (Fase de Chegadas)...\n";

    // Fase 1: Chegada de Pacientes (automáticos e manuais) e processamento
    while (ut < totalUT) {
        ut++;
        cout << "\n[UT " << ut << "]\n";

        cout << "Deseja adicionar um paciente manualmente nesta UT? (S/N): ";
        cin >> pacienteUsuarioOpcao;
        pacienteUsuarioOpcao = toupper(pacienteUsuarioOpcao); 

        if (pacienteUsuarioOpcao == 'S') {
            cin.ignore(); 
            chegadaPacienteManual(); // Adiciona manualmente pacientes
        } else{
            chegadaPacientesAutomatico(); // Adiciona automaticamente pacientes
        }
        // Chamadas das funções para gerenciar triagem e atendimento
        gerenciarTriagem(ut);
        gerenciarAtendimento(ut, emAtendimento, senhaPacienteAtendimento, prioridadePacienteAtendimento, nomePacienteAtendimento, tempoRestante);
    } // Fim da Fase de Chegadas

    cout << "\n>>> Fim da Fase de Chegadas. Iniciando Fase de Atendimento Final...\n";

    // Fase 2: Atendimento Final (sem novas chegadas ou perguntas)
    while (emAtendimento || filaTriagem != NULL || filaAtendimento != NULL) {
        ut++;
        cout << "\n[UT " << ut << "]\n";

        // Chamadas das funções para gerenciar triagem e atendimento
        gerenciarTriagem(ut);
        gerenciarAtendimento(ut, emAtendimento, senhaPacienteAtendimento, prioridadePacienteAtendimento, nomePacienteAtendimento, tempoRestante);
    } // Fim da Fase de Atendimento Final

    cout << "\n>>> Simulação concluída. Todas as filas vazias e atendimentos finalizados.\n";
    imprimeFila(filaTriagem);
    exibe(filaAtendimento);
}

int main() {
    srand(time(NULL));
    
    cout << "Bem-vindo(a) ao pronto-socorro!" << endl;
    cout << "Aqui voce pode adicionar pacientes e analizar as filas" << endl;
    cout << "Além disso, serão adicionados pacientes automaticamente" << endl;
    cout << "So determinar a quantidade de vezes que chegara pacientes!" << endl;

    int tempo;
    cout << "Digite o número de unidades de tempo para simularmos a fase de chegadas: ";
    cin >> tempo;
    
    atendimentoAutomatico(tempo);

    cout << "\nSimulação encerrada. Obrigado por usar o pronto-socorro! Se cuida!\n";
    return 0;
}
