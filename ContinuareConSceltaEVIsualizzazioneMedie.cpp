#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cctype>
#include<unistd.h>

using namespace std;

void controllo_reglog(string);
int reglog_ret(string);
void clearscreen();
string iniziali(string);
int rand_num_user();
bool controllo_pw_reg(string);
void log(string, string&);
void reg(string, string, char[], int);
int reglog_cond(string);
void genera_password(char[],int);
int verifica(char[],int);
void inserimento_voti(string, string);
float calcola_media_singola(float, string);
void tolowera_la_stringa(string);

int main(){
    srand((unsigned)time(NULL));
    //in questo do while sta tutta la registrazione/login
    cout << "Benvenuto nel registro scolastico!\nQui avrai a disposizione la possibilità di inserire/rimuovere voti, visualizzare medie globali e medie di ogni materia.\nPotrai anche tenere traccia dei tuoi ritardi, assenze, entrate e uscite anticipate/posticipate!\nDivertiti!!\nPremere INVIO per continuare!";
    getchar();
    string user;
    do{
        clearscreen();
        int dim_pass = 9;
        char pass[dim_pass];
        string password;
        cout << "1)Registrazione(reg)\n2)Login(log)";
        string reglog;
        cout << "\nCosa vuoi fare(reg/log): "; cin >> reglog;
        string username;
        while(reglog != "reg" && reglog != "log"){
            cout << "Scelta inserita non valida. ";
            sleep(3);
            clearscreen();
            cout << "1)Registrazione(reg)\n2)Login(log)";
            cout << "\nCosa vuoi fare(reg/log): "; cin >> reglog;
        }
        int logreg = reglog_ret(reglog);
        if(logreg == 1){
            reg(username,password,pass,dim_pass);
        }else{
            log(username, user);
        }
        cout << "Premere invio per continuare"; 
        if(logreg == 1){
            cin.ignore();
            getchar();
        }else{
            getchar();
            break;
        }
    }while(true);
    //da qua deve iniziare il registro dopo il login
    
    int sceltaAzione; //Questa variabile serve a far scegliere che azione compiere tra quelle qui sotto elencate
    clearscreen();
    cout << "Ora che hai fatto il login puoi scegliere tra una varieta' di azioni.\nCosa vuoi fare?\n";
    cout << "1)Inserimento voti\n2)Rimozione voti\n3)Visualizzazione medie\n4)Visualizzazione assenze/ritardi\n0)Esci dal registro" << endl;
    cin >> sceltaAzione;
    string materia;
    switch(sceltaAzione){
        case 0:
            cout << "Sto uscendo dal registro! Arrivederci.";
            return 0;
        case 1:
            inserimento_voti(materia, user);
            break;
        case 3:
            float media = 0;
            calcola_media_singola(media, user);
            break;
    }

}

/*
 * Funzione per decidere se registrarsi o fare l'accesso
 *@param reglog Variabile per decidere ahahah
 *@return 2 per il login
 *@return 1 per la registrazione
*/
int reglog_ret(string reglog){
    int var = 0;
    if(reglog== "log"){
        var = 2;
    }else if(reglog == "reg"){
        var = 1;
    }
    return var;

}

void clearscreen(){
    #ifdef _WIN32
        system("cls");
    #elif defined(__APPLE__) || defined(__linux__)
        system("clear || printf '\033c'");
    #else
        std::cout << "Impossibile pulire lo schermo su questo sistema operativo." << std::endl;
    #endif
}

string iniziali(string nomcogn){
    string iniziali;
    bool spazio = true;
    for(int i = 0; i < nomcogn.length(); i++){
        if(nomcogn[i] == ' ' ){
            spazio = true;
        }
        if(nomcogn[i] >= 'a' && nomcogn[i] <= 'z' || nomcogn[i] >= 'A' && nomcogn[i] <= 'Z'){
            if(spazio){
                spazio = false;
                nomcogn[i] = tolower(nomcogn[i]);
                iniziali += nomcogn[i];
            }
        }
    }
    return iniziali;
}

