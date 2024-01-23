#include <bits/stdc++.h>    
#include "ArbolBinario.h"
#include "ArbolAVL.h"
#include "ArbolRB.h"
#include "ColorsHead.h"

int main() {
    int opcion;
    ArbolAVL arbolAVL;
    ABB arbolABB = NULL;
    RedBlackTree<int> arbolRB;

    do {
		system("cls");

		cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout <<RESET_COLOR<<"\n\t\t                 ..[  "<<MAGENTA_COLOR<<ITALIC<<"MENU"<<RESET_COLOR<<"  ]..  \n";
		cout<<BLUE_COLOR<<"\n"<<"==============================================================================="<<"\n";
		cout << RED_COLOR<<"\t [1]"<<RESET_COLOR<<"  Arbol ABB  \n";
		cout << RED_COLOR<<"\t [2]"<<RESET_COLOR<<"  Arbol AVL  \n";
		cout << RED_COLOR<<"\t [3]"<<RESET_COLOR<<"  Arbol RB  \n";
		cout << RED_COLOR<<"\t [4]"<<RESET_COLOR<<"  Salir  \n";

        cout<<"\n\n"<<RESET_COLOR;
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
                menuRedBlack(arbolRB);
                break;
            case 4:
                break;

            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
        
        std::cout << std::endl;
    } while (opcion != 4);
    
    return 0;
}
