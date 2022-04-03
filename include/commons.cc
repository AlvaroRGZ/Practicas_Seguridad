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
#include <utility>

using namespace std;

typedef bitset<8> Byte;
typedef uint32_t palabra;

string BinarioACadena(string cadena){
  string resultado;
  int Ncaracter = cadena.size()/8;
  for (int i = 0; i < Ncaracter; i++){
    string caracter = cadena.substr(i*8, (i+1)*8);
    Byte aux = Byte(caracter);
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

// De cadena hexadecimal al cadena binario
string HexToBin(string cadena) {
  string resultado;
  for (int i = 0; i < cadena.size(); i++){
    switch (cadena[i]){
      case 'a':
        resultado += bitset<4>(10).to_string();
        break;
      case 'b':
        resultado += bitset<4>(11).to_string();
        break;
      case 'c':
        resultado += bitset<4>(12).to_string();
        break;
      case 'd':
        resultado += bitset<4>(13).to_string();
        break;
      case 'e':
        resultado += bitset<4>(14).to_string();
        break;
      case 'f':
        resultado += bitset<4>(15).to_string();
        break;
      default:
        resultado += bitset<4>(cadena[i]).to_string();
    }
  }
  return resultado;
}

string CadenaABinario(string cadena){
  string resultado;
  for (int i = 0; i < cadena.size(); i++){
    resultado += Byte(cadena.c_str()[i]).to_string();
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
