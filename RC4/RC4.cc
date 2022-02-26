#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef bitset<8> byte;

string CadenaABinario(string cadena){
  string resultado;
  for (int i = 0; i < cadena.size(); i++){
    resultado += byte(cadena.c_str()[i]).to_string();
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
    byte aux = byte(caracter);
    char car = char(int(aux.to_ulong()));
    resultado += car;
  }
  return resultado;
}

void menu(void){
  cout << "--------------------" << endl;
  cout << "Elija una opción: " << endl;
  cout << "1) Vernam" << endl;
  cout << "2) RC4" << endl;
  cout << "0) Salir" << endl;
  cout << "--------------------" << endl;
}

void swap(vector<byte> &x, int i, int j){
  byte aux = x[i];
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

/*

  cout << "S = [ ";
  for (int i = 0; i < 256; ++i){
    cout << S[i].to_string() << " ";
  }
  cout << "]" << endl;

  cout << "K = [ ";
  for (int i = 0; i < 256; ++i){
    cout << K[i].to_string() << " ";
  }
  cout << "]" << endl;

*/