#include <bits/stdc++.h> 
#include "texto.h"
using namespace std;

int BOARDSIZE = 130;

vector<vector<texto>> board;
void initBoard(){
    for (int i = 0; i < BOARDSIZE; i++){
        vector<texto> temp;
        for (int j = 0; j < BOARDSIZE; j++){
            temp.push_back(texto(WHITE,BLACK_COLOR,' '));
        }
        board.push_back(temp);
    }
    
    for (int i = 0; i < BOARDSIZE; i++){
        board[0][i].changeCaracter(BLUE_COLOR,'-');
        board[BOARDSIZE - 1][i].changeCaracter(BLUE_COLOR,'-');
        board[i][0].changeCaracter(BLUE_COLOR,'|');
        board[i][BOARDSIZE - 1].changeCaracter(BLUE_COLOR,'|');
    }
    board[0][0].changeCaracter(BLUE_COLOR,218);
    board[0][BOARDSIZE-1].changeCaracter(BLUE_COLOR,191);
    board[BOARDSIZE-1][0].changeCaracter(BLUE_COLOR,192);
    board[BOARDSIZE-1][BOARDSIZE-1].changeCaracter(BLUE_COLOR,217);

}
void printBoard(){
    for (auto i : board){
        for (auto j : i){
            cout << j;
        }
        cout << endl;
    }
}

class Punto{
public:
    int x;
    int y;
    Punto(int x, int y){
        this->x = x;
        this->y = y;
    }
    Punto(Punto* punto){
        this->x = punto->x;
        this->y = punto->y;
    }
    Punto* puntoMedio(Punto* punto){
        return new Punto((this->x + punto->x)/2,(this->y + punto->y)/2);
    }
    void printPunto(){
        cout<<"("<<this->x<<","<<this->y<<")"<<endl;
    }
};

class QNode{
public:
    Punto* contenido;
    Punto* punto_bajo;
    Punto* punto_alto;
    Punto* punto_medio;
    
