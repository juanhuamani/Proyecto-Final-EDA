#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef struct ABBnodo {
	int nro;
	struct ABBnodo *izq, *der;
}*ABB;

int numNodosABB = 0; 
int numK = 0, k;     

struct nodoCola {
	ABB ptr;
	struct nodoCola *sgte;
};
struct cola {
	struct nodoCola *delante;
	struct nodoCola *atras;
};

void inicializaCola(struct cola &q)
{
	q.delante = NULL;
	q.atras = NULL;
}

void encola(struct cola &q, ABB n)
{
	struct nodoCola *p;
	p = new(struct nodoCola);
	p->ptr = n;
	p->sgte = NULL;
	if (q.delante == NULL)
		q.delante = p;
	else
		(q.atras)->sgte = p;
	q.atras = p;
}

ABB desencola(struct cola &q)
{
	struct nodoCola *p;
	p = q.delante;
	ABB n = p->ptr;
	q.delante = (q.delante)->sgte;
	delete(p);
	return n;
}


ABB crearNodo(int x)
{
	ABB nuevoNodo = new(struct ABBnodo);
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}


void insertar(ABB &arbol, int x)
{
	if (arbol == NULL)
	{
		arbol = crearNodo(x);
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x > arbol->nro)
		insertar(arbol->der, x);
}


void limpiarArbol(ABB &arbol)
{
    if (arbol != NULL)
    {
        limpiarArbol(arbol->izq);
        limpiarArbol(arbol->der);
        delete arbol;
        arbol = NULL;
    }
}

int altura(ABB arbol) {
    if (arbol == NULL)
        return 0;
    int hizq = altura(arbol->izq);
    int hder = altura(arbol->der);
    return std::max(hizq, hder) + 1;
}

std::vector<std::vector<char>> crearMatriz(int n, int m) {
    std::vector<std::vector<char>> matriz(n, std::vector<char>(m, ' '));
    return matriz;
}

void imprimirMatriz(const std::vector<std::vector<char>>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 100; j < matriz[i].size(); j++) {
            std::cout << matriz[i][j];
        }
        std::cout << "\n\n";
    }
}

void rellenarMatriz(ABB arbol, std::vector<std::vector<char>>& matriz, int fila, int col, int offset) {
    if (arbol == NULL)
        return;
    std::string s = std::to_string(arbol->nro);
    for (int i = 0; i < s.size(); i++) {
        matriz[fila][col + i] = s[i];
    }
    if (arbol->izq != NULL) {
        matriz[fila + 1][col - offset / 2] = '/';
        rellenarMatriz(arbol->izq, matriz, fila + 2, col - offset, offset / 2);
    }
    if (arbol->der != NULL) {
        matriz[fila + 1][col + offset / 2] = '\\';
        rellenarMatriz(arbol->der, matriz, fila + 2, col + offset, offset / 2);
    }
}

void verArbol(ABB arbol) {
    int h = altura(arbol);
    std::vector<std::vector<char>> matriz = crearMatriz(h*3, 300);
    rellenarMatriz(arbol, matriz, 0, 150, 20);
    imprimirMatriz(matriz);
}

void insertarNumerosRandom(ABB &arbol, int n)
{
    system("cls");
    for (int i = 0; i < n; ++i)
    {
        int num = rand() % 100;
		std::cout<<"\n"<<"==============================================================================="<<"\n";
		std::cout << "\n\t\t           ..[ INSERTANDO "<<num<<" ]..  \n";
		std::cout<<"\n"<<"==============================================================================="<<"\n\n";
        insertar(arbol, num);
		verArbol(arbol);
		std::cout<<"\n\n";
    }
    cout << "\n\t  Números aleatorios insertados..!" << endl << endl;
}


void menuABB(ABB& arbol){
	int op , x;
	do{
		system("color 0a"); 
		system("cls");
		cout<<"\n"<<"==============================================================================="<<"\n";
		cout << "\n\t\t           ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n";
		cout<<"\n"<<"==============================================================================="<<"\n";
		cout << "\t [1]  Insertar elemento      arbol ABB   \n";
		cout << "\t [2]  Mostrar arbol          arbol ABB   \n";
		cout << "\t [3]  Limpiar arbol          arbol ABB   \n";
		cout << "\t [4]  Insertar random        arbol ABB   \n";
		cout << "\t [5]  Salir                  arbol ABB   \n";

		cout << "\n\t Ingrese opcion : ";

		cin >> op;
		cout << endl;
		system("cls"); 

		switch (op)
		{
			case 1:
				cout << " Ingrese valor : ";  cin >> x;
				insertar(arbol, x);
				break;

			case 2: 
				std::cout<<"\n"<<"==============================================================================="<<"\n";
				std::cout<<"\n"<<"                                   ARBOL ABB                                   "<<"\n";
				std::cout<<"\n"<<"==============================================================================="<<"\n\n\n";
				verArbol(arbol);
				system("pause");
				break;

			case 3:
				limpiarArbol(arbol);
				cout<<"\n"<<"==============================================================================="<<"\n";
				cout<<"\n"<<"                                   ARBOL LIMPIO                                "<<"\n";
				cout<<"\n"<<"==============================================================================="<<"\n";
				system("pause");
				break;

			case 4:
				int cantidadNumeros;
				cout << " Ingrese la cantidad de numeros aleatorios a insertar: ";
				cin >> cantidadNumeros;
				insertarNumerosRandom(arbol, cantidadNumeros);
				system("pause");
				break;
			
			case 5:
				break;

			default:
				cout << " Opcion incorrecta..!" << endl;
				break;

		} 

	} while (op != 5);
}

