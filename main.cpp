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

bool checkIfSomeoneWon(char ch)
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

bool isBoardEmpty()
{
    bool isEmpty = true;
    for (int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            if(board[i][j]==' ')
            {
                return false;
            }
        }
    }
    return isEmpty;
}

int currentScore()
{
    if(win(computer))
        return 1;
    if(win(human))
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
    for (int i=0;i<dim;i++)
    {
        for(int j=0;j<dim;j++)
        {
            if(board[i][j]==' ')
            {pair<int,int> tmp(i,j);
                temp.push_back(tmp);
            }
        }
    }
}

vector<int> minmax(bool who,int alpha,int beta)
{
    vector<pair<int,int> > allposiblemoves;
    allposiblemoves=allmoves();
    int scoree;
    int first=-1;
    int second=-1;
    if(notempty() || win(human) || win(computer))
    {
        scoree=score();
        vector<int> temp;
        temp.push_back(scoree);
        temp.push_back(first);
        temp.push_back(second);
        return temp;    }
    else{
         for(int i=0;i<allposiblemoves.size();i++){
             if(who==true)
            {
                 board[allposiblemoves[i].first][allposiblemoves[i].second]=computer;
                 scoree=minmax(false,alpha,beta)[0];
                if(scoree>alpha)
                {
                    alpha=scoree;
                    first=allposiblemoves[i].first;
                    second=allposiblemoves[i].second;
                }
            }
             else{
                 board[allposiblemoves[i].first][allposiblemoves[i].second]=human;
                 scoree=minmax(true,alpha,beta)[0];
                 if(scoree<beta)
                {
                    beta=scoree;
                    first=allposiblemoves[i].first;
                    second=allposiblemoves[i].second;
                }
            }
             board[allposiblemoves[i].first][allposiblemoves[i].second]=' ';
             if (alpha >= beta) break;}
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
