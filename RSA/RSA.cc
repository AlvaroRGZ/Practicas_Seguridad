#include "../include/commons.cc"

class RSA {
  private:
    long _p, _q;
    int _mod;
    std::vector<int> primerosPrimos = {2, 3, 5, 7, 11, 13, 17, 19};
		std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<int> mensaje_codificado;
    std::vector<int> mensaje_cifrado;

  public:

    int ExponenciacionRapida(int a, int b, int m);
    long EuclideExtendido(long a, long b);
    bool lehmanPeralta(long p);

    RSA(){}
    ~RSA(){}

    void execute();
};

// Devuelve el numero de bytes que le faltan para completar
// un estado
int RSA::ExponenciacionRapida(int a, int b, int m) {
  int x = 1;
  int y = a % m;
  while (b > 0 && y > 1) {
    if (b%2 == 1) {
      x = (x * y) % m;
      b--;
    } else {
      y = (y * y) % m;
      b /= 2;
    }
  }
  return x;
}

long RSA::EuclideExtendido(long a, long b) {

  long x = 1, y = 0;
  long xLast = 0, yLast = 1;
  long q, r, m, n;
  while (a != 0) {
      q = b / a;
      r = b % a;
      m = xLast - q * x;
      n = yLast - q * y;
      xLast = x, yLast = y;
      x = m, y = n;
      b = a, a = r;
  }
  return xLast;
}

bool RSA::lehmanPeralta(long p) {
	for (int i = 0; i < primerosPrimos.size(); i++)
		if ((p % primerosPrimos[i] == 0) && (p != primerosPrimos[i]))
			return false;

	//Enteros aleatorios entre 2 y p-1
	std::vector<int> randPrimes;

	for (int i = 0; i < 6; i++) // 65 + rand() % (122 - 65)
		randPrimes.push_back(2 + rand() %((p - 1) - 2));

	// Calcular Ai^((p-1)/2) % p. Si todos dan 1 es compuesto.
	bool compuesto = true;
	for (int i = 0; i < randPrimes.size(); i++)
		if (ExponenciacionRapida(randPrimes[i], (p - 1) / 2, p) != 1)
		{
			compuesto = false;
			break;
		}

	if (compuesto)
		return false;

	// Si existe un i tal que Ai^((p-1)/2) % p != -1, es compuesto.
	int temp = 0;
	for (int i = 0; i < randPrimes.size(); i++) {
		temp = ExponenciacionRapida(randPrimes[i], (p - 1) / 2, p);
		if (temp != 1)
			temp -= p;

		if ((temp != -1) && (temp != 1))
			return false;
	}

	//Tal vez es primo
	return true;
}
