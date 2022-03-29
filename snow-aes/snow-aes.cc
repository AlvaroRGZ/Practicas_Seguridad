#include "../include/commons.cc"

using namespace std;

typedef bitset<10> secuencia;
const Byte AES_byte  = Byte(string("00011011"));
const Byte SNOW_byte = Byte(string("10101001"));

Byte mult(Byte b1, int pos, Byte Const) {
  cout << endl;
  for (int i = 0; i < pos; i++) {
    if (b1[7]){
      b1 <<= 1;
      b1 ^= Const;
    } else {
      b1 <<= 1;
    }
  }
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
    cout << "1) SNOW" << endl;
    cout << "2) AES" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;
    //cin >> opt;
    opt = 1;
    switch (opt){
      case 1:{
        cout << "Mult = " << full_mult(Byte(string("01010111")), Byte(string("10000011")), AES_byte) << endl;
        quit = true;
        break;
      }
      case 2:{
        cout << "Mult = " << full_mult(Byte(string("01010111")), Byte(string("10000011")), SNOW_byte) << endl;
        quit = true;
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