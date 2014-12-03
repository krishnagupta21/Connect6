//Student Name: Krishna Gupta
// Student Id: 1000606980
// Code for Connect 6(Lab 7Part1)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


// Function Prototypes
void printBoard(char **board,int n);
int findLongest(char **board, int n,int row,int col);
char didAnyoneWin(char **board,int n,int row,int col);
void whoWon(char **board,int n);
void GetBestMove(char **board,int n,char color, int *rowu, int *colu);
bool isPossibleH(char **board, int n, int row, int col,char color);
bool isPossibleV(char **board, int n, int row, int col,char color);
bool isPossibleRD(char **board, int n, int row, int col,char color);
bool isPossibleLD(char **board, int n, int row, int col,char color);
bool isPossibleD(char **board, int n, int row, int col,char color);
bool ispossibleanywhere(char **board,int n,char color,int i,int j);
bool ispossibleanywhere2(char **board,int n,char color);

//Global variables
bool rdu,rdd,ldd,ldu,hor,ver,diag;
int countr,countd,countc,countrd,countld;
int main(void)
{
// Variable declarations
int n,i,j,row=0,col=0,playerno,num,rowH,colH,firstwhitemove=0;
char **board;
char bw;
char color;
bool black=false,white=false,nowinner=false;
int x,y;

// Setting the board

printf("Enter board dimensions (n): ");
scanf("%d",&n);

board=(char **)malloc(n*sizeof(char*));

for(i=0;i<n;i++)
board[i]=(char*)malloc(n*sizeof(char));
for(i=0;i<n;i++)
       for(j=0;j<n;j++)
   board[i][j]='U';

//Printing the board
printBoard(board,n);

// Giving computer a colour to play

printf("Computer playing B or W?: ");
scanf(" %c",&bw);
if(bw=='B')
 color='B';    
else if(bw=='W')
   color='W';

//If computer is black
if(color=='B')
    {

    //num=GetBestMove(board,n,color,&row,&col);
        printf("Computer lays a stone at ROW %d COL %d.\n",n/2,n/2);
    row=n/2; col=n/2;
        board[n/2][n/2]='B';
        printBoard(board,n);

    }

 do {    




      if(didAnyoneWin(board,n,row,col)=='N')
      {   // Checking human's stone on an unoccupied position.
        do {
            printf("Lay down a stone (ROW COL): ");
                   scanf("%d%d",&rowH,&colH);
       
                   if(board[rowH][colH]!='U')
                   printf("That square is occupied.\n");

             }while(board[rowH][colH]!='U');

        // Giving color to human stone and playing it.
        if(board[rowH][colH]=='U')
        {    
            if(color=='B')
            board[rowH][colH]='W';
            else board[rowH][colH]='B';
        }

        printBoard(board,n);



// Breaking outside the do..while as soon as someone wins.
        if(didAnyoneWin(board,n,rowH,colH)!='N')
        {break;
//printf("%c\n", didAnyoneWin(board,n,rowH,colH));
}
else {
//first white move for computer
    if(firstwhitemove==0 && color=='W')
    {    if(colH<n-1)
        {printf("Computer lays a stone at ROW %d COL %d.\n",rowH,colH+1);
        row=rowH;col=colH+1;}
        else if(colH>0)
        {printf("Computer lays a stone at ROW %d COL %d.\n",rowH,colH-1);
        row=rowH;col=colH-1;}
        firstwhitemove++;
    }
    else
    {
// Getting best move for computer.
               GetBestMove(board,n,color,&row,&col);
            printf("Computer lays a stone at ROW %d COL %d.\n",row,col);
    }
// Giving color to computer stone and playing it.
        if(color=='B')
            board[row][col]='B';
        else
             board[row][col]='W';
 
            printBoard(board,n);
    }
}
	if(didAnyoneWin(board,n,row,col)!='N')
	break;
        
    }while(didAnyoneWin(board,n,row,col)=='N' );

// If someone won, then tell who won the game.

    if(didAnyoneWin(board,n,row,col)=='B' || didAnyoneWin(board,n,rowH,colH)=='B')  
printf("Black player wins.\n");
else if(didAnyoneWin(board,n,row,col)=='W' || didAnyoneWin(board,n,rowH,colH)=='W')
printf("White player wins.\n");
else if(didAnyoneWin(board,n,row,col)=='D' || didAnyoneWin(board,n,rowH,colH)=='D')
printf("Draw!\n");



return 0;

for(i=0;i<n;i++)
    free(board[i]);
free(board);
}


