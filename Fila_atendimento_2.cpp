#include <iostream>
using namespace std;

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

struct Guiche {
    int id;
    FilaPont* senhasAtendidas;
    Guiche* prox;
};

struct ListaGuiche {
    Guiche* ini;
};

ListaGuiche* initListaGuiche() {
    ListaGuiche* lista = new ListaGuiche;
    lista->ini = NULL;
    return lista;
}

void adicionarGuiche(ListaGuiche* lista, int id) {
    Guiche* g = new Guiche;
    g->id = id;
    g->senhasAtendidas = initPont();
    g->prox = lista->ini;
    lista->ini = g;
}

Guiche* buscarGuiche(ListaGuiche* lista, int id) {
    Guiche* atual = lista->ini;
    while (atual != NULL) {
        if (atual->id == id)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

int contarGuiches(ListaGuiche* lista) {
    int qtde = 0;
    Guiche* atual = lista->ini;
    while (atual != NULL) {
        qtde++;
        atual = atual->prox;
    }
    return qtde;
}

void listarSenhasGuiche(Guiche* g) {
    NoPont* no = g->senhasAtendidas->ini;
    cout << "Senhas atendidas pelo guiche " << g->id << ": ";
    if (!no) {
        cout << "Nenhuma." << endl;
        return;
    }
    while (no != NULL) {
        cout << no->dado << " ";
        no = no->prox;
    }
    cout << endl;
}

void liberarGuiches(ListaGuiche* lista) {
    Guiche* atual = lista->ini;
    while (atual != NULL) {
        Guiche* aux = atual->prox;
        freePont(atual->senhasAtendidas);
        delete atual;
        atual = aux;
    }
    delete lista;
}

int main() {
    FilaPont* senhasGeradas = initPont();
    ListaGuiche* guiches = initListaGuiche();

    int senha = 1;
    int opcao;

    do {
        cout << endl;
        cout << "------------------------------" << endl;
        cout << "0 - Sair" << endl;
        cout << "1 - Gerar senha" << endl;
        cout << "2 - Abrir guiche" << endl;
        cout << "3 - Realizar atendimento" << endl;
        cout << "4 - Listar senhas atendidas" << endl;
        cout << "Senhas aguardando: " << countPont(senhasGeradas) << endl;
        cout << "Guiches abertos: " << contarGuiches(guiches) << endl;
        cout << "Opcao: ";
        cin >> opcao;


        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;            
            cout << "Entrada invalida! Digite um numero." << endl;
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: {
            	
				cout << endl;
                cout << "Senha gerada: " << senha << endl;
                enqueuePont(senhasGeradas, senha++);
                break;
            
		}
            case 2: {
                int id;
                
				cout << endl;
                cout << "Digite o ID do guiche: ";
                cin >> id;
                
				if (buscarGuiche(guiches, id)) {
                
					cout << endl;
                    cout << "Guiche ja existe." << endl;
                
				} else {
                	
                    adicionarGuiche(guiches, id);
                    cout << endl;
                    cout << "Guiche " << id << " aberto." << endl;
                
				}
                break;
            }
            case 3: {
                if (isEmptyPont(senhasGeradas)) {

                	cout << endl;
                    cout << "Nenhuma senha aguardando atendimento." << endl;
                    break;

                }

                int id;
                cout << endl;
                cout << "Digite o ID do guiche: ";
                cin >> id;
                Guiche* g = buscarGuiche(guiches, id);
                
                if (!g) {

                	cout << endl;
                    cout << "Guiche nao encontrado." << endl;;

                } else {

                    int s = dequeuePont(senhasGeradas);
                    enqueuePont(g->senhasAtendidas, s);
                    cout << endl;
				    cout << "Guiche " << id << " atendeu a senha " << s << endl;
                
				}
                
				break;
            }
            
			case 4: {
                int id;
                cout << endl;
                cout << "Digite o ID do guiche: ";
                cin >> id;
                Guiche* g = buscarGuiche(guiches, id);
                
                if (!g) {
                	
                	cout << endl;
                    cout << "Guiche nao encontrado." << endl;

                } else {
                
				    listarSenhasGuiche(g);
                
				}
                
				break;
            }
            
            case 0: {
                if (!isEmptyPont(senhasGeradas)) {
                	
					cout << endl;
                    cout << "Ainda ha senhas aguardando atendimento!" << endl;
                    opcao = -1; 
                
				}
                
				break;
            }
            default: {
            	
            	cout << endl;
                cout << "Opcao invalida!\n";
                opcao = -1;
                
				break;
            }
            
		}

    } while (opcao != 0);

    int totalAtendidas = 0;
    Guiche* atual = guiches->ini;
    while (atual != NULL) {
    	
        totalAtendidas += countPont(atual->senhasAtendidas);
        atual = atual->prox;
    
	}

    cout << "\nTotal de senhas atendidas: " << totalAtendidas << endl;

    freePont(senhasGeradas);
    liberarGuiches(guiches);

    return 0;
}