int rand_num_user(){
    return (rand()%1000)+1000;
}

bool controllo_pw_reg(string password){
    int contnum = 0;
    int contmaiusc = 0;
    for(int i = 0; i < password.length(); i++){
        if(password[i] >= '0' && password[i] <= '9'){
            contnum++;
        }
        if(password[i] >= 'A' && password[i] <= 'Z'){
            contmaiusc++;
        }
    }
    
    if(contnum < 1){
        return false;
    }else if(contmaiusc < 1){
        return false;
    }else if(password.length() < 8){
        return false;
    }else{
        return true;
    }
}

void log(string username, string &user){
    string riga;
    string pw;
    ifstream check;
    ifstream check_user;
    int cont = 0;
    int ignore = 0;
    do{
        clearscreen();
        cont = 0;
        cout << "Inserire l'username: "; 
        if(ignore == 0){
            cin.ignore();
        }
        getline(cin,user);
        check_user.close();
        check_user.open("tuttigliusername.txt");
        while(getline(check_user,riga)){
            if(user == riga){
                cont++;
            }
        }
        check.close();
        check.open(user + ".txt");
        while(getline(check,riga)){
            if(user != riga){
                cont++;
                break;
            }else{
                break;
            }
        }
        if(cont > 0){
            cont = 0;
            check.close();
            check.open(user + ".txt");
            check.ignore(1000,'\n');
            cout << "inserire la password: ";
            getline(cin,pw); 
            while(getline(check,riga)){
                if(pw == riga){
                    cont = 0;
                    break;
                }else{
                    cont++;
                    break;
                }
            }
            if(cont > 0){
                cout << "Password errata >:(";
                sleep(2);
            }else{
                cout << "Login avvenuto con successo! :)" << endl;
            }
        }else{
            cout << "Username non esistente! :(";
            sleep(2);
            cont = 1;
        }
        ignore++;
    }while(cont > 0);
}

void reg(string username, string password, char pass[],int dim_pass){
    clearscreen();
    ofstream regfile;
    string nomcogn;
    string nc;
    int numrand = 0;

    cout << "Inserire nome e cognome: ";
    cin.ignore();
    getline(cin, nomcogn);
    nc = iniziali(nomcogn);
    numrand = rand_num_user();
    username = nc + to_string(numrand);
    ofstream file_utente;
    ofstream file_con_username;
    int scelta;
    string passwordconf;
    do{
        cout << "1) Inserimento password\n2) Generatore di password sicura\nSCEGLI(1/2): ";
        cin >> scelta;
        if(scelta == 1){
            do{
                cout << "Inserisci la password (Min 8 caratteri, 1 Maiuscola, 1 Numero): ";
                cin >> password;
                if(!controllo_pw_reg(password)){
                    cout << "Password inserita non valida. Riprova." << endl;
                }
                else{
                    cout << "Conferma password: ";
                    cin >> passwordconf;
                    if(passwordconf == password){
                        file_utente.open(username + ".txt");
                        cout << "USERNAME: " << username << endl;
                        file_con_username.open("tuttigliusername.txt", ios::app);
                        file_con_username << username << endl;
                        file_con_username.close();
                        file_utente << username << endl;
                        cout << "PASSWORD: " << passwordconf << endl;
                        file_utente << passwordconf << endl;
                        break;
                    }
                    else{
                        cout << "Conferma della password errata. Riprova." << endl;
                    }
                } 
            }while(true);
            break;
        }else if(scelta == 2){
            int ver = 0;
            do{
                genera_password(pass,dim_pass);
                ver = verifica(pass,dim_pass);
            }while(ver == 0);
            file_utente.open(username + ".txt");
            cout << "USERNAME: " << username << endl;
            file_utente << username << endl;
            file_con_username.open("tuttigliusername.txt", ios::app);
            file_con_username << username << endl;
            file_con_username.close();
            cout << "PASSWORD: " << pass << endl;
            file_utente << pass << endl;
            break;
        }else{
            cout << "Valore inserito non valido. Riprova." << endl;
        }
    }while(true);

    file_utente << nomcogn << endl;
    file_utente.close();
}

