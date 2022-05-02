#include <iostream>
 #include <stdlib.h>
  #include <cstdio>
  #include <ctime>
  #include <unistd.h>
   #include <windows.h>
    #include <string.h>
     #include <conio.h>
      #include <dos.h>

  using namespace std;

char ru[40][40], zir[40][40], point[40][40];
int bombi[400], bombj[400], bt[40][40], v = 0;
void porzirVruVflag(int tool) {
  for (int i = 0; i < tool; i++)
    for (int j = 0; j < tool; j++) {
      zir[i][j] = '0';
      ru[i][j] = ' ';
      bt[i][j] = 0;
    }
}

void rang(int textColor, int backColor = 0)

{

  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  int colorAttribute = backColor << 4 | textColor;

  SetConsoleTextAttribute(consoleHandle, colorAttribute);

}

void khali(int i, int j, int tool) {
  if (ru[i][j] == ' ' && zir[i][j] != '!' && i >= 0 && i < tool && j >= 0 && j < tool) {
    ru[i][j] = zir[i][j];

    if (zir[i][j] == '0') {
      khali(i - 1, j - 1, tool);
      khali(i, j - 1, tool);
      khali(i, j + 1, tool);
      khali(i - 1, j, tool);
      khali(i + 1, j - 1, tool);
      khali(i - 1, j + 1, tool);
      khali(i + 1, j, tool);
      khali(i + 1, j + 1, tool);
    }
  }
}

