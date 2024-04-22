#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCT DOS ALUNOS
typedef struct{
    char nome[100];
    char telefone[100];
    char curso[100];
    float n1;
    float n2;
    char situacao[20];
    float media;
}aluno;

// DECLARANDO AS FUNCOES UTILIZADS
int lerDados(aluno alunos[]);
void calcularMediaESituacao(aluno alunos[], int numAlunos);
void escreverResultado(aluno alunos[], int numAlunos, const char *arquivoSaida);

int main(){

    system("cls");

    char *arquivoEntrada = "DadosEntrada.csv";
    char *arquivoSaida = "SituacaoFinal.csv";

    aluno alunos[93];

    int numAlunos = lerDados(alunos);
    if(numAlunos == 0){
        printf("Nenhum aluno encontrado ou erro ao ler o arquivo.\n");
        return 1;
    }

    calcularMediaESituacao(alunos, numAlunos);

    escreverResultado(alunos, numAlunos, arquivoSaida);

    printf("resultados gravados em %s.\n", arquivoSaida);

    return 0;
}

// FUNCAO PARA LER OS DADOS DO ARQUIVO
int lerDados(aluno alunos[]){

    FILE *dados;

    dados = fopen("DadosEntrada.csv", "r");
    if(dados == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    //IGNORANDO A PRIMEIRA LINHA
    char buffer[1000];
    fgets(buffer, sizeof(buffer), dados);

    for(int i = 0; i < 93; i++){
        fscanf(dados, "%[^,],%[^,],%[^,],%f,%f\n", &alunos[i].nome, &alunos[i].telefone, &alunos[i].curso, &alunos[i].n1, &alunos[i].n2);
    }

    fclose(dados);
    return(1);
}


// FUNCAO PARA CALCULAR A MEDIA E A SITUACAO DE CADA ALUNO
void calcularMediaESituacao(aluno alunos[], int numAlunos){

    for(int i = 0; i < 93; i++){
        alunos[i].media = (alunos[i].n1 + alunos[i].n2) / 2;

        if(alunos[i].media >= 7){
            strcpy(alunos[i].situacao, "APROVADO");
        }else{
            strcpy(alunos[i].situacao, "REPROVADO");
        }
    }
}

// FUNCAO PARA ESCREVER O RESULTADO NO ARQUIVO
void escreverResultado(aluno alunos[], int numAlunos, const char *arquivoSaida){

    FILE *resultado;

    resultado = fopen(arquivoSaida, "w");
    if(resultado == NULL){
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for(int i = 0; i < 93; i++){
        alunos[i].media = (alunos[i].n1 + alunos[i].n2) / 2;
        fprintf(resultado, "%s, %0.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].situacao);
    }

    fclose(resultado);
}
