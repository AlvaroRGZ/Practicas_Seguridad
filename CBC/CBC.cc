#include "../rijndael/rijndael.cc"
using namespace std;

typedef vector<estado> CadenaBloques;

// Devuelve el numero de bytes que le faltan para completar
// un estado
int emptyString(string s) {
  if (s.size() < 32) {
    return 32 - s.size();
  }
  int c = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '-') {
      c++;
    }
  }
  return c;
}

// Convierte un estado dado en una string por filas
// a por columnas y a la inversa
string shuffleBytes(string x) {
  string out;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out += x[(i + 4 * j)% x.size()];
    }
  }

}

CadenaBloques CBC(CadenaBloques plaintext, estado clave, estado IV) {

  CadenaBloques CipherTexts;
  CipherTexts.resize(plaintext.size());

  CipherTexts[0] = Rijndael(addRoundKey(plaintext[0], IV), clave);

  for (int i = 1; i < plaintext.size(); i++) {

    CipherTexts[i] = Rijndael(addRoundKey(plaintext[i], CipherTexts[i - 1]), clave);

  }
  return CipherTexts;
}

CadenaBloques stealingCBC(CadenaBloques plaintext, estado clave, estado IV, int lastBytesLeft = 0) {

  CadenaBloques CipherTexts;
  CipherTexts.resize(plaintext.size());

  CipherTexts[0] = Rijndael(addRoundKey(plaintext[0], IV), clave);
  int i = 1;
  for (i; i < plaintext.size() - 1; i++) {
    CipherTexts[i] = Rijndael(addRoundKey(plaintext[i], CipherTexts[i - 1]), clave);
  }

  // Las dos ultimas iteraciones las hacemos a mano
  estado lastState = Rijndael(addRoundKey(CipherTexts[i - 1], plaintext[i]), clave);
  string prevStateData = estadoToCadena(CipherTexts[i - 1]);

  // Intercambio de valores
  CipherTexts[i - 1] = lastState;     // Este encadenamiento de funciones, es para convertir un estado dado por filas a uno dado por columnas
  CipherTexts[i] = cadenaToEstado(estadoToCadena((cadenaToEstado(prevStateData.erase(32 - lastBytesLeft)))));

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

        estado key  = cadenaToEstado("0004080c0105090d02060a0e03070b0f");
        estado b1  = cadenaToEstado("004488cc115599dd2266aaee3377bbff");
        estado b2  = cadenaToEstado("00000000000000000000000000000000");
        string ib2cad = "000000000000000000000000000000";
        estado ib2 = cadenaToEstado(ib2cad);
        estado iv  = cadenaToEstado("00000000000000000000000000000000");
        
        CadenaBloques cb = {b1, ib2};
        showCBCSecuence(stealingCBC(cb, key, iv, emptyString(ib2cad)));

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