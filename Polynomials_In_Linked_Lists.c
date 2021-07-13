#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

typedef struct Node
{
    int stepen;
    float koef;
    struct Node* next;

}Red;

typedef struct listHeader {
    Red* head, * tail;
    int numElem, numElemMax;
} ListHeader;

ListHeader* nnode;


Red* NapraviPolinom(Red *niz) {
    int st,i;
    float kf;
    Red* node = NULL,*last=NULL,*head=NULL;
    printf("Unesite najveci stepen:\n");
    scanf("%d", &st);
    i = st;
    while(i>=0){
        printf("\nUnesite vrednost koeficijenta za x^%d:", i);
        scanf("%f", &kf);
        if (kf != 0) {
            niz = malloc(sizeof(Red));
            if (!niz) {
                printf("Mem greska");
                break;
            }
            niz->stepen = i;
            niz->koef = kf;
            niz->next = NULL;
            if (last == NULL)
                head = niz;
            else
                last->next = niz;
            last = niz;
        }
        i--;
    }
    return head;
}

Red* DodavanjeNovihCl(Red* head) {
    int step;
    float koefic;
    Red* current = head, * node = NULL;
    printf("Unesite stepen novog clana datog polinoma: ");
    scanf("%d", &step);
    printf("\nUnesite koeficijent novog clana datog polinoma: ");
    scanf("%f", &koefic);
    while (current)
    {
        if (current->stepen == step) {
            current->koef = current->koef + koefic;
            break;
        }
        else if (current->stepen > step && current->next->stepen < step) {

            node = malloc(sizeof(Red));
            if (!node) {
                printf("Mem greska");
                break;
            }
            node->next = current->next;
            current->next = node;
            node->koef = koefic;
            node->stepen = step;
            break;
        }
        else if (current == head && current->stepen < step) {
            node = malloc(sizeof(Red));
            if (!node) {
                printf("Mem greska");
                break;
            }
            node->next = current;
            head = node;
            node->koef = koefic;
            node->stepen = step;
            break;
        }


        current = current->next;
    }
    current=head;
    Red* temp = NULL;
     while(current!=NULL){
         printf("nice");

         if(current==head){
             if (current->koef == 0) {
                 head = head->next;
                 temp = current;
                 current = current->next;
                 free(temp);
             }
             else if (current->next->koef == 0) {
                 printf("nice");
                 temp = current->next;
                 current->next = current->next->next;
                 free(temp);
             }
             else current = current->next;
         }
         else if (current->next!=NULL && current->next->koef == 0){
             printf("nice");
             current->next=current->next->next;
             temp=current->next;
             free(temp);
         }
         else current=current->next;

     }
    


    return head;
}

Red* BrisanjeCl(Red* head) {
    int step,izbor,br,i=0;
    float koefic;
    Red* current = head, * p = head,*temp=NULL;
    printf("Unesite br za:\n1.Brisanje clanova sa unesenim stepenom\n2.Brisanje clanova sa unesenim koeficijentom\n3.Brisanje clanova na rednom mestu\n");
    while (1) {
        scanf("%d", &izbor);
        if (izbor == 1) {
            printf("Izvrsice se brisanje clanova sa stepenom:\n");
            scanf("%d", &step);
            while (current) {
                if (current->stepen == step) {
                    p->next = current->next;
                    temp = current;
                    if (current == head) {
                        head = head->next;
                        p = head;
                    }
                    current = current->next;
                    free(temp);

                    printf("Obrisan clan sa stepenom:%d\n", step);

                }
                else {
                    p = current;
                    current = current->next;
                }
            }
            break;
        }
        else if (izbor == 2) {
            printf("Izvrsice se brisanje clanova sa koeficijentom:\n");
            scanf("%f", &koefic);
            while (current) {
                if (current->stepen == koefic) {
                    p->next = current->next;
                    temp = current;
                    if (current == head) {
                        head = head->next;
                        p = head;
                    }
                    current = current->next;
                    free(temp);
                    printf("Obrisan clan sa koeficijentom:%f\n", koefic);

                }
                else {
                    p = current;
                    current = current->next;
                }
            }
            break;
        }
        else if (izbor == 3) {
            printf("Izvrsice se brisanje clana na rednom mestu:\n");
            scanf("%d", &br);
            while (current) {
                if (i == br) {
                    p->next = current->next;
                    temp = current;
                    if (current == head) {
                        head = head->next;
                        p = head;
                    }
                    current = current->next;
                    free(temp);
                    printf("Obrisan clan na rednom mestu:%d\n", br);
                }
                else {
                    p = current;
                    current = current->next;
                    i++;
                }

            }
            break;
        }
        else { printf("Unesite ponovo!\n"); }
    }



    return head;
}


void printList(Red* head)
{
    Red* current = head;
    while (current)
    {
        if (current->koef > 0) {
            printf("+%.1fx^%d ", current->koef, current->stepen);
        }
        else {
            printf("%.1fx^%d ", current->koef, current->stepen);
        }
        //if(current->next=NULL){printf("\n");}
        current = current->next;
        if (current == NULL) printf("\n");
    }
}

