#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[100];
    char cpf[15];
    char rg[20];
    char sexo;
    int dia, mes, ano;
} Aluno;

void cadastrarAluno();
void listarAlunos();
void lancarNotas();
void limparBuffer();

int main() {
    int opcao;
    
    printf("=== SISTEMA DE CADASTRO DE ALUNOS ===\n");
    
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar novo aluno\n");
        printf("2 - Listar todos os alunos\n");
        printf("3 - Lancar notas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                listarAlunos();
                break;
            case 3:
                lancarNotas();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarAluno() {
    Aluno aluno;
    FILE *arquivo;
    
    printf("\n=== NOVO CADASTRO ===\n");
    
    printf("Matricula: ");
    scanf("%d", &aluno.matricula);
    limparBuffer();
    
    printf("Nome: ");
    fgets(aluno.nome, 100, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = 0;
    
    printf("CPF: ");
    fgets(aluno.cpf, 15, stdin);
    aluno.cpf[strcspn(aluno.cpf, "\n")] = 0;
    
    printf("RG: ");
    fgets(aluno.rg, 20, stdin);
    aluno.rg[strcspn(aluno.rg, "\n")] = 0;
    
    printf("Sexo (M/F): ");
    scanf(" %c", &aluno.sexo);
    limparBuffer();
    
    printf("Data de nascimento (DD/MM/AAAA): ");
    char data_input[20];
    fgets(data_input, sizeof(data_input), stdin);
    data_input[strcspn(data_input, "\n")] = 0;
    
    int valores_lidos = sscanf(data_input, "%d/%d/%d", &aluno.dia, &aluno.mes, &aluno.ano);
    if (valores_lidos != 3)
        valores_lidos = sscanf(data_input, "%2d%2d%4d", &aluno.dia, &aluno.mes, &aluno.ano);
    if (valores_lidos != 3)
        valores_lidos = sscanf(data_input, "%d %d %d", &aluno.dia, &aluno.mes, &aluno.ano);
    
    if (valores_lidos != 3) {
        printf("Erro: Formato de data invalido!\n");
        return;
    }
    
    if (aluno.dia < 1 || aluno.dia > 31 || aluno.mes < 1 || aluno.mes > 12 || aluno.ano < 1900 || aluno.ano > 2100) {
        printf("Erro: Data invalida!\n");
        return;
    }
    
    arquivo = fopen("alunos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    fprintf(arquivo, "=== ALUNO CADASTRADO ===\n");
    fprintf(arquivo, "Matricula: %d\n", aluno.matricula);
    fprintf(arquivo, "Nome: %s\n", aluno.nome);
    fprintf(arquivo, "CPF: %s\n", aluno.cpf);
    fprintf(arquivo, "RG: %s\n", aluno.rg);
    fprintf(arquivo, "Sexo: %c\n", aluno.sexo);
    fprintf(arquivo, "Data de Nascimento: %02d/%02d/%d\n", aluno.dia, aluno.mes, aluno.ano);
    fprintf(arquivo, "------------------------\n");
    
    fclose(arquivo);
    printf("\nAluno cadastrado com sucesso!\n");
}

void listarAlunos() {
    FILE *arquivo;
    char linha[200];
    
    printf("\n=== LISTA DE ALUNOS CADASTRADOS ===\n");
    
    arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum aluno cadastrado ainda!\n");
        return;
    }
    
    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    
    fclose(arquivo);
}

// === NOVA FUNÇÃO ===
void lancarNotas() {
    FILE *arquivoAlunos, *arquivoNotas;
    int matricula;
    float np1, np2, pim;
    char nome[100];
    int encontrado = 0;

    printf("\n=== LANCAMENTO DE NOTAS ===\n");

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    limparBuffer();

    arquivoAlunos = fopen("alunos.txt", "r");
    arquivoNotas = fopen("notas.txt", "a");

    if (arquivoAlunos == NULL || arquivoNotas == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivoAlunos) != NULL) {
        if (sscanf(linha, "Matricula: %d", &encontrado) == 1 && encontrado == matricula) {
            // Encontrou o aluno
            fgets(linha, sizeof(linha), arquivoAlunos); // Lê nome
            sscanf(linha, "Nome: %[^\n]", nome);

            printf("Aluno encontrado: %s\n", nome);

            printf("Digite a nota da NP1: ");
            scanf("%f", &np1);
            printf("Digite a nota da NP2: ");
            scanf("%f", &np2);
            printf("Digite a nota do PIM: ");
            scanf("%f", &pim);

            fprintf(arquivoNotas, "Matricula: %d\n", matricula);
            fprintf(arquivoNotas, "Nome: %s\n", nome);
            fprintf(arquivoNotas, "NP1: %.2f\n", np1);
            fprintf(arquivoNotas, "NP2: %.2f\n", np2);
            fprintf(arquivoNotas, "PIM: %.2f\n", pim);
            fprintf(arquivoNotas, "------------------------\n");

            printf("\nNotas lançadas com sucesso!\n");
            fclose(arquivoAlunos);
            fclose(arquivoNotas);
            return;
        }
    }

    printf("Aluno com matricula %d nao encontrado!\n", matricula);

    fclose(arquivoAlunos);
    fclose(arquivoNotas);
}

