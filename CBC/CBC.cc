#include "../rijndael/rijndael.cc"
using namespace std;

typedef vector<estado> CadenaBloques;

CadenaBloques CBC(CadenaBloques plaintext, estado clave, estado IV) {

  CadenaBloques CipherTexts;
  CipherTexts.resize(plaintext.size());

  CipherTexts[0] = Rijndael(addRoundKey(plaintext[0], IV), clave);

  for (int i = 1; i < plaintext.size(); i++) {

    CipherTexts[i] = Rijndael(addRoundKey(plaintext[i], CipherTexts[i - 1]), clave);

  }
  return CipherTexts;
}

void showCBCSecuence(CadenaBloques s) {
  for (int i = 0; i < s.size(); i++) {
    cout << "Bloque " << i + 1 << " de texto cifrado" << endl;
    showEstado(s[i]);
    cout << estadoToCadena(s[i]) << endl;
  }
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "--------------------" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) Rijndael" << endl;
    cout << "2) Prueba addRoundKey" << endl;
    cout << "3) Prueba subBytes" << endl;
    cout << "4) Prueba ShiftRow" << endl;
    cout << "5) Prueba MixColumns" << endl;
    cout << "6) Prueba Expansion de clave" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    cin >> opt;

    switch (opt){
      case 1:{
        
        estado clave  = cadenaToEstado("0004080c0105090d02060a0e03070b0f");
        estado b1  = cadenaToEstado("004488cc115599dd2266aaee3377bbff");
        estado b2  = cadenaToEstado("00000000000000000000000000000000");
        estado ib2 = cadenaToEstado("000000000000000000000000000000--");
        estado iv  = cadenaToEstado("00000000000000000000000000000000");
        CadenaBloques cb = {b1, b2};
        showCBCSecuence(CBC(cb, clave, iv));

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