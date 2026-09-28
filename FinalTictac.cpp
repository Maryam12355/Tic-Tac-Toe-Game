#include<iostream>
#include <string>
using namespace std; 

struct Move {
    int row, col;
    string oldValue;
    string player;
    int oldBlockToDo;
};

struct Node {
    Move data;
    Node* next;
};

struct Stack {
    Node* top = NULL;
};
Stack undoStack;
Stack redoStack;

void displayboard();
int tell_next_block(int row,int col);
int checkCurrentBlock(int row,int col);
int find_Row_And_col_to_check_win_for_small_block(int block);
bool bigBlockWinCheck();
void switchPlayers();
void set_the_small_block_as_current_player_for_small_win(int row,int col,int currentBlock);
void check_Small_Block_win(int row,int col,int currentblock);
int placemakerFun(int choice);
void coutthebigboard();
void checkarbitraryMovevalidation(int block);
void push(Stack &s, Move m);
bool pop(Stack &s, Move &m);
void clearStack(Stack &s);
void undoMove();
void redoMove();
bool isDraw(); 



string board[9][9] = {
    {" 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9"},
    {"10","11","12","13","14","15","16","17","18"},
    {"19","20","21","22","23","24","25","26","27"},
    {"28","29","30","31","32","33","34","35","36"},
    {"37","38","39","40","41","42","43","44","45"},
    {"46","47","48","49","50","51","52","53","54"},
    {"55","56","57","58","59","60","61","62","63"},
    {"64","65","66","67","68","69","70","71","72"},
    {"73","74","75","76","77","78","79","80","81"}
};
int block_to_do_turn_in=11;
bool smallblackwin=false;
bool makemistake=false;
bool arbitrarymove=false;
string big_board_representation[3][3] = {
    {"1","2","3"},
    {"4","5","6"},
    {"7","8","9"}
};
string currentPlayer="X";



int main(){
    while(true){
        system("clear");
        if(bigBlockWinCheck()){
            cout<<"Player "<<currentPlayer<<" Win the game"<<endl;
            return 1;
        }
        if(isDraw()){
            cout<<"Unfortunately game drawed"<<endl;
            return 1;
        }
        int choice;
        displayboard();
        cout << "Enter 1-81 | -1 Undo | -2 Redo" << endl;

        cout<<"Current Player"<<" "<<currentPlayer<<endl;
        if(block_to_do_turn_in!=11&&!arbitrarymove){
            cout<<"Do turn in block "<<block_to_do_turn_in<<endl;
        }
        else if(arbitrarymove){
            cout<<"You can do turn in any block"<<endl;
        }
        if(makemistake==true){
            cout<<"You enter a invalid move or you do turn in wrong block"<<endl;
            makemistake=false;
        }
        // if(smallblackwin){
        //     coutthebigboard();
        // }
        cin >> choice;

if(choice == -1) {   
    undoMove();
    continue;
}
if(choice == -2) {   
    redoMove();
    continue;
}

        int placemakerValue=placemakerFun(choice);
        if(choice<1||choice>81||placemakerValue==1){
            makemistake=true;
            continue;
        }
        if(placemakerValue==2){
            makemistake=true;
            continue;
        }
        if(!smallblackwin){
            switchPlayers();
        }else{smallblackwin=false;}
    }
    checkarbitraryMovevalidation(5);
    }

