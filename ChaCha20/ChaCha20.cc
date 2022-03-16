#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h> 
#include <string.h>
#include <iomanip>

using namespace std;

const int ROUNDS = 20;

typedef bitset<8> byte;
//typedef bitset<32> palabra;
typedef uint32_t palabra;

string BinarioACadena(string cadena){
  string resultado;
  int Ncaracter = cadena.size()/8;
  for (int i = 0; i < Ncaracter; i++){
    string caracter = cadena.substr(i*8, (i+1)*8);
    byte aux = byte(caracter);
    char car = char(int(aux.to_ulong()));
    resultado += car;
  }
  return resultado;
}

string BinHexACadena(string cadena){
  string resultado, x;
  int Ncaracter = cadena.size()/4;
  for (int i = 0; i < Ncaracter; i++){
    string caracter = cadena.substr(i*4, i*4 + 4);
    bitset<4> aux = bitset<4>(caracter);
    std::stringstream stream;
    stream << std::hex << aux.to_ulong();
    std::string result( stream.str() );
    resultado += result;
  }
  return resultado;
}

string CadenaABinario(string cadena){
  string resultado;
  for (int i = 0; i < cadena.size(); i++){
    resultado += byte(cadena.c_str()[i]).to_string();
  }
  return resultado;
}

string reverse(string r) {
  string s;
  int Ncaracter = r.size()/2;
  for (int i = Ncaracter - 1; i >= 1; i -= 2){
    string caracter = r.substr((i*2 -2)%16, (i*2)%16);
    cout << "c1 = " << caracter[1] << " c2 = " << caracter[0]<< endl;
    s += (caracter[1] + caracter[0]);
  }
  

  return s;
}

palabra hexToUint32(string cadena){ // Quite reverse
  return palabra(stoul((cadena), nullptr, 16));
}

string u32ToString(palabra pal){
  // return palabra(stoul(reverse(cadena), nullptr, 16));
  bitset<32> x(pal);
  return BinHexACadena(x.to_string());
}

string uint32ToHex(string cadena){
  bitset<32> x;
  string r;
  for (int i = 0; i < cadena.size(); i++){
    r += palabra(cadena.c_str()[i]);
  }
  return r;
}

string ClaveAleatoria(int size){
  string resultado;
  resultado.resize(size);
  srand(time(NULL));
  for(int i=0; i <size; i++)
    resultado[i] = char(65 + rand() % (122 - 65));
  cout << "Clave normal: " << resultado << endl;
  cout << "Clave binaria: " << CadenaABinario(resultado) << endl;

  return CadenaABinario(resultado);
}

string Encriptado(string cad_bin, string clave){
  string resultado;
  resultado.resize(cad_bin.size());
  for (int i = 0; i < cad_bin.size(); i++){
    if (cad_bin[i] != clave[i]){
      resultado[i] = '1';
    } else{
      resultado[i] = '0';
    }
  }
  return resultado;
}

void menu(void){
  cout << "--------------------" << endl;
  cout << "Elija una opción: " << endl;
  cout << "1) Vernam" << endl;
  cout << "2) RC4" << endl;
  cout << "3) ChaCha20" << endl;
  cout << "0) Salir" << endl;
  cout << "--------------------" << endl;
}

template<typename T>
void swap(vector<T> &x, int i, int j){
  T aux = x[i];
  x[i] = x[j];
  x[j] = aux;
}

// Implementa el algoritmo de encriptado RC4
// Recibe la cadena clave e imprime la cadena cifrante parcialmente hasta
//  devolver la cadena completa al final para su posterior uso

string RC4(string cadena, string clave){
  string resultado;
  vector<byte> S(256), K(256);

  for (int i = 0; i < 256; ++i){
    S[i] = byte(i);
    K[i] = byte(clave[i%clave.size()]);
  }

  int j = 0;
  for (int i = 0; i < 256; ++i){
    j = (j + int(S[i].to_ulong()) + int(K[i].to_ulong()))%256;
    swap(S,i,j);
  }
  // Generación de secuencia cifrante
  
  int i = 0, t = 0;
  j = 0;

  for (int c = 0; c < cadena.size(); ++c){

    i = (i + 1)%256;
    j = (j + int(S[i].to_ulong()))%256;

    swap(S,i,j);

    t = (int(S[i].to_ulong()) + int(S[j].to_ulong()))%256;

    cout << "Byte " << c + 1 << " de la secuencia cifrante: S[" << t << "] = " << int(S[t].to_ulong()) << " BIN: " << S[t] << endl;
    cout << "Byte " << c + 1 << " de texto original : M[" << c << "] = " << cadena[c] << " BIN: " << byte(cadena[c]) << endl;
    cout << "Byte " << c + 1 << " de texto cifrado : C[" << c << "] = " << Encriptado(byte(cadena[c]).to_string(),S[t].to_string()) << endl;
  
    resultado += Encriptado(byte(cadena[c]).to_string(),S[t].to_string());
  }
  return resultado;
}

palabra RDTL(palabra a, palabra b){
  return (((a) << (b)) | ((a) >> (32 - b)));
}

void QR(palabra &a, palabra &b, palabra &c, palabra &d){
  a += b;
  d ^= a;
  d = RDTL(d, 16);

  c += d;
  b ^= c;
  b = RDTL(b, 12);

  a += b;
  d ^= a;
  d = RDTL(d, 8);

  c += d;
  b ^= c;
  b = RDTL(b, 7);
}