void GetBestMove(char **board,int n,char color,int *rowu,int *colu)
{


int i,j,k,l,scoreC,scoreH,mybiggest=0,hisbiggest=0,num,x,y;
char hiscolor;
bool isposs,updated=false;
if(color=='B')
hiscolor='W';
else if(color=='W')
 hiscolor='B';


    for(i=0;i<n;i++)
        for(j=0;j<n;j++)    
        {
            if(board[i][j]==color)
            {
            
 
            scoreC=findLongest(board,n,i,j); 
    if(scoreC>=mybiggest)
    {   
//1 HVD
	if((isPossibleH(board,n,i,j,color)==true) && (isPossibleV(board,n,i,j,color)==true) && (isPossibleD(board,n,i,j,color)==true))
	{ 
		if(countr>=countc && countr>=countd)
		{
			 mybiggest=scoreC;
            	if(j<n-1 && board[i][j+1]=='U')
               		 {*rowu=i; *colu=j+1; updated=true;}
            	else if(j>0 && board[i][j-1]=='U')
          		  {*rowu=i; *colu=j-1; updated=true;}
		}
		else if(countc>=countr && countc>=countd)
		{	   mybiggest=scoreC;
          		  if(i<n-1 && board[i+1][j]=='U')
           			 {*rowu=i+1; *colu=j; updated=true;}
           		 else if(i>0 && board[i-1][j]=='U')
           			 {*rowu=i-1; *colu=j; updated=true;}
            
			
		}
		else
		{	if(isPossibleLD(board,n,i,j,color)==true)
			{
			 mybiggest=scoreC;
          	  if(i<n-1 && j<n-1 && ldd==true && board[i+1][j+1]=='U')
           		 {
           		 *rowu=i+1; 
             		   *colu=j+1;
				updated=true;
          	 	 }
           	 else if(i>0 && j>0 && ldu==true && board[i-1][j-1]=='U')
         		   {
         		   *rowu=i-1; 
        	           *colu=j-1;
				updated=true;
           	           }
			}
			else
			{
				mybiggest=scoreC;
          	   if(i<n-1 && j>0 &&rdd==true && board[i+1][j-1]=='U')
          		  {
          		  *rowu=i+1; 
           	 	    *colu=j-1;
				updated=true;
         	 	  }
        	    else if(i>0 && j<n-1 && rdu==true && board[i-1][j+1]=='U')
       		     {
        		    *rowu=i-1; 
             		   *colu=j+1;
				updated=true;
           	     }
			}
			
		}
	}
//2HV
	else if((isPossibleH(board,n,i,j,color)==true) && (isPossibleV(board,n,i,j,color)==true) && (isPossibleD(board,n,i,j,color)==false))
	{

		if(countr>=countc)
		{
			 mybiggest=scoreC;
            		if(j<n-1 && board[i][j+1]=='U')
               			 {*rowu=i; *colu=j+1; updated=true;}
            		else if(j>0 && board[i][j-1]=='U')
          		  {*rowu=i; *colu=j-1; updated=true;}
		}
		else 
		{
			  mybiggest=scoreC;
          		  if(i<n-1 && board[i+1][j]=='U')
           			 {*rowu=i+1; *colu=j; updated=true;}
           		 else if(i>0 && board[i-1][j]=='U')
           			 {*rowu=i-1; *colu=j; updated=true;}
            
		}		
	}
//3VD
	else if((isPossibleH(board,n,i,j,color)==false) && (isPossibleV(board,n,i,j,color)==true) && (isPossibleD(board,n,i,j,color)==true))
	{
		//printf("scoreC: %d,countc: %d,countd: %d\n",scoreC,countc,countd);
		if(countc>=countd)
		{
			
			  mybiggest=scoreC;
          		  if(i<n-1 && board[i+1][j]=='U')
           			 {*rowu=i+1; *colu=j; updated=true;}
           		 else if(i>0 && board[i-1][j]=='U')
           			 {*rowu=i-1; *colu=j; updated=true;}
            
		}
		else 
		{
		if(isPossibleLD(board,n,i,j,color)==true)
			{
		 mybiggest=scoreC;
            if(i<n-1 && j<n-1 && ldd==true && board[i+1][j+1]=='U')
            {
            *rowu=i+1; 
                *colu=j+1;
		updated=true;
            }
            else if(i>0 && j>0 && ldu==true && board[i-1][j-1]=='U')
            {
            *rowu=i-1; 
                *colu=j-1;
		updated=true;
            }
			}
		else {
			mybiggest=scoreC;
             if(i<n-1 && j>0 &&rdd==true && board[i+1][j-1]=='U')
            {
            *rowu=i+1; 
                *colu=j-1;
		updated=true;
            }
            else if(i>0 && j<n-1 && rdu==true && board[i-1][j+1]=='U')
            {
            *rowu=i-1; 
                *colu=j+1;
		updated=true;
            }
		}
            
		}		
	}
	
//4HD
	
	else if((isPossibleH(board,n,i,j,color)==true) && (isPossibleV(board,n,i,j,color)==false) && (isPossibleD(board,n,i,j,color)==true))
	{

		if(countr>=countd)
		{
			 mybiggest=scoreC;
        	    if(j<n-1 && board[i][j+1]=='U')
          	      {*rowu=i; *colu=j+1; updated=true;}
        	    else if(j>0 && board[i][j-1]=='U')
        	    {*rowu=i; *colu=j-1; updated=true;}
		}

		else 
		{ if(isPossibleLD(board,n,i,j,color)==true)
			{ 
		mybiggest=scoreC;
            if(i<n-1 && j<n-1 && ldd==true && board[i+1][j+1]=='U')
            {
            *rowu=i+1; 
                *colu=j+1;
		updated=true;
            }
            else if(i>0 && j>0 && ldu==true && board[i-1][j-1]=='U')
            {
            *rowu=i-1; 
                *colu=j-1;
		updated=true;
            }
		}
		else {
			mybiggest=scoreC;
             if(i<n-1 && j>0 &&rdd==true && board[i+1][j-1]=='U')
            {
            *rowu=i+1; 
                *colu=j-1;
		updated=true;
            }
            else if(i>0 && j<n-1 && rdu==true && board[i-1][j+1]=='U')
            {
            *rowu=i-1; 
                *colu=j+1;
		updated=true;
            }
		}
            
		}		
	}
//5H
	else if((isPossibleH(board,n,i,j,color)==true) && (isPossibleV(board,n,i,j,color)==false) && (isPossibleD(board,n,i,j,color)==false))
	{
		mybiggest=scoreC;
        	    if(j<n-1 && board[i][j+1]=='U')
          	      {*rowu=i; *colu=j+1; updated=true;}
        	    else if(j>0 && board[i][j-1]=='U')
        	    {*rowu=i; *colu=j-1; updated=true;}
		

				
	}
//6V
	else if((isPossibleH(board,n,i,j,color)==false) && (isPossibleV(board,n,i,j,color)==true) && (isPossibleD(board,n,i,j,color)==false))
	{

		 mybiggest=scoreC;
            if(i<n-1 && board[i+1][j]=='U')
            {*rowu=i+1; *colu=j; updated=true;}
            else if(i>0 && board[i-1][j]=='U')
            {*rowu=i-1; *colu=j; updated=true;}
		

				
	}
//7D
	else if((isPossibleH(board,n,i,j,color)==false) && (isPossibleV(board,n,i,j,color)==false) && (isPossibleD(board,n,i,j,color)==true))
	{
	if(isPossibleLD(board,n,i,j,color)==true)
			{
		mybiggest=scoreC;
            if(i<n-1 && j<n-1 && ldd==true && board[i+1][j+1]=='U')
            {
            *rowu=i+1; 
                *colu=j+1;
		updated=true;
            }
            else if(i>0 && j>0 && ldu==true && board[i-1][j-1]=='U')
            {
            *rowu=i-1; 
                *colu=j-1;
		updated=true;
            }
		}
		else {
		mybiggest=scoreC;
             if(i<n-1 && j>0 &&rdd==true && board[i+1][j-1]=='U')
            {
            *rowu=i+1; 
                *colu=j-1;
		updated=true;
            }
            else if(i>0 && j<n-1 && rdu==true && board[i-1][j+1]=='U')
            {
            *rowu=i-1; 
                *colu=j+1;
		updated=true;
            }
		}

				
	}

       

//these 3 brackets should be here! dont touch them.
    		}

    
           }
    }
int counter=0;
if(updated==false)
{
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)    
        {
       if(isPossibleH(board,n,i,j,color)==false && isPossibleV(board,n,i,j,color)==false && isPossibleD(board,n,i,j,color)==false)
	{	   for(i=0;i<n;i++)
       			 for(j=0;j<n;j++)
		{	//counter++;
			if(board[i][j]=='U')
			{ 
				*rowu=i;
				*colu=j;
				

							 
			}
		}
		
		
			if(ispossibleanywhere2(board,n,color)==false)
			{	for(i=0;i<n;i++)
       					 for(j=0;j<n;j++)
				{
				if(board[i][j]=='U')
				{	*rowu=i;
					*colu=j; }
			}
		}
		
	 }
	}
}


