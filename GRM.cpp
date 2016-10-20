#include <stdio.h>
#include <stdlib.h>

unsigned short power(const unsigned short& exponent)
{
	return (1 << exponent);
}

void grm(const short& n, const short& m, const short& lim, unsigned char** matrix, unsigned short& idx, short* row, short rowIdx, short& rowValue)
{
	if (lim <= rowIdx)
	{
		int i = 0;
		while (i != rowIdx)
		{
			for (int j = 0; j < n; j++)
			{
				matrix[idx][j] *= matrix[row[i]][j];
			}
			i++;
		}
		idx++;
		return;
	}

	for (short i = rowValue - 1; i >= 1; i--)
	{
		row[rowIdx] = i;
		grm(n, m, lim, matrix, idx, row, rowIdx + 1, i);
	}

}


void generateMatrix(const short& r, const short& m, const short& n, unsigned char** matrix)
{
	for (int i = 0; i < n; i++)
	{
		matrix[0][i] = 1;
	}

	for (int i = 1; i <= m; i++)
	{
		static unsigned char temp = 0;
		int z = 0;
		for (int j = 0; j < n / power(i - 1); j++)
		{
			for (int k = 0; k < power(i - 1); k++)
			{
				matrix[i][z] = temp;
				z++;
			}
			temp = temp == 0 ? 1 : 0;
		}
	}


	for (int i = r; i > 1; i--)
	{
		short* multiplRows = (short*)malloc(sizeof(short) * r);
		for (short j = m; j >= 1; j--)
		{
			short rowIdx = 0;
			static unsigned short idx = m + 1;
			multiplRows[rowIdx] = j;
			grm(n, m, i, matrix, idx, multiplRows, rowIdx + 1, j);
		}
		free(multiplRows);
	}
	
}

unsigned short combination(unsigned short n, const unsigned short& k)
{
	if (k > n) return 0;

	unsigned short result = 1;
	for (unsigned short i = 1; i <= k; i++)
	{
		result *= n--;
		result /= i;
	}

	return result;
}


void main()
{
	unsigned short r = 2; //4;
	unsigned short m = 4; //10;

	unsigned short n = 0; //code length
	unsigned short k = 0; //message length	

	printf("r : ");
	scanf("%hd", &r);

	printf("m : ");
	scanf("%hd", &m);

	n = power(m);
	for (int i = 0; i <= r; i++)
	{
		k += combination(m, i);
	}

	printf("n = %d, k = %d\n\n", n, k);

	unsigned char **G = (unsigned char **)malloc(sizeof(unsigned char *) * k);

	for (int i = 0; i < k; i++)
	{
		G[i] = (unsigned char *)malloc(sizeof(unsigned char) * n);
		for (int j = 0; j<n; j++)
		{
			G[i][j] = 1;
		}
	}


	generateMatrix(r, m, n, G); //generate G
	printf("\nGRM\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n"); printf("\n");

	
	for (int i = 0; i < k; i++)
	{
		free(G[i]);
	}

	free(G);

	return;
}
