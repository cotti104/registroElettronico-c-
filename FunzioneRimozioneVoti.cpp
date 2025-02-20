#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<cctype>
#include<unistd.h>
#include<vector>
#include<sstream>

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
void calcola_media_singola(string);
void tolowera_la_stringa(string);
bool dataValida(int,int,int);
bool annoBis(int);
int verificaGgMese(int,int);
bool controllo_voto(float);
bool controllo_ora_rit(int, int);
bool controllo_ora_usc(int, int);
void inserimento_assenze(string); /*new*/
void visuRitUscAss(string);
void visugeneralevoti(string);
void rimozione_voti(string);
string dataOdierna();
bool materiainseritocorrettamente(string);

int main(){
    srand((unsigned)time(NULL));
    //in questo do while sta tutta la registrazione/login
    clearscreen();
    cout << "Benvenuto nel registro scolastico!\nQui avrai a disposizione la possibilita' di inserire/rimuovere voti, visualizzare medie globali e medie di ogni materia.\nPotrai anche tenere traccia dei tuoi ritardi, assenze, entrate e uscite anticipate/posticipate!\nPremere INVIO per continuare!";
    getchar();
    string user;
    do{
        clearscreen();
        int dim_pass = 9;
        char pass[dim_pass];
        string password;
        cout << "1)Registrazione(reg)\n2)Login(log)";
        int reglog = 0;
        cout << "\nCosa vuoi fare(1/2): "; cin >> reglog;
        string username;
        while(reglog != 1 && reglog != 2){
            cout << "Scelta inserita non valida. ";
            sleep(2);
            clearscreen();
            cout << "1)Registrazione(reg)\n2)Login(log)";
            cout << "\nCosa vuoi fare(1/2): "; cin >> reglog;
        }
        if(reglog == 1){
            reg(username,password,pass,dim_pass);
        }else{
            log(username, user);
        }
        cout << "Premere invio per continuare";
        if(reglog == 1){
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
    cout << "Ora che hai fatto il login potrai scegliere tra una varieta' di azioni.\n";
    do{
        clearscreen();
        cout << "Cosa vuoi fare?\n";
        cout << "1)Inserimento voti\n2)Rimozione voti\n3)Visualizzazione medie\n4)Inserimento assenze/ritardi/uscite anticipate\n5)Visualizzazione assenze/ritardi/uscite anticipate\n6)Visualizzazione generale voti\n0)Esci dal registro" << endl;
        cout << "SCEGLI: ";
        cin >> sceltaAzione;
        string materia;
        clearscreen();
        switch(sceltaAzione){
            case 0:
                cout << "Sto uscendo dal registro! Arrivederci.";
                return 0;
            case 1:
                inserimento_voti(materia, user);
                break;
            case 2:
                rimozione_voti(user);
                break;
            case 3:
                calcola_media_singola(user);
                break;
            case 4:
                inserimento_assenze(user); /*new*/
                break;
            case 5:{
                visuRitUscAss(user);
                break;
            }
            case 6:{
                visugeneralevoti(user);
                break;
            }
        }
    }while(true);
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
    ofstream mat;

    cout << "Perfetto, eccoci nell'interfaccia di inserimento dei voti.\nIn quale materia vuoi aggiungere un voto?" << endl;
    cout << "Matematica(mat)\nItaliano(ita)\nStoria(sto)\nSistemi e Reti(siret)\nInformatica(inf)\nReligione(rel)\nEducazione Fisica(edfis)\n";
    cout << "Tecnologie e Progettazione di Sistemi Informatici e Telecomunicazioni(tpsit)\nTelecomunicazioni(tlc)\nInglese(ing)\n";
    cout << "Scrivere EXIT per terminare l'inserimento dei voti.\n";

    do{
        cout << "Inserisci materia: ";
        cin >> materia;

        tolowera_la_stringa(materia);

        time_t now = std::time(0);
        tm *ltm = std::localtime(&now);

        clearscreen();

        if(materia == "mat"){
            cout << "Inserisci il voto per MATEMATICA: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per MATEMATICA: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; 
                        cin >> g;
                        cout << "Mese: "; 
                        cin >> m;
                        cout << "Anno: "; 
                        cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "ita"){
            cout << "Inserisci il voto per ITALIANO : ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per ITALIANO: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; 
                    cin >> g;
                    cout << "Mese: "; 
                    cin >> m;
                    cout << "Anno: "; 
                    cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "sto"){
            cout << "Inserisci il voto per STORIA: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per STORIA: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; 
                    cin >> g;
                    cout << "Mese: "; 
                    cin >> m;
                    cout << "Anno: "; 
                    cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "siret"){
            cout << "Inserisci il voto per SISTEMI E RETI: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per SISTEMI E RETI: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "inf"){
            cout << "Inserisci il voto per INFORMATICA: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per INFORMATICA: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "rel"){
            cout << "Inserisci il voto per RELIGIONE: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per RELIGIONE: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "edfis"){
            cout << "Inserisci il voto per EDUCAZIONE FISICA: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per EDUCAZIONE FISICA: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "tpsit"){
            cout << "Inserisci il voto per TECNOLOGIE E PROGETTAZIONE DI SISTEMI INFORMATICI E TELECOMUNICAZIONI : ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per TECNOLOGIE E PROGETTAZIONE DI SISTEMI INFORMATICI E TELECOMUNICAZIONI: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "tlc"){
            cout << "Inserisci il voto per TELECOMUNICAZIONI: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per TELECOMUNICAZIONI: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "ing"){
            cout << "Inserisci il voto per INGLESE: ";
            cin >> votomat;
            while(!controllo_voto(votomat)){
                cout << "Voto inserito non valido. Riprova.\n";
                cout << "Inserisci il voto per INGLESE: ";
                cin >> votomat;
            }
            cout << "1)Inserire la data manualmente(es. gg/mm/anno)\n2)Inserimento automatico della data odierna\nCosa vuoi fare(1/2):";
            char scelta;
            cin >> scelta;
            while(scelta != '1' && scelta != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> scelta;
            }
            switch(scelta){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    cout << "Giorno: "; cin >> g;
                    cout << "Mese: "; cin >> m;
                    cout << "Anno: "; cin >> a;
                    while(!dataValida(g,m,a)){
                        cout << "Data inserita non valida. Reinserire la data." << endl;
                        cout << "Giorno: "; cin >> g;
                        cout << "Mese: "; cin >> m;
                        cout << "Anno: "; cin >> a;
                    }
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << g << "/" << m << "/" << a << endl;
                    mat.close();
                    break;
                }
                case '2':{
                    mat.open(materia + "_" + username + ".txt", ios::app);
                    mat << votomat << endl << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;
                    mat.close();
                    break;
                }
                default: break;
            }
            cout << "Voto inserito con successo";
                sleep(2);
            break;
        }
        else if(materia == "exit"){
            return;
        }
        else{
            cout << "Non e' stata trovata alcuna materia chiamata " << materia << ". Riprova.\n";
            sleep(2);
            clearscreen();
            cout << "Matematica(mat)\nItaliano(ita)\nStoria(sto)\nSistemi e Reti(siret)\nInformatica(inf)\nReligione(rel)\nEducazione Fisica(edfis)\n";
            cout << "Tecnologie e Progettazione di Sistemi Informatici e Telecomunicazioni(tpsit)\nTelecomunicazioni(tlc)\nInglese(ing)\n";
            cout << "Scrivere EXIT per terminare l'inserimento dei voti.\n";
        }
    }while(true);
}

void calcola_media_singola(string username){
    clearscreen();
    int contamaterie = 0;
    float mediaglob = 0;
    float sommaglob = 0;
    float votiglob = 0;
    cout << "------------------------|" << endl;
    do{
        string materia;
        switch(contamaterie){
            case 0:{
                materia = "mat";
                break;
            }
            case 1:{
                materia = "ita";
                break;
            }
            case 2:{
                materia = "sto";
                break;
            }
            case 3:{
                materia = "siret";
                break;
            }
            case 4:{
                materia = "inf";
                break;
            }
            case 5:{
                materia = "rel";
                break;
            }
            case 6:{
                materia = "edfis";
                break;
            }
            case 7:{
                materia = "tpsit";
                break;
            }
            case 8:{
                materia = "tlc";
                break;
            }
            case 9:{
                materia = "ing";
                break;
            }
            default : break;
        }
        float media = 0;
        float somma = 0;
        int cont = 0;
        float cont1 = 0;
        string voto;

            ifstream fin(materia + "_" + username + ".txt");
            while(getline(fin, voto)){
                if(cont % 2 == 0){
                    float voto_num = stof(voto);
                    if(voto_num >= 1){
                        somma += voto_num;
                        cont1++;
                    }
                }
                cont++;
            }
            if(cont1 != 0){
                media = somma / cont1;
                cout << materia << " : ";
                if(media >= 1 && media < 5){
                    cout << "\033[31m" << media << "\033[0m" << endl;
                }
                if(media >= 5 && media < 6){
                    cout << "\033[33m" << media << "\033[0m" << endl;
                }
                if(media >= 6){
                    cout << "\033[32m" << media << "\033[0m" << endl;
                }
                cout << "------------------------|" << endl;
                sommaglob += media;
                votiglob++;
            }else{
                cout << materia << " : " << "nessun voto." << endl;
                cout << "------------------------|" << endl;
            }
            fin.close();
            contamaterie++;
    }while(contamaterie != 10);
    if(votiglob != 0){
        mediaglob = sommaglob / (float)votiglob;
        cout << "MEDIA GLOBALE: " ;
        if(mediaglob >= 1 && mediaglob < 5){
                    cout << "\033[31m" << mediaglob << "\033[0m" << endl;
                }
                if(mediaglob >= 5 && mediaglob < 6){
                    cout << "\033[33m" << mediaglob << "\033[0m" << endl;
                }
                if(mediaglob >= 6){
                    cout << "\033[32m" << mediaglob << "\033[0m" << endl;
                }
        cout << "------------------------|" << endl;
    }else{
        cout << "MEDIA GLOBALE : ancora nessun voto" << endl;
        cout << "------------------------|" << endl;
    }
    cin.ignore();
    cout << "Premere invio per continuare.";
    getchar();
}

void tolowera_la_stringa(string riga){
    for(int i = 0; i < riga.length(); i++){
        riga[i] = tolower(riga[i]);
    }
}

bool dataValida(int g, int m, int a){
    if(a < 0 || m < 1 || m > 12 || g < 1 || g > 31){
        return false;
    }else{
        int giorni = verificaGgMese(a,m);
        if(g > giorni){
        return false;
    }
    if(a < 2000 || a > 2100){
        return false;
    }
    }
    return true;
}

bool annoBis(int a){
    if(a%400==0){
        return true;
    }
    if(a % 4 == 0 && a % 100 != 0){
        return true;
    }
    return false;
}

int verificaGgMese(int a, int m){
    switch(m){
        case 1:
            return 31;
            break;
        case 2:
            if(annoBis(a)){
                return 29;
            }
            else{
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

bool controllo_voto(float votomat){
    if(votomat > 10){
        return false;
    }
    else if(votomat < 1){
        return false;
    }
    return true;
}

bool controllo_ora_rit(int h, int min){
    if(h >= 8 && h <= 10 && min >= 0 && min < 60){
        return true;
    }
    return false;
}

bool controllo_ora_usc(int h, int min){
    if(h < 8 || h > 14){
        return false;
    }
    else if(h == 14){
        if(min > 0 || min < 0){
            return false;
        }
    }
    else if(min < 0 || min > 60){
        return false;
    }
        return true;
}

void inserimento_assenze(string user){
    int scelta;
    string data;
    ofstream ass, rit, usc;
    cout << "Benvenuto nell'interfaccia di inserimento assenze/ritardi/uscite anticipate" << endl;
    do{
        cout << "1)Inserimento assenze\n2)Inserimento ritardi\n3)Inserimento uscite anticipate\n0)Torna indietro\n";
        cout << "SCEGLI: ";
        cin >> scelta;

        clearscreen();

        time_t now = std::time(0);
        tm *ltm = std::localtime(&now);

        if(scelta == 1){
            cout << "1)Inserire la data dell'assenza manualmente(gg/mm/aaaa)\n2)Inserimento automatico dell'assenza in base alla data odierna\nSCEGLI:";
            char sceltadata;
            cin >> sceltadata;
            while(sceltadata != '1' && sceltadata != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> sceltadata;
            }

            ass.open("ass_" + user + ".txt",ios::app);

            switch(sceltadata){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    char slash;
                    cout << "Inserire la data dell'assenza (gg/mm/aaaa): ";
                    cin >> g >> slash >> m >> slash >> a;
                    while(!dataValida(g, m, a)){
                        cout << "Data inserita non valida. Reinserire la data: " << endl;
                        cin >> g >> slash >> m >> slash >> a;
                    }
                    cout << "1)Giustificata\n2)Non Giustificata" << endl;
                    int giust = 0;
                    cout << "SCEGLI(1/2): "; cin >> giust;
                    while(giust < 1 || giust > 2){
                        cout << "Scelta inserita non valida. Reinserire la scelta(1/2): "; cin >> giust;
                    }
                    if(giust == 1){
                        ass << "Data assenza: " << g << "/" << m << "/" << a << " | " << "Giustificata" << endl;
                    }else{
                        ass << "Data assenza: " << g << "/" << m << "/" << a << " | " << "Non Giustificata" << endl;
                    }
                    cout << "Assenza inserita con successo!" << endl;
                    sleep(1);
                    clearscreen();
                    break;
                }
                case '2':{
                    cout << "1)Giustificata\n2)Non Giustificata"<<endl;
                    int giust = 0;
                    cout << "SCEGLI(1/2): "; cin >> giust;
                    while(giust < 1 || giust > 2){
                        cout << "Scelta inserita non valida. Reinserire la scelta(1/2): "; cin >> giust;
                    }
                    if(giust == 1){
                        ass << "Data assenza: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " | " << "Giustificata" << endl;
                    }else{
                        ass << "Data assenza: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " | " << "Non Giustificata" << endl;
                    }
                    cout << "Assenza inserita con successo!" << endl;
                    sleep(1);
                    clearscreen();
                    break;
                }
            }
            ass.close();
        }
        else if(scelta == 2){
            string oraent;
            cout << "1)Inserire la data del ritardo manualmente(gg/mm/aaaa)\n2)Inserimento automatico del ritardo in base alla data odierna\nSCEGLI:";
            char sceltadata;
            cin >> sceltadata;
            while(sceltadata != '1' && sceltadata != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> sceltadata;
            }

            rit.open("rit_" + user + ".txt",ios::app);

            switch(sceltadata){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    int h = 0;
                    int min = 0;
                    char duepunti;
                    char slash;
                    cout << "Inserire la data del ritardo (gg/mm/aaaa): ";
                    cin >> g >> slash >> m >> slash >> a;
                    while(!dataValida(g, m, a)){
                        cout << "Data inserita non valida. Reinserire la data: " << endl;
                        cin >> g >> slash >> m >> slash >> a;
                    }
                    do{
                        cout << "Inserire l'ora di entrata (h:m): ";
                        cin >> h >> duepunti >> min;
                        if(controllo_ora_rit(h, min)){
                            break;
                        }
                        else{
                            cout << "Ora inserita non valida (Le entrate sono previste dalle (8 alle 10:59)). Riprova." << endl;
                        }
                    }while(true);
                    cout << "1)Giustificato\n2)Non Giustificato" << endl;
                    int giust = 0;
                    cout << "SCEGLI(1/2): "; cin >> giust;
                    while(giust < 1 || giust > 2){
                        cout << "Scelta inserita non valida. Reinserire la scelta(1/2): "; cin >> giust;
                    }
                    if(giust == 1){
                        rit << "Data ritardo: " <<  g << "/" << m << "/" << a << " | Ora di entrata: " << h << ":" << min << " | " << "Giustificato" << endl;
                    }else{
                        rit << "Data ritardo: " <<  g << "/" << m << "/" << a << " | Ora di entrata: " << h << ":" << min << " | " << "Non Giustificato" << endl;
                    }

                    cout << "Ritardo inserito con successo!" << endl;

                    sleep(1);
                    clearscreen();
                    break;
                }
                case '2':{
                    int h = 0;
                    int min = 0;
                    char duepunti;

                    rit << "Data ritardo: " <<  ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year;

                    do{
                        cout << "Inserire l'ora di entrata (h:m): ";
                        cin >> h >> duepunti >> min;
                        if(controllo_ora_rit(h, min)){
                            break;
                        }
                        else{
                            cout << "Ora inserita non valida (Le entrate sono previste dalle (8 alle 10:59)). Riprova." << endl;
                        }
                    }while(true);
                    cout << "1)Giustificato\n2)Non Giustificato" << endl;
                    int giust = 0;
                    cout << "SCEGLI(1/2): "; cin >> giust;
                    while(giust < 1 || giust > 2){
                        cout << "Scelta inserita non valida. Reinserire la scelta(1/2): "; cin >> giust;
                    }
                    if(giust == 1){
                        rit << " | Ora di entrata: " << h << ":" << min << " | " << "Giustificato" << endl;
                    }else{
                        rit << " | Ora di entrata: " << h << ":" << min << " | " << "Non Giustificato" << endl;
                    }

                    cout << "Ritardo inserito con successo!" << endl;

                    sleep(1);
                    clearscreen();
                    break;
                }
            }
            rit.close();
        }
        else if(scelta == 3){
            string orausc;
            cout << "1)Inserire la data dell'uscita anticipata manualmente(gg/mm/aaaa)\n2)Inserimento automatico dell'uscita anticipata in base alla data odierna\nSCEGLI:";
            char sceltadata;
            cin >> sceltadata;
            while(sceltadata != '1' && sceltadata != '2'){
                cout << "Scelta inserita non valida. Reinserire cosa si vuole fare(1/2): ";
                cin >> sceltadata;
            }

            usc.open("usc_" + user + ".txt",ios::app);

            switch(sceltadata){
                case '1':{
                    int g = 0;
                    int m = 0;
                    int a = 0;
                    int h = 0;
                    int min = 0;
                    char duepunti;
                    char slash;
                    cout << "Inserire la data dell'uscita anticipata (gg/mm/aaaa): ";
                    cin >> g >> slash >> m >> slash >> a;
                    while(!dataValida(g, m, a)){
                        cout << "Data inserita non valida. Reinserire la data: " << endl;
                        cin >> g >> slash >> m >> slash >> a;
                    }
                    do{
                        cout << "Inserire l'ora di uscita (h:m): ";
                        cin >> h >> duepunti >> min;
                        if(controllo_ora_usc(h, min)){
                            break;
                        }
                        else{
                            cout << "Ora inserita non valida (Le uscite anticipate sono previste dalle (8 alle 14)). Riprova." << endl;
                        }
                    }while(true);

                    usc << "Data dell'uscita anticipata: " <<  g << "/" << m << "/" << a << " | Ora di uscita: " << h << ":" << min << endl;

                    cout << "Uscita anticipata inserita con successo!" << endl;
                    sleep(1);
                    clearscreen();
                    break;
                }
                case '2':{
                    int h = 0;
                    int min = 0;
                    char duepunti;

                    usc << "Data dell'uscita anticipata: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year;

                    do{
                        cout << "Inserire l'ora di uscita (h:m): ";
                        cin >> h >> duepunti >> min;
                        if(controllo_ora_usc(h, min)){
                            break;
                        }
                        else{
                            cout << "Ora inserita non valida (Le uscite anticipate sono previste dalle (8 alle 14)). Riprova." << endl;
                        }
                    }while(true);

                    usc << " | Ora di uscita: " << h << ":" << min << endl;

                    cout << "Uscita anticipata inserita con successo!" << endl;

                    sleep(1);
                    clearscreen();
                    break;
                }
            }
            usc.close();
        }
        else if(scelta == 0){
            return;
        }
        else{
            cout << "Scelta inserita non valida. Riprova." << endl;
            sleep(1);
        }
    }while(true);
}

void visuRitUscAss(string user){
    cout << "Benvenuto nell'interfaccia di visualizzazione assenze/ritardi/uscite anticipate" << endl;
    do{
        cout << "1)Visualizzazione assenze\n2)Visualizzazione ritardi\n3)Visualizzazione uscite anticipate\n0)Torna indietro\n";
        cout << "SCEGLI(da 0 a 3): ";
        ifstream fin;
        int scelta = 0;
        cin >> scelta;
        while(scelta < 0 || scelta > 3){
            cout << "Scelta inserita non valida.";
            sleep(1);
            clearscreen();
            cout << "1)Visualizzazione assenze\n2)Visualizzazione ritardi\n3)Visualizzazione uscite anticipate\n0)Torna indietro\n";
            cout << "SCEGLI(da 0 a 3): ";
            cin >> scelta;
        }
        switch(scelta){
            case 0:{
                return;
            }
            case 1:{
                fin.open("ass_" + user + ".txt");
                string riga;
                clearscreen();
                cout << "Qui seguiranno le tue assenze: " << endl;
                int cont = 0;
                while(getline(fin,riga)){
                    cout << riga << endl;
                    cont++;
                }
                cout << "Hai " << cont << " assenze " << endl;
                fin.close();
                cin.ignore();
                cout << "premere invio per continuare " ; getchar();
                clearscreen();
                break;
            }
            case 2:{
                fin.open("rit_" + user + ".txt");
                string riga;
                clearscreen();
                cout << "Qui seguiranno i tuoi ritardi: " << endl;
                int cont = 0;
                while(getline(fin,riga)){
                    cout << riga << endl;
                    cont++;
                }
                cout << "Hai " << cont << " ritardi " << endl;
                fin.close();
                cin.ignore();
                cout << "premere invio per continuare " ; getchar();
                clearscreen();
                break;
            }
            case 3:{
                fin.open("usc_" + user + ".txt");
                string riga;
                clearscreen();
                cout << "Qui seguiranno le tue uscite anticipate: " << endl;
                int cont = 0;
                while(getline(fin,riga)){
                    cout << riga << endl;
                    cont++;
                }
                cout << "Hai " << cont << " uscite anticipate " << endl;
                fin.close();
                cin.ignore();
                cout << "premere invio per continuare " ; getchar();
                clearscreen();
                break;
            }
            default: break;
        }
    }while(true);
}

void visugeneralevoti(string user){
    ifstream fin;
    int contamaterie = 0;
    do{
        string materia;
        switch(contamaterie){
            case 0:{
                materia = "mat";
                break;
            }
            case 1:{
                materia = "ita";
                break;
            }
            case 2:{
                materia = "sto";
                break;
            }
            case 3:{
                materia = "siret";
                break;
            }
            case 4:{
                materia = "inf";
                break;
            }
            case 5:{
                materia = "rel";
                break;
            }
            case 6:{
                materia = "edfis";
                break;
            }
            case 7:{
                materia = "tpsit";
                break;
            }
            case 8:{
                materia = "tlc";
                break;
            }
            case 9:{
                materia = "ing";
                break;
            }
            default : break;
        }
        string riga;
        fin.open(materia + "_" + user + ".txt");
        int cont = 0;
        cout << "---------- " << materia << " ----------" << endl;
        while(getline(fin,riga)){
            cont++;
            if(cont % 2 != 0){
                float votonum = stof(riga);
                if(votonum >= 1 && votonum < 5){
                    cout << "\033[31m" << riga << "\033[0m" ;
                }
                if(votonum >= 5 && votonum < 6){
                    cout << "\033[33m" << riga << "\033[0m" ;
                }
                if(votonum >= 6){
                    cout << "\033[32m" << riga << "\033[0m";
                }
                cout << " Preso il: ";
            }
            if(cont % 2 == 0 && cont != 0){
                cout << riga;
                cout << endl;
            }
        }
        if(cont == 0){
            cout << "ANCORA NESSUN VOTO!" << endl;
        }
        fin.close();
        contamaterie++;
    }while(contamaterie != 10);
    cin.ignore();
    cout << "Premere invio per tornare indietro!";
    getchar();
}

void rimozione_voti(string user){
    string materia;
    string voto_da_rimuovere;

    cout << "In quale materia vuoi rimuovere un voto?" << endl;
    cout << "Matematica(mat)\nItaliano(ita)\nStoria(sto)\nSistemi e Reti(siret)\nInformatica(inf)\nReligione(rel)\nEducazione Fisica(edfis)\n";
    cout << "Tecnologie e Progettazione di Sistemi Informatici e Telecomunicazioni(tpsit)\nTelecomunicazioni(tlc)\nInglese(ing)\n";
    cout << "Inserisci la materia: ";
    cin >> materia;
    while(!materiainseritocorrettamente(materia)){
        cout << "materia inserita non valida. Reinserire la materia: ";
        cin >> materia;
    }
    clearscreen();
    
    cout << "Inserisci il voto da rimuovere: ";
    cin >> voto_da_rimuovere;
    float var = stof(voto_da_rimuovere);
    while(!controllo_voto(var)){
        cout << "Voto inserito non valido. Reinserire il voto: "; 
        cin >> voto_da_rimuovere;
        var = stof(voto_da_rimuovere);
    }
    cout << "1) Inserire la data manualmente (es. gg/mm/anno)\n2) Inserimento automatico della data odierna\nCosa vuoi fare (1/2): ";
    char scelta;
    cin >> scelta;
    while(scelta != '1' && scelta != '2'){
        cout << "Scelta inserita non valida. Reinserire cosa si vuole fare (1/2): ";
        cin >> scelta;
    }
    string data;
    switch(scelta){
        case '1': {
            int g = 0;
            int m = 0;
            int a = 0;
            cout << "inserire la data: "; cin >> data;
            
            string dataEffettiva = to_string(g) + to_string(m) + to_string(a);
            break;
        }
        case '2': {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            data = dataOdierna();
            break;
        }
        default: break;
    }


    tolowera_la_stringa(materia);


    ifstream file_lettura(materia + "_" + user + ".txt");
    ofstream file_temp("temp.txt");

    string riga;
    bool rimuovi_riga_successiva = false; 
    bool voto_trovato = false; 
    while(getline(file_lettura, riga)){
        if(!voto_trovato && riga.find(voto_da_rimuovere) != string::npos && getline(file_lettura, riga) && riga.find(data) != string::npos){
            voto_trovato = true;
            continue;
        }
        file_temp << riga << endl;
    }

    file_lettura.close();
    file_temp.close();

    remove((materia + "_" + user + ".txt").c_str());
    rename("temp.txt", (materia + "_" + user + ".txt").c_str());
    cout << "Voto rimosso con successo." << endl;
    sleep(2);
    clearscreen();
}

string dataOdierna(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    stringstream ss;
    ss << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year;

    return ss.str();
}

bool materiainseritocorrettamente(string materia){
    if(materia == "mat" || materia == "tpsit" || materia == "tlc" || materia == "rel" || materia == "siret" || materia == "edfis" || 
    materia == "inf" || materia == "ing" || materia == "ita" || materia == "sto"){
        return true;
    }
    return false;
}
