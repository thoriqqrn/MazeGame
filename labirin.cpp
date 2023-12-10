#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>

int koin1_x = 90, koin1_y = 58;
int koin2_x = 265, koin2_y = 58;
int koin3_x = 180, koin3_y = 330;
int koin4_x = 445, koin4_y = 553;
int koin5_x = 510, koin5_y = 326;
int koin6_x = 700, koin6_y = 165;
int koin7_x = 750, koin7_y = 340;

int score = 0;
bool menang = false;
bool kalah = false;

int musuhY = 300; 
int musuhSpeed = 5; 
int musuhArah = 1; 
int musuhRadius = 25;


void pacman(int x, int y, int arah) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    pieslice(x, y, 40 + arah, 310 + arah, 20);
}

void musuh(int x, int y) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(x, y, musuhRadius);
    floodfill(x, y, RED);
}

void pergerakanMusuh() {
    musuhY += musuhSpeed * musuhArah;

    if (musuhY <= 150 || musuhY >= 550) {
        musuhArah *= -1;
    }
}

bool nabrakMusuh(int x, int y, int musuhX, int musuhY, int musuhRadius) {
    return (sqrt(pow((x - musuhX), 2) + pow((y - musuhY), 2)) < musuhRadius + 20);
}

void labirin() {
    setcolor(GREEN);

    line(10, 10, 10, 590);
    line(790, 10, 790, 590);
    line(10, 590, 790, 590);
    line(10, 10, 790, 10);

    rectangle(86, 500, 97, 100);
    rectangle(174, 250, 185, 10);
    rectangle(174, 590, 185, 390);
    rectangle(261, 500, 272, 100);
    rectangle(340, 79, 711, 90);
    rectangle(340, 488, 610, 499);
    rectangle(420, 257, 431, 488);
    rectangle(590, 173, 601, 404);
    rectangle(685, 278, 790, 289);
    rectangle(700, 404, 711, 589);
}

bool tabrakan(int x, int y) {
    return (x < 10 || x > 790 || y < 10 || y > 590 ||
            (x >= 86 && x <= 97 && y >= 100 && y <= 500) ||
            (x >= 174 && x <= 185 && y >= 10 && y <= 250) ||
            (x >= 174 && x <= 185 && y >= 390 && y <= 590) ||
            (x >= 26 && x <= 272 && y >= 100 && y <= 500) ||
            (x >= 340 && x <= 711 && y >= 90 && y <= 100) || 
            (x >= 340 && x <= 610 && y >= 488 && y <= 499) ||
            (x >= 420 && x <= 431 && y >= 257 && y <= 488) ||
            (x >= 590 && x <= 601 && y >= 173 && y <= 404) ||
            (x >= 685 && x <= 790 && y >= 278 && y <= 289) ||
            (x >= 700 && x <= 711 && y >= 404 && y <= 589));
}

void bendera() {
    setcolor(YELLOW); 
    rectangle(725, 532, 732, 589);
    rectangle(732, 532, 772, 561);
    line(732, 532, 772, 561);
}
bool nabrakBendera(int x, int y) {
    return (x >= 725 && x <= 772 && y >= 532 && y <= 589);
}

void koin(int x, int y) {
    int warna = RGB(173, 216, 230);

    setcolor(warna);
    setfillstyle(SOLID_FILL, warna);
    circle(x, y, 10);
    floodfill(x, y, warna);
}
bool makan(int x, int y, int koin_x, int koin_y) {
    int jarak = sqrt(pow((x - koin_x), 2) + pow((y - koin_y), 2));
    return jarak < 15; 
}

void skor(int timeLeft) {
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char scoreStr[30];
    sprintf(scoreStr, "Score: %d Time: %d s", score, timeLeft);
    outtextxy(10, 10, scoreStr);
}

void youwin() {
    setcolor(GREEN);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(250, 250, "You Win!");
    char scoreStr[20];
    sprintf(scoreStr, "Score: %d", score);
    outtextxy(10, 10, scoreStr);
}

void youlose() {
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
    outtextxy(250, 250, "You Lose!");
}

int main() {
    initwindow(800, 600, "Athariq Qur'ani Fajri -- Labirin Game -- Dasar Pemograman");

    int x = 40;  
    int y = 550; 
    int arah = 0;

    time_t startTime, currentTime;
    int elapsedTime = 0;
    int timeLimit = 30; 

    char ch;
    time(&startTime); 

    while (1) {
        if (!menang && !kalah) {
            if (kbhit()) {
                ch = getch();
                switch (ch) {
                case 'a':
                    arah = 180;
                    x -= 10;
                    break;
                case 'd':
                    arah = 0;
                    x += 10;
                    break;
                case 'w':
                    arah = 90;
                    y -= 10;
                    break;
                case 's':
                    arah = 270;
                    y += 10;
                    break;
                case 27:
                    closegraph();
                    exit(0);
                }
            }

            if (tabrakan(x, y)) {
                x = 40;
                y = 550;
            }

            cleardevice();
            labirin();
            pacman(x, y, arah);
            bendera();
            pergerakanMusuh();  
            musuh(225, musuhY);
            musuh(650, musuhY);

            // Check for coin eating
            if (makan(x, y, koin1_x, koin1_y)) {
                koin1_x = -1;
                koin1_y = -1;
                score += 10;
            }
            if (makan(x, y, koin2_x, koin2_y)) {
                koin2_x = -1;
                koin2_y = -1;
                score += 10;
            }
            if (makan(x, y, koin3_x, koin3_y)) {
                koin3_x = -1;
                koin3_y = -1;
                score += 10;
            }
            if (makan(x, y, koin4_x, koin4_y)) {
                koin4_x = -1;
                koin4_y = -1;
                score += 10;
            }
            if (makan(x, y, koin5_x, koin5_y)) {
                koin5_x = -1;
                koin5_y = -1;
                score += 10;
            }
            if (makan(x, y, koin6_x, koin6_y)) {
                koin6_x = -1;
                koin6_y = -1;
                score += 10;
            }
            if (makan(x, y, koin7_x, koin7_y)) {
                koin7_x = -1;
                koin7_y = -1;
                score += 10;
            }

            if (nabrakBendera(x, y)) {
                menang = true;
            }

            time(&currentTime);
            elapsedTime = difftime(currentTime, startTime);
            int timeLeft = (timeLimit - elapsedTime) > 0 ? (timeLimit - elapsedTime) : 0;

            if (timeLeft == 0) {
                kalah = true;
            }
            if (nabrakMusuh(x, y, 225, musuhY, musuhRadius)) {
            kalah = true;
            }
            if (nabrakMusuh(x, y, 650, musuhY, musuhRadius)) {
            kalah = true;
            }

            if (koin1_x != -1) koin(koin1_x, koin1_y);
            if (koin2_x != -1) koin(koin2_x, koin2_y);
            if (koin3_x != -1) koin(koin3_x, koin3_y);
            if (koin4_x != -1) koin(koin4_x, koin4_y);
            if (koin5_x != -1) koin(koin5_x, koin5_y);
            if (koin6_x != -1) koin(koin6_x, koin6_y);
            if (koin7_x != -1) koin(koin7_x, koin7_y);

            skor(timeLeft); 
        } else {
            cleardevice();
            if (menang) {
                youwin();
            } else {
                youlose();
            }
        }

        delay(10);
    }

    closegraph();
    return 0;
}