//  k=*rowu;
 // l=*colu; 

//board[k][l]=color;

    for(i=0;i<n;i++)
       for(j=0;j<n;j++)    
         {
            if(board[i][j]=='U')
            { 
                board[i][j]=hiscolor;
                scoreH=findLongest(board,n,i,j);
                if(scoreH>hisbiggest)
                {
            hisbiggest=scoreH;
            if(hisbiggest>=mybiggest ) //&& (isPossibleH(board,n,i,j,hiscolor)==true || isPossibleV(board,n,i,j,hiscolor)==true || isPossibleD(board,n,i,j,hiscolor)==true)
            {	printf("hey\n");
                    *rowu=i; 
                        *colu=j;    
		
            }
          
            
       		 }
        
    

                board[i][j]='U';
            }
        }
//board[k][l]='U';

   // printf("Final Row: %d,Final Col: %d\n",*rowu,*colu); 

 

}
bool ispossibleanywhere2(char **board,int n,char color)
{ int i,j;
  bool anywhere=false;
  for(i=0;i<n;i++)
       	 for(j=0;j<n;j++)
		{
        if(isPossibleH(board,n,i,j,color)==true || isPossibleV(board,n,i,j,color)==true || isPossibleD(board,n,i,j,color)==true)
        {
            anywhere=true;
		break;
          
        }
	}
return anywhere;
}
bool ispossibleanywhere(char **board,int n,char color,int i,int j)
{ 
  bool anywhere=false;
 
        if(isPossibleH(board,n,i,j,color)==true || isPossibleV(board,n,i,j,color)==true || isPossibleD(board,n,i,j,color)==true)
        {
            anywhere=true;
          
        }
	else return anywhere;
}
bool isPossibleH(char **board, int n, int row, int col,char color)
{
    int counth=1,colh;
//horizontal    
colh=col;
    do
    {
    if(colh<n)
    {
        if(board[row][colh+1]=='U' || board[row][colh+1]==color)    
        {
            while(colh<n && (board[row][colh+1]=='U' || board[row][colh+1]==color) )
            {counth++;
            colh++;
            }
        colh=col;

        }
    }


    if(colh>0)
    {    if(board[row][colh-1]=='U'|| board[row][colh-1]==color)
        {
            while(colh>0 && (board[row][colh-1]=='U'|| board[row][colh-1]==color))
            {counth++;
            colh--;
            }
        colh=col;    
        }
    }
        
    }while((colh>0 && colh<n) && colh!=col);
//printf("CountH: %d\n",counth);
if(counth>=6)
return true;
else return false;

}

