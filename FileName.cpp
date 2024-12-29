#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

struct SIGN
{
	char letter;
	int row;
};

struct PERSON
{
	char person[100];
};

void print(char board[3][3])
{
	printf("\n    0   1   2  \n");
	printf("  -------------\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(j == 0) printf("%d | %c ", i, board[i][j]);
			else if (j == 1) printf("| %c ", board[i][j]);
			else printf("| %c |", board[i][j]);
		}
		printf("\n  -------------\n");
	}
	printf("\n");
}

void initiallize(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
}

int put(char board[3][3], int x, int y, bool playerTurn)
{
	int res = 0;

	if (board[x][y] != ' ')
	{
		if(playerTurn) printf("\n\n이미 돌이 있습니다.");
		res = 0;
	}
	else
	{
		if (playerTurn) board[x][y] = 'O';
		else board[x][y] = 'X';

		res = 1;
	}

	return res;
}

int check(SIGN sign[9], char board[3][3], bool playerTurn)
{
	bool end = false;
	int blank = 0;

	int cnt = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++, cnt++)
		{
			sign[cnt].letter = board[i][j];
			sign[cnt].row = i;
		}
	}

	bool hor = false, ver = false,
		dia = false, // /
		dia2 = false;// \

	int row = 0;

	for (int i = 2; i < cnt; i++) //가로
	{
		if (i % 2 == 0) row++;

		if (sign[i - 1].letter != ' ')
		{
			if (sign[i].letter == sign[i - 1].letter && sign[i - 1].letter == sign[i - 2].letter &&
				sign[i].row == sign[i - 1].row && sign[i - 1].row == sign[i - 2].row)
			{
				hor = true;
			}
		}
		else blank++;
	}

	for (int i = 6; i < cnt; i++) //세로
	{
		if (sign[i - 3].letter != ' ')
		{
			if (sign[i].letter == sign[i - 3].letter && sign[i - 3].letter == sign[i - 6].letter &&
				sign[i].row + 0 == sign[i - 3].row + 1 && sign[i - 3].row + 1 == sign[i - 6].row + 2)
			{
				hor = true;
			}
		}
	}

	if (sign[0].letter == sign[4].letter && sign[4].letter == sign[8].letter && sign[8].letter != ' ') dia = true;
	if (sign[2].letter == sign[4].letter && sign[4].letter == sign[6].letter && sign[6].letter != ' ') dia2 = true;

	if (hor || ver || dia || dia2)
	{
		print(board);

		if (playerTurn) printf("\n\n플레이어의 승리!\n");
		else printf("\n\n컴퓨터의 승리!\n");	

		printf("%d %d %d %d", hor, ver, dia, dia2);

		end = true;

	}
	else if (blank == 9)
	{
		print(board);

		printf("\n\n무승부!\n");
		printf("%d %d %d %d", hor, ver, dia, dia2);

		end = true;
	}

	return end;
}

int main()
{
	char board[3][3];
	int answer = 0;

	PERSON person[2] =
	{
		"컴퓨터", "플레이어"
	};
	SIGN sign[9];

	printf("틱택토의 세계에 오신것을 환영합니다!\n\n");
	Sleep(1000);
	printf("혹시 틱택토를 해 보신 적이 있나요? (없으면 0) ==> ");
	scanf("%d", &answer);

	if (answer == 0)
	{
		printf("\n\n틱택토는 오목과 비슷하지만, 가로, 세로, 대각선으로 3개의 똑같은 돌을 두면 이기는 게임입니다.\n참고로 돌은 O (플레이어), X (컴퓨터)입니다.\n\n");
		Sleep(2000);
		printf("보드를 보여드리겠습니다!");
		Sleep(1000);

		initiallize(board);
		print(board);
		
		printf("각 보드의 행 (가로)에는 0, 1, 2이라는 숫자를 일시적으로 부여하겠습니다.\n");
		Sleep(1000);
		printf("또한 각 보드의 열 (세로)에도 0, 1, 2이라는 숫자를 일시적으로 부여하겠습니다.\n\n");
		Sleep(1000);

		printf("그러므로 가로 1번째 줄의 세로 2번째는 (0, 1)이 됩니다.\n또한 가로 3번째 줄의 세로 2번째는 (2, 1)이 됩니다.\n");
		Sleep(1000);
	}

	printf("\n게임을 시작합니다!!\n단, 좌표의 꼴은 (y, x)\n");

	Sleep(2000);
	system("cls");

	bool playerTurn = true;


	int x = 0, y = 0;
	int res = 0;
	bool end;

	srand(time(NULL));

	initiallize(board);

	while (1)
	{
		end = false;

		Sleep(1000);
		system("cls");

		print(board);
		Sleep(1000);

		printf("\n%s의 차례", person[playerTurn]);

		if (playerTurn)
		{
			while (1)
			{
				printf("\n\n돌을 어디다 두시겠습니까? ==> ");
				scanf("%d,%d", &x, &y);

				if (x < 0 && x > 2 && y < 0 && y > 2)
				{
					printf("\n잘못 입력하셨습니다.");
				}
				else
				{
					res = put(board, x, y, playerTurn);
					if (res) break;
				}
			}
		}
		else
		{
			printf("\n\n컴퓨터가 돌을 선택하는 중입니다.");

			Sleep(1000);

			while (1)
			{
				int randomX = rand() % 3;
				int randomY = rand() % 3;

				res = put(board, randomX, randomY, playerTurn);

				if (res) break;
			}
		}

		end = check(sign, board, playerTurn);

		if (end) break;

		playerTurn = !playerTurn;
	}
}