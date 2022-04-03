#include "../include/commons.cc"
using namespace std;

const Byte AES_byte  = Byte(string("00011011"));
const Byte SNOW_byte = Byte(string("10101001"));
typedef vector<vector<Byte>> estado;

const int nIter = 10;

const int sbox[256] =   {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

estado getSBox (){

  estado out;
  out.resize(16);
  for (int i = 0; i < 16; i++)
    out[i].resize(16);

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      out[i][j] = sbox[i*16 + j];
    }
  }
/*
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      cout << BinHexACadena(out[i][j].to_string()) << " ";
    }
    cout << endl;
  }
*/
  return out;
}

void showEstado(estado e) {
  cout << "―――――――――――" << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << BinHexACadena(e[i][j].to_string()) << " ";
    }
    cout << endl;
  }
  cout << "―――――――――――" << endl;
}

estado claveToEstado(string clave){
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] = Byte(HexToBin(clave.substr(count, 2)));
      count += 2;
    }
  }
  return out;
}

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

// obtiene el primer numero hexadecimal de un numero
int get1Hex(Byte b) {
  return Byte(b.to_string().substr(0, 4)).to_ulong();
}

// obtiene el segundo numero hexadecimal de un numero
int get2Hex(Byte b) {
  return Byte(b.to_string().substr(4)).to_ulong();
}

// Primera operacion, realiza una exclusive-OR a cada elemento de
// los dos estados entrantes y devuelve el estado resultado
estado addRoundKey(estado& e1, estado& e2) {

  estado out;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] = e1[i][j] ^ e2[i][j];
    }
  }

  return out;
}

// Segunda iter Byte Sub

estado SubBytes(estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out[i][j] =  getSBox()[get1Hex(e[i][j])][get2Hex(e[i][j])];
    }
  }
  return out;
}

// shift Rows

estado shiftRows(estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < 4; k++) {
        out[i][k] = e[i][(k+i)%4];
      }
    }
  }
  return out;
}

// Ha de llamarse 4 veces, una por cada columna
estado mixColums (estado e) {
  estado out;
  out.resize(4);
  for (int i = 0; i < 4; i++)
    out[i].resize(4);


  /*for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      s[j] = 0;
      for (int k = 0; k < 4; k++) {
        s[j] = s[j] ^ aes_mul(state[i * 4 + k], y[j * 4 + k]);
      }
    }
    for (int j = 0; j < 4; j++) {
      state[i * 4 + j] = s[j];
    }
  }*/
  return out;
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
        estado ejemplo = claveToEstado("19a09ae93df4c6f8e3e28d48be2b2a08");
        showEstado(ejemplo);
        showEstado(SubBytes(ejemplo));
        showEstado(shiftRows(SubBytes(ejemplo)));
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