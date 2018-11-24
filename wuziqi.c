#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 15
#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define FLAG_BLACK 0
#define FLAG_WHITE 1
int chessmap[MAX+1][MAX+1];
bool lockmap[MAX][MAX];// 0:Not Lock, 1:Locked
int Line = 5, Row = 5;
void init(int map[][MAX+1]);
void newprint(int map[][MAX+1]);
void move(int map[][MAX+1],char key);
char search(int map[][MAX+1]);//BLACK win then return FLAG_BLACK, WHITE win then return FLAG_WHITE, none of color win then return -1
bool start = 0;
bool winflag = 0;
bool color = FLAG_BLACK;
bool pushflag = 0;
int SCORE_WHITE = 0;
int SCORE_BLACK = 0;
char author[]= "PPPPPPPPaleZero";
int main()
{
	char key,winlose;
	start = 1;
	winflag = 1;
	init(chessmap);
	newprint(chessmap);
	while(1)
	{
		if(!start || !winflag)
		{
			init(chessmap);
			if(!start)
				printf("Restarted, Push a key and play again\n");
			else
				printf("Having fun!!!\n");
			start = 1;
			winflag = 1;
			getchar();
		}
		key = getchar();
		move(chessmap, key);
		winlose = search(chessmap);
		newprint(chessmap);
		if(winlose == BLACK)
		{
			printf("Black win!!!\n");
			printf("Press any key to play again\n");
			SCORE_BLACK++;
			winflag = 0;
			winlose = EMPTY;
		}
		else if(winlose == WHITE)
		{
			printf("White win!!!\n");
			printf("Press any key to play again\n");
			SCORE_WHITE++;
			winflag = 0;
			winlose = EMPTY;
		}
		if(key == 'q'||key == 'Q')
		{
			printf("Exiting>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			break;
		}
		if(key == 'r'||key == 'R')
			start = 0;
	}
	return 0;
}
char search(int map[][MAX+1])
{
	int count;
	int Row_Low = Row, Row_High = Row;
	int Line_Low = Line, Line_High = Line;
	int Pos_Row_Low = Row, Pos_Row_High = Row, Pos_Line_Low = Line, Pos_Line_High = Line;
	int Neg_Row_Low = Row, Neg_Row_High = Row, Neg_Line_Low = Line, Neg_Line_High = Line;
	char chesscolor;
	if(lockmap[Line-1][Row-1])
	{
	    chesscolor = map[Line][Row];
	    count = 2;
		while((--Row_Low >= 1) && (map[Line][Row_Low] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		while((++Row_High <= MAX) && (map[Line][Row_High] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		count = 2;
		while((--Line_Low >= 1) && (map[Line_Low][Row] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		while((++Line_High <= MAX) && (map[Line_High][Row] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		count = 2;
		while((--Pos_Line_Low >= 1) && (++Pos_Row_High <= MAX) && (map[Pos_Line_Low][Pos_Row_High] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		while((++Pos_Line_High <= MAX) && (--Pos_Row_Low >= 1) && (map[Pos_Line_High][Pos_Row_Low] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		count = 2;
		while((--Neg_Line_Low >= 1) && (--Neg_Row_Low >= 1) && (map[Neg_Line_Low][Neg_Row_Low] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
		while((++Neg_Line_High <= MAX) && (++Neg_Row_High <= MAX) && (map[Neg_Line_High][Neg_Row_High] == chesscolor))
		{
			if(count >= 5)
				return chesscolor;
			count++;
		}
	}
	return 0;
}
void move(int map[][MAX+1], char key)
{
	if(!lockmap[Line-1][Row-1])
		map[Line][Row] = EMPTY;
	switch(key)
	{
		case 'w':Line--;if(Line < 1)Line = MAX; break;
		case 'a':Row--;if(Row < 1)Row = MAX; break;
		case 's':Line++;if(Line > MAX)Line = 1; break;
		case 'd':Row++;if(Row >MAX)Line = 1; break;
		case 'W':Line--;if(Line < 1)Line = MAX; break;
		case 'A':Row--;if(Row < 1)Row = MAX; break;
		case 'S':Line++;if(Line > MAX)Line = 1; break;
		case 'D':Row++;if(Row >MAX)Line = 1; break;
		case 'f':if(!lockmap[Line-1][Row-1])
				{
					lockmap[Line-1][Row-1] = 1;
					map[Line][Row] = color?WHITE:BLACK;
					color = !color;
					pushflag = 1;
				}
		 		break;
 		case 'F':if(!lockmap[Line-1][Row-1])
		{
			lockmap[Line-1][Row-1] = 1;
			map[Line][Row] = color?WHITE:BLACK;
			color = !color;
			pushflag = 1;
		}
 		break;
	}
}
void init(int map[][MAX+1])
{
	int i,j;
	for (i = 1; i < MAX+1; i++)
		for (j = 1; j < MAX+1; j++)
		{
			map[i][j] = EMPTY;
			lockmap[i-1][j-1] = 0;
		}
	map[0][0] = EMPTY;
	for(i = 1; i < MAX+1; i++)
	{
		map[0][i] = i;
		map[i][0] = i;
	}
}
void newprint(int map[][MAX+1])
{
	int i,j;
	system("cls");
	for (i = 0; i < MAX+1; i++)
	{
		for (j = 0; j < MAX+1; j++)
		{
			if(i > 0&&j > 0)
			{
				if(i == Line && j == Row)
					printf("o ");
				else
				{
					switch(map[i][j])
					{
						case EMPTY: printf("+ ");break;
						case BLACK: if(lockmap[i-1][j-1])
						printf("B ");
						break;
						case WHITE: if(lockmap[i-1][j-1])
						printf("W ");
						break;
					}
				}
			}
			else if(i == 0)
			{
				if(j == 0)
					printf("-------------------------------------\n| "); 
				printf("%2d",map[i][j]);
			}
			else if(j == 0)
			{

				printf("|%c%2d ",author[i],map[i][j]);
			}
		}
		printf("\n");
	}
	if(start)
	{
		printf("-------------------------------------\n");
		printf("Now your position is Line: %d,Row: %d\n", Line, Row);
		printf("Press f to set chess, q to exit, r to restart\n");
		printf("WHITE SCORE:%d\n",SCORE_WHITE);
		printf("BLACK SCORE:%d\n",SCORE_BLACK);
		printf("Game: five-in-a-row(ver 1.0)\n\tdeveloped by PaleZero\n\t2018.11.3\n");
		if(color)
		{
			if(pushflag)
			{
				printf("Your have pushed chess Black\n");
				getchar();
				pushflag = 0;
			}
			else
				printf("Now your chess is White\n");
		}
		else
		{
			if(pushflag)
			{
				printf("Your have pushed chess White\n");
				getchar();
				pushflag = 0;
			}
			else
				printf("Now your chess is Black\n");
		}
	}
	else
		printf("Push a key and the game start: ");
}
