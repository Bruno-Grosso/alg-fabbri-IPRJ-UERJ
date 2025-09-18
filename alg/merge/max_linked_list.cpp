#include "max_linked_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


 

Node* removerNodePorPosicao(Node* head) {
    if (head == NULL) {
        printf("A lista esta vazia. Nao ha elementos para remover.\n");
        return NULL;
    }

    int posicao;
    printf("Digite a posicao do no a ser excluido (1 a 4): ");
    scanf("%d", &posicao);
    getchar();

    if (posicao < 1) {
        printf("Posicao invalida. A posicao deve ser maior que 0.\n");
        return head;
    }

    // Caso 1: Remocao do PRIMEIRO no
    if (posicao == 1) {
        Node* temp = head;
        head = head->next;
        // Se a struct tiver campos dinamicos, libere-os
        if (temp->nota1 != NULL) {
            free(temp->nota1);
        }
        free(temp);
        printf("\nElemento removido do INICIO.\n");
        return head; // Retorna o novo inicio da lista
    }

    // Caso 2, 3 ou 4: Remocao de nos intermediarios ou do FIM
    Node* atual = head;
    // Navega ate o no ANTERIOR ao que sera removido
    for (int i = 1; i < posicao - 1; i++) {
        if (atual->next == NULL) {
            printf("\nPosicao invalida. A lista nao tem tantos elementos.\n");
            return head;
        }
        atual = atual->next;
    }
    
    // Confere se o no a ser removido existe
    if (atual == NULL || atual->next == NULL) {
        printf("\nPosicao invalida. A lista nao tem tantos elementos.\n");
        return head;
    }

    Node* noParaRemover = atual->next;
    atual->next = noParaRemover->next;

    if (noParaRemover->nota1 != NULL) {
        free(noParaRemover->nota1);
    }
    free(noParaRemover);
    printf("\nElemento removido da posicao %d.\n", posicao);
    
    return head;
}





int main(){
	
	

    char a[500], b[500], c[500], d[500]; //variáveis de texto
	int i =0; // indentificador de inserir e remover
	int j =0; // indentificador do tipo de lista
	int k =50; // indentificador de circular
//---------------------------------------------------------------------------------------------------	
	
	Node* node1 = (Node*)malloc(sizeof(Node)); //alocando memória para os nós e criando o nó 2
	Node* node2 = (Node*)malloc(sizeof(Node));
	Node* node3 = (Node*)malloc(sizeof(Node));
	
	if ((node1 == NULL) or (node2 == NULL) or (node3 == NULL)) { 
		printf("houve um erro na alocação de memória");
		free(node1);
		free(node2);
		free(node3);
		
		return 1;
	}
	
//----------------------------------------------------------------------------------------------------
	printf("escolha o primeiro termo: "); //pedindo o texto de cada nó para o usuário
	fgets(a, sizeof(a), stdin);
	printf("escolha o segundo termo: ");
	fgets(b, sizeof(b), stdin);
	printf("escolha o terceiro termo: ");
	fgets(c, sizeof(c), stdin);
	
	node1 -> nota1 = (char*)malloc(strlen(a) + 1); //alocando memória da constante char nota1 
	node2 -> nota1 = (char*)malloc(strlen(b) + 1);
	node3 -> nota1 = (char*)malloc(strlen(c) + 1);
	
	if ((node1 -> nota1 == NULL) or (node2 -> nota1 == NULL) or (node3 -> nota1 == NULL)) {
		printf("houve um erro na alocação de memória");
		free(node1 -> nota1);
		free(node2 -> nota1);
		free(node3 -> nota1);
		
		return 1;
	}
	
	a[strcspn(a, "\n")] = 0; //excluindo o /n dos elementos
    b[strcspn(b, "\n")] = 0;
    c[strcspn(c, "\n")] = 0;
	strcpy(node1 ->nota1, a); //copiando o elemento do vetor a e b e colando no nó
	strcpy(node2 ->nota1, b);
    strcpy(node3 ->nota1, c);
//----------------------------------------------------------------------------------------------------	
	

	
	printf("qual tipo de lista pretende usar? encadeada (1), duplamente encadeada (2) ou buffer circular (3)");
	scanf("%d", &j);
		
	if(j == 1){//encadeada
			
		node1 -> next = node2; //next para o próximo nó
		node1 -> prev = NULL;
		node2 -> next = node3;
		node2 -> prev = NULL;
		node3 -> next = NULL;
		node3 -> prev = NULL;
	
			
	}
	if(j == 2){//duplamente encadeada
			
		node1 -> next = node2; //next para o próximo nó
		node1 -> prev = NULL;
		node2 -> next = node3;
		node2 -> prev = node1;
		node3 -> next = NULL;
		node3 -> prev = node2;
					
	}
	if(j == 3){//buffer circular
		
		node1 -> next = node2; //next para o próximo nó
		node1 -> prev = NULL;
		node2 -> next = node3;
		node2 -> prev = NULL;
		node3 -> next = node1;
		node3 -> prev = NULL;
		
		printf("deseja que apareca quantos elementos? ");
		scanf("%d", &k);
	}
		
	




	Node* head = node1;
//----------------------------------------------------------------------------------------------------	
	printf("se deseja inserir mais um elemento, digite 1: "); //adicionando elemento na sequência
	scanf("%d", &i);
	
	if (i == 1){
		
		printf("Escolha a posicao para inserir: ");// (0) Será inicio e assim seguirá a sequência
		scanf("%d", &i);
		
		getchar();
		
		printf("escolha outra palavra para adicionar na sequencia: ");
		fgets(d, sizeof(d), stdin);
		d[strcspn(d, "\n")] = 0;
		
		Node* node0 = (Node*)malloc(sizeof(Node));
		node0 -> nota1 = (char*)malloc(strlen(d)+1);
	
		strcpy(node0 -> nota1, d);
		if (i == 0){
			node0 -> next= node1;
			head = node0;
			
			if (j == 2){
				node1 -> prev= node0;				
			}
			if (j == 3){
				node3 -> next= node0;
			}
		}
		if (i == 1){ 
			node1 -> next = node0;
			node0 -> next = node2;			
			head = node1;
			
			if (j == 2){
				node2 -> prev= node0;
				node0 -> prev= node1;				
			}
			
		}
		if (i == 2){ 
			node2 -> next = node0;
			node0 -> next = node3;
			
			head = node1;
			
			if (j == 2){
				node3 -> prev= node0;
				node0 -> prev= node2;				
			}
		}
		if (i == 3){ 
			node3 -> next = node0;
			node0 -> next = NULL;
			
			head = node1;
			
			if (j == 2){
				node0 -> prev= node3;
							
			}
			if (j == 3){
				node0 -> next= node1;
			}
		}
	}

	printf("\nDeseja remover algum elemento? Digite 1 para SIM ou 0 para NAO: "); // eliminando elementos da sequência
	scanf("%d", &i);
	getchar();
	
	if (i == 1) {		
    	head = removerNodePorPosicao(head);  
	}
	
	
	

//----------------------------------------------------------------------------------------------------		

	



	
	printf("\n");	
	for (Node*current = head; current != NULL and i < k; current = current->next) { //printando os elementos individualmente
	    i ++;
		printf("elemento %d e: %s \n", i, current -> nota1);
		
	}
    i= 0;


	printf("\nfrase completa com todos os elementos: "); //printando os elementos em conjunto
	
	for (Node*current = head; current != NULL and i < k; current = current->next) {
		i++;
		printf("%s", current -> nota1);
		
	}
	
	
	return 0;
}
