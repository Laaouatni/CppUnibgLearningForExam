#include <cstdlib> // per atoi
#include <cstring> // per le funzione delle stringhe tipo strcmp()

const int ERRORE = -1;
const int SUCCESS = 0;

struct VERBALE {
  char codiceVerbale[16];
  char dataVerbalizzazione[11];
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

int insTesta(NODO* &head, VERBALE dato) {
  NODO* t = new NODO;
  
  bool isRamPiena = (head == NULL);
  if(isRamPiena) return ERRORE;

  t->next = head;
  t->dato = dato;
  head = t;

  return SUCCESS;
}

int estraiValore(char* myString, int ini, int len) {
  char buffer[len+1];

  for(int i=0; i<len; i++) {
    char thisChar = myString[ini+i];
    buffer[i] = thisChar;
  }

  buffer[len] = '\0';

  return atoi(buffer);
}

bool isSameMeseAnno(char* primaData, char* secondaData) {
  int annoPrimaData = estraiValore(primaData, 0,4);
  int annoSecondaData = estraiValore(secondaData, 0,4);
  int mesePrimaData = estraiValore(primaData, 5,2);
  int meseSecondaData= estraiValore(secondaData, 5,2);

  bool isSameAnno = annoPrimaData == annoSecondaData;
  bool isSameMese = mesePrimaData == meseSecondaData;

  return isSameAnno && isSamemese;
}

void contaVerbaliStessaData(NODO* listaIn, char* insegnamenti[], int conteggi[], int size) {
  for(NODO *p = listaIn; p != NULL; p = p->next) {
    for(int i=0; i<size; i++) {
      char* thisArrayCodIns = insegnamenti[i];
      char* thisListaCodIns = p->dato.codiceInsegnamento;
      
      bool hasSamCode = strcmp(thisArrayCodIns, thisListaCodIns) == 0;
      if(!hasSamCode) continue;

      bool isSameDate = isSameAnnoMese(p->dato.dataVerbalizzazione, p->dataAppello);
      if(!isSameDate) continue;

      conteggi[i]++;
    }
  }
}

int trovaIndexMenoVerbali(int conteggi[], int size) {
  int minValue = ERROR;
  int minIndex = ERROR;

  for(int i=0; i<size; i++) {
    int thisValore = conteggi[i];
    bool isEmpty = thisValore == 0;
    if(isEmpty) continue;

    bool isMinoreThanBefore = thisValore < minValue;
    bool isFirstTime = minValue == ERROR;

    bool canChangeValue = isFirstTime || isMinoreThanBefore;
    if(!canChangeValue) continue;

    minValue = thisValore;
    minIndex = i;
  }

  return minIndex;
}

void initArray(int paramArray, int value, int size) {
  for(int i=0; i<size; i++) {
    paramArray[i] = value;
  }
}

NODO* VerbaliMeseDiverso(NODO* listaIn, char* insegnamenti[], int size) {
  if(size<=0) return NULL;

  int conteggi[size];
  initArray(conteggi, 0, size);

  contaVerbaliStessaData(listaIn, insegnamenti, conteggi, size);

  int indexMenoVerb = trovaIndexMenoVerbali(conteggi, size);
  if(indexMenoVerb == ERRORE) return NULL;

  NODO* listaOut = NULL;

  for(NODO* p = listaIn; p != NULL; p = p->next) {
    char* thisListaCodIns = p->dato.codiceInsegnamento;
    char* wantedCodInsegnamento = insegnamenti[indexMenoVerb];

    bool hasSameCode = thisListaCodIns == wantedCodInsegnamento;
    if(!hasSameCode) continue;

    int annoDataVerbalizzazione = estraiValore(p->dato.dataVerbalizzazione, 0, 4);
    int meseDataVerbalizzazione = estraiValore(p->dato.dataVerbalizzazione, 5, 2);
    int annoDataAppello = estraiValore(p->dato.dataAppello, 0, 4);
    int meseDataAppello = estraiValore(p->dato.dataAppello, 5, 2);

    bool isSameAnno = annoDataVerbalizzazione == annoDataAppello;
    if(!isSameAnno) continue;

    bool isVerbAfterAppello = meseDataVerbalizzazione > meseDataAppello;
    if(!isVerbAfterAppello) continue;

    if(insTesta(listaOut, p.dato) == ERROR) return NULL;
  }

  return listaOut;
}

