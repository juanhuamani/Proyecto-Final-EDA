#include <iostream>

#include "ArbolBinario.h"
#include "ArbolAVL.h"


int main() {
    int opcion;
    ArbolAVL arbolAVL;
    ABB arbolABB = NULL;

    do {
        system("color 0a"); 
		system("cls");
		cout<<"\n"<<"==============================================================================="<<"\n";
		cout << "\n\t\t                 ..[  MENU  ]..  \n";
		cout<<"\n"<<"==============================================================================="<<"\n";
		cout << "\t [1]  Arbol ABB  \n";
		cout << "\t [2]  Arbol AVL  \n";
		cout << "\t [3]  Salir  \n";

        cout<<"\n\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                menuABB(arbolABB);
                break;
            case 2:
                menuAVL(arbolAVL);
                break;
            case 3:
                break;
            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
        
        std::cout << std::endl;
    } while (opcion != 3);
    
    return 0;
}
