#include "./RSA.cc"
#include <math.h>
using namespace std;

int main (void){

  bool quit = false;
  int opt;
  RSA encoder;

  while(!quit){

    cout << "---------------――---" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) RSA automatico" << endl;
    cout << "2) RSA manual" << endl;
    cout << "3) Banco de Pruebas" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    
    cin >> opt;

    switch (opt){
      case 1:{
        int p = 43, alpha = 23, xa = 25, xb = 33, m = 18;
        cout << ((encoder.lehmanPeralta(423)) ? "Primo" : "No es primo") << endl;
        break;
      }
      case 2:{
        break;
      }
      case 3:{
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
