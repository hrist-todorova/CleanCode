#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int dimension = 3;
int lowerBound = 20000;
int upperBound = -20000;
char human;
char computer;
enum PlayerTurn
{
    AI, USER
};
char board[dimension][dimension];

void generateEmptyBoard()
{
    for (int i = 0;i < dimension;i++)
    {
        for(int j = 0;j < dimension;j++)
        {
            board[i][j]=' ';
        }
    }
}



void printTable()
{
    for (int i = 0; i < dimension;i++)
    {

        for(int j = 0; j < dimension;j++)
        {
            cout << '|' << board[i][j];
        }
        cout << '|' << endl;
    }
}

bool isCurrentWinner(char ch)
{
    for(int i = 0; i < dim; i++) {
        int counter = dimension;
        while(--counter > 0 && board[i][counter] == board[i][0]);
        if(board[i][0] == ch && counter == 0) return true;
        counter = dimension;


        while(--counter > 0 && board[counter][i] == board[0][i]);
        if(board[0][i] == ch && counter == 0) return true;
    }
    counter = 0;


    while(board[counter][counter] == board[dimension - 1][dimension - 1])
    {
        counter++;
    }
    if (board[0][0] == ch && counter == dimension) {
        return true;
    }

    counter = 0;
    int secondaryCounter = 0;
    while(board[secondaryCounter][dimension - secondaryCounter - 1] == board[0][dimension - 1])
    {
        counter++;
        secondaryCounter++;
    }
    if (board[0][dimension - 1] == ch && counter == dimension)
    {
        return true;
    }

    return false;

}

bool isBoardFull()
{
    bool isFull = true;
    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0;j < dimension; j++)
        {
            if(board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return isFull;
}

int currentScore()
{
    if(isCurrentWinner(computer))
        return 1;
    if(isCurrentWinner(human))
        return -1;
    return 0;
}

vector<pair<int,int> > getAllEmptyMoves()
{
    vector<pair<int,int>> emptyMoves;
    if(isBoardFull())
    {
        return emptyMoves;
    }
    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            if(board[i][j] == ' ')
            {
                pair<int,int> cell(i,j);
                emptyMoves.push_back(cell);
            }
        }
    }
}

vector<int> minmaxAlgorithm(PlayerTurn currentPlayer, int alpha, int beta)
{
    vector<pair<int,int> > allPosibleMoves;
    allPosibleMoves = getAllEmptyMoves();
    int currentScore;
    int first=-1;
    int second=-1;

    if(notempty() || win(human) || win(computer))
    {
        currentScore = currentScore();
        vector<int> temp;
        temp.push_back(currentScore);
        temp.push_back(first);
        temp.push_back(second);
        return temp;
    }
    else {
         for(int i = 0;i < allPosibleMoves.size();i++)
         {
             if(currentPlayer == PlayerTurn.AI)
            {
                 board[allPosibleMoves[i].first][allPosibleMoves[i].second] = computer;
                 currentScore = minmaxAlgorithm(PlayerTurn.USER, alpha, beta)[0];
                if(currentScore > alpha)
                {
                    alpha = currentScore;
                    first = allPosibleMoves[i].first;
                    second = allPosibleMoves[i].second;
                }
            }
             else
             {
                 board[allPosibleMoves[i].first][allPosibleMoves[i].second] = human;
                 currentScore = minmax(true,alpha,beta)[0];
                 if(currentScore < beta)
                {
                    beta = currentScore;
                    first = allPosibleMoves[i].first;
                    second = allPosibleMoves[i].second;
                }
            }

            board[allPosibleMoves[i].first][allPosibleMoves[i].second] = ' ';
            if (alpha >= beta) break;
        }
        if(who==true)
        {
            vector<int> temp;
            temp.push_back(alpha);
            temp.push_back(first);
            temp.push_back(second);
            return temp;


        }
        else{
            vector<int> temp;
            temp.push_back(beta);
            temp.push_back(first);
            temp.push_back(second);
            return temp;



        }
    }

}
 int main()
{
    gen();
    cout<<"choce x for second and o for first";
    char a;
    cin>>a;
    human=a;
    if(a=='o')
    {
        computer='x';

    }
    else{
        computer='o';
    }
    int i,j;
    print();
    cout<<"turns start from 0 and end on dimention-1"<<endl;
    while(!notempty() && !win(computer) && !win(human) )
    {
         if(human=='o')
        {
            cin>>i>>j;
            board[i][j]='o';
            print();
            vector<int>temp=minmax(true,ninf,inf);
             board[temp[1]][temp[2]]=computer;
            print();
        }
         else{
            vector<int>temp=minmax(true,ninf,inf);
             board[temp[1]][temp[2]]=computer;
            print();
            if(win(human)||win(computer)||notempty())
            {
                break;
            }
            cin>>i>>j;
            board[i][j]='x';
            print();

        }
    }

    return 0;
}