void RacunanjeVrPolinoma(Red* head) {
    //float x;
    //int i;
    double rez = 0,x,i,pom=0;
    Red* current = head;
    printf("Unesite vrednost za x:\n");
    scanf("%lf", &x);
    while (current) {
        i = current->stepen;
        pom=pom+pow(x,i);
        pom = pom * current->koef;
        rez = rez + pom;
        pom = 0;
        current = current->next;
    }
    printf("Vrednost polinoma za dato x=%.1lf je:%.2lf\n",x,rez);
}

void OslobodiMemoriju(Red* head)
{
    Red* current = head;
    while (current != NULL)
    {
        Red* temp = current;
        current = current->next;
        free(temp);
    }
}

Red* Operacija2Pol(Red* head1, Red* head2) {
    int o, tmp;
    float tmp2;
    Red* Pol = NULL, * pom = head2, * current = NULL;
    Pol = (struct Red*)malloc(sizeof(Red));
    Red* head = Pol;
    printf("Izaberite jednu od sledecih opcija:\n1.Sabiranje 2 polinoma\n2.Mnozenje 2 polinoma\n");
    //Podrazumeva se da je dobro uneseno 1 ili 2
    scanf("%d", &o);
    if (o == 1) {
        while (head1 && head2) {
            if (head1->stepen > head2->stepen) {
                Pol->stepen = head1->stepen;
                Pol->koef = head1->koef;
                head1 = head1->next;
            }
            else if (head1->stepen < head2->stepen) {
                Pol->stepen = head2->stepen;
                Pol->koef = head2->koef;
                head2 = head2->next;
            }
            else {
                Pol->stepen = head1->stepen;
                Pol->koef = head1->koef + head2->koef;
                head1 = head1->next;
                head2 = head2->next;
            }
            if (head1 && head2) {
                Pol->next = (struct Red*)malloc(sizeof(Red));
                Pol = Pol->next;
                Pol->next = NULL;
            }
        }
        while (head1 || head2) {
            Pol->next = (struct Red*)malloc(sizeof(Red));
            Pol = Pol->next;
            Pol->next = NULL;
            if (head1->next) {
                Pol->stepen = head1->stepen;
                Pol->koef = head1->koef;
                head1 = head1->next;
            }
            if (head2->next) {
                Pol->stepen = head2->stepen;
                Pol->koef = head2->koef;
                head2 = head2->next;
            }
        }
    }
    else {
        while (head1) {
            while (pom) {
                Pol->stepen = head1->stepen + pom->stepen;
                Pol->koef = head1->koef * pom->koef;
                if (head1->next == NULL && pom->next == NULL) {
                    
                }
                else{
                    Pol->next = (struct Red*)malloc(sizeof(Red));
                    Pol = Pol->next;
                    Pol->next = NULL;
                }
                pom = pom->next;
            }
            head1 = head1->next;
            pom = head2;
        }
        Pol = head;
        //printList(Pol);
        current = Pol->next;
        while (current) {
            if (Pol->stepen == current->stepen) {
                Pol->koef = Pol->koef + current->koef;
                current->koef = 0;
            }
            current = current->next;
            if (current == NULL && Pol->next != NULL) {
                Pol = Pol->next;
                current = Pol->next;
            }
        }
        current = head;
        //printList(current);
        Red* temp = NULL;
        while (current != NULL) {
            //printf("nice");

            if (current == head) {
                if (current->koef == 0) {
                    head = head->next;
                    temp = current;
                    current = current->next;
                    free(temp);
                }
                else if (current->next->koef == 0) {
                    //printf("nice");
                    temp = current->next;
                    current->next = current->next->next;
                    free(temp);
                }
                else current = current->next;
            }
            else if (current->next != NULL && current->next->koef == 0) {
                //printf("nice");
                temp = current->next;
                current->next = current->next->next;
                
                free(temp);
            }
            else current = current->next;
        }
        Pol = head;
        //printList(Pol);
        current = Pol->next;
        while (Pol->next) {
            while (current) {
                if (current->stepen > Pol->stepen) {
                    tmp = Pol->stepen;
                    Pol->stepen = current->stepen;
                    current->stepen = tmp;

                    tmp2 = Pol->koef;
                    Pol->koef = current->koef;
                    current->koef = tmp2;
                }
                current = current->next;
            }
            Pol = Pol->next;
            current = Pol->next;
        }
    }
    //OslobodiMemoriju(head1);
    //OslobodiMemoriju(head2);
    return head;
}

