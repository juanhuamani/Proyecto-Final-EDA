#include <bits/stdc++.h>

using namespace std;
int BOARDSIZE = 127;
vector<vector<char>> board;
ofstream archivo("puntos.txt");
void llenarBoard(){
    for(int i = 0; i < BOARDSIZE+2; i++){
        vector<char> temp;
        for(int j = 0; j < BOARDSIZE+2; j++){
            temp.push_back(' ');
        }
        board.push_back(temp);
    }
    for(int i=0;i<BOARDSIZE+2;i++){
        board[0][i]='-';
        board[BOARDSIZE+1][i]='-';
        board[i][0]='|';
        board[i][BOARDSIZE+1]='|';
    }
    board[0][0]=218;
    board[0][BOARDSIZE+1]=191;
    board[BOARDSIZE+1][0]=192;
    board[BOARDSIZE+1][BOARDSIZE+1]=217;
}
void printBoard(){
    for(int i = 0; i < BOARDSIZE+2; i++){
        for(int j = 0; j < BOARDSIZE+2; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}
template <class T>
bool operator ==(const vector<T> &a, const vector<T> &b){
    for(auto i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return false;
        }
    }
    return true;
}
template <class T>
class KDNode{
public:
    vector<T> point;
    int dimension;
    KDNode<T> *left, *right;
    //bool depth;
    
    KDNode(vector<T> point, int dimension){
        this->point = point;
        this->dimension = dimension;
        this->left = NULL;
        this->right = NULL;
        //depth = 0;
    }

    bool operator==(const KDNode<T> &other) const{
        for(auto i = 0; i < point.size(); i++){
            if(point[i] != other.point[i]){
                return false;
            }
        }
    }
    void printArbol(ostream &os){
        os << "\"";
        for(int i = 0; i < dimension; i++){
            os << point[i];
            if(i != dimension - 1){
                os << ", ";
            }
        }
        os << "\"";
    }
};

template <class T>
class KDTree{
public:
    KDNode<T> *root=nullptr;
    int dimension;
    int maxsize = 0;
    KDTree(){
        //this->root = nullptr;
        this->dimension = 0;
    }
    KDTree(int d){
        //this->root = nullptr;
        this->dimension = d;
    }
    void insert(int maxX, int minX, int maxY, int minY, vector<T> point, KDNode<T>*& node, int da){
    if (!node){
        node = new KDNode<T>(point, dimension);
        if (point[0] > maxsize){
            maxsize = point[0];
        }
        if (!da){
            for (int i = minY; i < maxY; i++){
                if (board[i][point[0]] != 'X')
                    board[i][point[0]] = '|';
            }
        } else {
            for (int i = minX; i < maxX; i++){
                if (board[point[1]][i] != 'X')
                    board[point[1]][i] = '-';
            }
        }
        board[point[1]][point[0]] = 'X';
        archivo<<"("<<point[0]<<","<<point[1]<<")"<<maxX<<","<<minX<<","<<maxY<<","<<minY<<endl;

        return;
    } else if (node->point == point){
        return;
    } else {
        if (!da){
            if (point[0] < node->point[0]){
                insert(node->point[0], minX, maxY, minY, point, node->left, (da +1)  % this->dimension);
            } else {
                insert(maxX, node->point[0] + 2, maxY, maxY, point, node->right, (da + 1) % this->dimension);
            }
        } else {
            if (point[1] < node->point[1]){
                insert(maxX, minX, node->point[1], minY, point, node->left, (da + 1) % this->dimension);
            } else {
                insert(maxX, minX, maxY, node->point[1] + 1,point, node->right, (da + 1) % this->dimension);
            }
        }
    }
}

    KDNode<T>* find(vector<T> point, KDNode<T> *node, int da){
        if(!node){
            return nullptr;
        }else if(node->point == point){
            return node;
        }else if(point[da] < node->point[da]){
            return find(point, node->left, (da + 1) % this->dimension);
        }else return find(point, node->right, (da + 1) % this->dimension);
    }
    void printArbol(ostream &os, KDNode<T> *node){
        if(!node){
            return;
        }
        if(node->left){
            node->printArbol(os);
            os<<" -> ";
            node->left->printArbol(os);
            os<<endl;
        }
        if(node->right){
            node->printArbol(os);
            os<<" -> ";
            node->right->printArbol(os);
            os<<endl;
        }
        printArbol(os, node->left);
        printArbol(os, node->right);
    }
public:
    void insert(vector<T> point){
        insert(BOARDSIZE+1,1,BOARDSIZE+1,1,point, root, 0);
        cout<<"Insertado"<<endl;
    }
    KDNode<T>* find(vector<T> point){
        return find(point, root, 0);
    }
    void printArbol(ostream &os){
        os<<"digraph G {"<<endl;
        printArbol(os, root);
        os<<"}\n";
    }
};
int main(){
    ofstream file("test.dot");
    
    llenarBoard();
    KDTree<int> a(2);
    a.insert({60,60});
    a.insert({100,60});
    a.insert({100,100});
    //cout<<"aqui";
    printBoard();
    // cout<<a.find({5, 2})->point[0]<<endl;
};