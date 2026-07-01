#include <cstdlib> // atoi
#include <cstring> // strcmp

struct VERBALE {
  char codiceVerbale[16];
  char dataEmissioneVerbale[11];
  char dataAppelloEsame[11];
  char dataSuperamentoEsame[11];
  char codiceInsegnamento[11];
  char nomeDocente[51];
  char matricolaStudente[8];
  int voto;
};

struct NODO {
  VERBALE dato;
  NODO* next;
};

const int ERRORE = -1;
const int SUCCESS = 0;

int insTesta(NODO* &heap, VERBALE dato) {
  NODO* t = new NODO;
  bool isRamPiena = (t == NULL);
  if(isRamPiena) return ERRORE;

  t->next = heap;
  t->dato = dato;

  heap = t;

  return SUCCESS;
};

void initArray(int array[], int value, int size) {
  for(int i=0; i<size; i++) {
    array[i] = value;
  };
};

int estraiValore(char* dataString, int ini, int len) {
  const int BUFFER_LENGTH = len+1;
  char buffer[BUFFER_LENGTH];

  for(int i=0; i<len; i++) {
    char thisChar = dataString[ini+i];
    buffer[i] = thisChar;
  };

  buffer[len] = '\0';

  return atoi(buffer);
};

void contaAppelliStessaData(NODO* lista, char* dateAppelli[], int conteggi[], int size) {
  for(NODO* p = lista; p != NULL; p = p->next) {
    char* thisDataAppello = p->dato.dataAppelloEsame;
    for(int i=0; i<size; i++) {
      char* thisForDataAppello = dateAppelli[i];
      bool isSameDate = strcmp(thisDataAppello, thisForDataAppello) == 0;
      if(!isSameDate) continue;

      conteggi[i]++;
    }
  }
}

int trovaIndexDataMax(int conteggi[], int size) {
  int maxValue = ERRORE;
  int maxIndex = ERRORE;

  for(int i=0; i<size; i++) {
    int thisConteggio = conteggi[i];
    bool isFirstTime = maxValue == ERRORE;
    bool isBiggerThanBefore = thisConteggio > maxValue;
    bool canChangeValue = isFirstTime || isBiggerThanBefore;
    if(!canChangeValue) continue;

    maxValue = thisConteggio;
    maxIndex = i;
  }

  return maxIndex;
}

int insTestaSeData(NODO* &listaOut, NODO* lista, char* wantedDataAppello) {
  for(NODO* p = lista; p != NULL; p = p->next) {
    char* thisListaDataAppello = p->dato.dataAppelloEsame;
    bool isSameDate = strcmp(thisListaDataAppello, wantedDataAppello) == 0;
    if(!isSameDate) continue;
    if(insTesta(listaOut, p->dato) == ERRORE) return ERRORE;
  };

  return SUCCESS;
};

NODO* copiaAlcuniVerbali(NODO* lista1, NODO* lista2, char* dateAppelli[], int size) {
  if(size<=0) return NULL;
  int conteggi[size];
  initArray(conteggi, 0, size);

  contaAppelliStessaData(lista1, dateAppelli, conteggi, size);
  contaAppelliStessaData(lista2, dateAppelli, conteggi, size);

  int indexMax = trovaIndexDataMax(conteggi, size);
  if(indexMax == ERRORE) return NULL;

  char* wantedDataAppello = dateAppelli[indexMax];

  NODO* listaOut = NULL;
  if(insTestaSeData(listaOut, lista1, wantedDataAppello) == ERRORE) return NULL;
  if(insTestaSeData(listaOut, lista2, wantedDataAppello) == ERRORE) return NULL;

  return listaOut;
}
