#ifndef ArbolRB_H
#define ArbolRB_H
#include <iostream>
#include <fstream>
#include <vector>
#include "ColorsHead.h"

enum Color { REDRB, BLACKRB };

template <typename Key>
class Node {
public:
    Key key;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(Key key, Color color = REDRB)
        : key(key), color(color), parent(nullptr), left(nullptr), right(nullptr) {}
};

template <typename Key>
class RedBlackTree {
private:
    Node<Key>* root;

    void leftRotate(Node<Key>* x);
    void rightRotate(Node<Key>* y);
    void insertFixup(Node<Key>* z);

public:
    RedBlackTree() : root(nullptr) {}
    
    Node<Key>* getRoot(){
        return root;
    }
    
    void insert(Key key);
    void print();
    void clearTree(Node<Key>* );
    void clear();
 
};


template <typename Key>
void RedBlackTree<Key>::leftRotate(Node<Key>* x) {
    Node<Key>* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

template <typename Key>
void RedBlackTree<Key>::rightRotate(Node<Key>* y) {
    Node<Key>* x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

template <typename Key>
void RedBlackTree<Key>::insertFixup(Node<Key>* z) {
    while (z->parent && z->parent->color == REDRB) {
        if (z->parent == z->parent->parent->left) {
            Node<Key>* y = z->parent->parent->right;
            if (y && y->color == REDRB) {
                z->parent->color = BLACKRB;
                y->color = BLACKRB;
                z->parent->parent->color = REDRB;
                z = z->parent->parent;
                std::cout << "Cambio de color en la raiz.\n";
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACKRB;
                z->parent->parent->color = REDRB;
                rightRotate(z->parent->parent);
                std::cout << "Rotacion derecha.\n";
            }
        } else {
            Node<Key>* y = z->parent->parent->left;
            if (y && y->color == REDRB) {
                z->parent->color = BLACKRB;
                y->color = BLACKRB;
                z->parent->parent->color = REDRB;
                z = z->parent->parent;
                std::cout << "Cambio de color en la raiz.\n";
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACKRB;
                z->parent->parent->color = REDRB;
                leftRotate(z->parent->parent);
                std::cout << "Rotacion izquierda.\n";
            }
        }
    }
    root->color = BLACKRB;
}

template <typename Key>
void RedBlackTree<Key>::insert(Key key) {
    Node<Key>* z = new Node<Key>(key);
    Node<Key>* y = nullptr;
    Node<Key>* x = root;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFixup(z);
}


template <typename Key>
void RedBlackTree<Key>::clearTree(Node<Key>* node) {
    if (node == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);

    delete node;
}

template <typename Key>
void RedBlackTree<Key>::clear() {
    clearTree(root);
    root = nullptr;
}



std::vector<std::vector<char>> crearMatrizRB(int n, int m) {
    std::vector<std::vector<char>> matriz(n, std::vector<char>(m, ' '));
    return matriz;
}

void imprimirMatrizRB(const std::vector<std::vector<char>>& matriz) {
    for (std::vector<char>::size_type i = 0; i < matriz.size(); i++) {
        for (std::vector<char>::size_type j = 0; j < matriz[i].size(); j++) {

            std::cout << matriz[i][j];
        }
        std::cout << "\n\n\n";
    }
}

template <typename Key>
void rellenarMatriz(Node<Key>* root, std::vector<std::vector<char>>& matriz, int fila, int col, int offset) {
    if (root == nullptr)
        return;
    std::string s;
    if(root->color == REDRB) s = RED_COLOR + std::to_string(root->key) ;
    else s =BLUE_COLOR + std::to_string(root->key) ;
    for (std::string::size_type i = 0; i < s.size(); i++) {
        matriz[fila][col + i] = s[i];
    }
    if (root->left != NULL) {
        matriz[fila + 1][col - offset / 2] =  '/';
        rellenarMatriz(root->left, matriz, fila + 2, col - offset, offset / 2);
    }
    if (root->right != NULL) {
        matriz[fila + 1][col + offset / 2] =  '\\';
        rellenarMatriz(root->right, matriz, fila + 2, col + offset, offset / 2);
    }
}

template <typename Key>
int altura(Node<Key>* nodo) {
    if (nodo == nullptr)
        return 0;
    int hizq = altura(nodo->left);
    int hder = altura(nodo->right);
    return std::max(hizq, hder) + 1;
}

template <typename Key>
void printHelper(Node<Key>* root) {
    int h = altura(root); 
    std::vector<std::vector<char>> matriz = crearMatrizRB(h*2, 100); 
    rellenarMatriz(root, matriz, 0, 50, 25); 
    imprimirMatrizRB(matriz); 
}

void insertarNumerosRandom(RedBlackTree <int> & rbTree, int n) {
    srand(time(NULL));
    int numero ;
    for (int i = 0; i < n; i++) {
        numero = 1 + rand() % (100);
        std::cout<<"\n"<<"==============================================================================="<<"\n";
		std::cout << "\n\t\t           ..[ INSERTANDO "<<numero<<" ]..  \n";
		std::cout<<"\n"<<"==============================================================================="<<"\n\n";
        rbTree.insert(numero);
        printHelper(rbTree.getRoot());
        std::cout<<"\n\n\n";
    }

    std::cout << "\n\t  Numeros aleatorios insertados..!" << std::endl << std::endl;

}

void menuRedBlack (RedBlackTree <int> & rbTree ){
    int op , x;
	do{
		system("color 0a"); 
		system("cls");
		std::cout<<"\n"<<"==============================================================================="<<"\n";
		std::cout << "\n\t\t           ..[ ARBOL RED BLACK  ]..  \n";
		std::cout<<"\n"<<"==============================================================================="<<"\n";
		std::cout << "\t [1]  Insertar elemento      arbol RB    \n";
		std::cout << "\t [2]  Mostrar arbol          arbol RB    \n";
		std::cout << "\t [3]  Limpiar arbol          arbol RB    \n";
		std::cout << "\t [4]  Insertar random        arbol RB    \n";
		std::cout << "\t [5]  Salir                  arbol RB    \n";

		std::cout << "\n\t Ingrese opcion : ";

		std::cin >> op;
		std::cout << std::endl;
		system("cls"); 

		switch (op)
		{
			case 1:
				std::cout << " Ingrese valor : ";  std::cin >> x;
				rbTree.insert(x);
				break;

			case 2: 
				std::cout<<"\n"<<"==============================================================================="<<"\n";
				std::cout<<"\n"<<"                                   ARBOL RB                                    "<<"\n";
				std::cout<<"\n"<<"==============================================================================="<<"\n\n\n";
				printHelper(rbTree.getRoot());
				system("pause");
				break;

			case 3:
				rbTree.clear();
				std::cout<<"\n"<<"==============================================================================="<<"\n";
				std::cout<<"\n"<<"                                   ARBOL LIMPIO                                "<<"\n";
				std::cout<<"\n"<<"==============================================================================="<<"\n";
				system("pause");
				break;

			case 4:
				int cantidadNumeros;
				std::cout << " Ingrese la cantidad de numeros aleatorios a insertar: ";
				std::cin >> cantidadNumeros;
				insertarNumerosRandom(rbTree, cantidadNumeros);
				system("pause");
				break;
			
            case 5:
                break;

			default:
				std::cout << " Opcion incorrecta..!" << std::endl;
				break;
		} 

	} while (op != 5);
}

#endif 

/* 
int main() {
    RedBlackTree<int> rbTree;

    menuRedBlack(rbTree);
}
*/