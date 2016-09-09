/*
 * File contenente il modulo per l'utilizzo di funzioni generiche.
 */

//INIZIO DEL MODULO
int precInRange (int n, int peso, int min)
{
	n -= peso;
	if (n < min)
	{
		n = min;
	}
	return n;
}

int precInRange (int n, int min)
{
	return precInRange (n, 1, min);
}

int sucInRange (int n, int peso, int max)
{
	n += peso;
	if (n > max)
	{
		n = max;
	}
	return n;
}

int sucInRange (int n, int max)
{
	return sucInRange (n, 1, max);
}

int precInRangeCircuito (int n, int min, int max)
{
	n--;
	if (n < min)
	{
		n = max - 1;
	}
	return n;
}

int sucInRangeCircuito (int n, int min, int max)
{
	n++;
	if (n > (max - 1))
	{
		n = min;
	}
	return n;
}
//FINE DEL MODULO