    QNode* padre;
    vector<QNode*> hijos;
    bool isLeaf=0;
    QNode(){
        this->contenido = NULL;
        this->punto_bajo = NULL;
        this->punto_alto = NULL;
        this->padre = NULL;
    }
    QNode(Punto* contenido, Punto* punto_bajo, Punto* punto_alto){
        this->contenido = contenido;
        this->punto_bajo = punto_bajo;
        this->punto_alto = punto_alto;
        this->punto_medio = punto_bajo->puntoMedio(punto_alto);
        this->padre = NULL;
    }
    QNode(Punto* punto_bajo, Punto* punto_alto){
        this->contenido = NULL;
        this->punto_bajo = punto_bajo;
        this->punto_alto = punto_alto;
        this->punto_medio = punto_bajo->puntoMedio(punto_alto);
        this->padre = padre;
    }
    void printNodeINFO(){
        cout<<"NODO de cuadrante"<<this->punto_bajo->x<<","<<this->punto_bajo->y<<" -> "<<this->punto_alto->x<<" "<<this->punto_alto->y<<endl;
        if(this->contenido){
            cout<<"Contenido: "<<this->contenido->x<<","<<this->contenido->y<<endl;
        }
    }
    int divideNode(){
        cout<<"DIVIDIENDO NODO "<<this->punto_bajo->x<<","<<this->punto_bajo->y<<" -> "<<this->punto_alto->x<<" "<<this->punto_alto->y<<endl;
        //QUADRANTE 1
        this->hijos.push_back(new QNode(new Punto(this->punto_bajo),new Punto(punto_medio)));
        //QUADRANTE 2
        this->hijos.push_back(new QNode(new Punto(punto_medio->x,this->punto_bajo->y),new Punto(this->punto_alto->x,punto_medio->y))); 
        //QUADRANTE 3
        this->hijos.push_back(new QNode(new Punto(this->punto_bajo->x,punto_medio->y),new Punto(punto_medio->x,this->punto_alto->y)));
        //QUADRANTE 4
        this->hijos.push_back(new QNode(new Punto(punto_medio),new Punto(this->punto_alto)));
        for (auto i : this->hijos){
            i->padre = this;
        }
        cout<<"Llenando division"<<endl;
        for (int i = this->punto_bajo->x + 1; i <= this->punto_alto->x+1; i++) {
            board[this->punto_medio->y+1][i].changeCaracter(BLUE_COLOR,'-');
        }
        cout<<"Línea vertical"<<endl;
        for (int i = this->punto_bajo->y + 1; i <= this->punto_alto->y+1; i++) {
                board[i][this->punto_medio->x + 1].changeCaracter(BLUE_COLOR, '|');
        }
        cout<<"Línea vertical"<<endl;
        
        board[this->punto_medio->y + 1][this->punto_medio->x + 1].changeCaracter(BLUE_COLOR, '+');

        cout<<"Fin llenado"<<endl;
        if(!this->contenido) return -1;

        if(this->contenido->x<punto_medio->x && this->contenido->y<punto_medio->y){
            this->hijos[0]->contenido = this->contenido;
            this->hijos[0]->isLeaf = 1;
            return 0;
        }
        else if(this->contenido->x>=punto_medio->x && this->contenido->y<punto_medio->y){
            this->hijos[1]->contenido = this->contenido;
            this->hijos[1]->isLeaf = 1;
            return 1;
        }
        else if(this->contenido->x<punto_medio->x && this->contenido->y>=punto_medio->y){
            this->hijos[2]->contenido = this->contenido;
            this->hijos[2]->isLeaf = 1;
            return 2;

        }
        else if(this->contenido->x>=punto_medio->x && this->contenido->y>=punto_medio->y){
            this->hijos[3]->contenido = this->contenido;
            this->hijos[3]->isLeaf = 1;
            return 3;

        }
        this->contenido = NULL;
        this->isLeaf = 0;
    }
    int colocarPunto(Punto* punto){
        cout<<"Colocando punto";
        punto->printPunto();
        
        if(punto->x<punto_medio->x && punto->y<punto_medio->y){
            if(!this->hijos[0]->contenido){
                this->hijos[0]->contenido = punto;
                this->hijos[0]->isLeaf = 1;
            }else{
                this->hijos[0]->divideNode();
                this->hijos[0]->colocarPunto(punto);
            }
            cout<<"en Quadrante 0"<<endl;
            return 0;
        }
        else if(punto->x>=punto_medio->x && punto->y<punto_medio->y){
            if(!this->hijos[1]->contenido){
                this->hijos[1]->contenido = punto;
                this->hijos[1]->isLeaf = 1;
            }else{
                this->hijos[1]->divideNode();
                this->hijos[1]->colocarPunto(punto);
            }
            cout<<"en Quadrante 1"<<endl;
            
            return 1;
        }
        else if(punto->x<punto_medio->x && punto->y>=punto_medio->y){
            if(!this->hijos[2]->contenido){
                this->hijos[2]->contenido = punto;
                this->hijos[2]->isLeaf = 1;
            }
            else{
                this->hijos[2]->divideNode();
                this->hijos[2]->colocarPunto(punto);
            }
            cout<<"en Quadrante 2"<<endl;
            return 2;
        }
        else if(punto->x>=punto_medio->x && punto->y>=punto_medio->y){
            if(!this->hijos[3]->contenido)
                this->hijos[3]->contenido = punto;
            else{
                this->hijos[3]->divideNode();
                this->hijos[3]->colocarPunto(punto);
            }
            cout<<"en Quadrante 3"<<endl;

            return 3;
        }
    }

    int get_Cuadrante(Punto *punto){
        if(punto->x<punto_medio->x && punto->y<punto_medio->y){
            return 0;
        }
        else if(punto->x>=punto_medio->x && punto->y<punto_medio->y){
            return 1;
        }
        else if(punto->x<punto_medio->x && punto->y>=punto_medio->y){
            return 2;
        }
        else if(punto->x>=punto_medio->x && punto->y>=punto_medio->y){
            return 3;
        }
    }
};
class QTree{
    QNode* root;
    public:
        QTree(){
            root = new QNode(new Punto(0,0), new Punto(127,127));
            root->divideNode();
        }
        void insert(QNode* node, Punto* punto){
            if(node==this->root){
                node->colocarPunto(punto);
                node->isLeaf = 0;
                return;
            }
            else{
                if(node->contenido->x == punto->x && node->contenido->y == punto->y){
                    return;
                }
                if(node->isLeaf){
                    node->colocarPunto(punto);
                    return;
                }else{
                    int cuadrante = node->get_Cuadrante(punto);
                    insert(node->hijos[cuadrante],punto);
                
                }
            }
        }
        void insert(Punto* punto){
            insert(root,punto);
        }
        void insert_Demo(Punto* punto){
            board[punto->y+1][punto->x+1].changeCaracter(RED,RESET_COLOR,'X');
            insert(root,punto);
            printBoard();
            cout<<"------------------"<<endl;
        }    
};

int main(){
    system("cls");
    initBoard();
    QTree* tree = new QTree();
    tree->insert_Demo(new Punto(20,20));
    tree->insert_Demo(new Punto(10,10));

    printBoard();
    /*
    
    cout<<"------------------"<<endl;
    cout<<"------------------"<<endl;
    tree->insert(new Punto(40,40));
    cout<<"------------------"<<endl;
    tree->insert(new Punto(90,70));
    */

}