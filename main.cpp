#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int dimension = 3;
int upperBound = 20000;
int lowerBound = -20000;
char human;
char computer;
enum PlayerTurn
{
    AI, USER
};
char board[dimension][dimension];

void generateEmptyBoard()
{
    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printTable()
{
    for (int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            cout << '|' << board[i][j];
        }
        cout << '|' << endl;
    }
}

bool isCurrentWinner(char ch)
{
    for(int i = 0; i < dimension; i++)
    {
        int counter = dimension;
        while(--counter > 0 && board[i][counter]==board[i][0]);
        if(board[i][0] == ch && counter == 0) return true;
        counter = dimension;

        while(--counter>0 && board[counter][i]==board[0][i]);
        if(board[0][i] == ch && counter==0) return true;
    }
    int secondCounter = 0;

    while(board[secondCounter][secondCounter]==board[dimension-1][dimension-1])
    {
        secondCounter++;
    }
    if (board[0][0] == ch && secondCounter == dimension) {
        return true;
    }


    secondCounter = 0;
    int help = 0;
    while(board[help][dimension-help-1]==board[0][dimension-1])
    {
        secondCounter++;
        help++;
    }
    if (board[0][dimension-1] == ch && secondCounter == dimension)
    {
        return true;
    }

    return false;
}

bool notempty()
{
    bool flag = true;
    for (int i=0;i < dimension;i++)
    {
        for(int j=0;j < dimension;j++)
        {
            if(board[i][j]==' ')
            {
                return false;
            }
        }
    }
    return flag;
}

int currentScore()
{
    if(isCurrentWinner(computer))
        return 1;
    if(isCurrentWinner(human))
        return -1;
    return 0;
}

 vector<pair<int,int> > allmoves()
{
    vector<pair<int,int> >temp;
    if(notempty())
    {
        return temp;
    }
    for (int i=0;i < dimension;i++)
    {
        for(int j=0;j < dimension;j++)
        {
            if(board[i][j]==' ')
            {pair<int,int> tmp(i,j);
                temp.push_back(tmp);
            }
        }
    }
}

vector<int> minmax(PlayerTurn currentPlayer, int alpha, int beta)
{
    vector<pair<int,int> > allposiblemoves;
    allposiblemoves = allmoves();
    int score;
    int first = -1;
    int second = -1;
    if(notempty() || isCurrentWinner(human) || isCurrentWinner(computer))
    {
        score = currentScore();
        vector<int> result;
        result.push_back(score);
        result.push_back(first);
        result.push_back(second);
        return result;
    }
    else{
         for(int i=0;i<allposiblemoves.size();i++)
         {
             if(currentPlayer == AI)
            {
                 board[allposiblemoves[i].first][allposiblemoves[i].second]=computer;
                 score=minmax(USER,alpha,beta)[0];
                if(score>alpha)
                {
                    alpha = score;
                    first = allposiblemoves[i].first;
                    second = allposiblemoves[i].second;
                }
            }
             else{
                 board[allposiblemoves[i].first][allposiblemoves[i].second] = human;
                 score = minmax(AI,alpha,beta)[0];
                 if(score<beta)
                {
                    beta = score;
                    first = allposiblemoves[i].first;
                    second = allposiblemoves[i].second;
                }
            }
             board[allposiblemoves[i].first][allposiblemoves[i].second]=' ';
             if (alpha >= beta) break;
        }
        if(currentPlayer == AI)
        {
            vector<int> result;
            result.push_back(alpha);
            result.push_back(first);
            result.push_back(second);
            return result;


        }
        else{
            vector<int> result;
            result.push_back(beta);
            result.push_back(first);
            result.push_back(second);
            return result;



        }
    }

}
 int main()
{
    generateEmptyBoard();
    cout<<"choce x for second and o for first";
    char a;
    cin>>a;
    human=a;
    if(a == 'o')
    {
        computer = 'x';
    }
    else{
        computer = 'o';
    }
    int i,j;
    printTable();
    cout<<"turns start from 0 and end on dimention-1"<<endl;
    while(!notempty() && !isCurrentWinner(computer) && !isCurrentWinner(human) )
    {
         if(human == 'o')
        {
            cin>>i>>j;
            board[i][j] = 'o';
            printTable();
            vector<int>temp = minmax(AI,lowerBound,upperBound);
            board[temp[1]][temp[2]] = computer;
            printTable();
        }
         else{
            vector<int>temp = minmax(USER,lowerBound,upperBound);
             board[temp[1]][temp[2]] = computer;
             printTable();
            if(isCurrentWinner(human)|| isCurrentWinner(computer)||notempty())
            {
                break;
            }
            cin>>i>>j;
            board[i][j]='x';
             printTable();
        }
    }

    return 0;
}
