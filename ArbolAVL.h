#include <iostream>
#include <algorithm>

class NodoAVL {
public:
    int key;
    NodoAVL* left;
    NodoAVL* right;
    int altura;

    NodoAVL(int val) : key(val), left(nullptr), right(nullptr), altura(1) {}
};

class ArbolAVL {
private:
    NodoAVL* root;

public:
    ArbolAVL() : root(nullptr) {}

    void clearAll() {
        root = nullptr;
    }

    // Métodos de inserción
    void insertar(int key) {
        root = insertarAVL(root, key);
    }

    NodoAVL* insertarAVL(NodoAVL* nodoActual, int key) {
        if (nodoActual == nullptr) {
            return new NodoAVL(key);
        }

        if (key < nodoActual->key) {
            nodoActual->left = insertarAVL(nodoActual->left, key);
        } else if (key > nodoActual->key) {
            nodoActual->right = insertarAVL(nodoActual->right, key);
        } else {
            return nodoActual;
        }

        nodoActual->altura = 1 + std::max(getAltura(nodoActual->left), getAltura(nodoActual->right));

        int fe = getFactorEquilibrio(nodoActual);

        if (fe > 1 && key < nodoActual->left->key) {
            return rightRotate(nodoActual);
        }

        if (fe < -1 && key > nodoActual->right->key) {
            return leftRotate(nodoActual);
        }

        if (fe > 1 && key > nodoActual->left->key) {
            nodoActual->left = leftRotate(nodoActual->left);
            return rightRotate(nodoActual);
        }

        if (fe < -1 && key < nodoActual->right->key) {
            nodoActual->right = rightRotate(nodoActual->right);
            return leftRotate(nodoActual);
        }

        return nodoActual;
    }

    // Métodos de búsqueda
    void buscar(int elemento) {
        if (BuscaEnAVL(root, elemento)) {
            std::cout << "Existe" << std::endl;
        } else {
            std::cout << "No Existe" << std::endl;
        }
    }

    bool BuscaEnAVL(NodoAVL* nodoActual, int elemento) {
        if (nodoActual == nullptr) {
            return false;
        } else if (elemento == nodoActual->key) {
            return true;
        } else if (elemento < nodoActual->key) {
            return BuscaEnAVL(nodoActual->left, elemento);
        } else {
            return BuscaEnAVL(nodoActual->right, elemento);
        }
    }

    // Métodos de eliminación
    void eliminar(int key) {
        root = eliminarAVL(root, key);
    }

    NodoAVL* eliminarAVL(NodoAVL* nodoActual, int key) {
        if (nodoActual == nullptr)
            return nodoActual;

        if (key < nodoActual->key) {
            nodoActual->left = eliminarAVL(nodoActual->left, key);
        } else if (key > nodoActual->key) {
            nodoActual->right = eliminarAVL(nodoActual->right, key);
        } else {
            if ((nodoActual->left == nullptr) || (nodoActual->right == nullptr)) {
                NodoAVL* temp = nullptr;
                if (temp == nodoActual->left) {
                    temp = nodoActual->right;
                } else {
                    temp = nodoActual->left;
                }

                if (temp == nullptr) {
                    nodoActual = nullptr;
                } else {
                    nodoActual = temp;
                }
            } else {
                NodoAVL* temp = getNodoConValorMaximo(nodoActual->left);
                nodoActual->key = temp->key;
                nodoActual->left = eliminarAVL(nodoActual->left, temp->key);
            }
        }

        if (nodoActual == nullptr)
            return nodoActual;

        nodoActual->altura = std::max(getAltura(nodoActual->left), getAltura(nodoActual->right)) + 1;

        int fe = getFactorEquilibrio(nodoActual);

        if (fe > 1 && getFactorEquilibrio(nodoActual->left) >= 0) {
            return rightRotate(nodoActual);
        }

        if (fe < -1 && getFactorEquilibrio(nodoActual->right) <= 0) {
            return leftRotate(nodoActual);
        }

        if (fe > 1 && getFactorEquilibrio(nodoActual->left) < 0) {
            nodoActual->left = leftRotate(nodoActual->left);
            return rightRotate(nodoActual);
        }

        if (fe < -1 && getFactorEquilibrio(nodoActual->right) > 0) {
            nodoActual->right = rightRotate(nodoActual->right);
            return leftRotate(nodoActual);
        }

        return nodoActual;
    }

    // Rotaciones
    NodoAVL* rightRotate(NodoAVL* nodoActual) {
        NodoAVL* nuevaRaiz = nodoActual->left;
        NodoAVL* temp = nuevaRaiz->right;

        nuevaRaiz->right = nodoActual;
        nodoActual->left = temp;

        nodoActual->altura = std::max(getAltura(nodoActual->left), getAltura(nodoActual->right)) + 1;
        nuevaRaiz->altura = std::max(getAltura(nuevaRaiz->left), getAltura(nuevaRaiz->right)) + 1;

        return nuevaRaiz;
    }