void jadval(int tool) {

  rang(11, 0);
  cout << "    ";
  for (int j = 1; j <= tool; j++) {

    if (j < 10)
      cout << " ";
    cout << j << " " << " ";
  }
  cout << endl << "   ";

  for (int i = 0; i < tool; i++)

    cout << "____";
  cout << endl;
  for (int j = 0; j < tool; j++) {
    if (j + 1 < 10)

      cout << j + 1 << "  |";
    else
      cout << j + 1 << " |";
    for (int k = 0; k < tool; k++) {

      cout << " ";

      cout << ru[j][k];
      rang(14, 0);
      cout << point[j][k];
      rang(11, 0);
      cout << "|";
    }

    cout << endl << "   ";
    for (int f = 0; f < tool; f++)
      cout << "|___";
    cout << "|" << endl;
  }
  rang(14, 0);

  cout << "Hint :" << endl << "W  ===> Up" << endl << "S  ===> Down" << endl << "A  ===> Left" << endl << "D  ===> Right" << endl << endl;
  rang(11, 0);
}
int randm(int tool) {

  int x = rand() % tool;

  return x;
}
int por(int bomb, int tool) {
  while (v < bomb) {
    bombi[v] = randm(tool);
    bombj[v] = randm(tool);
    if (bt[bombi[v]][bombj[v]] == 0) {
      bt[bombi[v]][bombj[v]] = 1;
      v++;
    }
  }
  v = 0;
  for (int f = 0; f < bomb; f++) {
    if (zir[bombi[f]][bombj[f] - 1] != '!' && bombi[f] >= 0 && bombi[f] < tool && bombj[f] - 1 >= 0 && bombj[f] - 1 < tool)
      zir[bombi[f]][bombj[f] - 1] += 1;

    if (zir[bombi[f] - 1][bombj[f]] != '!' && bombi[f] - 1 >= 0 && bombi[f] - 1 < tool && bombj[f] >= 0 && bombj[f] < tool)
      zir[bombi[f] - 1][bombj[f]] += 1;

    if (zir[bombi[f]][bombj[f] + 1] != '!' && bombi[f] >= 0 && bombi[f] < tool && bombj[f] + 1 >= 0 && bombj[f] + 1 < tool)
      zir[bombi[f]][bombj[f] + 1] += 1;

    if (zir[bombi[f] - 1][bombj[f] - 1] != '!' && bombi[f] - 1 >= 0 && bombi[f] - 1 < tool && bombj[f] - 1 >= 0 && bombj[f] - 1 < tool)
      zir[bombi[f] - 1][bombj[f] - 1] += 1;

    if (zir[bombi[f] - 1][bombj[f] + 1] != '!' && bombi[f] - 1 >= 0 && bombi[f] - 1 < tool && bombj[f] + 1 >= 0 && bombj[f] + 1 < tool)
      zir[bombi[f] - 1][bombj[f] + 1] += 1;

    if (zir[bombi[f] + 1][bombj[f]] != '!' && bombi[f] + 1 >= 0 && bombi[f] + 1 < tool && bombj[f] >= 0 && bombj[f] < tool)
      zir[bombi[f] + 1][bombj[f]] += 1;

    if (zir[bombi[f] + 1][bombj[f] - 1] != '!' && bombi[f] + 1 >= 0 && bombi[f] + 1 < tool && bombj[f] - 1 >= 0 && bombj[f] - 1 < tool)
      zir[bombi[f] + 1][bombj[f] - 1] += 1;

    if (zir[bombi[f] + 1][bombj[f] + 1] != '!' && bombi[f] + 1 >= 0 && bombi[f] + 1 < tool && bombj[f] + 1 >= 0 && bombj[f] + 1 < tool)
      zir[bombi[f] + 1][bombj[f] + 1] += 1;

  }
  for (int f = 0; f < bomb; f++)
    zir[bombi[f]][bombj[f]] = '!';

}
void game() {

  int i, j, bomb, tool, tempi = 0, tempj = 0;
  char s = '\a', x;
  rang(15, 0);
  cout << "Enter size of game:";
  cin >> tool;
  cout << "Enter amount of bomb:";
  cin >> bomb;
  cout << endl;
  srand(time(0));
  int flag = 0;
  porzirVruVflag(tool);

  por(bomb, tool);

  point[0][0] = 221;
  jadval(tool);
  std::clock_t start;
  double duration;
  start = std::clock();
  while (flag != 1) {
    int flg = 1;
    while ((x = getch()) != 13) {

      if (x == 's') //down
      {
        tempi += 1;
        if (1) {
          point[tempi - 1][tempj] = ' ';
          point[tempi][tempj] = 221;
          system("cls");
          jadval(tool);
        }
      }
      if (x == 'a') //left{
      {
        tempj -= 1;
        if (1) {
          point[tempi][tempj + 1] = ' ';
          point[tempi][tempj] = 221;
          system("cls");
          jadval(tool);
        }
      }

      if (x == 'd') //right{
      {
        tempj += 1;
        if (1) {
          point[tempi][tempj - 1] = ' ';
          point[tempi][tempj] = 221;
          system("cls");
          jadval(tool);
        }
      }
      if (x == 'w') //up
      {
        tempi -= 1;
        if (1) {
          point[tempi + 1][tempj] = ' ';
          point[tempi][tempj] = 221;
          system("cls");
          jadval(tool);
        }
      }

    }

    i = tempi;
    j = tempj;
    cout << "Are you sure?y or n" << endl;
    char m;
    cin >> m;
    if (m == 'n'&&ru[i][j]==' ') {
      ru[i][j] = '^';
      system("cls");
      jadval(tool);
    } else
    if (zir[i][j] == '!') {
      flag = 1;
      for (int i = 0; i < tool; i++)
        for (int j = 0; j < tool; j++)
          ru[i][j] = zir[i][j];
      system("cls");
      jadval(tool);
      cout << endl << endl << endl << endl << endl << "                                              ";
      rang(12, 0);
      cout << endl;

      cout << "        ggggggggg   ggggg aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee            ooooooooooo vvvvvvv           vvvvvvv eeeeeeeeeeee    rrrrr   rrrrrrrrr                 " << endl;
      cout << "       g:::::::::ggg::::g a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee        oo:::::::::::oov:::::v         v:::::vee::::::::::::ee  r::::rrr:::::::::r            " << endl;
      cout << "      g:::::::::::::::::g aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee     o:::::::::::::::ov:::::v       v:::::ve::::::eeeee:::::eer:::::::::::::::::r               " << endl;
      cout << "     g::::::ggggg::::::gg          a::::a m::::::::::::::::::::::me::::::e     e:::::e     o:::::ooooo:::::o v:::::v     v:::::ve::::::e     e:::::err::::::rrrrr::::::r          " << endl;
      cout << "     g:::::g     g:::::g    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e     o::::o     o::::o  v:::::v   v:::::v e:::::::eeeee::::::e r:::::r     r:::::r      " << endl;
      cout << "     g:::::g     g:::::g  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e      o::::o     o::::o   v:::::v v:::::v  e:::::::::::::::::e  r:::::r     rrrrrrr" << endl;
      cout << "     g:::::g     g:::::g a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee       o::::o     o::::o    v:::::v:::::v   e::::::eeeeeeeeeee   r:::::r            " << endl;
      cout << "     g::::::g    g:::::ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e                o::::o     o::::o     v:::::::::v    e:::::::e            r:::::r            " << endl;
      cout << "     g:::::::ggggg:::::ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e               o:::::ooooo:::::o      v:::::::v     e::::::::e           r:::::r            " << endl;
      cout << "      g::::::::::::::::ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee       o:::::::::::::::o       v:::::v       e::::::::eeeeeeee   r:::::r            " << endl;
      cout << "       gg::::::::::::::g a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e        oo:::::::::::oo         v:::v         ee:::::::::::::e   r:::::r            " << endl;
      cout << "         gggggggg::::::g  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee          ooooooooooo            vvv            eeeeeeeeeeeeee   rrrrrrr            " << endl;
      cout << "                 g:::::g                                                                                                                                                " << endl;
      cout << "     gggggg      g:::::g                                                                                                                                                " << endl;
      cout << "     g:::::gg   gg:::::g                                                                                                                                                " << endl;
      cout << "      g::::::ggg:::::::g                                                                                                                                                " << endl;
      cout << "       gg:::::::::::::g                                                                                                                                                 " << endl;
      cout << "         ggg::::::ggg                                                                                                                                                   " << endl;
      cout << "            gggggg                                                                                                                                                      " << endl;

      rang(11, 0);

      cout << endl;

      for (int w = 0; w < 10; w++) {
        cout << s;
        cout << s;
        //sleep(1);
      }

    } else {
      ru[i][j] = ' ';
      khali(i, j, tool);
      system("cls");
      jadval(tool);
    }
    for (int i = 0; i < tool; i++)
      for (int j = 0; j < tool; j++) {
        if (ru[i][j] == ' ' && zir[i][j] != '!') {
          flg = 0;
        }

      }
    if (flg == 1 && flag != 1) {

      rang(10, 0);
      cout << "     YYYYYYY       YYYYYYY     OOOOOOOOO     UUUUUUUU     UUUUUUUU     WWWWWWWW                           WWWWWWWWIIIIIIIIIINNNNNNNN        NNNNNNNN          " << endl;
      cout << "     Y:::::Y       Y:::::Y   OO:::::::::OO   U::::::U     U::::::U     W::::::W                           W::::::WI::::::::IN:::::::N       N::::::N          " << endl;
      cout << "     Y:::::Y       Y:::::Y OO:::::::::::::OO U::::::U     U::::::U     W::::::W                           W::::::WI::::::::IN::::::::N      N::::::N              " << endl;
      cout << "     Y::::::Y     Y::::::YO:::::::OOO:::::::OUU:::::U     U:::::UU     W::::::W                           W::::::WII::::::IIN:::::::::N     N::::::N              " << endl;
      cout << "     YYY:::::Y   Y:::::YYYO::::::O   O::::::O U:::::U     U:::::U       W:::::W           WWWWW           W:::::W   I::::I  N::::::::::N    N::::::N              " << endl;
      cout << "        Y:::::Y Y:::::Y   O:::::O     O:::::O U:::::D     D:::::U        W:::::W         W:::::W         W:::::W    I::::I  N:::::::::::N   N::::::N              " << endl;
      cout << "         Y:::::Y:::::Y    O:::::O     O:::::O U:::::D     D:::::U         W:::::W       W:::::::W       W:::::W     I::::I  N:::::::N::::N  N::::::N                  " << endl;
      cout << "          Y:::::::::Y     O:::::O     O:::::O U:::::D     D:::::U          W:::::W     W:::::::::W     W:::::W      I::::I  N::::::N N::::N N::::::N                  " << endl;
      cout << "           Y:::::::Y      O:::::O     O:::::O U:::::D     D:::::U           W:::::W   W:::::W:::::W   W:::::W       I::::I  N::::::N  N::::N:::::::N                  " << endl;
      cout << "            Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U            W:::::W W:::::W W:::::W W:::::W        I::::I  N::::::N   N:::::::::::N                  " << endl;
      cout << "            Y:::::Y       O:::::O     O:::::O U:::::D     D:::::U             W:::::W:::::W   W:::::W:::::W         I::::I  N::::::N    N::::::::::N              " << endl;
      cout << "            Y:::::Y       O::::::O   O::::::O U::::::U   U::::::U              W:::::::::W     W:::::::::W          I::::I  N::::::N     N:::::::::N              " << endl;
      cout << "            Y:::::Y       O:::::::OOO:::::::O U:::::::UUU:::::::U               W:::::::W       W:::::::W         II::::::IIN::::::N      N::::::::N                  " << endl;
      cout << "         YYYY:::::YYYY     OO:::::::::::::OO   UU:::::::::::::UU                 W:::::W         W:::::W          I::::::::IN::::::N       N:::::::N                  " << endl;
      cout << "         Y:::::::::::Y       OO:::::::::OO       UU:::::::::UU                    W:::W           W:::W           I::::::::IN::::::N        N::::::N              " << endl;
      cout << "         YYYYYYYYYYYYY         OOOOOOOOO           UUUUUUUUU                       WWW             WWW            IIIIIIIIIINNNNNNNN         NNNNNNN                  " << endl;

      rang(11, 0);

      break;
    }
  }
  duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
  rang(10, 0);
  std::cout << endl << "Your record: " << duration << " s" << '\n' << endl;
  rang(11, 0);
  cout << "Do you want play again? type y or n" << endl;
  char t;

  cin >> t;

  if (t == 'y') {
    point[tempi][tempj] = ' ';

    game();
  }

}
void load() {
  char g = 254;
  cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
  rang(13, 0);
  cout << "                                                                     dddddddd                                              " << endl;
  cout << "               lllllll                                               d::::::d  iiii                                       " << endl;
  cout << "               l:::::l                                               d::::::d i::::i                                      " << endl;
  cout << "               l:::::l                                               d::::::d  iiii                                       " << endl;
  cout << "               l:::::l                                               d:::::d                                              " << endl;
  cout << "               l::::l    ooooooooooo     aaaaaaaaaaaaa      ddddddddd:::::d iiiiiiinnnn  nnnnnnnn       ggggggggg   ggggg" << endl;
  cout << "               l::::l  oo:::::::::::oo   a::::::::::::a   dd::::::::::::::d i:::::in:::nn::::::::nn    g:::::::::ggg::::g" << endl;
  cout << "               l::::l o:::::::::::::::o  aaaaaaaaa:::::a d::::::::::::::::d  i::::in::::::::::::::nn  g:::::::::::::::::g" << endl;
  cout << "               l::::l o:::::ooooo:::::o           a::::ad:::::::ddddd:::::d  i::::inn:::::::::::::::ng::::::ggggg::::::gg" << endl;
  cout << "               l::::l o::::o     o::::o    aaaaaaa:::::ad::::::d    d:::::d  i::::i  n:::::nnnn:::::ng:::::g     g:::::g " << endl;
  cout << "               l::::l o::::o     o::::o  aa::::::::::::ad:::::d     d:::::d  i::::i  n::::n    n::::ng:::::g     g:::::g " << endl;
  cout << "               l::::l o::::o     o::::o a::::aaaa::::::ad:::::d     d:::::d  i::::i  n::::n    n::::ng:::::g     g:::::g " << endl;
  cout << "               l::::l o::::o     o::::oa::::a    a:::::ad:::::d     d:::::d  i::::i  n::::n    n::::ng::::::g    g:::::g " << endl;
  cout << "               l::::::lo:::::ooooo:::::oa::::a    a:::::ad::::::ddddd::::::ddi::::::i n::::n    n::::ng:::::::ggggg:::::g " << endl;
  cout << "               l::::::lo:::::::::::::::oa:::::aaaa::::::a d:::::::::::::::::di::::::i n::::n    n::::n g::::::::::::::::g " << endl;
  cout << "               l::::::l oo:::::::::::oo  a::::::::::aa:::a d:::::::::ddd::::di::::::i n::::n    n::::n  gg::::::::::::::g " << endl;
  cout << "               llllllll   ooooooooooo     aaaaaaaaaa  aaaa  ddddddddd   dddddiiiiiiii nnnnnn    nnnnnn    gggggggg::::::g " << endl;
  cout << "                                                                                                                  g:::::g " << endl;
  cout << "                                                                                                      gggggg      g:::::g " << endl;
  cout << "                                                                                                      g:::::gg   gg:::::g " << endl;
  cout << "                                                                                                       g::::::ggg:::::::g " << endl;
  cout << "                                                                                                        gg:::::::::::::g  " << endl;
  cout << "                                                                                                          ggg::::::ggg    " << endl;
  cout << "                                                                                                             gggggg       " << endl;

  cout << endl;
  cout << "                ";
  for (int i = 0; i < 105; i++) {
    Sleep(60);
    if(i==20||i==60||i==100)
        Sleep(1000);
    rang(5, 0);
    cout << g;
  }
  rang(10, 0);
  cout << endl << "                                                                  %100    " << endl;
  //delay(3000);
  Sleep(3000);

  rang(11, 0);

  system("cls");
}
int main() {
  load();

  game();

  return 0;
}
