#include <iostream>
#include <windows.h>

using namespace std;

bool dataValida(int gg, int mm, int aa)
{
    if (aa < 0 || mm < 1 || mm > 12 || gg < 1 || gg > 31)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool annoBis(int aa)
{
    if(aa%400==0)
    {
        return true;
    }
    else if(aa%4 == 0 && aa%100 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int verificaGgMese(int aa, int mm)
{
    switch(mm)
    {
        case 1:
            return 31;
            break;
        case 2:
            if(annoBis(aa))
            {
                return 29;
            }
            else
            {
                return 28;
            }
            break;
        case 3:
            return 31;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 31;
            break;
        case 6:
            return 30;
            break;
        case 7:
            return 31;
            break;
        case 8:
            return 31;
            break;
        case 9:
            return 30;
            break;
        case 10:
            return 31;
            break;
        case 11:
            return 30;
            break;
        case 12:
            return 31;
            break;
        default:
            break;
    }
}

int ggFineAa(int gg, int mm, int aa)
{
    int ggtot = 0;
    for(int i=mm; i<=12; i++)
    {
        ggtot += verificaGgMese(aa,i);
    }
    ggtot -= gg;
    return ggtot;
}

int ggInizioAa(int gg, int mm, int aa)
{
    int ggtot = gg;
    for(int i=mm-1; i>=1; i--)
    {
        ggtot += verificaGgMese(aa,i);
    }
    return ggtot;
}

int main(){
    int gg, mm, aa, scelta;
    char slash;

    do
    {
        do
        {
            cout << "Inserisci una data (gg/mm/aaaa): ";
            cin >> gg >> slash >> mm >> slash >> aa;
            if (!dataValida(gg, mm, aa))
            {
                cout << "--> Data non valida <--" << endl;
            }
            else
            {
                break;
            }
        }while(true);

        Sleep(500);

        do
        {
            cout << "1) Calcolo giorni mancanti alla fine dell'anno\n2) Calcolo giorni passati dall'inizio dell'anno\n3) Verifica anno bisestile\n4) Esci" << endl;
            Sleep(500);
            cout << "Utente, ";
            Sleep(500);
            cout << "Scegli: ";
            cin >> scelta;
            if(scelta < 1 || scelta > 4)
            {
                cout << "Mi dispiace, ";
                Sleep(500);
                cout << "ma non sono riuscito a trovare quest'opzione. ";
                Sleep(500);
                cout << "Riprova." << endl;
                Sleep(1000);
            }
            else
            {
                break;
            }
        }while(true);
        
        if(scelta == 1)
        {
            cout << "-->I giorni mancanti alla fine dell'anno sono: " << ggFineAa(gg,mm,aa) << "<--" << endl;
            Sleep(1000);
        }

        if(scelta == 2)
        {
            cout << "-->I giorni passati dall'inizio dell'anno sono: " << ggInizioAa(gg,mm,aa) << "<--" << endl;
            Sleep(1000);
        }

        if(scelta == 3)
        {
            if(annoBis(aa))
            {
                cout << "-->Il " << aa << " e' bisestile<--" << endl;
                Sleep(1000);
            }
            else
            {
                cout << "-->Il " << aa << " non e' bisestile<--" << endl;
                Sleep(1000);
            }
        }
        
        if(scelta == 4)
        {
            cout << "Grazie per aver provato il programma. ";
            Sleep(500);
            cout << "Arrivederci!" << endl;
            break;
        }

    }while(true);

    return 0;
}
