#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <assert.h>
#include "main.h"

Polinom* Create()
/* Резервируем память на куче для Polinom и 10 коэффициентов */
{
	Polinom *polinom = (Polinom*) malloc(sizeof(Polinom));
	if (polinom == NULL)
		return NULL;

	polinom->length = 0;
	polinom->capacity =9;
	polinom->multiplier = malloc(10 * sizeof(Multiplier));
	if (polinom->multiplier == NULL)
		return NULL;

	return polinom;
}


int AppendMultiplaier(Polinom *polinom, Multiplier *multiplier)
{
	if (polinom->length == polinom->capacity)
	{
		polinom = realloc(polinom, 10 * sizeof(Multiplier));
		if (polinom == NULL)
			return -1;		

		polinom->capacity+=10;
	}

	polinom->multiplier[polinom->length] = multiplier;
	polinom->length++;
	return 0;
}


int AppendInt(Polinom *polinom, int value)
{
	int *val = malloc(sizeof(int));
	*val = value;

	Multiplier *multiplier = (Multiplier*) malloc(sizeof(Multiplier));
	if (polinom->multiplier == NULL)
		return -1;

	multiplier->type_ = 1;
	multiplier->val = val;

	AppendMultiplaier(polinom, multiplier);
	return 0;
}


int AppendComplex(Polinom *polinom, double _Complex value)
{
	double _Complex *val = malloc(sizeof(double _Complex));
	*val = value;

	Multiplier *multiplier = (Multiplier*) malloc(sizeof(Multiplier));
	if (polinom->multiplier == NULL)
		return -1;

	multiplier->type_ = 2;
	multiplier->val = val;

	AppendMultiplaier(polinom, multiplier);
	return 0;
}

// Умножение на скаляр 
int Scalar(Polinom *p, double arg)
{
	double _Complex *val;

	for (int i = 0; i < p->length; ++i)
	{
		switch (p->multiplier[i]->type_)
		{
			case 1:
				*(int*) p->multiplier[i]->val = *(int*) p->multiplier[i]->val * arg;
				break;

			case 2:
				val = (double _Complex*) p->multiplier[i]->val;
				*val = *val * arg;
				break;
		}; 
	}
	return 0;
}


void Free(Polinom *polinom)
{
	for (int i = 0; i < polinom->length; ++i)
	{
		free(polinom->multiplier[i]->val);
		free(polinom->multiplier[i]);
	}
	free(polinom);
}


int main()
{
	//модульные тесты
 	Polinom *m_polinom = Create();
 	assert(m_polinom != NULL);

 	double _Complex val;
	
	AppendInt(m_polinom, 42);
	AppendComplex(m_polinom, 1.0 + 42.0 * I);

	assert(m_polinom->length == 2);

	Scalar(m_polinom, 10.0);
	assert( *(int*) m_polinom->multiplier[0]->val == 420);
	assert( creal(*(double _Complex*) m_polinom->multiplier[1]->val) == 10.0 );
	assert( cimag(*(double _Complex*) m_polinom->multiplier[1]->val) == 420.0 );
	
	Free(m_polinom);
	return 0;
}