/*
*Funzione che genera una password sicura casuale
*@param password Array di caratteri contenente la password sicura
*@param dim_pass Lunghezza della password
*/
void genera_password(char password[], int dim_pass){
    int casuale = 0;
    int i = 0;
    int special = 0;
    while(i < dim_pass - 1){
        casuale = 0;
        casuale = (rand()%4);
        switch(casuale){
            case 0:{
                password[i] = (rand()%26)+65;
                break;
            }
            case 1:{
                password[i] = (rand()%26)+97;
                break;
            }
            case 2:{
                password[i] = (rand()%10)+48;
                break;
            }
            case 3:{
                do{
                    special = 0;
                    special = (rand()%32)+33;
                }while(special >= 48 && special <= 57);
                password[i] = special;
                break;
            }
            default:{
                break;
            }
        }
        i++;
    }
    password[dim_pass - 1] = '\0';
}

int verifica(char password[], int dim_pass) {
    int cont_minuscole = 0;
    int cont_maiuscole = 0;
    int cont_numeri = 0;
    int cont_speciali = 0;

    int i = 0;
    while(i < dim_pass - 1){
        if(password[i] >= 'a' && password[i] <= 'z'){
            cont_minuscole = 1;
        }else if(password[i] >= 'A' && password[i] <= 'Z'){
            cont_maiuscole = 1;
        }else if(password[i] >= '0' && password[i] <= '9'){
            cont_numeri = 1;
        }else if(password[i] >= 33 && password[i] <= 46 || password[i] >= 57 && password[i] <= 64){
            cont_speciali = 1;
        }
        i++;
    }

    if (cont_minuscole > 0 && cont_maiuscole > 0 && cont_numeri > 0 && cont_speciali > 0) {
        return 1;
    } else {
        return 0;
    }
}

