#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdio.h>

using namespace std;

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct character{
    int x;
    int y;
};

struct obstacle{
    int x;
    int y;
    int intervalA;
    int intervalB;
};

struct checkPoint{
    int x;
    int y;
};

struct locCheckPoint{
    int x;
    int y;
};

struct finish{
    int x;
    int y;
};

void moveCharater(int x, int y){
    gotoxy(x,y); cout << "U";
}

void moveObstacle(int x, int y){
    gotoxy(x,y); cout << "X";
}

void deleteMoveCharacter(int x, int y){
    gotoxy(x,y); cout << " ";
}

void color(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void set_cursor(bool visible){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

main(){
    character c;
    obstacle o1[3], o2[5], o3[9];
    checkPoint cp;
    locCheckPoint lcp1, lcp2[2];
    finish f;
    int Set[] = {11,12,7,7}, y = 1, menu = 1, nObstacle = 0, nCp = 0, nyawa = 3; //Set = warna awal masing-masing menu //y = untuk pergerakan koordinat y menu
    char nama[100], inputKb;
    bool keluar = false, statusMenu1 = true;
    bool obs1_0 = true, obs1_1 = true, obs1_2 = true; //Untuk Obstacle Destinasi 1
    bool obs2_0 = true, obs2_1 = true, obs2_2 = true, obs2_3 = true, obs2_4 = true; //Untuk Obstacle Destinasi 2
    bool obs3_0 = true, obs3_1 = true, obs3_2 = true, obs3_3 = true, obs3_4= true, obs3_5 = true, obs3_6 = true, obs3_7 = true, obs3_8 = true;
    char mapDestinasi1[15][17] = {
    "################",
    "#U#            #",
    "# # # ##  #  # #",
    "# # # ##  #  # #",
    "#   #X##  #  # #",
    "########  #  ###",
    "#     #X       #",
    "# # # ###### # #",
    "# # #          #",
    "# #X############",
    "# # #   #   ####",
    "# # # # # # #  F",
    "# # # # # #   ##",
    "#     #   # # ##",
    "################",
    };
    char mapDestinasi2[15][35] = {
    "##################################",
    "#U#X#                # #F      # #",
    "#   ## # # # # ####### # ####### #",
    "### ## # # # # ##### # # ### ### #",
    "##     # # # #       # # ##  ### #",
    "### #### # #### ###### #        X#",
    "### #    #   ##   #  # #######   #",
    "### ############### ##     ##  # #",
    "##          #       ########  ## #",
    "### ####### # ##  ###    ##  ###X#",
    "### #   # # # ###  ## ####  #### #",
    "### # # #   #   ##  # #       X# #",
    "### # # ####### ### #C# ######## #",
    "##    #         #X               #",
    "##################################",
    };
    char mapDestinasi3[33][40] = {
    "#######################################",
    "#U#   #        ###   # #       #     ##",
    "# # # #  #X# #     #   # ##### # ###  #",
    "# # # # ## # ##### ##### #   # #   ####",
    "#   #   #      #         # # # # #    #",
    "# ####### ################ #   # #### #",
    "#       #    #   C  # ## # #####   #  #",
    "####### ###    ## # #  #   #   #   # ##",
    "#       # #####   #    # ### # #   # ##",
    "# ### ### #   # ###### # # # ###   #  #",
    "#   X # # #  #       #   # # # # ### ##",
    "# ##### # ####  # #  ##### # # # #   ##",
    "#     #     #   # ####     #   # ######",
    "####### ###   #X#    #   # # #     # ##",
    "#   #     ####### ################## ##",
    "#X                                    #",
    "#                                    X#",
    "# #### ########################## #####",
    "# #### ############             C #####",
    "# #    ########     ########### #######",
    "# # ## #    ### ############# # #     #",
    "# # ## # ## #             ### # # ### #",
    "#   X#   ## # ########### #   #   ### #",
    "#### ###### #   #         # ######### #",
    "#       ### ##### #########      #    #",
    "# ## ##   # ###     ####   ## ##   ####",
    "#    ####   ### ###    # # ## #########",
    "## # #   ####   ### ## # # ## ###     #",
    "## #   #    # #      #   #  #X  # ### #",
    "## ######## # #### #X## ### # # # ### #",
    "##  #       #    #       ## ###   #   #",
    "###   ##X     ##   ########     ### ###",
    "###################################F###",
    };

    set_cursor(false);

    do{
        if(menu == 1){
            y = 1;
            statusMenu1 = true;
            nyawa = 3;
            while(statusMenu1){
                system("cls"); color(7);
                cout<< "**       **         ****        **********   **********";
                cout<< "\n***     ***        **  **       **********   **";
                cout<< "\n** ** ** **       ********          ******   **********";
                cout<< "\n**  * *  **      **********     ******       **********";
                cout<< "\n**   *   **     **        **    **********   **";
                cout<< "\n**       **    **          **   **********   **********";
                cout<< "\nU ' S        E    X    I    T       P     L     A     N"<<endl;
                gotoxy(20,10); color(Set[0]); cout<< "-- M E N U --";
                gotoxy(15,12); color(Set[1]); cout<< "--> Mulai";
                gotoxy(15,13); color(Set[2]); cout<< "--> Tentang";
                gotoxy(15,14); color(Set[3]); cout<< "--> Keluar";
                gotoxy(20,17); color(Set[0]); cout << "** Kontrol **";
                gotoxy(16,18); color(7); cout << "W : Atas    S : Bawah";

                inputKb = getch();
                if(inputKb == 'w' || inputKb == 'W'){
                    y--;
                    if(y == 0)
                        y = 3;
                }
                if(inputKb == 's' || inputKb == 'S'){
                    y++;
                    if(y == 4)
                        y = 1;
                }
                if(inputKb == '\r'){
                    system("cls");
                    if(y == 1){
                        menu = 2;
                        cout << "\nHalo Petualang!";
                        cout<< "\nSiapa namamu? ";gets(nama);
                        system("cls");
                        cout<< "\nSelamat datang, "<< nama<< "!.\nSelamat datang di game Maze : U's Exit Plan, pada game ini kamu diharapkan";
                        cout<< "\nuntuk dapat keluar dari rintangan-rintangan yang ada. Gunakanlah otakmu untuk menyusun rencana agar dapat";
                        cout<< "\nkeluar dari segala macam rintangan tersebut. Mari kita lihat rencanamu pada rintangan pertama yang akan kamu";
                        cout<< "\nlewati ini. Kami harap kamu tidak mengecewakan kami, buatlah rencana dengan baik " << nama << endl << endl;
                        system("PAUSE");
                        statusMenu1 = false;
                    }
                    if(y == 2){
                        cout<< "\n\n\t\tABOUT THE GAME";
                        cout<< "\n\t     MAZE : U's EXIT PLAN"<<endl;
                        cout<< "\nDeskripsi :"<<endl;
                        cout<< "\nMaze : U's Exit Plan merupakan sebuah game bergenre adventure yang mengisahkan";
                        cout<< "\nseorang karakter U yang terjebak di suatu labirin.  Labirin tersebut memiliki";
                        cout<< "\nbanyak rintangan yang harus ia hadapi. Tak hanya itu, di dalamnya  terdapat tiga";
                        cout<< "\ndestinasi yang harus U lewati. U harus bisa melewati semua destinasi dan rintangan";
                        cout<< "\ntersebut agar dapat keluar dari labirin itu.";
                        cout<< "\n\nPembuat Game :"<<endl;
                        cout<< "\n->Tegar Ridwansyah \n->Nabila Handayani \n->Vincentsius Kevin \n->Muhammad Mudzaky \n->Rahel Vanesa Sianturi"<<endl<<endl;
                        system("PAUSE");
                    }
                    if(y == 3){
                        keluar = true; break;
                    }
                }
                //untuk mengubah warnanyaa, misal awalnya putih(set[]=7) jadi warna merah (set[]=12)
                Set[1]= 7; Set[2]= 7; Set[3]= 7;
                if(y == 1) Set[1] = 12;
                if(y == 2) Set[2] = 12;
                if(y == 3) Set[3] = 12;
            }
        }
        else if(menu == 2){
            nObstacle = 0;
            system("cls");
            //Looping Untuk Nampilin Map dan Ambil (x,y) Character U, Obstacle, dan Finish
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 17; j++){
                    if(mapDestinasi1[i][j] == '#')
                        cout << (char) 219;
                    else{
                        if(mapDestinasi1[i][j] == 'U'){
                            c.x = j;
                            c.y = i;
                        }

                        if(mapDestinasi1[i][j] == 'X'){
                            o1[nObstacle].x = j;
                            o1[nObstacle].y = i;
                            if(nObstacle == 0){
                                o1[nObstacle].intervalA = i-3;
                                o1[nObstacle].intervalB = i;
                            } else if(nObstacle == 1){
                                o1[nObstacle].intervalA = j;
                                o1[nObstacle].intervalB = j+7;
                            } else{
                                o1[nObstacle].intervalA = i-3;
                                o1[nObstacle].intervalB = i+4;
                            }
                            nObstacle++;
                        }

                        if(mapDestinasi1[i][j] == 'F'){
                            f.x = j;
                            f.y = i;
                        }
                        cout << mapDestinasi1[i][j];
                    }

                }
                cout << endl;
            }

            gotoxy(18,0); cout << "DESTINASI 1";
            gotoxy(18,2); cout << "Kontrol";
            gotoxy(18,3); cout << "W : Atas";
            gotoxy(18,4); cout << "A : Kiri";
            gotoxy(18,5); cout << "S : Bawah";
            gotoxy(18,6); cout << "D : Kanan";
            gotoxy(18,8); cout << "Nyawa : ";
            int xNyawa = 26;
            for(int i = 0; i < nyawa; i++){
                gotoxy(xNyawa,8); cout << (char)254;
                xNyawa += 2;
            }

            cp.x = c.x;
            cp.y = c.y;
            while(true){
                moveCharater(c.x,c.y);

                //Obstacle Destinasi 1 Index 0
                if(o1[0].y == o1[0].intervalA)
                    obs1_0 = true;
                else if(o1[0].y == o1[0].intervalB)
                    obs1_0 = false;

                deleteMoveCharacter(o1[0].x,o1[0].y);
                if(obs1_0 == true)
                    o1[0].y++;
                else
                    o1[0].y--;
                moveObstacle(o1[0].x,o1[0].y);

                //Obstacle Destinasi 1 Index 1
                if(o1[1].x == o1[1].intervalA)
                    obs1_1 = true;
                else if(o1[1].x == o1[1].intervalB)
                    obs1_1 = false;

                deleteMoveCharacter(o1[1].x,o1[1].y);
                if(obs1_1 == true)
                    o1[1].x++;
                else
                    o1[1].x--;
                moveObstacle(o1[1].x,o1[1].y);

                //Obstacle Destinasi 1 Index 2
                if(o1[2].y == o1[2].intervalA)
                    obs1_2 = true;
                else if(o1[2].y == o1[2].intervalB)
                    obs1_2 = false;

                deleteMoveCharacter(o1[2].x,o1[2].y);
                if(obs1_2 == true)
                    o1[2].y++;
                else
                    o1[2].y--;
                moveObstacle(o1[2].x,o1[2].y);

                //Cek Character Nabrak Obstacle
                for(int i = 0; i < 3; i++){
                    if(c.x == o1[i].x && c.y == o1[i].y){
                        c.x = cp.x;
                        c.y = cp.y;
                        nyawa--;
                        xNyawa -= 2;
                        gotoxy(xNyawa,8); cout << " ";
                    }
                }

                if(nyawa == 0){
                    gotoxy(3,17);
                    system("PAUSE");
                    system("cls");
                    cout << "\n\tG A M E  O V E R" << endl << endl;
                    menu = 1;
                    break;
                }

                //Cek Character Sudah Sampai Finish
                if(c.x == f.x && c.y == f.y){
                    gotoxy(3,17);
                    system("PAUSE");
                    system("cls");
                    cout<< "\nSelamat "<< nama <<", telah berhasil melewati rintangan pertama dengan rencana dan strategi yang baik.";
                    cout<< "\nSelanjutnya, kamu akan diarahkan ke destinasi dengan rintangan yang jauh lebih sulit lagi. Persiapkan ";
                    cout<< "\nrencana-rencana yang akan kamu lakukan untuk keluar dari tempat tersebut, lalu mari bertemu kembali" ;
                    cout<< "\nsetelah kamu berhasil melewatinya. Good Luck "<< nama <<endl << endl;
                    menu = 3;
                    break;
                }

                //Untuk Control Character U
                if(kbhit()){
                    gotoxy(c.x,c.y); inputKb = getch();

                    if(inputKb == 'W' || inputKb == 'w'){
                        if(mapDestinasi1[c.y-1][c.x] != '#'){
                            c.y -= 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x,c.y+1);
                        }
                    }
                    if(inputKb == 'A' || inputKb == 'a'){
                        if(mapDestinasi1[c.y][c.x-1] != '#'){
                            c.x -= 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x+1,c.y);
                        }
                    }
                    if(inputKb == 'S' || inputKb == 's'){
                        if(mapDestinasi1[c.y+1][c.x] != '#'){
                            c.y += 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x,c.y-1);
                        }
                    }
                    if(inputKb == 'D' || inputKb == 'd'){
                        if(mapDestinasi1[c.y][c.x+1] != '#'){
                            c.x += 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x-1,c.y);
                        }
                    }
                }
                Sleep(300);
            }
            system("PAUSE");
        }
        else if(menu == 3){
            nObstacle = 0;
            system("cls");
            //Looping Untuk Nampilin Map dan Ambil (x,y) Character U, Obstacle, dan Finish
            for(int i = 0; i < 15; i++){
                for(int j = 0; j < 35; j++){
                    if(mapDestinasi2[i][j] == '#')
                        cout << (char) 219;
                    else{
                        if(mapDestinasi2[i][j] == 'U'){
                            c.x = j;
                            c.y = i;
                        }

                        if(mapDestinasi2[i][j] == 'X'){
                            o2[nObstacle].x = j;
                            o2[nObstacle].y = i;
                            if(nObstacle == 0){
                                o2[nObstacle].intervalA = i;
                                o2[nObstacle].intervalB = i+12;
                            } else if(nObstacle == 1){
                                o2[nObstacle].intervalA = j-8;
                                o2[nObstacle].intervalB = j;
                            } else if(nObstacle == 2){
                                o2[nObstacle].intervalA = i-4;
                                o2[nObstacle].intervalB = i+4;
                            } else if(nObstacle == 3){
                                o2[nObstacle].intervalA = j-7;
                                o2[nObstacle].intervalB = j;
                            } else{
                                o2[nObstacle].intervalA = j;
                                o2[nObstacle].intervalB = j+15;
                            }
                            nObstacle++;
                        }

                        if(mapDestinasi2[i][j] == 'F'){
                            f.x = j;
                            f.y = i;
                        }

                        if(mapDestinasi2[i][j] == 'C'){
                            lcp1.x = j;
                            lcp1.y = i;
                        }
                        cout << mapDestinasi2[i][j];
                    }
                }
                cout << endl;
            }
            gotoxy(38,0); cout << "DESTINASI 2";
            gotoxy(38,2); cout << "Kontrol";
            gotoxy(38,3); cout << "W : Atas";
            gotoxy(38,4); cout << "A : Kiri";
            gotoxy(38,5); cout << "S : Bawah";
            gotoxy(38,6); cout << "D : Kanan";
            gotoxy(38,8); cout << "Nyawa : ";
            int xNyawa = 46;
            for(int i = 0; i < nyawa; i++){
                gotoxy(xNyawa,8); cout << (char)254 << " ";
                xNyawa += 2;
            }

            cp.x = c.x;
            cp.y = c.y;
            while(true){
                moveCharater(c.x,c.y);

                //Obstacle Destinasi 2 Index 0
                if(o2[0].y == o2[0].intervalA)
                    obs2_0 = true;
                else if(o2[0].y == o2[0].intervalB)
                    obs2_0 = false;

                deleteMoveCharacter(o2[0].x,o2[0].y);
                if(obs2_0 == true)
                    o2[0].y++;
                else
                    o2[0].y--;
                moveObstacle(o2[0].x,o2[0].y);

                //Obstacle Destinasi 2 Index 1
                if(o2[1].x == o2[1].intervalA)
                    obs2_1 = true;
                else if(o2[1].x == o2[1].intervalB)
                    obs2_1 = false;

                deleteMoveCharacter(o2[1].x,o2[1].y);
                if(obs2_1 == true)
                    o2[1].x++;
                else
                    o2[1].x--;
                moveObstacle(o2[1].x,o2[1].y);

                //Obstacle Destinasi 2 Index 2
                if(o2[2].y == o2[2].intervalA)
                    obs2_2 = true;
                else if(o2[2].y == o2[2].intervalB)
                    obs2_2 = false;

                deleteMoveCharacter(o2[2].x,o2[2].y);
                if(obs2_2 == true)
                    o2[2].y++;
                else
                    o2[2].y--;
                moveObstacle(o2[2].x,o2[2].y);

                //Obstacle Destinasi 2 Index 3
                if(o2[3].x == o2[3].intervalA)
                    obs2_3 = true;
                else if(o2[3].x == o2[3].intervalB)
                    obs2_3 = false;

                deleteMoveCharacter(o2[3].x,o2[3].y);
                if(obs2_3 == true)
                    o2[3].x++;
                else
                    o2[3].x--;
                moveObstacle(o2[3].x,o2[3].y);

                //Obstacle Destinasi 2 Index 4
                if(o2[4].x == o2[4].intervalA)
                    obs2_4 = true;
                else if(o2[4].x == o2[4].intervalB)
                    obs2_4 = false;

                deleteMoveCharacter(o2[4].x,o2[4].y);
                if(obs2_4 == true)
                    o2[4].x++;
                else
                    o2[4].x--;
                moveObstacle(o2[4].x,o2[4].y);

                //Cek Character Nabrak Obstacle
                for(int i = 0; i < 5; i++){
                    if(c.x == o2[i].x && c.y == o2[i].y){
                        c.x = cp.x;
                        c.y = cp.y;
                        nyawa--;
                        xNyawa -= 2;
                        gotoxy(xNyawa,8); cout << " ";
                    }
                }

                if(nyawa == 0){
                    gotoxy(3,18);
                    system("PAUSE");
                    system("cls");
                    cout << "\n\tG A M E  O V E R" << endl << endl;
                    menu = 1;
                    break;
                }

                //Cek Character Sudah Sampai Finish
                if(c.x == f.x && c.y == f.y){
                    gotoxy(3,18);
                    system("PAUSE");
                    system("cls");
                    cout << "\nWahhhh, rintangan tadi benar-benar sulit sekali. Benar bukan, "<< nama<<"? Lagi-lagi selamat karena";
                    cout << "\ntelah berhasil melewatinya. Sungguh rencana yang kamu susun untuk keluar dari tempat tadi sangatlah";
                    cout << "\napik, kami sangat tidak sabar melihat rencana yang akan kamu susun untuk rintangan selanjutnya. Baiklah\n";
                    cout << nama << " hanya tersisa satu rintangan lagi yang perlu kamu lewati. Akan tetapi, kami memperingatkanmu, untuk";
                    cout << "\nlebih berhati-hati pada rintangan selanjutnya. " << endl << endl;
                    menu = 4;
                    break;
                }

                //Untuk Control Character U
                if(kbhit()){
                    gotoxy(c.x,c.y); inputKb = getch();

                    if(inputKb == 'W' || inputKb == 'w'){
                        if(mapDestinasi2[c.y-1][c.x] != '#'){
                            c.y -= 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x,c.y+1);
                            if(c.x == lcp1.x && c.y == lcp1.y){
                                cp.x = lcp1.x;
                                cp.y = lcp1.y;
                            }
                        }
                    }
                    if(inputKb == 'A' || inputKb == 'a'){
                        if(mapDestinasi2[c.y][c.x-1] != '#'){
                            c.x -= 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x+1,c.y);
                        }
                    }
                    if(inputKb == 'S' || inputKb == 's'){
                        if(mapDestinasi2[c.y+1][c.x] != '#'){
                            c.y += 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x,c.y-1);
                        }
                    }
                    if(inputKb == 'D' || inputKb == 'd'){
                        if(mapDestinasi2[c.y][c.x+1] != '#'){
                            c.x += 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x-1,c.y);
                        }
                    }
                }
                Sleep(250);
            }
            system("PAUSE");
            system("cls");
        }
        else if(menu == 4){
            nObstacle = 0;
            nCp = 0;
            system("cls");
            for(int i = 0; i < 33; i++){
                for(int j = 0; j < 40; j++){
                    if(mapDestinasi3[i][j] == '#')
                        cout << (char) 219;
                    else{
                        if(mapDestinasi3[i][j] == 'U'){
                            c.x = j;
                            c.y = i;
                        }

                        if(mapDestinasi3[i][j] == 'X'){
                            o3[nObstacle].x = j;
                            o3[nObstacle].y = i;
                            if(nObstacle == 0){
                                o3[nObstacle].intervalA = i-1;
                                o3[nObstacle].intervalB = i+2;
                            } else if(nObstacle == 1){
                                o3[nObstacle].intervalA = j-3;
                                o3[nObstacle].intervalB = j;
                            } else if(nObstacle == 2){
                                o3[nObstacle].intervalA = i-5;
                                o3[nObstacle].intervalB = i;
                            } else if(nObstacle == 3){
                                o3[nObstacle].intervalA = j;
                                o3[nObstacle].intervalB = j+36;
                            } else if(nObstacle == 4){
                                o3[nObstacle].intervalA = j-36;
                                o3[nObstacle].intervalB = j;
                            } else if(nObstacle == 5){
                                o3[nObstacle].intervalA = j-3;
                                o3[nObstacle].intervalB = j;
                            } else if(nObstacle == 6){
                                o3[nObstacle].intervalA = i+1;
                                o3[nObstacle].intervalB = i-4;
                            } else if(nObstacle == 7){
                                o3[nObstacle].intervalA = i+1;
                                o3[nObstacle].intervalB = i-1;
                            } else{
                                o3[nObstacle].intervalA = j;
                                o3[nObstacle].intervalB = j+5;
                            }
                            nObstacle++;
                        }

                        if(mapDestinasi3[i][j] == 'F'){
                            f.x = j;
                            f.y = i;
                        }

                        if(mapDestinasi3[i][j] == 'C'){
                            lcp2[nCp].x = j;
                            lcp2[nCp].y = i;
                            nCp++;
                        }
                        cout << mapDestinasi3[i][j];
                    }
                }
                cout << endl;
            }
            gotoxy(43,0); cout << "DESTINASI 3";
            gotoxy(43,2); cout << "Kontrol";
            gotoxy(43,3); cout << "W : Atas";
            gotoxy(43,4); cout << "A : Kiri";
            gotoxy(43,5); cout << "S : Bawah";
            gotoxy(43,6); cout << "D : Kanan";
            gotoxy(43,8); cout << "Nyawa : ";
            int xNyawa = 51;
            for(int i = 0; i < nyawa; i++){
                gotoxy(xNyawa,8); cout << (char)254 << " ";
                xNyawa += 2;
            }

            cp.x = c.x;
            cp.y = c.y;
            while(true){
                moveCharater(c.x,c.y);

                //Obstacle Destinasi 3 Index 0
                if(o3[0].y == o3[0].intervalA)
                    obs3_0 = true;
                else if(o3[0].y == o3[0].intervalB)
                    obs3_0 = false;

                deleteMoveCharacter(o3[0].x,o3[0].y);
                if(obs3_0 == true)
                    o3[0].y++;
                else
                    o3[0].y--;
                moveObstacle(o3[0].x,o3[0].y);

                //Obstacle Destinasi 3 Index 1
                if(o3[1].x == o3[1].intervalA)
                    obs3_1 = true;
                else if(o3[1].x == o3[1].intervalB)
                    obs3_1 = false;

                deleteMoveCharacter(o3[1].x,o3[1].y);
                if(obs3_1 == true)
                    o3[1].x++;
                else
                    o3[1].x--;
                moveObstacle(o3[1].x,o3[1].y);

                //Obstacle Destinasi 3 Index 2
                if(o3[2].y == o3[2].intervalA)
                    obs3_2 = true;
                else if(o3[2].y == o3[2].intervalB)
                    obs3_2 = false;

                deleteMoveCharacter(o3[2].x,o3[2].y);
                if(obs3_2 == true)
                    o3[2].y++;
                else
                    o3[2].y--;
                moveObstacle(o3[2].x,o3[2].y);

                 //Obstacle Destinasi 3 Index 3
                if(o3[3].x == o3[3].intervalA)
                    obs3_3 = true;
                else if(o3[3].x == o3[3].intervalB)
                    obs3_3 = false;

                deleteMoveCharacter(o3[3].x,o3[3].y);
                if(obs3_3 == true)
                    o3[3].x++;
                else
                    o3[3].x--;
                moveObstacle(o3[3].x,o3[3].y);

                //Obstacle Destinasi 3 Index 4
                if(o3[4].x == o3[4].intervalA)
                    obs3_4 = true;
                else if(o3[4].x == o3[4].intervalB)
                    obs3_4 = false;

                deleteMoveCharacter(o3[4].x,o3[4].y);
                if(obs3_4 == true)
                    o3[4].x++;
                else
                    o3[4].x--;
                moveObstacle(o3[4].x,o3[4].y);

                //Obstacle Destinasi 3 Index 5
                if(o3[5].x == o3[5].intervalA)
                    obs3_5 = true;
                else if(o3[5].x == o3[5].intervalB)
                    obs3_5 = false;

                deleteMoveCharacter(o3[5].x,o3[5].y);
                if(obs3_5 == true)
                    o3[5].x++;
                else
                    o3[5].x--;
                moveObstacle(o3[5].x,o3[5].y);

                //Obstacle Destinasi 3 Index 6
                if(o3[6].y == o3[6].intervalA)
                    obs3_6 = false;
                else if(o3[6].y == o3[6].intervalB)
                    obs3_6 = true;

                deleteMoveCharacter(o3[6].x,o3[6].y);
                if(obs3_6 == true)
                    o3[6].y++;
                else
                    o3[6].y--;
                moveObstacle(o3[6].x,o3[6].y);

                //Obstacle Destinasi 3 Index 7
                if(o3[7].y == o3[7].intervalA)
                    obs3_7 = false;
                else if(o3[7].y == o3[7].intervalB)
                    obs3_7 = true;

                deleteMoveCharacter(o3[7].x,o3[7].y);
                if(obs3_7 == true)
                    o3[7].y++;
                else
                    o3[7].y--;
                moveObstacle(o3[7].x,o3[7].y);

                //Obstacle Destinasi 3 Index 8
                if(o3[8].x == o3[8].intervalA)
                    obs3_8 = true;
                else if(o3[8].x == o3[8].intervalB)
                    obs3_8 = false;

                deleteMoveCharacter(o3[8].x,o3[8].y);
                if(obs3_8 == true)
                    o3[8].x++;
                else
                    o3[8].x--;
                moveObstacle(o3[8].x,o3[8].y);

                //Cek Character Nabrak Obstacle
                for(int i = 0; i < 9; i++){
                    if(c.x == o3[i].x && c.y == o3[i].y){
                        c.x = cp.x;
                        c.y = cp.y;
                        nyawa--;
                        xNyawa -= 2;
                        gotoxy(xNyawa,8); cout << " ";
                    }
                }

                if(nyawa == 0){
                    gotoxy(3,35);
                    system("PAUSE");
                    system("cls");
                    cout << "\n\tG A M E  O V E R" << endl << endl;
                    menu = 1;
                    break;
                }

                //Cek Character Sudah Sampai Finish
                if(c.x == f.x && c.y == f.y){
                    gotoxy(3,35);
                    system("PAUSE");
                    system("cls");
                    cout << "Sepertinya kamu melihat cahaya yang sangat terang di luar sana!";
                    cout << "\nWahhh, ternyata kamu sudah berhasil keluar dari labirin ini!!";
                    cout << "\nSelamat petualang, " << nama << "!" << endl << endl;
                    menu = 5;
                    break;
                }

                //Untuk Control Character U
                if(kbhit()){
                    gotoxy(c.x,c.y); inputKb = getch();

                    if(inputKb == 'W' || inputKb == 'w'){
                        if(mapDestinasi3[c.y-1][c.x] != '#'){
                            c.y -= 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x,c.y+1);
                        }
                    }
                    if(inputKb == 'A' || inputKb == 'a'){
                        if(mapDestinasi3[c.y][c.x-1] != '#'){
                            c.x -= 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x+1,c.y);
                            if(c.x == lcp2[0].x && c.y == lcp2[0].y){
                                cp.x = lcp2[0].x;
                                cp.y = lcp2[0].y;
                            }
                            if(c.x == lcp2[1].x && c.y == lcp2[1].y){
                                cp.x = lcp2[1].x;
                                cp.y = lcp2[1].y;
                            }
                        }
                    }
                    if(inputKb == 'S' || inputKb == 's'){
                        if(mapDestinasi3[c.y+1][c.x] != '#'){
                            c.y += 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x,c.y-1);
                        }
                    }
                    if(inputKb == 'D' || inputKb == 'd'){
                        if(mapDestinasi3[c.y][c.x+1] != '#'){
                            c.x += 1;
                            moveCharater(c.x,c.y);
                            deleteMoveCharacter(c.x-1,c.y);
                            if(c.x == lcp2[0].x && c.y == lcp2[0].y){
                                cp.x = lcp2[0].x;
                                cp.y = lcp2[0].y;
                            }
                            if(c.x == lcp2[1].x && c.y == lcp2[1].y){
                                cp.x = lcp2[1].x;
                                cp.y = lcp2[1].y;
                            }
                        }
                    }
                }

                Sleep(200);
            }
            system("PAUSE");
            system("cls");
        }
        else{
            system("cls");
            cout << "*****  *****  *         *     *       *     *     *********" << endl;
            cout << "*   *  *      *        * *    * *   * *    * *        *" << endl;
            cout << "*      *      *       *   *   *  * *  *   *   *       *" << endl;
            cout << "*****  *****  *      *******  *   *   *  *******      *" << endl;
            cout << "    *  *      *      *     *  *       *  *     *      *" << endl;
            cout << "*   *  *      *      *     *  *       *  *     *      *" << endl;
            cout << "*****  *****  *****  *     *  *       *  *     *      *" << endl << endl;

            cout << "    ****************************";
            cout << "\n   ***                         *";
            cout << "\n  *   *                        *";
            cout << "\n *      *                      *";
            cout << "\n*        *                     *";
            cout << "\n********************************";
            cout << "\n*  ***** *       *     *       *";
            cout << "\n*  *   * *       *     *       *";
            cout << "\n*  ***** *       *     *       *";
            cout << "\n*        *       *     *       *";
            cout << "\n*        *       *     *       *";
            cout << "\n*_______ *_______*_____*_______*____";
            cout << "\n_____          _____       _____     ";
            cout << "\n_____          _____       _____     ";
            cout << "\n_____________________________________\n\n";
            system("PAUSE");
            menu = 1;
        }
    }while(keluar == false);

    system("cls");
    cout<< "\n\t\t+==========+";
    cout<< "\n\t\t+   QUIT   +";
    cout<< "\n\t\t+==========+\n";
}
