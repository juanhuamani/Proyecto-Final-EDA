#include <iostream>
#include <stdlib.h>

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
	system("cls");
	if (arbol == NULL)
	{
		arbol = crearNodo(x);
		cout << "\n\t  Insertado..!" << endl << endl;
		system("cls");
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x > arbol->nro)
		insertar(arbol->der, x);
}


void verArbol(ABB arbol, int n)
{
	if (arbol == NULL)
		return;
	verArbol(arbol->der, n + 1);

	for (int i = 0; i<n; i++)
		cout << "   ";

	numNodosABB++;
	cout << "("<< arbol->nro<<")" << endl;

	verArbol(arbol->izq, n + 1);
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



void recorrerxNivel(ABB arbol)
{
	struct cola q;
	inicializaCola(q);
	cout << "\t";

	if (arbol != NULL)
	{
		encola(q, arbol);

		while (q.delante != NULL)
		{
			arbol = desencola(q);
			cout << arbol->nro << ' ';

			if (arbol->izq != NULL)
				encola(q, arbol->izq);
			if (arbol->der != NULL)
				encola(q, arbol->der);
		}
	}
}

void insertarNumerosRandom(ABB &arbol, int n)
{
    system("cls");
    for (int i = 0; i < n; ++i)
    {
        int num = rand() % 100;
        insertar(arbol, num);
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
				verArbol(arbol, 0);
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
				cout << " Ingrese la cantidad de números aleatorios a insertar: ";
				cin >> cantidadNumeros;
				insertarNumerosRandom(arbol, cantidadNumeros);
				system("pause");
				break;
				
			default:
				cout << " Opcion incorrecta..!" << endl;
				break;

		} 

	} while (op != 5);
}


/*	
int main()
{
	ABB arbol = NULL;
	menuABB(arbol); 
	

}
*/