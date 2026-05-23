#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "cenario.h"
#include "caixadetexto.h"

void mostrartexto(const char *texto);


int rx;
int ry;

int xc=0;
int yc=0;

int coins=0;
int vida=9;
int chave=0;

void vercenario(){
    xc=0;
    yc=0;
    while(xc<100){
        while(yc<20){
            mvaddch(yc, xc, cenario[yc][xc]);
            yc++;
        }
        xc++;
        yc=0;
    }
    
}

int xp=2;
int yp=2;

void verp(){
    mvaddch(yp, xp, '@');
}



int t;

void moverp() {

    int nx = xp;
    int ny = yp;

    t = getch();

    
    

    switch(t) {
        //eu sei que não era pra estar aqui mas estou com preguiça de reafazer certo
        case 'h':

        mostrartexto(
            "use the arrow keys to move\n"
            "collect coins ($)\n"
            "avoid bombs (*)\n"
            "you can also find keys (+)\n"
            "to open doors (:)\n"
            "press q to close any message"
        );

    return;

        case KEY_UP:
            ny--;
            break;

        case KEY_DOWN:
            ny++;
            break;

        case KEY_LEFT:
            nx--;
            break;

        case KEY_RIGHT:
            nx++;
            break;

        default:
            return;
    }



    char bloco = cenario[ny][nx];



    if(bloco == '#') {
        return;
    }



    if(bloco == ':') {

        if(chave > 0) {

            chave--;

            cenario[ny][nx] = ' ';

        } else {

            mostrartexto("you need a key to open this door");

            return;
        }
    }



    xp = nx;
    yp = ny;



    if(cenario[yp][xp] == '$') {

        coins++;

        cenario[yp][xp] = ' ';
    }



    if(cenario[yp][xp] == '*') {

        vida--;

        cenario[yp][xp] = ' ';
    }



    if(cenario[yp][xp] == '+') {

        chave++;

        cenario[yp][xp] = ' ';
    }
}


//void status(){
//    cenario[1][58]=vida+'0';
//    cenario[2][58]=coins+'0';
//}
int i;

void gcoins(){

    i = 0;

    while(i < 9){

        ry = rand() % 16 + 3;
        rx = rand() % 47 + 2;

        if(cenario[ry][rx] == ' '){

            cenario[ry][rx] = '$';

            i++;
        }
    }
}

void gbombs(){

    i = 0;

    while(i < 9){

        ry = rand() % 16 + 3;
        rx = rand() % 47 + 2;

        if(cenario[ry][rx] == ' '){

            cenario[ry][rx] = '*';

            i++;
        }
    }
}


void limparcaixa() {

    
    int x;

    for(x = 1; x < 19; x++) {

        caixadetexto[2][x] = ' ';
    }
}



void mostrartexto(const char *texto) {

    int xt;
    int yt;
    char q = 0;

    int largura = 50;
    int altura = 10;

    int iniciox = (100 - largura) / 2;
    int inicioy = (20 - altura) / 2;

    char caixa[10][50];



    for(yt = 0; yt < altura; yt++) {

        for(xt = 0; xt < largura; xt++) {

            caixa[yt][xt] = ' ';
        }
    }



    caixa[0][0] = '+';
    caixa[0][largura - 1] = '+';

    caixa[altura - 1][0] = '+';
    caixa[altura - 1][largura - 1] = '+';



    for(xt = 1; xt < largura - 1; xt++) {

        caixa[0][xt] = '-';
        caixa[altura - 1][xt] = '-';
    }



    for(yt = 1; yt < altura - 1; yt++) {

        caixa[yt][0] = '|';
        caixa[yt][largura - 1] = '|';
    }



    int linha = 2;
    int coluna = 2;
    int i = 0;



    while(texto[i] != '\0') {

        if(texto[i] == '\n') {

            linha++;
            coluna = 2;
            i++;

            continue;
        }



        if(coluna >= largura - 2) {

            linha++;
            coluna = 2;
        }



        if(linha >= altura - 2) {

            break;
        }



        caixa[linha][coluna] = texto[i];

        coluna++;
        i++;
    }



    while(q != 'q') {

        q = getch();

        clear();

        vercenario();
        verp();



        for(yt = 0; yt < altura; yt++) {

            for(xt = 0; xt < largura; xt++) {

                mvaddch(
                    inicioy + yt,
                    iniciox + xt,
                    caixa[yt][xt]
                );
            }
        }

        refresh();
    }

    clear();
}


int main() {
    
    srand(time(NULL));
    int v=0;
    int l=1;
   
    initscr();
    //set up
    curs_set(0);
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    noecho();
    mvprintw(10, 30, "jogo em c");
    mvprintw(20, 40, "double press h for help");
    refresh();
    sleep(3);
    clear();
    refresh();
    gbombs();
    gcoins();
    //clear();
        while(l){

        vercenario();
        verp();

        refresh();

        moverp();

        

        if(coins > 8){
            v = 1;
            l = 0;
        }

        if(vida < 1){
            l = 0;
        }
    }
    clear();
    if(v){
        mvprintw(10, 30, "victory");
        refresh();
    }else{
        mvprintw(10, 30, "game over");
        refresh();
    }
    sleep(10);
    
    endwin();
    return 0;
}
