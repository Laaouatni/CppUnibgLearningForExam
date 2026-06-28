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

int insTesta(NODO* &head, VERBALE datoToInserire) {
  NODO *tempNodo = new NODO;
  
  bool isRamPiena = tempNodo == NULL;
  if(isRamPiena) return ERROR;

  tempNodo->dato = datoToInserire;
  tempNodo->next = head;

  head = tempNodo;

  return SUCCESS;
};

int cercaData(char* dataToSearch, char* listaDateAppelli[], int size) {
  for(int i=0;i<size; i++) {
    const char* thisDataAppello = listaDateAppelli[i];
    const bool isDataAppelloFound = strcmp(dataToSearch, thisDataAppello) == 0;

    if(isDataAppelloFound) return i;
  }

  return ERROR;
}

void calcolaConteggiAppelli(NODO* lista, char *listaDateAppelli[], int listaConteggi[], int size) {  
  int indexData;

  for(NODO *p=lista; p != NULL; p = p->next) {
    indexData = cercaData(p->dato.dataAppello, listaDateAppelli, size);
    
    if(indexData == ERROR) continue;
    listaConteggi[indexData]++;
  }
}

int calcolaMaxPos(int listaConteggi[], int size) {
  int maxPos = ERROR;
  int maxVal = 0;

  for(int i=0; i<size; i++) {
    const int thisConteggio = listaConteggi[i];
    const bool isBiggerThanBefore = thisConteggio > maxVal;
    
    if(!isBiggerThanBefore) continue;
    
    maxPos = i;
    maxVal = thisConteggio;
  }

  return maxPos; // se non trovo maxPos allora rimane il valore -1 di errore di default (non servono altri if)
}

int copiaSeDataMax(NODO *lista, char* dataMax, NODO *&listaOut) {
  for(NODO *p = lista; p != NULL; p = p->next) {
    char* thisDataAppello = p->dato.dataAppello;
    bool isThisDataMax = strcmp(thisDataAppello, dataMax) == 0;

    if(!isThisDataMax) continue;
    if(insTesta(listaOut, p->dato) == ERROR) return ERROR;
  }
  return SUCCESS;
}

NODO* copiaAlcuniVerbali(NODO* lista1, NODO* lista2, char* listaDateAppelli[], int size) {
  if(size <= 0) return NULL;

  int conteggi[size];
  NODO* listaOut=NULL;

  // inizializzazione
  for(int i=0; i<size; i++) { conteggi[i]=0; };

  // riempi array conteggi con numero volte stessa data è stata trovata
  calcolaConteggiAppelli(lista1, listaDateAppelli, conteggi, size);
  calcolaConteggiAppelli(lista2, listaDateAppelli, conteggi, size);

  // troviamo indice data con maggior appelli
  int maxPos = calcolaMaxPos(conteggi, size);
  if(maxPos == ERROR) return NULL;

  // troviamo stringa con la data che vogliamo
  char* dataMax = listaDateAppelli[maxPos];

  if(copiaSeDataMax(lista1, dataMax, listaOut) == ERROR) return NULL;
  if(copiaSeDataMax(lista2, dataMax, listaOut) == ERROR) return NULL;

  return listaOut;
}


