#include <iostream>

using namespace std;
struct cell
{
    int x,y,val=0;
    int cageindex=0;
};
struct cage
{
     cell * cells ;
     int length=0;
     int sum;
     cage()
     {
        cells = new cell[10];
     }
};
cell** sudoku=0;
cage* cages;
void printsud()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
            cout<<sudoku[i][j].val<<" ";
        cout<<endl;
    }
    cout<<endl;
}
bool checker(int x, int y, int val)
{   
    for(int i=0;i<9;i++)
        if((val==sudoku[i][y].val)&&(x!=i))
            return 0;
    for(int j=0;j<9;j++)
        if(val==sudoku[x][j].val&&y!=j)
            return 0;
    int x1=(x/3)*3;
    int y1=(y/3)*3;
    for(int i=x1;i<x1+3;i++)
        for(int j=y1;j<y1+3;j++)
            if((val==sudoku[i][j].val)&&!((x==i)&&(y==j)))
                return 0;
    return 1;
}
bool checkcage(int x, int y, int val)
{   
    int n=sudoku[x][y].cageindex;
    int sum=0;
    for(int i=0; i<cages[n].length; i++)
    {
        int x1 =cages[n].cells[i].x;
        int y1 =cages[n].cells[i].y;
        if(sudoku[x1][y1].val==val) return 0;
        sum+=sudoku[x1][y1].val;
    }
    if(sum+val<=cages[n].sum) 
        return 1;
    return 0; 
}

bool SolveSudoku(int row, int col)
{
    for (int num = 9; num >= 1; num--)
    {
        if(row==9)
            return true;
        if (checker(row, col, num)&&checkcage(row,col,num))
        {   
            sudoku[row][col].val = num;
            if (SolveSudoku(row + (col+1)/9,((col+1)%9)))
                return true;
            sudoku[row][col].val = 0;
        }
    }
    return false; 
}

int main()
{   
    sudoku = new cell*[9];
    for (int i = 0; i < 9; ++i)
        sudoku[i]= new cell[9];       
    int n;
    cin>>n;
    cages = new cage[n];
    int t,s;
    for (int i = 0; i < n; ++i)
    {
        cin>>t>>s;
        cages[i].sum=s;
        cages[i].length=t;
        for (int j=0;j<t;++j)
        {   
            int x,y;
            cin>>x>>y;
            sudoku[x][y].cageindex=i;
            cages[i].cells[j].x=x;
            cages[i].cells[j].y=y;
            cages[i].cells[j].cageindex=i;
        }
    }
  if(SolveSudoku(0,0))
  {
    cout<<"Done"<<endl;
    printsud();
  }  
  else cout<<"not Done"<<endl;  
    
}
