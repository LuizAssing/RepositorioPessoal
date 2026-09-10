    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>


    typedef struct{

    char Pergunta[100];
    char Resposta;

    } Pergunta;

    typedef struct {

    char Nome[100];
    int pontuacao;
    char status [50];

    } Jogador;

void LerPergunta(Pergunta lista[], int Npergunta){
    printf("Escreva a afirmação: ");
    fgets(lista[Npergunta].Pergunta, 100, stdin);
    lista[Npergunta].Pergunta[strcspn(lista[Npergunta].Pergunta, "\n")] = '\0';
}

void LerResposta (Pergunta lista[], int Npergunta){
    char r;
    do {
        printf("Escreva a resposta (V/F): ");
        scanf(" %c", &r);
        if (r == 'v' || r == 'V') lista[Npergunta].Resposta = 'V';
        else if (r == 'f' || r == 'F') lista[Npergunta].Resposta = 'F';
        else printf("\nDigite uma resposta valida\n");
    }
    while (r != 'F' && r != 'V');
}

void CadastrarJogador (Jogador lista2[], int Njogador){
    printf("Escreva o Nome do jogador: ");
    fgets(lista2[Njogador].Nome, 100, stdin);
    lista2[Njogador].Nome[strcspn(lista2[Njogador].Nome, "\n")] = '\0';
    lista2[Njogador].pontuacao = 0;
    printf("\n");
    strcpy(lista2[Njogador].status, "Disponivel");
}

void RespostaUsuario (int Npergunta, Pergunta lista[], Jogador lista2[], int JogadorAtual){
    char RespostaUsu;
    for (int k = 0; k < Npergunta; k++){
        printf("Afirmção %d: %s\n", k + 1, lista[k].Pergunta);
        scanf(" %c", &RespostaUsu);
        if (RespostaUsu == 'v') RespostaUsu = 'V';
        if (RespostaUsu == 'f') RespostaUsu = 'F';
        if (RespostaUsu == lista[k].Resposta){
            printf("\nCorreto!\n\n");
            lista2[JogadorAtual].pontuacao = lista2[JogadorAtual].pontuacao + 10;
        }
        else
            printf("\nIncorreto!\n\n");
    }
}

int EscolhaJogador(int Njogador, Jogador lista2[]){
    int JogadorEscolhido;
    do{
        printf("\nQual Jogador irá responder? \n");
        printf("[0] Voltar pro menu\n");
        for (int l = 0; l < Njogador; l++){
            printf("[%d] %s [%s]\n", l + 1, lista2[l].Nome, lista2[l].status);
        }
        scanf("%d", &JogadorEscolhido);
        if (JogadorEscolhido == 0){
            return -1;
        }
        if(strcmp(lista2[JogadorEscolhido - 1].status, "indisponivel") == 0)
            printf("\nJogador indisponivel, tente outro!\n");
    }while (strcmp(lista2[JogadorEscolhido - 1].status, "indisponivel") == 0);
    strcpy(lista2[JogadorEscolhido - 1].status, "indisponivel");
    getchar();
    return JogadorEscolhido - 1;
}

void OrdenarRanking(int Njogador, Jogador lista2[]){
    Jogador temp;
    for (int v = 0; v < Njogador - 1; v++){
        for (int c = 0; c < Njogador -1 - v; c++){
            if (lista2[c].pontuacao < lista2[c + 1].pontuacao){
                temp = lista2[c];
                lista2[c] = lista2[c + 1];
                lista2[c + 1] = temp;
            }
        }
    }
}

void MostrarRanking(int Njogador, Jogador lista2[]) {
    OrdenarRanking(Njogador, lista2);
    if (Njogador > 0){
        printf("\n===== RANKING =====\n");
        for (int i = 0; i < Njogador; i++) {
            printf("%dº %s - %d pontos\n", i + 1, lista2[i].Nome, lista2[i].pontuacao);
        }
    } else printf("\nCadastre os jogadores primeiro\n");
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    Pergunta lista [10];
    Jogador lista2 [5];
    int Npergunta = 0;
    int Njogador = 0;
    int opcao;

    do{
        printf(" --- Sistema Quiz (V/F) --- \n\n");
        printf("1. Cadastrar Pergunta (%d/10) \n", Npergunta);
        printf("2. Cadastrar jogador (%d/5) \n", Njogador);
        printf("3. Jogar \n");
        printf("4. Ranking \n");
        printf("0. Sair \n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch (opcao){

            case 1:
                if (Npergunta < 10){
                    LerPergunta(lista, Npergunta);
                    LerResposta(lista, Npergunta);
                    Npergunta++;
                } else {
                    printf("\nNúmero maximo de perguntas atingido \n");
                }
            break;

            case 2:
                if (Njogador < 5){
                    CadastrarJogador(lista2, Njogador);
                    Njogador++;
                } else {
                    printf("\nNúmero maximo de jogadores atingido \n\n");
                }
                break;

            case 3:
                if (Npergunta < 1 || Njogador < 1)
                    printf("\nRealize os cadastros primeiro!\n\n");
                else{
                    int JogadorEscolhido;
                    JogadorEscolhido = EscolhaJogador(Njogador, lista2);
                    if (JogadorEscolhido == -1) {
                        break;
                    }
                    RespostaUsuario(Npergunta, lista, lista2, JogadorEscolhido);
                }
                break;

            case 4:
                MostrarRanking(Njogador, lista2);

                break;
        }

    }while (opcao != 0);
    printf("\nFim!");
    return 0;
}