int main() {

    int izbor, o = 0,x=0,provera=0,br=0,b=0,odg,odg2,odg3,odg4,br2=0,m,n,prvi=0,izbor2;
    Red* niz=NULL,*niz2=NULL, * node = NULL, * head = NULL, * last = NULL,*pomoc,*pom;
    Red** nizz=NULL;
    nnode = malloc(sizeof(ListHeader));
    while (o < 2)
    {
        printf("\n---------------MAIN MENU---------------\n1.Unos polinoma po stepenima\n2.Dodavanje novog clana u polinom\n3.Brisanje zeljenog clana polinoma\n4.Ispis jednog ili svih polinoma\n5.Racunanje vrednosti polinoma\n6.Dealokacija i brisanje celog polinoma\n7.Sabiranje ili mnozenje 2 polinoma\n8.Quit\n---------------------------------------\n");
        scanf("%d", &izbor);
        switch (izbor)
        {
        case 1:
            if (br < 5) {
                niz = NapraviPolinom(niz);

                if (!prvi) {
                    nizz = realloc(NULL, (br + 1) * sizeof(nizz));
                    prvi++;
                    nizz[br] = niz;
                    if (!nizz) {
                        printf("Mem greska");
                        break;
                    }
                    nnode->head = nizz[br];
                }
                else {
                    nizz = realloc(nizz, (br + 1) * sizeof(nizz));
                    nizz[br] = niz;
                    if (!nizz) {
                        printf("Mem greska");
                        break;
                    }
                    nnode->tail = nizz[br];
                }
                    /*nizz[br][b]->stepen = niz->stepen;
                    nizz[br][b]->koef = niz->koef;
                    nizz[br][b]->next = niz->next;
                    if (last == NULL)
                        head = nizz[br][b];
                    else
                        last->next = nizz[br][b];
                    last = nizz[br][b];*/
                    br++;
                    nnode->numElem = br;
                provera = 1;
            }
            else { printf("Ima max broj polinoma(5)!\n"); }
            break;

        case 2:
            if (provera == 1) {
                printf("Kom polinomu zelite dodati novi clan od 0tog do %d\n", br-1);
                scanf("%d", &odg);
                if (odg <= br) {
                    pomoc = nizz[odg];
                    nizz[odg] = DodavanjeNovihCl(pomoc);
                }
                else printf("Nije dobro uneseno!!\n");
            }
            else { printf("Napravite polinom prvo!\n"); }
            break;
        case 3:
            if (provera == 1) {
                printf("Kom polinomu zelite obrisati clan od 0tog do %d\n", br-1);
                scanf("%d", &odg2);
                if (odg2 <= br) {
                    nizz[odg2] = BrisanjeCl(nizz[odg2]);
                }
                else printf("Nije dobro uneseno!!\n");
            }
            else { printf("Napravite polinom prvo!\n"); }

            break;
        case 4:
            if (provera == 1) {
                printf("Zelite li ispis svih polinoma ili samo odredjenog? (1-samo odredjenog;2-svih)\n");
                scanf("%d", &izbor2);
                if (izbor2 == 1) {
                    printf("Ispis kog polinoma zelite videti od 0tog do %d\n", br - 1);
                    scanf("%d", &odg3);
                    if (odg3 <= br) {
                        printf("Ispis polinoma:\n");
                        printList(nizz[odg3]);
                    }
                    else printf("Nije dobro uneseno!!\n");
                }
                else if (izbor2 == 2) {
                    x = 0;
                    printf("Ispis polinoma:\n");
                    while (x < br) {
                        printList(nizz[x]);
                        x++;
                    }
                }
                else printf("Nije dobro uneseno!\n");
            }
            else { printf("Napravite polinom prvo!\n"); }

            break;
        case 5:
            if (provera == 1) {
                printf("Koji polinom zelite izracunati od 0tog do %d\n", br-1);
                scanf("%d", &odg4);
                if (odg4 <= br) {
                    RacunanjeVrPolinoma(nizz[odg4]);
                }
                else printf("Nije dobro uneseno!!\n");
            }
            else { printf("Napravite polinom prvo!\n"); }
            break;
        case 6:
            if (provera == 1) {
                while (br2<br) {
                    OslobodiMemoriju(nizz[br2]);
                    br2++;
                }
                free(nizz);
                br = 0;
                br2 = 0;
                provera = 0;
                prvi = 0;
                nnode->head = NULL;
                nnode->tail = NULL;
                nnode->numElem = 0;
                //nizz = NULL;
            }
            else { printf("Napravite polinom prvo!\n"); }
            break;
        case 7:
            if (provera == 1) {
                printf("Koja 2 polinoma zelite koristiti od 0tog do %d ( Unesete 1 broj pa enter,onda 2gi broj pa enter :D )\n", br-1);
                scanf("%d%d", &m, &n);
                if (m < br && n < br) {
                    //niz2 = NapraviPolinom(niz2);
                    //niz promenljiva dobija vrednost rezultujuceg niza posle sabiranja ili mnozenja
                    nizz[m] = Operacija2Pol(nizz[m], nizz[n]);
                    while (n < br-1) {
                        if (nizz[n + 1] != NULL) {
                            pom = nizz[n];
                            nizz[n] = nizz[n + 1];
                            nizz[n + 1] = pom;
                            nnode->tail = nizz[n];
                            n++;
                        }
                    }
                    OslobodiMemoriju(nizz[n]);
                    br--;
                    nnode->numElem--;
                }
                else printf("Nije dobro uneseno!!\n");
            }
            else { printf("Napravite polinom prvo!\n"); }
            break;
        case 8: return -1;
        default:printf("Nije dobro uneseno pokusaj ponovo!\n");
            break;
        }
    }
    return 0;
}