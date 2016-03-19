#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
 
 
/*
 	Fazemos um sumário dos métodos para que possa ser compilado sem erros pelo Dev-c++ o código.
*/
float calcularMedia();
void menuPrincipal();
void inserirElemento();
int removerElemento();
void imprimir();
int removerElemento();
void inserirUltimoElemento();
int maiorNumeroVetor();
int removerUltimoElemento();
void iniciarMeio();

/*
	Struct NO
	Toda atribuição irá gerar uma instância nova com o nome (p)
	o atributo [prox] na verdade sempre será o [valor] anterior.
	
	Exemplo de input de dados [1,2,3,4,5,6]
		será processado como  [6,5,4,3,2,1] 
		Pois é uma pilha, ou melhor uma lista encadeada.
*/

struct no{
	int info;
	struct no * prox;
};

/*
 	Método Main, será responsável por administrar o valor
 	input do menu principal, e distribuir seus valores
 	a suas devidas ações.
*/
int main(int argc, char *argv[]) {

	setlocale(LC_ALL,"portuguese");
	int tecla = 0;
	struct no *inicio;
	int x;
	inicio = NULL;
	
	do{
		menuPrincipal();
		printf("Insira a opcao ->");
		scanf("%d",&tecla);
		menuPrincipal();
		
		switch(tecla){
			case 1:{
				inserirElemento(&inicio);
				break;
			}
			case 2:{
				imprimir(inicio);
				break;
			}
			case 3:{
			    int contagem = contar(inicio);
			    printf("%d elementos inseridos na alocação dinâmica.",contagem);
			    getch();
				break;
			}
			case 4:{
			    float media = calcularMedia(inicio);
			    printf("%.2f media.",media);
			    getch();
				break;
			}
			case 5:{
			   int valor = removerElemento(&inicio);
			   
			   if(valor != -1){
			   	printf("%d é o numero removido",valor);
			   	getch();
			   }
			    
				break;
			}
			case 6:{
			   int valor = removerUltimoElemento(&inicio);
		 	   if(valor != -1){
			   	printf("%d é o numero removido",valor);
			   	getch();
			   }
			
			
				break;
			}
			case 7:{
			     inserirUltimoElemento(&inicio);
		 		    
				break;
			}
			case 8:{
			    procurarExistencia(&inicio);
				getch();
				break;
			}
			case 10:{
		   		int valor = maiorNumeroVetor(&inicio);
		      	if(valor != -1){
			   	printf("%d é o maior número",valor);
			   		getch();
			  	}
		
				break;
			}
			case 11:{
		   	  iniciarMeio(&inicio);
		   	  	break;
				}
		
			
		}
	}while(tecla != 9);
   
}

/*
 	Menu principal é responsável por printar
 	na tela, todas as opções disponíveis
*/
void menuPrincipal(){
	system("cls");
	printf("--- MALLOC ---\n\n");
	printf("1) Inserir Numero\n");
	printf("2) Imprimir Números\n");
	printf("3) Contar\n");
	printf("4) Media\n");
	printf("5) Remover Primeiro Elemento\n");
	printf("6) Remover Último Elemento\n");
	printf("7) Adicionar no final\n");
	printf("8) Procurar número\n");
	printf("10) Maior número\n");
	printf("11) Verifica existência / caso não insere no meio \n");
	printf("\n9) Sair\n\n");
}

/*
	Inserir elemento
	Podemos simular o seguinte cenário
	1) Nenhum valor foi armazenado ainda, sendo assim de forma simples para
		a explicação, pegaremos a instancia do struct NULL, instanciamos uma nova
		struct p sem valores em [p=malloc(sizeof(struct no))]
		
		struct no p
		{
			info : 0,
			prox : NULL
		}
	
		apontamos o atributo -> info para a variável x ( Supomos que seja o valor 7)
		e também atribuimos o atributo->prox = inicio (Lembrando que inicio é null)
		
		struct no p
		{
			info : x (7),
			prox : inicio (NULL)
		}
		
		no final apontamos inicio como p, ficando assim:
		
		struct no inicio
		{
			info : 7,
			prox : inicio (NULL)
		}	
			
	2) Nese cenário, já temos um valor apontando para inicio, sendo que sua struct estará como
	
		struct no inicio
		{
			info : 7,
			prox : NULL
		}
		assim iremos gerar uma instancia, iremos atribuir o valor x que será (3) para info,
		e para prox, apontamos o Inicio, sendo assim ele irá ficar assim:
	
		struct no p
		{
			info : x (3),
			prox : 	struct no Inicio
					{
						info : x (7),
						prox : inicio (NULL)
					}
		}
		
		Toda vez chamando o método, teremos uma lista encadeada infinita, desde que tenhamos
		memória disponível no sistema.
		
		
*/
void inserirElemento(struct no **inicio){
	
	int x = 0;
	printf("Entre com um elemento: ");
	scanf("%d", &x);
	
	struct no *p;
 
		if((p=malloc(sizeof(struct no))) == NULL){
			printf("Erro na alocação de memoria \n");
		}
		else{
			p->info = x;
			p->prox = *inicio;
			*inicio = p;
		}
		
		printf("Elemento inserido!\n");
 
}


