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

void ElGamal(int p, int alpha, int xa, int xb, int m) {
  cout << "yA = " << ExponenciacionRapida(alpha, xa, p) << endl;
  cout << "yB = " << ExponenciacionRapida(alpha, xb, p) << endl;
  cout << "KA = " << ExponenciacionRapida(ExponenciacionRapida(alpha, xa, p), xb, p) << endl;
  cout << "KB = " << ExponenciacionRapida(ExponenciacionRapida(alpha, xb, p), xa, p) << endl;
  cout << "C  = " << (xa * m) % p << endl;
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "--------------------" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) ElGamal" << endl;
    cout << "2) Diffie Hellman" << endl;
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