bool isPossibleV(char **board, int n, int row, int col,char color)    
{
int rowv,countv=1;
//vertical
rowv=row;
    do
    {
    if(rowv<n-1)
    {
        if(board[rowv+1][col]=='U' || board[rowv+1][col]==color)    
        {
            while(rowv<n-1 && (board[rowv+1][col]=='U' || board[rowv+1][col]==color) )
            {countv++;
            rowv++;
            }
        rowv=row;

        }
    }
    

    if(rowv>0)
    {    if(board[rowv-1][col]=='U'|| board[rowv-1][col]==color)
        {
            while(rowv>0 && (board[rowv-1][col]=='U'|| board[rowv-1][col]==color))
            {countv++;
            rowv--;
            }
        rowv=row;    
        }
    }
        
    }while((rowv>0 && rowv<n) && rowv!=row);
if(countv>=6)
return true;
else return false;

}

bool isPossibleD(char **board, int n, int row, int col,char color)    
{
int rowd,cold,countd=1;
//diagonal
rowd=row;cold=col;
int countrd=1,countld=1;
rdu=false;
rdd=false;
ldd=false;
ldu=false;
        do
        {
        
            if(rowd<n-1 && cold<n-1)
            {            while((rowd<n-1 && cold<n-1) && (board[rowd+1][cold+1]=='U' || board[rowd+1][cold+1]==color))
                        {rowd++; cold++; countld++;}
                        rowd=row;
                        cold=col;
        if(board[rowd+1][cold+1]=='U')
        ldd=true;
            }
            if(rowd>0 && cold>0)
            {            while((rowd>0 && cold>0) && (board[rowd-1][cold-1]=='U' || board[rowd-1][cold-1]==color))
                        {rowd--; cold--; countld++;}
                        rowd=row;
                        cold=col;
        if(board[rowd-1][cold-1]=='U')
        ldu=true;
            }
        
    
         
            if(rowd>0 && cold<n-1)
            {            while((rowd>0 && cold<n-1) && (board[rowd-1][cold+1]=='U' || board[rowd-1][cold+1]==color))
                        {rowd--; cold++; countrd++;}
                        rowd=row;
                        cold=col;
        if(board[rowd-1][cold+1]=='U')
        rdu=true;
            }
            if(rowd<n-1 && cold>0)
            {            while((rowd<n-1 && cold>0) && (board[rowd+1][cold-1]=='U' || board[rowd+1][cold-1]==color))
                        {rowd++; cold--; countrd++;}
                        rowd=row;
                        cold=col;
        if(board[rowd+1][cold-1]=='U')
        rdd=true;
            }
        

if(countrd>=countld) countd=countrd; else countd=countld;


        }while((cold>=0 && cold<n) && (rowd>=0 && rowd<n) && (rowd!=row && cold!=col));

if(countd>=6)
return true;
else return false;
}