void inserirUltimoElemento(struct no **inicio){
	
	int x = 0;
	printf("Entre com um elemento: ");
	scanf("%d", &x);
	
	struct no *p, *q;
   
  	if((p=malloc(sizeof(struct no))) == NULL){
  		printf("Falha na alocação da memória\n\n");
  		getch();
	  }
	  else{
	  	p->info = x;
	  	p->prox = NULL;
	  	
	  	if(*inicio == NULL)
	  		*inicio = p;
	  	else{
	  		q = *inicio;
	  		
			while(q->prox != NULL)
				q = q->prox;
				
			q->prox = p;
				
		 }
	  }

 	*inicio = q; 
	printf("Elemento %d inserido!\n",x);
	getch();
 
}

void imprimir(struct no *inicio){
 struct no *p;
 
 	p=inicio;
	 if(inicio != NULL){
 
 
 		while(p != NULL){
 			printf("--> %d <-- \n", p->info);
 			p = p->prox;
 		}
	}
	else
	{
		printf("Lista Vazia");
	}
	getch();
}
int contar(struct no *inicio){
 	struct no *p;
 	p=inicio;
 	
 	int contagem = 0;
 		
	 if(inicio != NULL){
 		while(p != NULL){
 			contagem++; 
 			p = p->prox;
 			
 		}
	}
	return contagem;
}

float calcularMedia(struct no *inicio){

 	int contagem = contar(inicio);
 	int soma = 0;
	 	
 	struct no *p;
 	p=inicio;
 	
	 if(inicio != NULL){
 		while(p != NULL){
 			soma = soma + p->info; 
 			p = p->prox;
 		}
	}
	
	if(soma == 0 || contagem == 0)
		return 0;
	
	return soma / contagem;
}

int removerElemento(struct no **inicio){

	if(*inicio == NULL){
 		printf("A Lista está vazia.");
 		getch();
 		return -1;
	 }
	 	
	int i = 0; 	
 	struct no *p;
 	
 	p = *inicio;
 	int valor = p->info;
 	*inicio = (*inicio)->prox; 
 
 	free (p);
	p = NULL;
 	return valor;	
}

int removerUltimoElemento(struct no **inicio){

	if(*inicio == NULL){
 		printf("A Lista está vazia.");
 		getch();
 		return -1;
	 }
	 	
	struct no *p;	
	struct no *q;		
	p = *inicio;
	q = *inicio;
	
	if(p->prox == NULL){
		int valor = p->info;
	
		*inicio = (*inicio)->prox; 
		free (p);
		p = NULL;
		return valor;
	}
	
	while(p->prox != NULL){
		q = p;
		p = p->prox;
	}
	
	q->prox = NULL;
	
	inicio = q;
	return p->info;
 
}

void procurarExistencia (struct no ** inicio)
{
	int x = 0;
	printf("Entre com um elemento: ");
	scanf("%d", &x);
   
  	struct no *p;
 	p= *inicio;
 	
   while (p != NULL && p->info != x) 
      p = p->prox; 
      
    if(p == NULL){
    	printf("Não foi encontrado \n");
	}
	else{
		printf("Foi encontrado \n");
	}
	getch();
   
}

void iniciarMeio(struct no ** inicio)
{
	int x = 0;
	printf("Entre com um elemento para buscar: ");
	scanf("%d", &x);
   
  	struct no *p;
 	p= *inicio;
 
   while (p != NULL) {
   	
   	    if(p->info == x){
			printf("Foi encontrado, não vamos inserir \n");
			getch();
			return;
    	
		}
		p = p->prox;
   }
     
      

 	struct no *q;
 	
	if((q=malloc(sizeof(struct no))) == NULL){
		printf("Falha na alocação da memória\n\n");
		getch();
 	}
	  
 	
	printf("Não foi encontrado, vamos inserir no meio \n");
 
	int contagem = 0;
	p= *inicio;
	while(p != NULL){
		contagem++; 
		p = p->prox;
	}
	
	int posicao = 0;
 
		posicao  = (contagem / 2) + 1;
		int i = 0;
		p= *inicio;
		while(p != NULL){
		
			if(posicao == i)
			{
				q->info = x;
				q->prox = p->prox;
				p = q;
			}
			else{
				p = p->prox;
			}
			
				i++; 
		}
		inicio = p;
		
 }
 
int maiorNumeroVetor(struct no **inicio){
	
	int mostValue = 0;
	struct no *p;
	p = *inicio;
	  while (p != NULL && p->info != mostValue) {
	  	if(p->info > mostValue){
	  		mostValue = p->info;
		  }
	  	p = p->prox; 
	  }
	  
	  return mostValue;
}

