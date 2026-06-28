#include <iostream>
#include <cstring>

using namespace std;

struct VERBALE {
  char codice[16];
  char dataEmissione[11];
  char dataAppello[11];
  char dataSuperamentoEsame[11];
  char codiceInsegnamento[11];
  char nomeDocente[51];
  char matricolaStudente[8];
  int voto;
};

struct NODO {
  VERBALE dato;
  NODO *next;
};

int insTesta(NODO *&paramHead, VERBALE paramDato) {
  NODO *tempNodo = new NODO;
  
  bool isRamPiena = t == NULL;
  if(isRamPiena) {
    cout << "Ram Piena";
    return -1;
  }

  tempNodo->dato = paramDato;

  tempNodo->next = paramHead;
  paramHead = tempNodo;

  return 0;
};

int cercaData(char paramData[], char *paramDateAppelli[], int size) {
  for
}


