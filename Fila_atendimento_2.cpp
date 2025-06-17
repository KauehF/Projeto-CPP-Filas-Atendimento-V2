#include <iostream>
using namespace std;

#define MAX 100

//fila feita com vetor

struct FilaVet {
    int dados[MAX];
    int ini;
    int fim;
};

FilaVet* initVet() {
    FilaVet* f = new FilaVet;
    f->ini = f->fim = 0;
    return f;
}

int isEmptyVet(FilaVet* f) {
    return f->ini == f->fim;
}

int incrementa(int i) {
    return (i + 1) % MAX;
}

int enqueueVet(FilaVet* f, int v) {
    int prox = incrementa(f->fim);
    if (prox == f->ini) return 0; // cheio
    f->dados[f->fim] = v;
    f->fim = prox;
    return 1;
}

int dequeueVet(FilaVet* f) {
    if (isEmptyVet(f)) return -1;
    int val = f->dados[f->ini];
    f->ini = incrementa(f->ini);
    return val;
}

int countVet(FilaVet* f) {
    if (f->fim >= f->ini) return f->fim - f->ini;
    return MAX - f->ini + f->fim;
}

void freeVet(FilaVet* f) {
    delete f;
}

//fila feita com ponteiro

struct NoPont {
    int dado;
    NoPont* prox;
};

struct FilaPont {
    NoPont* ini;
    NoPont* fim;
};

FilaPont* initPont() {
    FilaPont* f = new FilaPont;
    f->ini = NULL;
	f->fim = NULL;
    return f;
}

int isEmptyPont(FilaPont* f) {
    return f->ini == NULL;
}

void enqueuePont(FilaPont* f, int v) {
    NoPont* no = new NoPont;
    no->dado = v;
    no->prox = NULL;
    if (isEmptyPont(f)) {
        f->ini = no;
    } else {
        f->fim->prox = no;
    }
    f->fim = no;
}

int dequeuePont(FilaPont* f) {
    if (isEmptyPont(f)) return -1;
    NoPont* no = f->ini;
    int ret = no->dado;
    f->ini = no->prox;
    if (f->ini == NULL) f->fim = NULL;
    delete no;
    return ret;
}

int countPont(FilaPont* f) {
    int qtde = 0;
    NoPont* no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void freePont(FilaPont* f) {
    NoPont* no = f->ini;
    while (no != NULL) {
        NoPont* aux = no->prox;
        delete no;
        no = aux;
    }
    delete f;
}

int main()
{
	
	FilaPont* senhasGeradasPont = initPont();
    FilaVet* senhasAtendidasVet = initVet();
    
    int senha = 1;
    int opcao;

    do {
    	
    	cout << endl;

        cout << "0 - Sair" << endl;
        cout << "1 - Gerar senha" << endl;
        cout << "2 - Abrir Guiche" << endl;
	cout << "3 - Realizar atendimento" << endl;
	cout << "4 - Listar senhas atendidas" << endl;
        cout << "Senhas aguardando: " << countPont(senhasGeradasPont) << endl;
        cout << "Opcao: ";
        cin >> opcao;
        
        if (cin.fail()){
        	
        cin.clear(); 
        cin.ignore(1000, '\n');
        cout << "Entrada invalida! Digite um numero." << endl;
        opcao = -1;
		 
        continue;
		 
    	}

        switch (opcao) {
        	
            case 1: {
            
			    cout << "Senha gerada: " << senha << endl;
                enqueuePont(senhasGeradasPont, senha++);
                break;
            
			}
            
            case 2:{
            
			
            
			}

		 case 3:{
            
			        if (!isEmptyPont(senhasGeradasPont)) {
            
			        int s = dequeuePont(senhasGeradasPont);
                    enqueueVet(senhasAtendidasVet, s);
                    cout << "Atendendo senha: " << s << endl;
            
			    } else {
            
			        cout << "Nenhuma senha para atender.\n";
            
			    }
                break;
            
			}

		 case 4:{
            
			    
            
			}
            
            case 0: {
            
			    if (!isEmptyPont(senhasGeradasPont)) {
            
			        cout << "Ainda ha senhas aguardando atendimento!\n";
                    opcao = -1; // força o loop continuar
            
			    }
                break;
            
			}
            
            default:{
            
			    cout << "Opcao invalida!\n";
				opcao = -1;
				break;
				
			}
				
        }
        
    } while (opcao != 0);

    cout << "\nTotal de senhas atendidas: " << countVet(senhasAtendidasVet) << endl;


    freePont(senhasGeradasPont);
    freeVet(senhasAtendidasVet);
	
	return 0;
}
