#include <stdio.h> // printf();
#include <windows.h> //setcur(0,0)
#include <conio.h>  //kbhit
#include <time.h>  // for random

#define N 20
#define M 40

int Field[N][M],x,y,smove,Head,Tail,Game,apples,a,b,var,dir,score,HighScore,Speed;
FILE *f;

void showHighscore()
{
    f = fopen("highscore.txt", "r"); // save highscore
    fscanf(f,"%d", &HighScore);
    fclose(f);
}


void snakeInitialization()
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            Field[i][j] = 0;

    x = N / 2; // Start Õ
    y = M / 2; // Start Y
    Head = 5; // Initial length
    Tail = 1; // tail
    Game = 0; // 0 game start,  1 game end
    apples = 0;
    dir = 'd';
    score = 0; //  Score
    Speed = 100; // Game speed , the lower the faster;
}

void print()
{
    for(int i = 0; i <= M + 1; i++)
        if(i <= M +1)
            printf("%c", 219);
    printf("\n");

    for(int i = 0; i < N; i++)
    {
        printf("%c", 219);

        for(int j = 0; j < M; j++)
        {
            if(Field[i][j] == 0) printf(" ");
            if(Field[i][j] > 0 && Field[i][j] != Head) printf("%c", 219);
            if(Field[i][j] == Head) printf("%c", 254);
            if(Field[i][j] == -1) printf("%c", '@');
            if(j == M - 1) printf("%c\n", 219);
        }
    }

    for(int i = 0; i <= M + 1; i++)
        if(i >= 0)
            printf("%c", 219);
    printf("\n  Score: %d\n  HighScore: %d",score,HighScore);
}

void setcur(int x, int y)  // Removes screen flicker
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Random()
{
    srand(time(0));
    a = 1 + rand() % 18;
    b = 1 + rand() % 38;

    if(apples == 0 && Field[a][b] == 0)
    {
        Field[a][b] = -1;
        apples = -1; //
        if(Speed > 10 && score != 0) Speed = Speed - 5;
    }
}

int getch_noblock()
{
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void movement()
{
    var = getch_noblock();
    var = tolower(var);

    if(((var == 'd' || var == 'a' ) || (var == 'w' || var == 's')) \
                                    &&(abs(dir - var) > 5)) dir = var;
    if(dir == 'd')
    {
        y++;
        if(y == M - 1) y = 0;
        if(Field[x][y] != 0 && Field[x][y] != -1) GameOver();
        if(Field[x][y] == -1)
        {
            apples = 0;
            score += 5;
            Tail -= 1;
        }

        Head++;
        Field[x][y] = Head;
    }

    if(dir == 'a')
    {
        y--;
        if(y == 0) y = M - 1;
        if(Field[x][y] != 0 && Field[x][y] != -1) GameOver();
        if(Field[x][y] == -1)
        {
            apples = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir == 'w')
    {
        x--;
        if(x == -1) x = N - 1;
        if(Field[x][y] != 0 && Field[x][y] != -1) GameOver();
        if(Field[x][y] == -1)
        {
            apples = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir == 's')
    {
        x++;
        if(x == N - 1) x = 0;
        if(Field[x][y] != 0 && Field[x][y] != -1) GameOver();
        if(Field[x][y] == -1)
        {
            apples = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }
}

void TailRemove()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(Field[i][j] == Tail)
                Field[i][j] = 0;
        }
    }
            Tail++;
}

void GameOver()
{
    Sleep(1200);
    system("cls");

    if(score > HighScore)
    {
        printf("New highscore !\n\n",score);
        system("pause");
        f = fopen("highscore.txt","w");
        fprintf(f,"%d",score);
        fclose(f);
    }

    system("cls");
    printf("GAME OVER !\n");
    printf("Score : %d \n\n",score);
    printf("Press ENTER to play again or ESC to exit ... \n");


    while(1)
    {
        var = getch_noblock();
        if(var == 13)
        {
            Game = 0;
            snakeInitialization();
            break;
        }
        else if(var == 27)
        {
            Game = 1;
            break;
        }
    }
    system("cls");
}

int main(void)
{
    showHighscore();
    snakeInitialization();
    while(Game == 0)
    {
        print();
        setcur(0,0);
        Random();
        movement();
        TailRemove();
        Sleep(Speed);
    }
}
