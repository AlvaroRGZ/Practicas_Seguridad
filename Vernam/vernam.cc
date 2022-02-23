#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <time.h>

using namespace std;

string CadenaABinario(string cadena){
  string resultado;
  for (int i = 0; i < cadena.size(); i++){
    resultado += bitset<8>(cadena.c_str()[i]).to_string();
  }
  return resultado;
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

string BinarioACadena(string cadena){
  string resultado;
  int Ncaracter = cadena.size()/8;
  for (int i = 0; i < Ncaracter; i++){
    string caracter = cadena.substr(i*8, (i+1)*8);
    bitset<8> aux = bitset<8>(caracter);
    char car = char(int(aux.to_ulong()));
    resultado += car;
  }
  return resultado;
}

void menu(void){
  cout << "--------------------" << endl;
  cout << "Elija una opción: " << endl;
  cout << "1) Introducir cadena" << endl;
  cout << "0) Salir" << endl;
  cout << "--------------------" << endl;
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