palabra ChaCha20(palabra out[16], palabra in[16]){
  // int i;
  palabra x[16];
  for (int i = 0; i < 16; ++i)
    x[i] = in[i];

  for (int i = 0; i < ROUNDS; i += 2){

    QR(x[0], x[4], x[ 8], x[12]);
    QR(x[1], x[5], x[ 9], x[13]);
    QR(x[2], x[6], x[10], x[14]);
    QR(x[3], x[7], x[11], x[15]);

    QR(x[0], x[5], x[10], x[15]);
    QR(x[1], x[6], x[11], x[12]);
    QR(x[2], x[7], x[ 8], x[13]);
    QR(x[3], x[4], x[ 9], x[14]);
  }

  for (int i = 0; i < 16; ++i)
    out[i] = x[i] + in[i];
}

void show(palabra x[16]){
  cout << endl <<  "------------------------------------" << endl;
  for (int i = 0; i < 16; ++i){
    if(i % 4 == 0){
      cout << endl;
    }
    cout << u32ToString(x[i]) << " ";
  }
  cout  << endl << "------------------------------------" << endl;
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    menu();
    cin >> opt;
    
    switch (opt)
    {
    case 1:{
      string cadena;
      cout << "Introduzca el mensaje: ";
      cin >> cadena;
      string clave = ClaveAleatoria(cadena.size());

      string M_encriptado = Encriptado(CadenaABinario(cadena), clave);

      cout << "Mensaje encriptado en bin: " << M_encriptado << endl;
      cout << "Mensaje encriptado normal: " << BinarioACadena(M_encriptado) << endl;

      string M_desencriptado = Encriptado(M_encriptado, clave);

      cout << "Mensaje desencriptado en bin: " << M_desencriptado << endl;
      cout << "Mensaje desencriptado normal: " << BinarioACadena(M_desencriptado) << endl;
      break;
    }

    case 2:{
      string cadena, clave, resultado;
      cout << "Introduzca el mensaje: ";
      cin >> cadena;

      cout << "Introduzca la clave  : ";
      cin >> clave;
      
      resultado = RC4(cadena, clave);
      cout << "Secuencia cifrada: " << resultado << endl;

      break;
    }

    case 3:{
      string clave, resultado;
      palabra c1, c2, c3, c4, k1, k2, k3, k4, k5, k6, k7, k8, cu, n1, n2, n3;
      /*c1 = hexToUint32("56870716"); AL REVES
      c2 = hexToUint32("e6460233");
      c3 = hexToUint32("23d22697");
      c4 = hexToUint32("475602b6");*/

      /*c1 = hexToUint32("56870716");
      c2 = hexToUint32("e6460233");
      c3 = hexToUint32("23d22697");
      c4 = hexToUint32("475602b6");

      k1 = hexToUint32("00010203");
      k2 = hexToUint32("04050607");
      k3 = hexToUint32("08090a0b");
      k4 = hexToUint32("0c0d0e0f");
      k5 = hexToUint32("10111213");
      k6 = hexToUint32("14151617");
      k7 = hexToUint32("18191a1b");
      k8 = hexToUint32("1c1d1e1f");

      cu  = hexToUint32("10000000");

      n1 = hexToUint32("00000009");
      n2 = hexToUint32("0000004a");
      n3 = hexToUint32("00000000");*/


      c1 = hexToUint32("61707865");
      c2 = hexToUint32("3320646e");
      c3 = hexToUint32("79622d32");
      c4 = hexToUint32("6b206574");

      k1 = hexToUint32("03020100");
      k2 = hexToUint32("07060504");
      k3 = hexToUint32("0b0a0908");
      k4 = hexToUint32("0f0e0d0c");
      k5 = hexToUint32("13121110");
      k6 = hexToUint32("17161514");
      k7 = hexToUint32("1b1a1918");
      k8 = hexToUint32("1f1e1d1c");

      cu  = hexToUint32("00000001");

      n1 = hexToUint32("09000000");
      n2 = hexToUint32("4a000000");
      n3 = hexToUint32("00000000");

      palabra key[16] = {c1, c2, c3, c4, k1, k2, k3, k4, k5, k6, k7, k8, cu, n1, n2, n3};
      palabra out[16];

      show(key);

      cout << endl << "----------------------" << endl;

      ChaCha20(out, key);

      show(out);

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

/*      BUENO
       e4e7f110  15593bd1  1fdd0f50  c47120a3
       c7f4d1c7  0368c033  9aaa2204  4e6cd4c3
       466482d2  09aa9f07  05d7c214  a2028bd9
       d19c12b5  b94e16de  e883d0cb  4e3c50a2


        INICIALES
        BUENO
        61707865 3320646e 79622d32 6b206574
        03020100 07060504 0b0a0908 0f0e0d0c
        13121110 17161514 1b1a1918 1f1e1d1c
        00000001 09000000 4a000000 00000000
        MALO

        61707865 3320646e 79622d32 6b206574 
        30201000 70605040 b0a09080 f0e0d0c0 
        31211101 71615141 b1a19181 f1e1d1c1 
        00000001 90000000 a4000000 00000000

*/