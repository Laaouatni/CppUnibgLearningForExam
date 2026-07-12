#include <cstdlib>
#include <cstring>

struct VERBALE {
    char codiceVerbale[16];
    char dataVerbalizzazione[11];
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

int insTesta(NODO* &head, VERBALE dato) {
    NODO* t = new NODO;
    bool isRamPiena = (t == NULL);
    if(!isRamPiena) return ERRORE;

    t->dato = dato;
    t->next = head;
    head = t;

    return SUCCESS;
};

int estraiValore(char* paramString, int ini, int len) {
    char buffer[len+1];

    for(int i=0; i<len; i++) {
        const char thisChar = paramString[ini+len];
        buffer[i] = thisChar;
    };
    buffer[len] = '\0';

    return atoi(buffer);
};

bool isSameMeseAnno(char* firstData, char* secondData) {
    int firstAnno = estraiValore(firstData, 0,4);
    int secondAnno = estraiValore(secondData, 0,4);
    int firstMese = estraiValore(firstData, 5,2);
    int secondMese = estraiValore(secondData, 5,2);

    bool isSameAnno = firstAnno == secondAnno;
    bool isSameMese = firstMese == secondMese;

    bool isWantedDate = isSameAnno && isSameMese;

    return isWantedDate;
}

void initArray(int array[], int value, int size) {
    for(int i=0; i<size; i++) {
        array[i] = value;
    };
}

int contaVerbaliStessoAnno(NODO* listaIn, int conteggi[], char* insegnamenti[], int size) {
    for(NODO* p = listaIn; p != NULL; p = p->next) {
        char* pDataAppello = p->dato.dataAppello;
        char* pInsegnamento = p->dato.codiceInsegnamento;
        for(int i=0; i<size; i++) {
            char* thisInsegnamento = insegnamenti[i];
            bool isSameInsegnamento = strcmp(pInsegnamento, thisInsegnamento) == 0;
            if(!isSameInsegnamento) continue;
            bool isSameDate = isSameMeseAnno(pDataAppello, thisInsDataAppello);
            if(!isSameDate) continue;
            conteggi[i]++;
        }
    }
}

int insMin(int conteggi[], int size) {
    int minIndex = ERRORE;
    int minValue = ERRORE;

    for(int i=0; i<size; i++) {
        int thisValue = conteggi[i];
        bool isEmpty = thisValue == 0;
        if(isEmpty) continue;

        bool isFirstTime = minValue == ERRORE;
        bool isSmallerThanBefore = thisValue<minValue;

        bool canUpdate = isFirstTime || isSmallerThanBefore;
        
        if(!canUpdate) continue;
        minIndex = i;
        minValue = thisValue;
    };

    return minIndex;
};

NODO* VerbaliMeseDiverso(NODO* listaIn, char* insegnamenti[], int size) {
    if(size<=0) return NULL;

    int conteggi[size];
    initArray(conteggi, 0, size);
    contaVerbaliStessoAnno(listaIn, conteggi, insegnamenti, size);
    
    int minIndex = insMin(conteggi, size);
    
    bool isMinIndexFound = minIndex != ERRORE;
    if(!isMinIndexFound) return NULL;

    char* wantedInsegnamento = insegnamenti[minIndex];

    NODO* listaOut = NULL;

    for(NODO* p=listaIn; p!=NULL; p=p->next) {
        char* pInsegnamento = p->dato.codiceInsegnamento;
        bool isWantedInsegnamento = strcmp(pInsegnamento, wantedInsegnamento) == 0;
        if(!isWantedInsegnamento) continue;
        
        char* thisDataVerb = p->dato.dataVerbalizzazione;
        char* thisDataAppello = p->dato.dataAppello;

        int appelloAnno = estraiValore(thisDataAppello,0,4);
        int verbalAnno = estraiValore(thisDataAppello,0,4);

        bool isSameAnno = appelloMese == verbalMese;
        if(!isSameAnno) continue;

        int appelloMese = estraiValore(thisDataAppello,5,2);
        int verbalMese = estraiValore(thisDataVerb,5,2);

        bool isCreatedAfterAppello = verbalMese > appelloMese;
        if(!isCreatedAfterAppello) continue;

        if(insTesta(listaOut, p->dato) == ERRORE) return NULL;
    }

    return listaOut;
}