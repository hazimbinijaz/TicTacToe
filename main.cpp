#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

int TwoDto3D(int ri, int ci, int Dim)
{
   return (ri-1)*Dim+(ci-1);
}

void Initializer(char B[],int Dim)
{
  for(int i=0;i<=Dim*Dim;i++)
  {

    B[i]='-';
  }
}

void PrintBoard(char B[],int Dim)
{
    for(int i=0;i<Dim*Dim;i++)
    {

        cout<<B[i];
        if((i+1)%Dim==0)
        {
            cout<<endl;
        }


    }

}

void AskForPos(int & ri,int & ci,int Turn)
{
    cout<<"Enter Position P"<<Turn+1<<"(ri,ci) ";
    cout<<"OR Enter 0,0 to save the game: ";
    cin>>ri>>ci;
}

void WriteOnBoard(char B[],int Dim,int ri,int ci,char S)
{
    int index=TwoDto3D(ri,ci,Dim);
    B[index]=S;
}

void TurnChanger(int&Turn)
{
    Turn=(Turn+1)%2;
}

bool PosValidation(char B[],int ri, int ci, int Dim)
{
   if(ri<1 || ri>Dim || ci<1 || ci>Dim)
   {
       return false;
   }

        int index=TwoDto3D(ri,ci,Dim);

   if(B[index]!='-')
    {
        return false;
    }

    else
    {
        return true;
    }
}

bool DrawGame(char B[], int Dim)
{
    for(int ri=1;ri<=Dim;ri++)
    {
        for(int ci=1;ci<=Dim;ci++)
        {
           int index=TwoDto3D(ri,ci,Dim);
            if(B[index]=='-')
            {
                return false;
            }

        }
    }
    return true;
}

bool VerticalWin(char B[],int Dim, char S)
{
    int index;
        for(int ci=1;ci<=Dim;ci++)
        {
            for(int ri=1;ri<=Dim;ri++)
            {
             index=TwoDto3D(ri,ci,Dim);
             if(B[index]!=S)
             {
                break;
             }
            if(ri==Dim)
            {
                return true;
            }
            }

        }
    return false;


}

bool HorizontalWin(char B[],int Dim, char S)
{
    int index;
        for(int ri=1;ri<=Dim;ri++)
        {
            for(int ci=1;ci<=Dim;ci++)
            {
             index=TwoDto3D(ri,ci,Dim);
             if(B[index]!=S)
             {
                break;
             }
            if(ci==Dim)
            {
                return true;
            }
            }

        }
    return false;




}

bool Diag1Win(char B[],int Dim, char S)
{
    int index;
    for(int ri=1;ri<=Dim;ri++)
    {
        for(int ci=1;ci<=Dim;ci++)
        {
            index=TwoDto3D(ri,ci,Dim);
            if(B[index]!=S)
            {
                return false;
            }
            else
            {
             ri++;
            if(ri==Dim+1)
            {
                return true;
            }

            }



        }
    }
}

bool Diag2Win(char B[],int Dim, char S)
{
    int index;
    for(int ri=1;ri<=Dim;ri++)
    {
        for(int ci=Dim;ci>=1;ci--)
        {
            index=TwoDto3D(ri,ci,Dim);
            if(B[index]!=S)
            {
                return false;
            }
            else
            {
             ri++;
            if(ri==Dim+1)
            {
                return true;
            }

            }

        }
    }
}


bool Winning(char B[],int Dim, char S, int Turn)
{

    if((VerticalWin(B,Dim,S))==true)
     {
         return true;
     }

     else if((HorizontalWin(B,Dim,S))==true)
     {
         return true;
     }

     else if((Diag1Win(B,Dim,S))==true)
     {
         return true;
     }

     else if((Diag2Win(B,Dim,S))==true)
     {
         return true;
     }
    return false;
}

void Saving(char B[], int Dim, int Turn)
{

    ofstream Writer("SavedGame.txt");
    Writer<<Turn<<" ";
    for(int i=0;i<Dim*Dim;i++)
    {
        Writer<<B[i]<<" ";
    }


}

void Loading(char B[],int & Turn,int Dim)
{
    ifstream Reader("SavedGame.txt");
    Reader>>Turn;
    for(int i=0;i<Dim*Dim;i++)
    {
        Reader>>B[i];
    }
}
int main()
{
    char Psymbol[2]={'O','X'};
    int Dimension;
    char choice;
    cout<<"Enter Dimension: ";
    cin>>Dimension;
    cout<<endl;
    cout<<"Press N/n for new game or L/l to load: ";
    cin>>choice;
    int ri,ci,Turn=0;
    char Board[Dimension*Dimension];
    if(choice=='L' || choice=='l')
    {
        Loading(Board,Turn,Dimension);
    }

    else if(choice=='N' || choice=='n')
    {
        Initializer(Board,Dimension);
    }



     do
     {
        system("cls");
     PrintBoard(Board,Dimension);
     do
     {
        AskForPos(ri,ci,Turn);
        if(ri==0 && ci==0)
        {
            Saving(Board,Dimension,Turn);
            exit(true);
        }
     }
     while(PosValidation(Board,ri,ci,Dimension)==false);

     WriteOnBoard(Board,Dimension,ri,ci,Psymbol[Turn]);
     if(Winning(Board,Dimension,Psymbol[Turn],Turn)==true)
     {
         system("cls");
        PrintBoard(Board,Dimension);

         cout<<"Player "<<Turn+1<<" Wins";
         exit(true);
     }

     TurnChanger(Turn);
    }
    while(DrawGame(Board,Dimension)==false);

    return 0;
}
