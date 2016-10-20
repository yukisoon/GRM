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
		printf("%d : ", idx);
		while (i != rowIdx)
		{
			printf("%d ", row[i]);
			for (int j = 0; j < n; j++)
			{
				matrix[idx][j] *= matrix[row[i]][j];
			}
			i++;
		}
		idx++;
		printf("\n");
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


	/*for(int i = 2; i <= r; i++)
	{
		short* multiplRows = (short*)malloc(sizeof(int) * r);
		for (int j = 1; j <= m; j++)
		{
			int rowIdx = 0;
			static unsigned short idx = m + 1;
			multiplRows[rowIdx] = j;
			grm(n, m, i, matrix, idx, multiplRows, rowIdx + 1, j);
		}	
		free(multiplRows);
	}*/
	
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



void idxCalculator(unsigned short *array, const short& arrayLen, unsigned short& arrayPointer, unsigned short *result, unsigned short& resultIdx, unsigned short& resultValue)
{
	if (arrayLen == arrayPointer)
	{
		arrayPointer--;
		
		result[resultIdx] = resultValue;
		resultIdx++;
		
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		unsigned short temp = power(array[arrayPointer]) * i;
		resultValue += temp;

		arrayPointer++;
		idxCalculator(array, arrayLen, arrayPointer, result, resultIdx, resultValue);

		resultValue -= temp;
	}
	arrayPointer--;
}


void SCalculate(unsigned short *row, const short& rowLength, unsigned short *S)
{
	unsigned short *rowCopy = (unsigned short *)malloc(sizeof(unsigned short) * rowLength);

	for (int i = 0; i < rowLength; i++)
	{
		rowCopy[i] = row[i] - 1;
	}

	unsigned short SValue = 0;
	unsigned short SIdx = 0;

	unsigned short rowPointer = 0;
	
	idxCalculator(rowCopy, rowLength, rowPointer, S, SIdx, SValue);

	free(rowCopy);

}

void ECalculate(unsigned short *row, const short& rowLength, const short& m, unsigned short *E)
{

	int k = 0;
	for (int i = 0; i < m; i++)
	{
		int temp = 0;
		for (int j = 0; j < rowLength; j++)
		{
			if (i == (row[j] - 1))
			{
				temp = 1;
				break;
			}
		}

		if (temp == 0)
		{
			E[k] = i;
			k++;
		}
	}
}

void SCCalculate(unsigned short *row, const short& rowLength, unsigned short *SC)
{
	unsigned short SCValue = 0;
	unsigned short SCIdx = 0;

	unsigned short rowPointer = 0;

	idxCalculator(row, rowLength, rowPointer, SC, SCIdx, SCValue);


}

void RMDecoding(const short& n, const short& m, const short& rowLength, unsigned short* row, short rowIdx, short& rowValue, unsigned short& idx)
{
	if (rowLength <= rowIdx)
	{
		int i = 0;
		printf("%d : ", idx);
		while (i != rowIdx)
		{
			printf("%d ", row[i]);
			i++;
		}
		printf("\n");



		/**/
		unsigned short SLength = power(rowLength);
		unsigned short *S = (unsigned short *)malloc(sizeof(unsigned short) * SLength);
		SCalculate(row, rowLength, S);

		/*for (int i = 0; i < SLength; i++)
		{
			printf("%d ", S[i]);
		}
		printf("\n");*/

		unsigned short ELength = m - (rowLength);
		unsigned short *E = (unsigned short *)malloc(sizeof(unsigned short) * ELength);
		ECalculate(row, rowLength, m, E);

		unsigned short SCLength = power(ELength);
		unsigned short *SC = (unsigned short *)malloc(sizeof(unsigned short) * SCLength);
		SCCalculate(E, ELength, SC);

		/*for (int i = 0; i < SCLength; i++)
		{
			printf("%d ", SC[i]);
		}
		printf("\n");*/





		free(SC);
		free(E);
		free(S);
		/**/

		idx++;
		printf("\n");
		return;
	}

	for (short i = rowValue - 1; i >= 1; i--)
	{
		row[rowIdx] = i;
		RMDecoding(n, m, rowLength, row, rowIdx + 1, i, idx);
	}

}

//void RMDecoder(unsigned char** GRM, const unsigned short& k, const unsigned short& n, unsigned char** c, unsigned char** msg, const unsigned short& r, const unsigned short& m)
//{
//
//	for (int i = r; i >= 1; i--)
//	{
//		short* multiplRows = (short*)malloc(sizeof(int) * r);
//		for (int j = m; j >= 1; j--)
//		{
//			int rowIdx = 0;
//			multiplRows[rowIdx] = j;
//			RMDecoding(n, m, i, multiplRows, rowIdx + 1, j, idx);
//		}
//		free(multiplRows);
//	}
//
//}





void main()
{
	unsigned short r = 2; //4;
	unsigned short m = 4; //10;

	unsigned short n = 0; //code length
	unsigned short k = 0; //message length	

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



	for (int i = r; i >= 2; i--)
	{
		unsigned short* multiplRows = (unsigned short*)malloc(sizeof(unsigned short) * r);
		for (short j = m; j >= 1; j--)
		{
			short rowIdx = 0;
			static unsigned short idx = m + 1;
			multiplRows[rowIdx] = j;
			RMDecoding(n, m, i, multiplRows, rowIdx + 1, j, idx);
		}
		free(multiplRows);
	}


	


	for (int i = 0; i < k; i++)
	{
		free(G[i]);
	}

	free(G);

	return;
}
