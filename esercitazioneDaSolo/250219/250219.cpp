#include <cstring>
#include <cstdlib>

struct VERBALE {
  char codiceVerbale[16];
  char dataVerbalizzazione[11];
  char dataAppello[11];
  char dataSuperamentoEsame[11];
  char codiceInsegnamento[11];
  char nomeDocente[51];
  int voto;
};

struct NODO  {
  VERBALE dato;
  NODO* next;
};

const int ERRORE = -1;
const int SUCCESS = 0;

int insTesta(NODO* &heap, VERBALE dato) {
  NODO* t=new NODO;
  bool isRamPiena = (t == NULL);
  if(isRamPiena) return ERRORE;

  t->dato = dato;
  t->next = heap;
  heap = t;

  return SUCCESS;
}

int estraiValore(char* paramString, int ini, int len) {
  const int BUFFER_SIZE = len+1;
  char buffer[BUFFER_SIZE];

  for(int i=0; i<len; i++) {
    char thisChar = paramString[ini+i];
    buffer[i] = thisChar;
  };

  buffer[len] = '\0';

  return atoi(buffer);
}

void initArray(int myArray[], int value, int size) {
  for(int i=0; i<size; i++) {
    myArray[i] = value;
  }
}

void calcolaMediaVerbali(NODO* listaIn, char* insegnamenti[], float medie[], int size) {
  int somme[size];

  initArray(somme, 0, size);

  for(NODO* p = listaIn; p != NULL; p = p->next) {
    char* thisListaInsegnamento = p->dato.codiceInsegnamento;

    int meseAppello = estraiValore(p->dato.dataAppello, 5, 2);
    int annoAppello = estraiValore(p->dato.dataAppello, 0, 4);
    int meseVerb = estraiValore(p->dato.dataVerbalizzazione, 5,2);
    int annoVerb = estraiValore(p->dato.dataVerbalizzazione, 0,4);

    bool isSameAnno = annoAppello == annoVerb;
    bool isSameMese = meseAppello == meseVerb;

    bool isSameDate = isSameAnno && isSameMese;
    if(!isSameDate) continue;

    for(int i=0; i<size; i++) {
      char* thisForInsegnamento = insegnamenti[i];
      bool isSameIns = strcmp(thisListaInsegnamento, thisForInsegnamento) == 0;
      if(!isSameIns) continue;
      somme[i] += p->dato.voto; 
    }
  }

  for(int i=0; i<size; i++) {
    medie[i] = (float)somme[i]/(float)size;
  }
}

int trovaIndexMediaMax(float medie[], int size) {
  float mediaMax = ERRORE;
  int indexMax = ERRORE;

  for(int i=0; i<size; i++) {
    float thisMedia = medie[i];
    bool isMediaBiggerThanBefore = thisMedia > mediaMax;
    bool isFirstTime = mediaMax == ERRORE;
    bool canChangeValue = isFirstTime || isMediaBiggerThanBefore;
    if(!canChangeValue) continue;

    mediaMax = thisMedia;
    indexMax = i;
  }

  return indexMax;
}

NODO* VerbaliVotiAlti(NODO* listaIn, char* insegnamenti[], int size) {
  if(size<=0) return NULL;
  float medie[size];
  calcolaMediaVerbali(listaIn, insegnamenti, medie, size);
  int foundedIndexMediaMax = trovaIndexMediaMax(medie, size);
  if(foundedIndexMediaMax == ERRORE) return NULL;
  float foundedMediaAlta = medie[foundedIndexMediaMax];
  char* wantedInsegnamento = insegnamenti[foundedIndexMediaMax];

  NODO* listaOut = NULL;

  for(NODO* p = listaIn; p != NULL; p = p->next) {
    char* thisListaInsegnamento = p->dato.codiceInsegnamento;
    bool haveSameCodIns = strcmp(thisListaInsegnamento, wantedInsegnamento) == 0;
    if(!haveSameCodIns) continue;

    bool isVotoBiggerThanMedia = (float)p->dato.voto > foundedMediaAlta;
    if(!isVotoBiggerThanMedia) continue;

    if(insTesta(listaOut, p->dato) == ERRORE) return NULL;
  }

  return listaOut;
};