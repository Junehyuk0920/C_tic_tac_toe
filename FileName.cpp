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
		if(playerTurn) printf("\n\n�̹� ���� �ֽ��ϴ�.");
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

	for (int i = 2; i < cnt; i++) //����
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

	for (int i = 6; i < cnt; i++) //����
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

		if (playerTurn) printf("\n\n�÷��̾��� �¸�!\n");
		else printf("\n\n��ǻ���� �¸�!\n");	

		printf("%d %d %d %d", hor, ver, dia, dia2);

		end = true;

	}
	else if (blank == 9)
	{
		print(board);

		printf("\n\n���º�!\n");
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
		"��ǻ��", "�÷��̾�"
	};
	SIGN sign[9];

	printf("ƽ������ ���迡 ���Ű��� ȯ���մϴ�!\n\n");
	Sleep(1000);
	printf("Ȥ�� ƽ���並 �� ���� ���� �ֳ���? (������ 0) ==> ");
	scanf("%d", &answer);

	if (answer == 0)
	{
		printf("\n\nƽ����� ����� ���������, ����, ����, �밢������ 3���� �Ȱ��� ���� �θ� �̱�� �����Դϴ�.\n����� ���� O (�÷��̾�), X (��ǻ��)�Դϴ�.\n\n");
		Sleep(2000);
		printf("���带 �����帮�ڽ��ϴ�!");
		Sleep(1000);

		initiallize(board);
		print(board);
		
		printf("�� ������ �� (����)���� 0, 1, 2�̶�� ���ڸ� �Ͻ������� �ο��ϰڽ��ϴ�.\n");
		Sleep(1000);
		printf("���� �� ������ �� (����)���� 0, 1, 2�̶�� ���ڸ� �Ͻ������� �ο��ϰڽ��ϴ�.\n\n");
		Sleep(1000);

		printf("�׷��Ƿ� ���� 1��° ���� ���� 2��°�� (0, 1)�� �˴ϴ�.\n���� ���� 3��° ���� ���� 2��°�� (2, 1)�� �˴ϴ�.\n");
		Sleep(1000);
	}

	printf("\n������ �����մϴ�!!\n��, ��ǥ�� ���� (y, x)\n");

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

		printf("\n%s�� ����", person[playerTurn]);

		if (playerTurn)
		{
			while (1)
			{
				printf("\n\n���� ���� �νðڽ��ϱ�? ==> ");
				scanf("%d,%d", &x, &y);

				if (x < 0 && x > 2 && y < 0 && y > 2)
				{
					printf("\n�߸� �Է��ϼ̽��ϴ�.");
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
			printf("\n\n��ǻ�Ͱ� ���� �����ϴ� ���Դϴ�.");

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