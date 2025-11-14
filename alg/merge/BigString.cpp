#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura simples
typedef struct No {
    char* texto;
    struct No* prox;
} No;


// Cria um nó novo e já aloca a memória do texto automaticamente
No* criar_no(char* txt, No* proximo) {
    No* n = (No*)malloc(sizeof(No));
    n->texto = (char*)malloc(strlen(txt) + 1);
    strcpy(n->texto, txt);
    n->prox = proximo;
    return n;
}

// --- FUNÇÃO 1: CRIAR O VETORES ---
void atualizar_indices(No* inicio, int** v_somas, No*** v_ptrs, int* total_chars, int* qtd_nos) {
    // 1. Conta quantos nós existem
    int count = 0;
    No* aux = inicio;
    while(aux) { count++; aux = aux->prox; }
    *qtd_nos = count;

    // 2. Prepara os vetores
    if (count > 0) {
        *v_somas = (int*)malloc(count * sizeof(int));
        *v_ptrs  = (No**)malloc(count * sizeof(No*));
    }

    // 3. Preenche o mapa
    int soma = 0, i = 0;
    aux = inicio;
    while(aux) {
        soma += strlen(aux->texto);
        (*v_somas)[i] = soma;
        (*v_ptrs)[i]  = aux;
        aux = aux->prox;
        i++;
    }
    *total_chars = soma;
}

// --- FUNÇÃO 2: INSERIR TEXTO---
void inserir_na_posicao(No** inicio, int pos_alvo, char* txt_novo) {
    No* atual = *inicio;
    No* anterior = NULL;
    int pos_global = 0;

    // Acha o nó certo
    while (atual) {
        int tam = strlen(atual->texto);
        if (pos_global + tam >= pos_alvo) break;
        pos_global += tam;
        anterior = atual;
        atual = atual->prox;
    }

    if (!atual) return; 

    int local = pos_alvo - pos_global;

    // Lógica Simplificada de Corte e Costura:
    
    if (local == 0) { // insere antes
        No* novo = criar_no(txt_novo, atual);
        if (anterior) anterior->prox = novo;
        else *inicio = novo;
    } 
    else { // Corta -> Cria Resto -> Cria Meio -> Liga
        // 1. Cria o nó com o resto da string (da direita)
        No* resto = criar_no(atual->texto + local, atual->prox);
        
        // 2. Cria o nó novo e liga no resto
        No* meio = criar_no(txt_novo, resto);
        
        // 3. Corta a string atual e liga no meio
        atual->texto[local] = '\0';
        atual->prox = meio;
    }
}

// --- FUNÇÃO 3: BUSCA BINÁRIA ---
int buscar_bloco(int* arr, int n, int val) {
    int l = 0, h = n - 1, ans = -1;
    while (l <= h) {
        int mid = l + (h - l) / 2;
        if (arr[mid] > val) {
            ans = mid;
            h = mid - 1;
        } else l = mid + 1;
    }
    return ans;
}


// ================= MAIN =================

int main() {
    // Setup inicial LIFO
    No* head = criar_no("klmno", NULL);
    head = criar_no("ghij", head);
    head = criar_no("def", head);
    head = criar_no("abc", head);

    
    int *v_somas = NULL;
    No **v_ptrs = NULL;
    int qtd_nos = 0, total_chars = 0;

    // Mapa inicial
    atualizar_indices(head, &v_somas, &v_ptrs, &total_chars, &qtd_nos);
    
    
    printf("Total caracteres: %d\n", total_chars);

    // --- PARTE 1: PEDIR INSERÇÃO ---
    int pos_ins;
    char txt_ins[100];

    printf("\n[EDICAO] Onde inserir (0 a %d)? ", total_chars);
    scanf("%d", &pos_ins);
    printf("[EDICAO] Qual texto? ");
    scanf("%s", txt_ins);

    if (pos_ins >= 0 && pos_ins <= total_chars) {
        inserir_na_posicao(&head, pos_ins, txt_ins);
        
        // Limpa vetores velhos e recria
        free(v_somas); free(v_ptrs);
        atualizar_indices(head, &v_somas, &v_ptrs, &total_chars, &qtd_nos);
        
        printf("\n... Atualizado ...\n");
       
    }

    // --- PARTE 2: PEDIR BUSCA ---
    int pos_busca;
    printf("\n[LEITURA] Qual posicao ler (0 a %d)? ", total_chars - 1);
    scanf("%d", &pos_busca);

    if (pos_busca >= 0 && pos_busca < total_chars) {
        int idx = buscar_bloco(v_somas, qtd_nos, pos_busca);
        
        if (idx != -1) {
            int anterior = (idx == 0) ? 0 : v_somas[idx - 1];
            char c = v_ptrs[idx]->texto[pos_busca - anterior];
            
            printf("\n--- RESULTADO ---\n");
            printf("Bloco: %d (Conteudo: \"%s\")\n", idx, v_ptrs[idx]->texto);
            printf("Caractere: '%c'\n", c);
        }
    } else {
        printf("Posicao invalida.\n");
    }

    // Limpeza final
    free(v_somas);
    free(v_ptrs);
    return 0;
}
