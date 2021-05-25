
typedef struct Multiplier
{
	int type_;
	void *val;
} Multiplier;


typedef struct Polinom
{
	unsigned length;
	unsigned capacity;
	Multiplier **multiplier;
} Polinom;


Polinom* Create();
int AppendMultiplaier(Polinom *polinom, Multiplier *multiplier);
int AppendInt(Polinom *polinom, int value);
int AppendComplex(Polinom *polinom, double _Complex value);
void Free(Polinom *polinom);
int Scalar(Polinom *p, double arg);
