A#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Tokens da linguagem

#define COMENTARIO 		0
#define ALGORITMO 		1
#define VARIAVEL		2
#define INTEIRO			3
#define LOGICO			4
#define INICIO			5
#define FIM				6
#define SE				7
#define ENTAO 			8
#define ENQUANTO		9
#define FACA 			10
#define LEIA			11
#define ESCREVA			12
#define DIV				13
#define VERDADEIRO		14
#define FALSO 			15
#define PONTO_VIRGULA	16
#define VIRGULA 		17
#define PONTO 			18
#define DOIS_PONTOS		19
#define IDENTIFICADOR	20
#define ATRIBUICAO		21
#define PAR_ABRINDO		22
#define PAR_FECHANDO	23
#define MENOR 			24
#define MENOR_IGUAL 	25
#define IGUAL  			26
#define DIFERENTE  		27
#define MAIOR 			28
#define MAIOR_IGUAL 	29
#define MAIS 			30
#define MENOS 			31
#define VEZES 			32
#define E 				33
#define OU 				34
#define NUMERO  		35
#define SENAO           36

const char *termos[] = { "comentario", "algoritmo", "variavel", "inteiro", "logico", "inicio", "fim", "se", "entao", "enquanto", "faca", "leia", "escreva", "div", "verdadeiro", "falso", "ponto e virgula", "virgula", "ponto", "dois pontos", "identificador", "atribuicao", "parentese abrindo", "parentese fechando", "menor", "menor_igual", "igual", "diferente", "maior", "maior_igual", "mais", "menos", "vezes", "e", "ou", "numero", "senao"};

// Estrura para um token
typedef struct{
	int tipo;
	int linha;
    char palavra[16];
} Token;