    NodoAVL* leftRotate(NodoAVL* nodoActual) {
        NodoAVL* nuevaRaiz = nodoActual->right;
        NodoAVL* temp = nuevaRaiz->left;

        nuevaRaiz->left = nodoActual;
        nodoActual->right = temp;

        nodoActual->altura = std::max(getAltura(nodoActual->left), getAltura(nodoActual->right)) + 1;
        nuevaRaiz->altura = std::max(getAltura(nuevaRaiz->left), getAltura(nuevaRaiz->right)) + 1;

        return nuevaRaiz;
    }

    // Métodos auxiliares
    void mostrarArbolAVL() {
        std::cout << "Arbol AVL" << std::endl;
        showTree(root, 0);
    }

    void showTree(NodoAVL* nodo, int depth) {
        if (nodo->right != nullptr) {
            showTree(nodo->right, depth + 1);
        }
        for (int i = 0; i < depth; i++) {
            std::cout << "    ";
        }
        std::cout << "(" << nodo->key << ")" << std::endl;

        if (nodo->left != nullptr) {
            showTree(nodo->left, depth + 1);
        }
    }

    void limpiarArbol(NodoAVL* nodoActual) {
        if (nodoActual != nullptr) {
            limpiarArbol(nodoActual->left);
            limpiarArbol(nodoActual->right);
            delete nodoActual;
            nodoActual = nullptr;
        }
    }

private:
    int getAltura(NodoAVL* nodoActual) {
        if (nodoActual == nullptr) {
            return 0;
        }

        return nodoActual->altura;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getFactorEquilibrio(NodoAVL* nodoActual) {
        if (nodoActual == nullptr) {
            return 0;
        }

        return getAltura(nodoActual->left) - getAltura(nodoActual->right);
    }

    NodoAVL* getNodoConValorMaximo(NodoAVL* node) {
        NodoAVL* current = node;

        while (current->right != nullptr) {
            current = current->right;
        }

        return current;
    }
};

void insertarNumerosRandom(ArbolAVL &arbol, int n) {
    for (int i = 0; i < n; i++) {
        arbol.insertar(rand() % 100);
    }

    std::cout << "\n\t  Números aleatorios insertados..!" << std::endl << std::endl;

}

void menuAVL(ArbolAVL &arbol) {
    int opcion = 0;
    int elemento = 0;

    do {
        system("color 0a"); 
		system("cls");
		std::cout<<"\n"<<"==============================================================================="<<"\n";
		std::cout << "\n\t\t           ..[ ARBOL ADELSON VELSKII Y LANDIS ]..  \n";
		std::cout<<"\n"<<"==============================================================================="<<"\n";
        std::cout << "\t [1]  Insertar elemento      arbol AVL   \n";
        std::cout << "\t [2]  Mostrar arbol          arbol AVL   \n";
        std::cout << "\t [3]  Limpiar arbol          arbol AVL   \n";
        std::cout << "\t [4]  Insertar random        arbol AVL   \n";
        std::cout << "\t [5]  Salir                  arbol AVL   \n";
  
        std::cout << "\n\t Ingrese opcion : ";
        std::cin >> opcion;
        system("cls"); 

        switch (opcion) {
            case 1:
                std::cout << "Ingrese el elemento a insertar: ";
                std::cin >> elemento;
                arbol.insertar(elemento);
                break;
            case 2:
                std::cout<<"\n"<<"==============================================================================="<<"\n";
                std::cout<<"\n"<<"                                   ARBOL AVL                                   "<<"\n";
                std::cout<<"\n"<<"==============================================================================="<<"\n\n\n";
                system("color 05"); 
                arbol.mostrarArbolAVL();
                system("pause");
                break;
            case 3:
                arbol.clearAll();
                std::cout<<"\n"<<"==============================================================================="<<"\n";
                std::cout<<"\n"<<"                                   ARBOL LIMPIO                                "<<"\n";
                std::cout<<"\n"<<"==============================================================================="<<"\n";
                system("pause");
                break;
            case 4:
                int cantidadNumeros;
                std::cout << " Ingrese la cantidad de números aleatorios a insertar: ";
                std::cin >> cantidadNumeros;
                insertarNumerosRandom(arbol, cantidadNumeros);
                system("pause");
                break;

            case 5:
                break;
            
            default:
                std::cout << "Opción inválida" << std::endl;
                break;
        }
        
    } while (opcion != 5);
}

/*
int main() {
    ArbolAVL arbol;

    menuAVL(arbol);
    return 0;
}
*/