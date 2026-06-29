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

// listaDate è listaDateAppelli
int cercaData(char* dataToSearch, char* listaDate[], int size) {
  for(int i=0;i<size; i++) {
    const char* thisData = listaDate[i];
    const bool isDataFound = strcmp(dataToSearch, thisData) == 0;

    if(isDataFound) return i;
  }

  return ERROR;
}

// listaDate è listaDateAppelli
// calcolaConteggi è calcolaConteggiAppelli
void calcolaConteggi(NODO* lista, char *listaDate[], int listaConteggi[], int size) {  
  int indexData;

  for(NODO *p=lista; p != NULL; p = p->next) {
    indexData = cercaData(p->dato.dataAppello, listaDate, size);
    
    if(indexData == ERROR) continue;
    listaConteggi[indexData]++;
  }
}

int calcolaQUALCOSA(int listaConteggi[], int size) {
  int VALUETORETURN=INITIALVALUE;

  for(int i=0; i<size; i++) {
    const int thisConteggio = listaConteggi[i];
    const bool isCONDIZIONE = CONDIZIONE;
    
    if(!isCONDIZIONE) continue;
    
    LOGICA
  }

  return VAUETORETURN;
}

int COPIACONDIZIONE(NODO* lista, char* dataMax, NODO* &listaOut) {
  for(NODO *p = lista; p != NULL; p = p->next) {
    char* thisData = p->dato.dataAppello;
    bool isThisCONDIZIONE = CONDIZIONE;

    if(!isThisCONDIZIONE) continue;
    if(insTesta(listaOut, p->dato) == ERROR) return ERROR;
  }
  return SUCCESS;
}

void initInt(int arrayToInit[], int val, int size) {
  for(int i=0; i<size; i++) {
    arrayToInit[i] = val;
  }
}

// listaDate è listaDateAppelli
NODO* copiaAlcuniVerbali(NODO* lista1, NODO* lista2, char* listaDate[], int size) {
  if(size <= 0) return NULL;

  int conteggi[size];
  NODO* listaOut=NULL;

  // inizializzazione
  arrayToInit(conteggi, 0, size);

  // riempi array conteggi con numero volte stessa data è stata trovata
  calcolaConteggi(lista1, listaDate, conteggi, size);
  calcolaConteggi(lista2, listaDate, conteggi, size);

  int QUALCOSA = CALCOLAQUALCOSA(conteggi, size);
  if(QUALCOSA == ERROR) return NULL;
  //char* dataMax = listaDateAppelli[maxPos];

  if(COPIACONCONDIZIONI(lista1, ALTRIPARAMETRI, listaOut) == ERROR) return NULL;
  if(COPIACONCONDIZIONI(lista2, ALTRIPARAMETRI, listaOut) == ERROR) return NULL;

  return listaOut;
}

/*
  IN ALTRI TEMI D'ESAMI CHIEDONO PURE
*/

float calcolaMedia(int conteggi[], int size) {
  int somma = 0;
  for(int i=0; i<size; i++) {
    const int thisConteggio = conteggi[i];
    somma += thisConteggio;
  }
  return (float)somma/size; // ricorda float se no, non esce il valore in float
}
