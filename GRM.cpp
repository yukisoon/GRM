#include <stdio.h>
#include <stdlib.h>


int idx[10] = { 0 };

unsigned int power(const unsigned int& exponent)
{
	return (1 << exponent);
}

void grm(int& i, const int& m, const int& r, int p, const int& n, unsigned char** matrix)
{
	if (r <= p)
	{
		int z = 0;
		while (z != p)
		{
			printf("%d ", idx[z]);
			z++;
		}
		printf("\n");
		return;
	}

	for (int j = i + 1; j <= m; j++)
	{
		idx[p] = j;		
		grm(j, m, r, p + 1, n, matrix);
	}

}
void generateMatrixMultiple(int& i, const int& m, const int& r, int p, const int& n, unsigned char** matrix, int& idx)
{
	if (r < p)
	{
		return;
	}

	for (int j = i + 1; j <= m; j++)
	{
		if (p == 2)
		{
			printf("%d %d %d\n", idx, i, j);
			for (int k = 0; k < n; k++)
			{
				matrix[idx][k] = matrix[i][k] * matrix[j][k];
			}
		}
		else
		{
			printf("%d %d %d\n", idx, idx - 1, j);
			for (int k = 0; k < n; k++)
			{
				matrix[idx][k] = matrix[idx - 1][k] * matrix[j][k];
			}
		}
		printf("\n\n");
		idx = idx + 1;
		generateMatrixMultiple(j, m, r, p + 1, n, matrix, idx);
	}

}

void generateMatrix(const int& r, const int& m, const int& n, unsigned char** matrix)
{
	for (int i = 0; i <= n; i++)
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

	
	for(int k=2; k<=r; k++)
	{
		for (int i = 1; i <= m; i++) //ÀÚ¸®¼ö
		{
			int p = 0;
			idx[p] = i;
			//generateMatrixMultiple(i, m, r, p, n, matrix, idx);
			grm(i, m, k, p+1, n, matrix);
		}
	}

}

unsigned int combination(unsigned int n, const unsigned int& k)
{
	if (k > n) return 0;

	unsigned int result = 1;
	for (unsigned int i = 1; i <= k; i++)
	{
		result *= n--;
		result /= i;
	}

	return result;
}

void main()
{
	unsigned int r = 3; //4;
	unsigned int m = 4; //10;

	unsigned int n = 0; //code length
	unsigned int k = 0; //message length	

	n = power(m);
	for (int i = 0; i <= r; i++)
	{
		k += combination(m, i);
	}

	printf("n = %d, k = %d\n\n", n, k);


	unsigned char** G = (unsigned char**)malloc(sizeof(unsigned char*) * k);

	for (int i = 0; i < k; i++)
	{
		G[i] = (unsigned char*)malloc(sizeof(unsigned char) * n);
		for (int j = 0; j<n; j++)
		{
			G[i][j] = 1;
		}
	}


	generateMatrix(r, m, n, G); //generate G



	printf("\nG\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n"); printf("\n");
	return;
}
