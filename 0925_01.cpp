#include <iostream>
#include <cstring>

using namespace std;

const int ERROR = -1;
const int SUCCESS = 0;

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
    return ERR;
  }

  tempNodo->dato = paramDato;

  tempNodo->next = paramHead;
  paramHead = tempNodo;

  return SUCCESS;
};

int cercaData(char dataToSearch[], char *listaDateAppelli[], int size) {
  for(int i=0;i<size; i++) {
    char *thisForData = listaDateAppelli[i];
    bool isDataFound = strcmp(dataToSearch, thisForData) == 0;
    if(isDataFound) return i;
  }
  return ERROR;
}

void CalcolaConteggiAppelli(NODO *lista, char *listaDateAppelli[], int size, int listaConteggi[]) {  
  int indexData;

  for(NODO *p=lista; p != NULL; p = p->next) {
    indexData = cercaData(p->dato.dataAppello, listaDateAppelli, size);
    
    if(indexData == ERROR) continue;
    listaConteggi[indexData]++;
  }
}

int calcolaMaxPos(int listaConteggi[], int size) {
  int maxPos = ERRORE;
  int maxVal = 0;

  for(int i=0; i<size; i++) {
    int thisConteggio = listaConteggi[i];
    bool isBiggerThanBefore = thisConteggio > maxVal;
    
    if(!isBiggerThanBefore) continue;
    
    maxPos = i;
    maxVal = thisConteggio;
  }

  return maxPos;
}

void 


