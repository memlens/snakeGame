#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
int *snakeX;
int *snakeY;
int fruitX;
int fruitY;
int taillqueue;
int score;
int abscisse;
int ordonnee;
enum Direction
{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
} direction;

void banderole(){
     //init
    int i = 0;

    while (i< 5)//!Halt
    {
        cout<<"# ";
        if(i == 0 || i == 4){
            for(int j = 0; j < 20; j++) cout<<"# ";
        }else if(i == 2){
            for(int j = 0; j < 7; j++) cout<<"  ";
cout <<"#      _                  #\n";         
cout <<"#      ___ _ __   __ _| | _____  ___      #\n";
cout <<"#     / __| '_ \\ / _` | |/ / _ \\/ __|     #\n";
cout<<"#     \\__ \\ | | | (_| |   <  __/\\__ \\     #\n";
cout <<"#     |___/_| |_|\\__,_|_|\\_\\___||___/     #\n";
            for(int j = 0; j < 8; j++) cout<<"  ";
        }else {
            for(int j = 0; j < 20; j++) cout<<"  ";
        } cout<<"#"<<endl;
        //iter
        i++;
    }
}

void Setup()
{
    gameOver = false;
    score = 0;
    taillqueue = 1;
    abscisse = 20;
    ordonnee = 20;
    snakeX = new int[100];
    snakeY = new int[100];
    snakeX[0] = abscisse / 2;
    snakeY[0] = ordonnee / 2;
    fruitX = rand() % abscisse;
    fruitY = rand() % ordonnee;
}

void Draw()
{
    system("cls");
    for (int i = 0; i <= abscisse + 1; i++)
        cout << "#";
    cout << endl;

    for (int j = 0; j < ordonnee; j++)
    {
        for (int i = 0; i < abscisse; i++)
        {
            if (i == 0)
                cout << "#"; //left wall

            if (i == snakeX[0] && j == snakeY[0])
                cout << "҈"; //snake head

            else if (i == fruitX && j == fruitY)
                cout << "a"; //fruit

            else
            {
                bool printqueue = false;
                for (int k = 1; k < taillqueue; k++)
                {
                    if (i == snakeX[k] && j == snakeY[k])
                    {
                        cout << "o"; //queue de serpent
                        printqueue = true;
                    }
                }
                if (!printqueue)
                    cout << " "; //between walls
            }

            if (i == abscisse - 1)
                cout << "#"; //right wall
        }
        cout << endl;
    }

    for (int i = 0; i <= abscisse + 1; i++)
        cout << "#";
    cout << endl;
    cout << "Score : " << score << endl;
    cout << "Entrez x pour arreter !"<< endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (direction != BAS)
                direction = HAUT;
            break;
        case 's':
            if (direction != HAUT)
                direction = BAS;
            break;
        case 'q':
            if (direction != DROITE)
                direction = GAUCHE;
            break;
        case 'd':
            if (direction != GAUCHE)
                direction = DROITE;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int tempX = snakeX[0];
    int tempY = snakeY[0];
    int temp2X, temp2Y;
    for (int i = 0; i < taillqueue; i++)
    {
        temp2X = snakeX[i];
        temp2Y = snakeY[i];
        snakeX[i] = tempX;
        snakeY[i] = tempY;
        tempX = temp2X;
        tempY = temp2Y;
    }
    switch (direction)
    {
    case HAUT:
        snakeY[0]--;
        break;
    case BAS:
        snakeY[0]++;
        break;
    case GAUCHE:
        snakeX[0]--;
        break;
    case DROITE:
        snakeX[0]++;
        break;
    }
    if (snakeX[0] >= abscisse)
        snakeX[0] = 0;
    else if (snakeX[0] < 0)
        snakeX[0] = abscisse - 1;

    if (snakeY[0] >= ordonnee)
        snakeY[0] = 0;
    else if (snakeY[0] < 0)
        snakeY[0] = ordonnee - 1;

    for (int i = 1; i < taillqueue; i++)
    {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
        {
            gameOver = true; // collision avec le corps du serpent
        }
    }

    if (snakeX[0] == fruitX && snakeY[0] == fruitY)
    {
        fruitX = rand() % abscisse;
        fruitY = rand() % ordonnee;
        score++;
        taillqueue++;
    }
}

int main()
{
    
    banderole();
    cout << "\t Veuillez choisir un niveau : " << endl;

    int choix = 0;
    while (choix != 1 && choix != 2 && choix != 3)
    {
        cout << "\t 1- Facile \n";
        cout << "\t 2- Moyen \n";
        cout << "\t 3- Dificile \n";
        cout << "\t Quelle est votre choix (1, 2 ou 3):  ";
        cin >> choix;

        if (cin.fail() || (choix != 1 && choix != 2 && choix != 3))
        {
            cout << "\n\t Choix invalide, veuillez entrer soit 1, soit 2, soit 3.\n\n";
            cin.clear();
            cin.ignore(256, '\n');
        }
    }

    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        if(choix == 1)
            Sleep(150);
        else if(choix == 2)
            Sleep(60);
        else 
            Sleep(1);
    }
    cout << "Game Over! Final Score: " << score << endl;
    delete[] snakeX;
    delete[] snakeY;
    return 0;
}