// Realiza a extracao de tokens
int Analise_Lexica(char * texto_programa, Token * tokens, int * numTokens, int * num_linha){
	int i = 0; // Posicao do caractere a ser lido
	int linha = 1; // Linha que esta sendo processada
    char caractere; // proximo caractere a ser lido

    // Processa o texto do programa a ser compilado
    while ((caractere = texto_programa[i]) != '\0'){
        if(caractere == '/' && texto_programa[i + 1] == '*'){ // Comentario Multiplas Linhas
            tokens[*numTokens].tipo = COMENTARIO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;

            // Ignora conteudo dentro do comentario
            while ((texto_programa[i] != '*' || texto_programa[i + 1] != '/') && texto_programa[i] != '\0'){
                if(texto_programa[i] == '\n')
                    linha++;
                i++;
            }

            if(texto_programa[i] == '\0'){
            	printf("# %d: Erro Lexico: Comentario de Multiplas Linhas Nao Fechado\n", linha);
            	return 0;
            }else
	            i += 2;
        }else if(caractere == '/' && texto_programa[i + 1] == '/'){ // Comentario Unica Linha
            tokens[*numTokens].tipo = COMENTARIO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            // Ignora conteudo dentro do comentario
            while(texto_programa[i] != '\n' && texto_programa[i] != '\0') i++;
        }else if(caractere == '\n'){ // Quebra de linha
        	i++;
        	linha++; // Nova linha
        }else if(caractere == ' ' || caractere == '\t' || caractere == '\r'){ // Caracteres a serem ignorados
        	i++;
        }else if(caractere == ';'){
        	tokens[*numTokens].tipo = PONTO_VIRGULA;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == ','){
        	tokens[*numTokens].tipo = VIRGULA;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == ':' && texto_programa[i+1] == '='){
        	tokens[*numTokens].tipo = ATRIBUICAO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i+=2;
        }else if(caractere == ':'){
        	tokens[*numTokens].tipo = DOIS_PONTOS;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '.'){
            tokens[*numTokens].tipo = PONTO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '('){
        	tokens[*numTokens].tipo = PAR_ABRINDO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == ')'){
        	tokens[*numTokens].tipo = PAR_FECHANDO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '<' && texto_programa[i+1] == '='){
        	tokens[*numTokens].tipo = MENOR_IGUAL;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i += 2;
        }else if(caractere == '<'){
        	tokens[*numTokens].tipo = MENOR;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '='){
        	tokens[*numTokens].tipo = IGUAL;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '#'){
        	tokens[*numTokens].tipo = DIFERENTE;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '>' && texto_programa[i+1] == '='){
        	tokens[*numTokens].tipo = MAIOR_IGUAL;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i += 2;
        }else if(caractere == '>'){
        	tokens[*numTokens].tipo = MAIOR;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '+'){
        	tokens[*numTokens].tipo = MAIS;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '-'){
        	tokens[*numTokens].tipo = MENOS;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == '*'){
        	tokens[*numTokens].tipo = VEZES;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == 'e' && texto_programa[i+1] == ' '){
        	tokens[*numTokens].tipo = E;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i++;
        }else if(caractere == 'o' && texto_programa[i+1] == 'u' && texto_programa[i+2] == ' '){
        	tokens[*numTokens].tipo = OU;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
            i += 2;
        }else if(caractere >= '0' && caractere <= '9'){
        	while(texto_programa[i] >= '0' && texto_programa[i] <= '9') i++;
        	if(texto_programa[i] != ' ' && texto_programa[i] != '\n'){
        		printf("# %d: Erro Lexico: Identificador nao pode iniciar por numero\n", linha);
        		return 0;
        	}
        	tokens[*numTokens].tipo = NUMERO;
            tokens[*numTokens].linha = linha;
            *numTokens = *numTokens + 1;
        }else if(caractere == '_'){
            printf("# %d: Erro Lexico: Identificador nao pode iniciar por _\n", linha);
            return 0;
        }else{
        	char palavra[16];
        	int j = 0;
        	while((isalnum(texto_programa[i]) || texto_programa[i] == '_') && j < 15){
                palavra[j++] = texto_programa[i];
                i++;
        	}

			if(isalnum(texto_programa[i]) || texto_programa[i] == '_'){
        		printf("# %d: Erro Lexico: Identificador nao pode ter mais de 15 caracteres\n", linha);
        		return 0;
        	}else{
        		palavra[j++] = '\0';
        	}

        	if(strcmp(palavra, "algoritmo") == 0){
        		tokens[*numTokens].tipo = ALGORITMO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
        	}else if(strcmp(palavra, "variavel") == 0){
                tokens[*numTokens].tipo = VARIAVEL;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "inteiro") == 0){
                tokens[*numTokens].tipo = INTEIRO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "logico") == 0){
                tokens[*numTokens].tipo = LOGICO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "inicio") == 0){
                tokens[*numTokens].tipo = INICIO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "fim") == 0){
                tokens[*numTokens].tipo = FIM;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "se") == 0){
                tokens[*numTokens].tipo = SE;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "senao") == 0){
                tokens[*numTokens].tipo = SENAO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "entao") == 0){
                tokens[*numTokens].tipo = ENTAO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "enquanto") == 0){
                tokens[*numTokens].tipo = ENQUANTO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "faca") == 0){
                tokens[*numTokens].tipo = FACA;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "leia") == 0){
                tokens[*numTokens].tipo = LEIA;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "escreva") == 0){
                tokens[*numTokens].tipo = ESCREVA;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "div") == 0){
                tokens[*numTokens].tipo = DIV;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "verdadeiro") == 0){
                tokens[*numTokens].tipo = VERDADEIRO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else if(strcmp(palavra, "falso") == 0){
                tokens[*numTokens].tipo = FALSO;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }else{
                strcpy(tokens[*numTokens].palavra, palavra);
                tokens[*numTokens].tipo = IDENTIFICADOR;
                tokens[*numTokens].linha = linha;
                *numTokens = *numTokens + 1;
            }
        }
    }

    *num_linha = linha; // Armazena o numero de linhas processadas

    return 1;
}

// Funcoes auxiliares da Analise Sintatica

int programa(Token * tokens, int *i);
int bloco(Token * tokens, int *i);
int declaracao_de_variaveis(Token * tokens, int *i);
int lista_variavel(Token * tokens, int *i);
int tipo(Token * tokens, int *i);
int comando_composto(Token * tokens, int *i);
int comando(Token * tokens, int *i);
int comando_atribuicao(Token * tokens, int *i);
int comando_se(Token * tokens, int *i);
int comando_enquanto(Token * tokens, int *i);
int comando_entrada(Token * tokens, int *i);
int comando_saida(Token * tokens, int *i);
int expressao(Token * tokens, int *i);
int relacional(Token * tokens, int *i);
int expressao_simples(Token * tokens, int *i);
int termo(Token * tokens, int *i);
int fator(Token * tokens, int *i);

// Implementacao das Funcoes auxiliares da Analise Sintatica

