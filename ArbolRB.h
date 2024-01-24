#include <iostream>
#include <fstream>
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

    // Constructor
    Node(Key key, Color color = REDRB)
        : key(key), color(color), parent(nullptr), left(nullptr), right(nullptr) {}
};

template <typename Key>
class RedBlackTree {
private:
    Node<Key>* root;

    // Helper functions
    void leftRotate(Node<Key>* x);
    void rightRotate(Node<Key>* y);
    void insertFixup(Node<Key>* z);

public:
    // Constructor
    RedBlackTree() : root(nullptr) {}

    // Public API
    void insert(Key key);
    void print();
    void clearTree(Node<Key>* );
    void clear();
 
};


// Left rotation
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

// Right rotation
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

// Insert fixup
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

// Insertion
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


// Print
template <typename Key>
void printHelper(Node<Key>* root, int space, int level = 0) {
    if (root == nullptr)
        return;

    space += 13;

    printHelper(root->right, space, level + 1);

    for (int i = 0; i < space; i++)
        std::cout << " ";

    std::cout << (root->color == REDRB ? "\033[31m" : "\033[30m") << root->key << "("
              << (root->color == REDRB ? "ROJO" : "NEGRO") << ")" << "\033[0m" << "\n";

    printHelper(root->left, space, level + 1);
}

template <typename Key>
void RedBlackTree<Key>::print() {
    printHelper(root, 0);
    std::cout<<"\n\n\n";
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

void insertarNumerosRandom(RedBlackTree <int> & rbTree, int n) {
    srand(time(NULL));
    int numero ;
    for (int i = 0; i < n; i++) {
        numero = 1 + rand() % (100);
        std::cout<<"\n"<<"==============================================================================="<<"\n";
		std::cout << "\n\t\t           ..[ INSERTANDO "<<numero<<" ]..  \n";
		std::cout<<"\n"<<"==============================================================================="<<"\n\n";
        rbTree.insert(numero);
        rbTree.print();
        std::cout<<"\n\n";
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
				rbTree.print();
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

/* 
int main() {
    RedBlackTree<int> rbTree;

    menuRedBlack(rbTree);
}
*/