void displayboard(){
    cout << "\n";

    for (int i = 0; i < 9; i++) {

        for (int j = 0; j < 9; j++) {
            cout << " " << board[i][j] << " ";

           
            if (j == 2 || j == 5)
                cout << "   ||   ";
            

            else if (j < 8)
                cout << " |";
        }
        cout << "\n";

        if (i == 2 || i == 5)
            cout << "================================================================\n";
        
        else if (i < 8)
            cout << "----------------------------------------------------------------\n";
        }

        cout << "\n";
}
int tell_next_block(int row,int col){
     if(row==0||row==3||row==6){
    if(col==0||col-3==0||col-6==0){
        cout<<" Do turn in block 1"<<endl;
        return 1;
    }
    else if(col==1||col-3==1||col-6==1){
        cout<<"Do turn in  block 2"<<endl;
        return 2;
    }
    else if(col==2||col-3==2||col-6==2){
        cout<<"Do turn in block 3"<<endl;
        return 3;
    }
}
    else if(row==1||row==4||row==7){
        if(col==0||col-3==0||col-6==0){
            cout<<" Do turn in block 4"<<endl;
            return 4;
        }
        else if(col==1||col-3==1||col-6==1){
            cout<<"Do turn in  block 5"<<endl;
            return 5;
        }
        else if(col==2||col-3==2||col-6==2){
            cout<<"Do turn in block 6"<<endl;
            return 6;
        }
    }
    else if(row==2||row==5||row==8){
        if(col==0||col-3==0||col-6==0){
            cout<<" Do turn in block 7"<<endl;
            return 7;
        }
        else if(col==1||col-3==1||col-6==1){
            cout<<"Do turn in  block 8"<<endl;
            return 8;
        }
        else if(col==2||col-3==2||col-6==2){
            cout<<"Do turn in block 9"<<endl;
            return 9;
        }
    }
    return 11; // default block

}
int checkCurrentBlock(int row,int col){
    if(row==0||row==1||row==2){
        if(col==0||col==1||col==2){
            return 1;
        }
       else if(col==3||col==4||col==5){
            return 2;
        }
       else {
            return 3;
        }   
    }
    else if(row==3||row==4||row==5){
        if(col==0||col==1||col==2){
            return 4;
        }
       else if(col==3||col==4||col==5){
            return 5;
        }
       else {
            return 6;
        }   
    }
    else{
        if(col==0||col==1||col==2){
            return 7;
        }
       else if(col==3||col==4||col==5){
            return 8;
        }
       else {
            return 9;
        }   
    }
}
void find_Row_And_col_to_check_win_for_small_block(int block,int &row,int &col) {
    
    if(block==1||block==2||block==3){
        row=0;
    }
    else if(block==4||block==5||block==6){
        row=3;
    }
    else{
        row=6;
    }
    
    if(block==1||block==4||block==7){
        col=0;
    }
    else if(block==2||block==5||block==8){
        col=3;
    }
    else{
        col=6;
    }
   
}
bool bigBlockWinCheck(){
     for(int i = 0; i < 3; i++) {
        if(big_board_representation[i][0] == currentPlayer &&
           big_board_representation[i][1] == currentPlayer &&
           big_board_representation[i][2] == currentPlayer)
            return true;

        if(big_board_representation[0][i] == currentPlayer &&
           big_board_representation[1][i] == currentPlayer &&
           big_board_representation[2][i] == currentPlayer)
            return true;
    }

    if(big_board_representation[0][0] == currentPlayer &&
       big_board_representation[1][1] == currentPlayer &&
       big_board_representation[2][2] == currentPlayer)
        return true;

    if(big_board_representation[0][2] == currentPlayer &&
       big_board_representation[1][1] == currentPlayer &&
       big_board_representation[2][0] == currentPlayer)
        return true;

    return false;
}
void switchPlayers(){
    currentPlayer=(currentPlayer=="X")?"O":"X";
}
void set_the_small_block_as_current_player_for_small_win(int row,int col,int currentBlock){
    for(int i=row;i<row+3;i++){
        for(int j=col;j<col+3;j++){
            board[i][j]=currentPlayer;
        }
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(big_board_representation[i][j]==to_string(currentBlock)){
                big_board_representation[i][j]=currentPlayer;
                smallblackwin=true;
            }
        }
    }
}
void coutthebigboard(){
      for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<big_board_representation[i][j];
        }
        cout<<endl;
    }
}
void check_Small_Block_win(int row,int col,int currentblock){
    int rowValcheck=row;
    int colValcheck=col;
    bool iswin=false;
    for(int i = row; i < rowValcheck+3; i++) {
        if(board[i][col] == currentPlayer &&
           board[i][col+1] == currentPlayer &&
           board[i][col+2] == currentPlayer){
               iswin=true;
           }

        }
        for(int i=col;i<colValcheck+3;i++){

            if(board[row][i] == currentPlayer &&
                board[row+1][i] == currentPlayer &&
                board[row+2][i] == currentPlayer)
                {
                    iswin=true;
                }
            }

    if(board[row][col] == currentPlayer &&
       board[row+1][col+1] == currentPlayer &&
       board[row+2][col+2] == currentPlayer)
       {
           iswin=true;
       }

    if(board[row][col+2] == currentPlayer &&
       board[row+1][col+1] == currentPlayer &&
       board[row+2][col] == currentPlayer){
           iswin=true;
        }

       if(iswin==true){
        set_the_small_block_as_current_player_for_small_win(row,col,currentblock);
       }
}

void push(Stack &s, Move m) {
    Node* n = new Node;
    n->data = m;
    n->next = s.top;
    s.top = n;
}

bool pop(Stack &s, Move &m) {
    if(s.top == NULL) return false;

    Node* temp = s.top;
    m = temp->data;
    s.top = temp->next;
    delete temp;
    return true;
}

void clearStack(Stack &s) {
    Move dummy;
    while(pop(s, dummy));
}


int placemakerFun(int choice){
    int row =(choice-1)/9;
    int col =(choice-1)%9;
    if(board[row][col]!="X"&&board[row][col]!="O"){
        int currentBlock=checkCurrentBlock(row,col);
        if(currentBlock==block_to_do_turn_in||block_to_do_turn_in==11||arbitrarymove){
            if (arbitrarymove) 
            arbitrarymove = false;
            block_to_do_turn_in=tell_next_block(row,col);
            if(board[row][col]!="X"&&board[row][col]!="O"){

Move m;
m.row = row;
m.col = col;
m.oldValue = board[row][col];
m.player = currentPlayer;
m.oldBlockToDo = block_to_do_turn_in;

push(undoStack, m);
clearStack(redoStack); 

board[row][col] = currentPlayer;

                int Row,Col;
                find_Row_And_col_to_check_win_for_small_block(currentBlock,Row,Col);
                check_Small_Block_win(Row,Col,currentBlock);
                checkarbitraryMovevalidation(block_to_do_turn_in);
                return 0;
            }
            return 1;
        }
        else{
            return 2;
        }
    }else{
        return 2;
    }
    }
void checkarbitraryMovevalidation(int block){
     int row = (block - 1) / 3;
     int col = (block - 1) % 3;

            if(big_board_representation[row][col]!=to_string(block)){
                arbitrarymove=true;
                cout<<"arbitrary move on "<<endl;
            }
           
             }

bool isDraw() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(big_board_representation[i][j] != "X" && big_board_representation[i][j] !="O")
                return false;
    return true;
}


void undoMove() {
    Move m;
    if(!pop(undoStack, m)) return;

    board[m.row][m.col] = m.oldValue;
    currentPlayer = m.player;
    block_to_do_turn_in = m.oldBlockToDo;

    push(redoStack, m);
}

void redoMove() {
    Move m;
    if(!pop(redoStack, m)) return;

    board[m.row][m.col] = m.player;
    currentPlayer = (m.player == "X") ? "O" : "X";
    block_to_do_turn_in = tell_next_block(m.row, m.col);

    push(undoStack, m);
}


