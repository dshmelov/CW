#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define HEADER ("Курсовая работа\nТема: Алгоритм Флойда.\nВыполнил: Шмелёв Д.В.\n")

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <queue>

using namespace std;

int** M,** A, n;

int numVertex()
{
	int n;
	printf("Введите размерность: ");
	scanf("%d", &n);
	return n;
}

int** createMatrix()
{
	int** M = (int**)(malloc(n * sizeof(int*)));
	for (int i = 0; i < n; i++)
	{
		M[i] = (int*)(malloc(n * sizeof(int)));
		for (int j = 0; j < n; j++)
		{
			M[i][j] = 0;
		}
	}
	return M;
}

void printMatrix(int** M)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] == SHRT_MAX)
			{
				printf(" %-3d ", NULL);
			}
			else
			{
				printf(" %-3d ", M[i][j]);
			}
		}
		printf("\n");
	}
}

void EditM()
{
	int i, j, d, c;
	printf("Введите номера смежных вершин и вес ребра между ними:\nДля завершения нажмите '-'\n");
	c = getch();
	if (c == '-')
	{
		return;
	}
	else
	{
		scanf("%d %d %d", &i, &j, &d);
		if (i > n || j > n)
		{
			printf("Таких вершин в графе нет!\n");
		}
		else
		{
			M[i][j] = d;
		}
		printMatrix(M);
		EditM();
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] == 0 && i != j)
			{
				M[i][j] = SHRT_MAX;
			}
		}
	}
}

void EditA()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				M[i][j] = 0;
			}
			else if (rand() % 100 < 30)
			{
				M[i][j] = SHRT_MAX;
			}
			else
			{
				M[i][j] = (rand() % n) + 1;
			}
		}
	}
}

void Save(int** M, int** A)
{
	FILE* G = fopen("Graph", "w");
	fprintf(G, "Размерность матрицы: %d\n", n);
	fprintf(G, "Матрица смежности графа:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] == SHRT_MAX)
			{
				fprintf(G, " %d ", NULL);
			}
			else
			{
				fprintf(G, " %d ", M[i][j]);
			}
		}
		fprintf(G, "\n");
	}
	fprintf(G, "Матрица кратчайших путей:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (A[i][j] == SHRT_MAX)
			{
				fprintf(G, " %d ", NULL);
			}
			else
			{
				fprintf(G, " %d ", A[i][j]);
			}
		}
		fprintf(G, "\n");
	}
	fclose(G);
}

void Read()
{
	FILE* G;
	if (!fopen("Graph", "r"))
	{
		printf("Невозможно открыть файл!\n");
		system("pause");
		return;
	}
	G = fopen("Graph", "r");
	fseek(G, 21, SEEK_SET);
	fscanf(G, "%d", &n);
	M = createMatrix();
	fseek(G, 28, SEEK_CUR);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(G, " %d ", &M[i][j]);
		}
	}
	fclose(G);
}

void printList(int** M)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d: ", i);
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] != 0 && M[i][j] != SHRT_MAX)
			{
				printf(" %d ", j);
			}
		}
		printf("\n");
	}
}

int** Floyd()
{
	int** A = (int**)(malloc(n * sizeof(int*)));
	for (int i = 0; i < n; i++)
	{
		A[i] = (int*)(malloc(n * sizeof(int)));
		for (int j = 0; j < n; j++)
		{
			A[i][j] = M[i][j];
		}
	}
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j];
				}
			}
		}
	}
	return A;
}

void addVertex()
{
	M = (int**)(realloc(M, (n + 1) * sizeof(int**)));
	for (int i = 0; i < n; i++)
	{
		M[i] = (int*)(realloc(M[i], (n + 1) * sizeof(int)));
	}
	M[n] = (int*)(malloc((n + 1) * sizeof(int)));
	n++;
	for (int i = 0; i < n; i++)
	{
		M[n - 1][i] = 0;
		M[i][n - 1] = 0;
	}
}

void delVertex(int v)
{
	for (int i = v; i < n - 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			M[i][j] = M[i + 1][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = v; j < n - 1; j++)
		{
			M[i][j] = M[i][j + 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		M[i] = (int*)(realloc(M[i], (n - 1) * sizeof(int)));
	}
	free(M[n - 1]);
	n--;
}

void menuEdit()
{
	int a, c;
	do
	{
		system("cls");
		printf("Редактирование\n1)Заполнение графа\n2)Добавление вершины\n3)Удаление вершины\n4)Назад\n->");
		c = getch();
		switch (c)
		{
		case '1':
			system("cls");
			printf("Заполнение матрицы?\n1)Ручное\n2)Автоматическое\n3)Назад\n->");
			a = getch();
			if (a == '1')
			{
				EditM();
			}
			else if (a == '2')
			{
				EditA();
				system("cls");
				printf("Матрица успешно заполнена!\n");
				system("pause");
			}
			else if (a == '3')
			{
				return;
			}
			else 
			{
				printf("Ошибка!\n");
				system("pause");
			}
			break;
		case '2':
			system("cls");
			addVertex();
			printf("Вершина успешно добавлена!\n");
			system("pause");
			break;
		case '3':
			system("cls");
			printf("Введите номер удаляемой вершины: ");
			scanf("%d", &a);
			if (a < n)
			{
				delVertex(a);
			}
			else
			{
				system("cls");
				printf("Такой вершины нет!\n");
				system("pause");
				return;
			}
			break;
		case '4':
			return;
		default:
			system("cls");
			printf("Ошибка!\n");
			system("pause");
			break;
		}
	} while (c != '4');
}

void menu()
{
	int c;
	do
	{
		system("cls");
		printf("Меню\n1)Создать граф\n2)Редактировать граф\n3)Посмореть граф\n4)Алгоритм Флойда\n5)Сохранить результат\n6)Загрузить граф\n7)Выход\n->");
		c = getch();
		switch (c)
		{
		case '1':
			system("cls");
			n = numVertex();
			M = createMatrix();
			A = createMatrix();
			break;
		case '2':
			menuEdit();
			break;
		case '3':
			system("cls");
			printf("Матрица смежности графа:\n");
			printMatrix(M);
			system("pause");
			break;
		case '4':
			system("cls");
			printf("Матрица смежности графа:\n");
			printMatrix(M);
			printf("Матрица кратчайших путей:\n");
			A = Floyd();
			printMatrix(A);
			system("pause");
			break;
		case '5':
			system("cls");
			printf("Результат сохранён в файл Graph.\n");
			Save(M, A);
			system("pause");
			break;
		case '6':
			system("cls");
			Read();
			printf("Матрица смежности успешно загружена!\n");
			system("pause");
			break;
		case '7':
			exit(NULL);
		default:
			printf("Ошибка!\n");
			system("pause");
			system("cls");
			break;
		}
	} while (c != '7');
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	printf(HEADER);
	Sleep(1337);
	menu();
	system("pause");
	return 0;
}

