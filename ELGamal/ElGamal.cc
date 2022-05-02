#include "../rijndael/rijndael.cc"
#include <math.h>
using namespace std;

typedef vector<estado> CadenaBloques;

// Devuelve el numero de bytes que le faltan para completar
// un estado
int ExponenciacionRapida(int a, int b, int m) {
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

/*
  int t = 0, newt = 1;
  int r = b, newr = a;

  while (newr != 0) {
    int cociente = floor(r / newr);
    t = newt;
    newt = t - (cociente * newt);
    
    r = newr;
    newr = r - (cociente * newr);
  }
  if (r > 1) {
    cout << a << " no es invertible" << endl;
  }
  if (t < 0) {
    t = t + b;
  }
  return t;
*/

long EuclideExtendido(long a, long b) {

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

void ElGamal(int p, int alpha, int xa, int xb, int m) {
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
  cout << "Entrada: p = " << p << " a = " << alpha << " k = " << xa << " x = " << xb << " m = " << m << endl;

  // Ambos calculan su clave publica y se la intercambian
  int yA = ExponenciacionRapida(alpha, xa, p);
  int yB = ExponenciacionRapida(alpha, xb, p);

  // Cada uno con la clave del otro, genera la clave secreta
  int KA = ExponenciacionRapida(yB, xa, p);
  int KB = ExponenciacionRapida(yA, xb, p);
  assert (KA == KB);

  // A cifra y envia el mensaje cifrado
  int C = (KA * m) % p;

  // B descifra el mensaje
  int invK = (EuclideExtendido(KA, p) + p) % p;
  int M = (invK * C) % p;

  cout << "Salida : yA = " << yA << " | yB = " << yB << " | K = " << KA << " | C = " << C << " | K^(-1) = " << invK << " | M = " << M << endl;
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
}

void DiffieHellman(int p, int alpha, int xa, int xb, int m) {
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
  cout << "Entrada: p = " << p << " a = " << alpha << " k = " << xa << " x = " << xb << " m = " << m << endl;
  // Ambos calculan su clave publica y se la intercambian
  int yA = ExponenciacionRapida(alpha, xa, p);
  int yB = ExponenciacionRapida(alpha, xb, p);

  // Cada uno con la clave del otro, genera la clave secreta
  int KA = ExponenciacionRapida(yB, xa, p);
  int KB = ExponenciacionRapida(yA, xb, p);

  // int C = (KA * m) % p;

  // B descifra el mensaje
  // int invK = (EuclideExtendido(KA, p) + p) % p;
  // int M = (invK * C) % p;

  cout << "Salida : yA = " << yA << " | yB = " << yB << " | K = " << KA << endl;
  cout << "―-―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――" << endl;
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "---------------――---" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) ElGamal" << endl;
    cout << "2) Diffie Hellman" << endl;
    cout << "3) Banco de Pruebas" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    
    cin >> opt;

    switch (opt){
      case 1:{
        int p = 43, alpha = 23, xa = 25, xb = 33, m = 18;
        ElGamal(p, alpha, xa, xb, m);
        break;
      }
      case 2:{
        int p = 43, alpha = 23, xa = 25, xb = 33, m = 18;
        DiffieHellman(p, alpha, xa, xb, m);
        break;
      }
      case 3:{
        ElGamal(13, 4, 5, 2, 8);
        ElGamal(43, 23, 25, 33, 18);
        ElGamal(113, 43, 54, 71, 28);
        break;
      }
      case 0:
        quit = true;
        break;          
      default:
        cout << "Opcion incorrecta" << endl;
        break;
    }
  }

  return 0;
}