int programa(Token * tokens, int *i){
    if(tokens[*i].tipo != ALGORITMO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[ALGORITMO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(tokens[*i].tipo != IDENTIFICADOR){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[IDENTIFICADOR], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(tokens[*i].tipo != PONTO_VIRGULA){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PONTO_VIRGULA], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(bloco(tokens, i) != 1) return 0;

    if(tokens[*i].tipo != PONTO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PONTO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    return 1;
}

int bloco(Token * tokens, int *i){
    return declaracao_de_variaveis(tokens, i) && comando_composto(tokens, i);
}

int declaracao_de_variaveis(Token * tokens, int *i){
    if(tokens[*i].tipo == VARIAVEL){
        *i = *i + 1;
        if(lista_variavel(tokens, i) != 1){
            return 0;
        }

        if(tokens[*i].tipo != DOIS_PONTOS){
            printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[DOIS_PONTOS], termos[tokens[*i].tipo]);
            return 0;
        }

        *i = *i + 1;

        if(tipo(tokens, i) != 1){
            return 0;
        }

        if(tokens[*i].tipo != PONTO_VIRGULA){
            printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PONTO_VIRGULA], termos[tokens[*i].tipo]);
            return 0;
        }

        *i = *i + 1;

        while(lista_variavel(tokens, i) == 1){
            *i = *i + 1;

            if(tokens[*i].tipo != DOIS_PONTOS){
                printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[DOIS_PONTOS], termos[tokens[*i].tipo]);
                return 0;
            }

            *i = *i + 1;

            if(tipo(tokens, i) != 1){
                return 0;
            }

            if(tokens[*i].tipo != PONTO_VIRGULA){
                printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PONTO_VIRGULA], termos[tokens[*i].tipo]);
                return 0;
            }

            *i = *i + 1;
        }
    }

    return 1;
}

int lista_variavel(Token * tokens, int *i){
    if(tokens[*i].tipo != IDENTIFICADOR){
        return 0;
    }

    *i = *i + 1;

    while(tokens[*i].tipo == VIRGULA){
        *i = *i + 1;
        if(tokens[*i].tipo != IDENTIFICADOR){
            printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[IDENTIFICADOR], termos[tokens[*i].tipo]);
            return 0;
        }

        *i = *i + 1;
    }

    return 1;
}


int tipo(Token * tokens, int *i){
    if(tokens[*i].tipo == INTEIRO || tokens[*i].tipo == LOGICO){
        *i = *i + 1;
        return 1;
    }

    return 0;
}