bool isPossibleLD(char **board, int n, int row, int col,char color)
{
	int rowd,cold;
//diagonal left
rowd=row;cold=col;
int countld=1;
ldd=false;
ldu=false;
        do
        {
        
            if(rowd<n-1 && cold<n-1)
            {            while((rowd<n-1 && cold<n-1) && (board[rowd+1][cold+1]=='U' || board[rowd+1][cold+1]==color))
                        {rowd++; cold++; countld++;}
                        rowd=row;
                        cold=col;
        if(board[rowd+1][cold+1]=='U')
        ldd=true;
            }
            if(rowd>0 && cold>0)
            {            while((rowd>0 && cold>0) && (board[rowd-1][cold-1]=='U' || board[rowd-1][cold-1]==color))
                        {rowd--; cold--; countld++;}
                        rowd=row;
                        cold=col;
        if(board[rowd-1][cold-1]=='U')
        ldu=true;
            }
	   }while((cold>=0 && cold<n) && (rowd>=0 && rowd<n) && (rowd!=row && cold!=col));
if(countld>=6)
return true;
else return false;
        
}
bool isPossibleRD(char **board, int n, int row, int col,char color)
{
	int rowd,cold;
//diagonal right
rowd=row;cold=col;
int countrd=1;
rdd=false;
rdu=false;
        do
        {
        
    
            if(rowd>0 && cold<n-1)
            {            while((rowd>0 && cold<n-1) && (board[rowd-1][cold+1]=='U' || board[rowd-1][cold+1]==color))
                        {rowd--; cold++; countrd++;}
                        rowd=row;
                        cold=col;
        if(board[rowd-1][cold+1]=='U')
        rdu=true;
            }
            if(rowd<n-1 && cold>0)
            {            while((rowd<n-1 && cold>0) && (board[rowd+1][cold-1]=='U' || board[rowd+1][cold-1]==color))
                        {rowd++; cold--; countrd++;}
                        rowd=row;
                        cold=col;
        if(board[rowd+1][cold-1]=='U')
        rdd=true;
            }
        
	   }while((cold>=0 && cold<n) && (rowd>=0 && rowd<n) && (rowd!=row && cold!=col));
if(countrd>=6)
return true;
else return false;
        
}
char didAnyoneWin(char **board,int n,int row,int col)
{
int num,i,j,countu=0;
char whoWon;
bool gamewon=false;
for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    {      
    if(board[i][j]=='U')
                countu++;
    }
num=findLongest(board,n,row,col);
    
    if(countu==0) whoWon='D';
  
    else if(num<6) whoWon='N';

    else if(num>=6)
    {
         
             //gamewon=true;  
             if(board[row][col]=='B')
                        whoWon='B';
                    
            else if(board[row][col]=='W')
                        whoWon='W';                  
            
            
    }
    
return whoWon;    
}

