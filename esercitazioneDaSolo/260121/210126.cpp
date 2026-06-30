#include <cstring>
#include <cstdlib>

const int ERRORE = -1;
const int SUCCESS = 0; 

struct VERBALE {
  char codice[16]; // codiceVerbale
  char dataEmissioneVerbale[11];  
  char dataAppello[11];
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

int insTesta(NODO* &heap, VERBALE dato) {
  NODO* t = new NODO;
  bool isRamPiena = (t == NULL);
  if(isRamPiena) return ERRORE;

  t->next = heap;
  t->dato = dato;
  heap = t;

  return SUCCESS;
};

void initIntArray(int paramArray[], int value, int size) {
  for(int i=0; i<size; i++) {
    paramArray[i] = value;
  };
};

int estraiValore(char* dataString, int ini, int len) {
  char buffer[len];

  for(int i=0; i<len; i++) {
    char thisChar = dataString[ini+i];
    buffer[i] = thisChar;
  };
  
  buffer[len] = '\0';

  return atoi(buffer);
};

void contaVerbali2025(NODO* lista, char* insegnamenti[], int conteggi[], int size) {
  for(NODO* p=lista; p != NULL; p=p->next) {
    char* thisListaCodIns = p->dato.codiceInsegnamento;

    int thisAnnoAppelloEsame = estraiValore(p->dato.dataAppello, 0, 4);
    bool is2025 = thisAnnoAppelloEsame == 2025;
    if(!is2025) continue;

    for(int i=0; i<size; i++) {
      char* thisForCodIns = insegnamenti[i];
      bool isSameCodIns = strcmp(thisListaCodIns, thisForCodIns) == 0;
      if(!isSameCodIns) continue;

      conteggi[i]++;
    }
  }
}
 
int insMax(int conteggi[], int size) {
  int maxValue = ERRORE;
  int maxIndex = ERRORE;

  for(int i=0; i<size; i++) {
    int thisConteggioValue = conteggi[i];
    bool isBiggerThanBefore = thisConteggioValue > maxValue;
    bool isFirstTime = maxValue == ERRORE;

    bool canUpdateValue = isFirstTime || isBiggerThanBefore;
    if(!canUpdateValue) continue;

    maxValue = thisConteggioValue;
    maxIndex = i;
  }

  return maxIndex;
}

NODO* copiaAlcuniVerbali(NODO* lista1, NODO* lista2, char* insegnamenti[], int size) {
  if(size<=0) return NULL;

  int conteggi[size];

  initIntArray(conteggi, 0, size);
  contaVerbali2025(lista1, insegnamenti, conteggi, size);
  contaVerbali2025(lista2, insegnamenti, conteggi, size);

  int foundedInsMax = insMax(conteggi, size);
  if(foundedInsMax == ERRORE) return NULL;
  char* foundedCodiceIns = insegnamenti[foundedInsMax];

  NODO* listaOut = NULL;
  
  for(NODO* p = lista1; p != NULL; p = p->next) {
    char* thisListaInsegnamento = p->dato.codiceInsegnamento;
    int thisListaAnno = estraiValore(p->dato.dataAppello, 0, 4);
    bool is2025 = thisListaAnno == 2025;
    if(!is2025) continue;
    bool isSameCodIns = strcmp(foundedCodiceIns, thisListaInsegnamento) == 0;
    if(!isSameCodIns) continue;

    if(insTesta(listaOut, p->dato) == ERRORE) return NULL;
  }

  return listaOut;
}