int comando_composto(Token * tokens, int *i){
    if(tokens[*i].tipo != INICIO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[INICIO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(comando(tokens, i) == 0){
        return 0;
    }

    while(tokens[*i].tipo == PONTO_VIRGULA){

        *i = *i + 1;

        if(comando(tokens, i) == 0){
            return 0;
        }
    }

    if(tokens[*i].tipo != FIM){
        return 0;
    }

    *i = *i + 1;

    return 1;
}

int comando(Token * tokens, int *i){
    return comando_atribuicao(tokens, i) || comando_se(tokens, i) || comando_enquanto(tokens, i) || comando_entrada(tokens, i) || comando_saida(tokens, i) || comando_composto(tokens, i);
}


int comando_atribuicao(Token * tokens, int *i){
    if(tokens[*i].tipo != IDENTIFICADOR) return 0;

    *i = *i + 1;

    if(tokens[*i].tipo != ATRIBUICAO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[ATRIBUICAO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    return expressao(tokens, i);
}

int comando_se(Token * tokens, int *i){
    if(tokens[*i].tipo != SE) return 0;

    *i = *i + 1;

    if(tokens[*i].tipo != PAR_ABRINDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_ABRINDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(expressao(tokens, i) == 0) return 0;

    if(tokens[*i].tipo != PAR_FECHANDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_FECHANDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(tokens[*i].tipo != ENTAO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[ENTAO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(comando(tokens, i) == 0) return 0;

    if(tokens[*i].tipo == SENAO){
        *i = *i + 1;
        return comando(tokens, i);
    }

    return 1;
}

int comando_enquanto(Token * tokens, int *i){
    if(tokens[*i].tipo != ENQUANTO) return 0;

    *i = *i + 1;

    if(tokens[*i].tipo != PAR_ABRINDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_ABRINDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(expressao(tokens, i) == 0) return 0;

    if(tokens[*i].tipo != PAR_FECHANDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_FECHANDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(tokens[*i].tipo != FACA){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[FACA], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    return comando(tokens, i);
}

int comando_entrada(Token * tokens, int *i){
    if(tokens[*i].tipo != LEIA) return 0;

    *i = *i + 1;

    if(tokens[*i].tipo != PAR_ABRINDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_ABRINDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(lista_variavel(tokens, i) == 0) return 0;

    if(tokens[*i].tipo != PAR_FECHANDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_FECHANDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    return 1;
}

int comando_saida(Token * tokens, int *i){
    if(tokens[*i].tipo != ESCREVA) return 0;

    *i = *i + 1;

    if(tokens[*i].tipo != PAR_ABRINDO){
        printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_ABRINDO], termos[tokens[*i].tipo]);
        return 0;
    }

    *i = *i + 1;

    if(expressao(tokens, i) == 0) return 0;

    while(tokens[*i].tipo == VIRGULA){
        *i = *i + 1;

        if(expressao(tokens, i) == 0) return 0;
    }

    if(tokens[*i].tipo != PAR_FECHANDO){
        printf("[ERRO] Linha: %d - Espera-se parentese fechando\n", tokens[*i].linha);
        return 0;
    }

    *i = *i + 1;

    return 1;
}

int expressao(Token * tokens, int *i){
    if(expressao_simples(tokens, i) == 0) return 0;

    if(relacional(tokens, i) == 1){
        if(expressao_simples(tokens, i) == 0) return 0;
    }

    return 1;
}

int relacional(Token * tokens, int *i){
    if(tokens[*i].tipo == MENOR || tokens[*i].tipo == MENOR_IGUAL || tokens[*i].tipo == IGUAL || tokens[*i].tipo == DIFERENTE || tokens[*i].tipo == MAIOR || tokens[*i].tipo == MAIOR_IGUAL){
        *i = *i + 1;
        return 1;
    }

    return 0;
}

int expressao_simples(Token * tokens, int *i){
    if(tokens[*i].tipo == MAIS || tokens[*i].tipo == MENOS) *i = *i + 1;

    if(termo(tokens, i) == 0) return 0;

    if(tokens[*i].tipo == MAIS || tokens[*i].tipo == MENOS || tokens[*i].tipo == OU){
        *i = *i + 1;
        if(termo(tokens, i) == 0){
            return 0;
        }
    }

    return 1;
}

int termo(Token * tokens, int *i){
    if(fator(tokens, i) == 0) return 0;

    if(tokens[*i].tipo == VEZES || tokens[*i].tipo == DIV || tokens[*i].tipo == E){
        *i = *i + 1;
        if(fator(tokens, i) == 0){
            return 0;
        }
    }

    return 1;
}

int fator(Token * tokens, int *i){
    if(tokens[*i].tipo == IDENTIFICADOR || tokens[*i].tipo == NUMERO || tokens[*i].tipo == VERDADEIRO || tokens[*i].tipo == FALSO){
        *i = *i + 1;
        return 1;
    }

    if(tokens[*i].tipo == PAR_ABRINDO){
        *i = *i + 1;

        if(expressao(tokens, i) == 0){
            return 0;
        }

        if(tokens[*i].tipo != PAR_FECHANDO){
            printf("# %d: Erro sintatico: esperado [%s] encontrado[%s]\n", tokens[*i].linha, termos[PAR_FECHANDO], termos[tokens[*i].tipo]);
            return 0;
        }

        *i = *i + 1;

        return 1;
    }

    return 0;
}

// Realiza a Analise Sintatica
int Analise_Sintatica(Token *tokens){
    int i = 0;
    return programa(tokens, &i);
}

// Imprime os tokens criados na analise lexica
void Imprime_Tokens(Token * tokens, int numero_tokens){
    for (int i = 0; i < numero_tokens; ++i){
        if (tokens[i].tipo == COMENTARIO){
            printf("# %d: comentario\n", tokens[i].linha);
        }else if (tokens[i].tipo == ALGORITMO){
            printf("# %d: algoritmo\n", tokens[i].linha);
        }else if (tokens[i].tipo == VARIAVEL){
            printf("# %d: variavel\n", tokens[i].linha);
        }else if (tokens[i].tipo == INTEIRO){
            printf("# %d: inteiro\n", tokens[i].linha);
        }else if (tokens[i].tipo == LOGICO){
            printf("# %d: logico\n", tokens[i].linha);
        }else if (tokens[i].tipo == INICIO){
            printf("# %d: inicio\n", tokens[i].linha);
        }else if (tokens[i].tipo == FIM){
            printf("# %d: fim\n", tokens[i].linha);
        }else if (tokens[i].tipo == SE){
            printf("# %d: se\n", tokens[i].linha);
        }else if (tokens[i].tipo == SENAO){
            printf("# %d: senao\n", tokens[i].linha);
        }else if (tokens[i].tipo == ENTAO){
            printf("# %d: entao\n", tokens[i].linha);
        }else if (tokens[i].tipo == ENQUANTO){
            printf("# %d: enquanto\n", tokens[i].linha);
        }else if (tokens[i].tipo == FACA){
            printf("# %d: faca\n", tokens[i].linha);
        }else if (tokens[i].tipo == LEIA){
            printf("# %d: leia\n", tokens[i].linha);
        }else if (tokens[i].tipo == ESCREVA){
            printf("# %d: escreva\n", tokens[i].linha);
        }else if (tokens[i].tipo == DIV){
            printf("# %d: div\n", tokens[i].linha);
        }else if (tokens[i].tipo == VERDADEIRO){
            printf("# %d: verdadeiro\n", tokens[i].linha);
        }else if (tokens[i].tipo == FALSO){
            printf("# %d: falso\n", tokens[i].linha);
        }else if (tokens[i].tipo == PONTO_VIRGULA){
            printf("# %d: ponto e virgula\n", tokens[i].linha);
        }else if (tokens[i].tipo == VIRGULA){
            printf("# %d: virgula\n", tokens[i].linha);
        }else if (tokens[i].tipo == PONTO){
            printf("# %d: ponto\n", tokens[i].linha);
        }else if (tokens[i].tipo == DOIS_PONTOS){
            printf("# %d: dois pontos\n", tokens[i].linha);
        }else if (tokens[i].tipo == IDENTIFICADOR){
            printf("# %d: identificador:%s\n", tokens[i].linha, tokens[i].palavra);
        }else if (tokens[i].tipo == ATRIBUICAO){
            printf("# %d: atribuicao\n", tokens[i].linha);
        }else if (tokens[i].tipo == PAR_ABRINDO){
            printf("# %d: parentese abrindo\n", tokens[i].linha);
        }else if (tokens[i].tipo == PAR_FECHANDO){
            printf("# %d: parentese fechando\n", tokens[i].linha);
        }else if (tokens[i].tipo == MENOR){
            printf("# %d: menor\n", tokens[i].linha);
        }else if (tokens[i].tipo == MENOR_IGUAL){
            printf("# %d: menor igual\n", tokens[i].linha);
        }else if (tokens[i].tipo == IGUAL){
            printf("# %d: igual\n", tokens[i].linha);
        }else if (tokens[i].tipo == DIFERENTE){
            printf("# %d: diferente\n", tokens[i].linha);
        }else if (tokens[i].tipo == MAIOR){
            printf("# %d: maior\n", tokens[i].linha);
        }else if (tokens[i].tipo == MAIOR_IGUAL){
            printf("# %d: maior igual\n", tokens[i].linha);
        }else if (tokens[i].tipo == MAIS){
            printf("# %d: mais\n", tokens[i].linha);
        }else if (tokens[i].tipo == MENOS){
            printf("# %d: menos\n", tokens[i].linha);
        }else if (tokens[i].tipo == VEZES){
            printf("# %d: vezes\n", tokens[i].linha);
        }else if (tokens[i].tipo == E){
            printf("# %d: e\n", tokens[i].linha);
        }else if (tokens[i].tipo == OU){
            printf("# %d: ou\n", tokens[i].linha);
        }else if (tokens[i].tipo == NUMERO){
            printf("# %d: numero\n", tokens[i].linha);
        }
    }
}

int main(){

    char * nome_arquivo = "exemplo2.txt";
    char texto_programa[1000000]; // Armazena todo o texto do programa

    // Abre o aqruivo e realiza a leitura

    FILE *arquivo;

    arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("[ERRO] Arquivo nao encontrado\n");
        return 1;
    }

    fread(texto_programa, 1, 1000000, arquivo);

    fclose(arquivo);

    // Realiza a Analise Lexica

    Token tokens[100000];
    Token tokens_sem_comentario[100000];
    int numero_tokens = 0;
    int linha = 0;

    if(Analise_Lexica(texto_programa, tokens, &numero_tokens, &linha)){

        // Ignora os comentarios para a analise sintatica
        int j = 0;
        for (int i = 0; i < numero_tokens; ++i){
            if(tokens[i].tipo != COMENTARIO){
                tokens_sem_comentario[j++] = tokens[i];
            }
        }

        // Realiza a Analise Sintatica

        if(Analise_Sintatica(tokens_sem_comentario)){
            Imprime_Tokens(tokens, numero_tokens);
            printf("%d linhas analisadas, programa sintaticamente correto\n", linha);
        }
    }

    return 0;
}
