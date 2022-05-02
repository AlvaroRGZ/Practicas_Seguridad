#include "./RSA.cc"
#include <math.h>
using namespace std;

int main (void){

  bool quit = false;
  int opt;

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
        string mensaje;
        long p, q, d;
        cout << "Mensaje > ";
        cin >> mensaje;
        cout << "P > ";
        cin >> p;
        cout << "q > ";
        cin >> q;
        cout << "d > ";
        cin >> d;
        RSA encoder(mensaje, p, q, d);
        encoder.printData();

        break;
      }
      case 2:{
        break;
      }
      case 3:{
        RSA encoder("MANDADINEROS", 421, 7, 1619);
        encoder.printData();
        RSA encoder2("AMIGOMIO", 2347, 347, 5);
        encoder2.printData();
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
