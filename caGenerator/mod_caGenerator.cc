#include "../include/commons.cc"

using namespace std;

typedef bitset<10> secuencia;

// Nos devuelve los dos bits que se utilizaran en
// el generador C/A
pair<int, int> selectorGPS(int ID){
  switch(ID){
    case 1: 
      return pair<int, int>(2,6);
    break;
    case 2: 
      return pair<int, int>(3,7);
    break;
    case 3: 
      return pair<int, int>(4,8);
    break;
    case 4: 
      return pair<int, int>(5,9);
    break;
    case 5: 
      return pair<int, int>(1,9);
    break;
    case 6: 
      return pair<int, int>(2,10);
    break;
    case 7: 
      return pair<int, int>(1,8);
    break;
    case 8: 
      return pair<int, int>(2,9);
    break;
    case 9: 
      return pair<int, int>(3,10);
    break;
    case 10: 
      return pair<int, int>(2,3);
    break;
    case 11: 
      return pair<int, int>(3,4);
    break;
    case 12: 
      return pair<int, int>(5,6);
    break;
    case 13: 
      return pair<int, int>(6,7);
    break;
    case 14: 
      return pair<int, int>(7,8);
    break;
    case 15: 
      return pair<int, int>(8,9);
    break;
    case 16: 
      return pair<int, int>(9,10);
    break;
    case 17: 
      return pair<int, int>(1,4);
    break;
    case 18: 
      return pair<int, int>(2,5);
    break;
    case 19: 
      return pair<int, int>(3,6);
    break;
    case 20: 
      return pair<int, int>(4,7);
    break;
    case 21: 
      return pair<int, int>(5,8);
    break;
    case 22: 
      return pair<int, int>(6,9);
    break;
    case 23: 
      return pair<int, int>(1,3);
    break;
    case 24: 
      return pair<int, int>(4,6);
    break;
    case 25: 
      return pair<int, int>(5,7);
    break;
    case 26: 
      return pair<int, int>(6,8);
    break;
    case 27: 
      return pair<int, int>(7,9);
    break;
    case 28: 
      return pair<int, int>(8,10);
    break;
    case 29: 
      return pair<int, int>(1,6);
    break;
    case 30: 
      return pair<int, int>(2,7);
    break;
    case 31: 
      return pair<int, int>(3,8);
    break;
    case 32: 
      return pair<int, int>(4,9);
    break;
    default:
      return pair<int, int>(2,6);
  }
}

// Desplazamiento hacia la derecha de 1 bit
// de la secuencia x
void RDRL(secuencia &x) {
  x >>= 1;
}

// Genera la secuancia cifrante C/A de longitud lenght
// con el satelite satID, Mostramos traza o no segun trace
string caGenerator(int satID1, int satID2, int lenght, bool trace){

  // Obtenemos los indices del satelite
  pair<int, int> x = selectorGPS(satID1);
  int fb1 = 10 - x.first, sb1 = 10 - x.second; 

  pair<int, int> y = selectorGPS(satID2);
  int fb2 = 10 - y.first, sb2 = 10 - y.second; 

  string output;

  // Inicializacion | g1 y g2 all bits set
  secuencia g1, g2;
  int re1, re2;
  int ca1, ca2, caBit;
  g1.set();
  g2.set();

  for (int i = 0; i < lenght; i++) {
    re1 = g1[  7] ^ g1[  0];
    ca1 = g1[fb1] ^ g1[sb1];
    RDRL(g1);
    g1.set(9,re1);  // Realimentamos con r1 por la cabeza

    re2 = g2[8] ^ g2[7] ^ g2[4] ^ g2[2] ^ g2[1] ^ g2[0];
    ca2 = g2[fb2] ^ g2[sb2];
    RDRL(g2);
    g2.set(9, re2); // Realimentamos con r2 por la cabeza
    
    // Añadimos el bit a la cadena resultado
    output += bitset<1>(ca1 ^ ca2).to_string(); 

    if (trace) { // Imprime los datos de cada iteracion 00001100100111
      cout << "re1: " << re1 << " ca1: "<< ca1 << endl;
      cout << "sec = " << g1.to_string() << endl;
      cout << "re2: " << re2 << " ca2: "<< ca2 << endl;
      cout << "sec2 = " << g2.to_string() << endl;
      cout << "caBit = " << (ca1+ ca2)%2 << endl << endl;
    }
  }
  return output;
}

int main (void){

  bool quit = false;
  int opt;

  while(!quit){

    cout << "--------------------" << endl;
    cout << "Elija una opción: " << endl;
    cout << "1) caGenerator" << endl;
    cout << "0) Salir" << endl;
    cout << "--------------------" << endl;

    cin >> opt;
    
    switch (opt)
    {

    case 1:{
      bool t; int s1, s2, l = 14;
      cout << "Trace? (0 | 1) > "; cin >> t; cout << endl;
      cout << "sat1? > "; cin >> s1; cout << endl;
      cout << "sat2? > "; cin >> s2; cout << endl;
      cout << "Secuencia C/A PRN1 = " << caGenerator(s1, s2, l, t) << endl;
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