void printBoard(char **board,int n)
{
int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)    
        printf("%c",board[i][j]);
        printf("\n");
    }
}

int findLongest(char **board, int n, int row, int col)
{ int rowh,rowv,rowd,colh,colv,cold;
rowh=rowv=rowd=row; 
colh=cold=colv=col;
hor=true,ver=false,diag=false;
int max;
countr=1,countd=1,countc=1;
    if(board[row][col]!='U')
    {
        //horizontal

        do
        {
        if(((colh>=0 && colh<n-1) && board[rowh][colh]==board[rowh][colh+1]) || ((colh>0 && colh<=n) && board[rowh][colh]==board[rowh][colh-1]))
            { 
                if(board[rowh][colh]==board[rowh][colh+1])
                {
                    while(board[rowh][colh]==board[rowh][colh+1])
                    {
                        colh++; countr++;
                        
                    }
                }
                     
                colh = col;
                    if(board[rowh][colh]==board[rowh][colh-1])
                    {
                        while((colh>0) && board[rowh][colh]==board[rowh][colh-1])
                        {
                            colh--;countr++;
                        }
                    }
                colh = col;
                    
                
                
            } 
            else break;
        }
        while(colh>=0 && colh<n && colh!=col);
    
         
        //vertical

        do
        {
        if((rowv>=0 && rowv<n-1) && (board[rowv][colv]==board[rowv+1][colv]))
        
            { 
                            
                while((rowv>=0 && rowv<n-1) && board[rowv][colv]==board[rowv+1][colv])
                {rowv++; countc++;}
                
            rowv=row; 
            }
        
         if(rowv>0)
        {
         while(rowv>0  && (board[rowv][colv]==board[rowv-1][colv]))
            {rowv--;countc++;}
            
            
                rowv=row;
                            
        }    
        else break;
        }
        while(rowv>=0 && rowv<n && rowv!=row);

        
        //diagonal
countrd=1,countld=1;
        do
        {
        
            if(rowd<n-1 && cold<n-1)
            {            while((rowd<n-1 && cold<n-1) && board[rowd][cold]==board[rowd+1][cold+1])
                        {rowd++; cold++; countld++;}
                        rowd=row;
                        cold=col;
            }
            if(rowd>0 && cold>0)
            {            while((rowd>0 && cold>0) && board[rowd][cold]==board[rowd-1][cold-1])
                        {rowd--; cold--; countld++;}
                        rowd=row;
                        cold=col;
            }
        
    
         
            if(rowd>0 && cold<n-1)
            {            while((rowd>0 && cold<n-1) && board[rowd][cold]==board[rowd-1][cold+1])
                        {rowd--; cold++; countrd++;}
                        rowd=row;
                        cold=col;
            }
            if(rowd<n-1 && cold>0)
            {            while((rowd<n-1 && cold>0) && board[rowd][cold]==board[rowd+1][cold-1])
                        {rowd++; cold--; countrd++;}
                        rowd=row;
                        cold=col;
            }
        

if(countrd>=countld) countd=countrd; else countd=countld;


        }while((cold>=0 && cold<n) && (rowd>=0 && rowd<n) && (rowd!=row && cold!=col));

   /* max=(countr>countc&&countr>countd?countr:countc>countd?countc:countd);  */

if(countr>=countc && countr>=countd)
{    hor=true;
     ver=false;
     diag=false;
	max=countr;}
else if(countc>=countd && countc>=countr)
{ hor=false;
  ver=true;
  diag=false;
max=countc;
}
else if(countd>=countc && countd>=countr)
{ hor=false;
 ver=false;
diag=true;
max=countd;
}

//printf("countr:%d,countc: %d,countd:%d\n",countr,countc,countd);
    
    }
    else max=0;


    
return max;
}
