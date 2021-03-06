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

// Pasa la cadena de binario a cadena hexadecimal
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

// Convierte la cadena de entrada a little endian
string reverse(string r) {
  string s;
  int Ncaracter = r.size()/2;
  for (int i = r.size() - 1; i >= 1; i -= 2){
    s += r.substr(i-1, 1) + r.substr(i, 1);
  }
  return s;
}

// Convierte la palabra en little endian a uint32_t
palabra hexToUint32(string cadena){ 
  return palabra(stoul(reverse(cadena), nullptr, 16));
}

// Convierte la cadena a uint32_t
palabra hexToUint32direct(string cadena){ 
  return palabra(stoul((cadena), nullptr, 16));
}

string u32ToString(palabra pal){
  bitset<32> x(pal);
  return BinHexACadena(x.to_string());
}

string uint32ToHex(string cadena){
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
  cout << "Elija una opci??n: " << endl;
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


// Desplazamiento lateral de la palabra a b bits
palabra RDTL(palabra a, palabra b){
  return (((a) << (b)) | ((a) >> (32 - b)));
}

// Realiza la operacion Quarte Round sobre las 4 palabras de entrada
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

// Muestra las matrices
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
      string clave, resultado;
      palabra c1, c2, c3, c4, k1, k2, k3, k4, k5, k6, k7, k8, cu, n1, n2, n3;

      c1 = hexToUint32direct("61707865");
      c2 = hexToUint32direct("3320646e");
      c3 = hexToUint32direct("79622d32");
      c4 = hexToUint32direct("6b206574");

      k1 = hexToUint32("00010203");
      k2 = hexToUint32("04050607");
      k3 = hexToUint32("08090a0b");
      k4 = hexToUint32("0c0d0e0f");
      k5 = hexToUint32("10111213");
      k6 = hexToUint32("14151617");
      k7 = hexToUint32("18191a1b");
      k8 = hexToUint32("1c1d1e1f");

      cu = hexToUint32("01000000");

      n1 = hexToUint32("00000009");
      n2 = hexToUint32("0000004a");
      n3 = hexToUint32("00000000");

      palabra key[16] = {c1, c2, c3, c4, k1, k2, k3, k4, k5, k6, k7, k8, cu, n1, n2, n3};
      palabra out[16];

      show(key);

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