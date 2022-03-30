#include "../include/commons.cc"

using namespace std;

typedef bitset<10> secuencia;
const Byte AES_byte  = Byte(string("00011011"));
const Byte SNOW_byte = Byte(string("10101001"));

Byte mult(Byte b1, int pos, Byte Const) {
  cout << "――――――――――――――――――――――――――――――" << endl;
  cout << "STEP " << 0 << endl;
  cout << setw(10) << b1.to_string() << endl;
  for (int i = 0; i < pos; i++) {
  cout << "STEP " << i + 1 << endl;
    if (b1[7]){
      b1 <<= 1;
      cout << setw(4) << b1.to_string() << " + " << Const.to_string() << " = ";
      b1 ^= Const;
      cout << b1.to_string() << endl;
    } else {
      b1 <<= 1;
      cout << setw(10) << b1.to_string() << endl;
    }
  }
  cout << "――――――――――――――――――――――――――――――" << endl;
  return b1;
}

Byte full_mult(Byte b1, Byte b2, Byte Const){
  
  Byte result = Byte(string("00000000"));
  for (int i = 0; i < 8; i++) 
    if (b2[i]) 
      result ^= mult(b1, i, Const);

  return result;
}


int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "--------------------" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) AES" << endl;
    cout << "2) SNOW" << endl;
    cout << "3) Personalizado" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    cin >> opt;
    switch (opt){
      case 1:{
        cout << full_mult(Byte(string("01010111")), Byte(string("10000011")), AES_byte) << endl;
        break;
      }
      case 2:{
        cout << full_mult(Byte(string("01010111")), Byte(string("10000011")), SNOW_byte) << endl;
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