/*
*Funzione per inserire i voti per ogni materia
*@param materia stringa per decidere in quale materia aggiungere voti
*/
void inserimento_voti(string materia, string username){
    float votomat;
    string datavoto;
    ofstream mat, ita, sto, siret, inf, rel, edfis, tpsit, tlc, ing;
    
    cout << "Perfetto, eccoci nell'interfaccia di inserimento dei voti.\nIn quale materia vuoi aggiungere un voto?" << endl;
    cout << "Matematica(mat)\nItaliano(ita)\nStoria(sto)\nSistemi e Reti(siret)\nInformatica(inf)\nReligione(rel)\nEducazione Fisica(edfis)\n";
    cout << "Tecnologie e Progettazione di Sistemi Informatici e Telecomunicazioni(tpsit)\nTelecomunicazioni(tlc)\nInglese(ing)\n";
    cout << "Scrivere EXIT per terminare l'inserimento dei voti.\n";

    do{
        cout << "Inserisci materia: ";
        cin >> materia;

        tolowera_la_stringa(materia);
        
        if(materia == "mat"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto; //per adesso lascio l'inserimento manuale, poi magari vediamo di mettere la funzione che ti calcola la data
            cout << "Inserisci il voto per MATEMATICA: ";
            cin >> votomat;
            mat.open(materia + "_" + username + ".txt", ios::app);
            mat << votomat << "=" << datavoto;
            mat.close();
            break;
        }
        else if(materia == "ita"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per ITALIANO : ";
            cin >> votomat;
            ita.open(materia + "_" + username + ".txt", ios::app);
            ita << votomat << "=" << datavoto;
            ita.close();
            break;
        }
        else if(materia == "sto"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per STORIA: ";
            cin >> votomat;
            sto.open(materia + "_" + username + ".txt", ios::app);
            sto << votomat << "=" << datavoto;
            sto.close();
            break;
        }
        else if(materia == "siret"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per SISTEMI E RETI: ";
            cin >> votomat;
            siret.open(materia + "_" + username + ".txt", ios::app);
            siret << votomat << "=" << datavoto;
            siret.close();
            break;
        }
        else if(materia == "inf"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per INFORMATICA: ";
            cin >> votomat;
            inf.open(materia + "_" + username + ".txt", ios::app);
            inf << votomat << "=" << datavoto;
            inf.close();
            break;
        }
        else if(materia == "rel"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per RELIGIONE: ";
            cin >> votomat;
            rel.open(materia + "_" + username + ".txt", ios::app);
            rel << votomat << "=" << datavoto;
            rel.close();
            break;
        }
        else if(materia == "edfis"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per EDUCAZIONE FISICA: ";
            cin >> votomat;
            edfis.open(materia + "_" + username + ".txt", ios::app);
            edfis << votomat << "=" << datavoto;
            edfis.close();
            break;
        }
        else if(materia == "tpsit"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per TECNOLOGIE E PROGETTAZIONE DI SISTEMI INFORMATICI E TELECOMUNICAZIONI : ";
            cin >> votomat;
            tpsit.open(materia + "_" + username + ".txt", ios::app);
            tpsit << votomat << "=" << datavoto;
            tpsit.close();
            break;
        }
        else if(materia == "tlc"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per TELECOMUNICAZIONI: ";
            cin >> votomat;
            tlc.open(materia + "_" + username + ".txt", ios::app);
            tlc << votomat << "=" << datavoto;
            tlc.close();
            break;
        }
        else if(materia == "ing"){
            cout << "Inserisci la data dell'inserimento (Es.: xx/xx/xxxx): ";
            cin >> datavoto;
            cout << "Inserisci il voto per INGLESE: ";
            cin >> votomat;
            ing.open(materia + "_" + username + ".txt", ios::app);
            ing << votomat << "=" << datavoto;
            ing.close();
            break;
        }
        else{
            cout << "Non e' stata trovata alcuna materia chiamata " << materia << ". Riprova.\n";
        }
    }while(true);
}

float calcola_media_singola(float media, string username){
    string sceltaMatGlob, materia;
    float somma;
    int cont = 0;
    float voto;

    cout << "Eccoci nel calcolo delle medie!\nVuoi visualizzare la media di una singola materia (mater) o quella globale (glob)?" << endl;
    getline(cin, sceltaMatGlob);

    // TODO fare funzione che loweri stringhe e sostituirla a tutti questi for in giro
    tolowera_la_stringa(sceltaMatGlob);

    if(sceltaMatGlob == "glob"){
        //TODO calcolo_media_globale();
    }
    else if(sceltaMatGlob == "mater"){
        cout << "Matematica(mat)\nItaliano(ita)\nStoria(sto)\nSistemi e Reti(siret)\nInformatica(inf)\nReligione(rel)\nEducazione Fisica(edfis)\n";
        cout << "Tecnologie e Progettazione di Sistemi Informatici e Telecomunicazioni(tpsit)\nTelecomunicazioni(tlc)\nInglese(ing)\n";
        cout << "Tra quelle sopra elencate, di quale materia vuoi conoscere la media?" << endl;
        cin >> materia;
        int temp = materia.length();

        for(int i = 0; i < materia.length(); i++){
            materia[i] = tolower(materia[i]);
        }

        ifstream fin(materia + "_" + username + ".txt");
        while(fin >> voto){
            somma += voto;
            cont++;
        }
        media = somma / cont;
        fin.close();
    }
    return media; 
}
//commento di prova

void tolowera_la_stringa(string riga){
    for(int i = 0; i < riga.length(); i++){
        riga[i] = tolower(riga[i]);
    }
}
