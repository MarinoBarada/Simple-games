#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class Ball {
private:
    int x, y;
    int originalX, originalY;
    eDir direction;
public:
    Ball(int posX, int posY);
    void Reset();
    void changeDirection(eDir d) { direction = d; }
    void randomDirection() { direction = (eDir)((rand() % 6) + 1); }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }
    void Move();
    friend ostream& operator<<(ostream& o, Ball c)
    {
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};

Ball::Ball(int posX, int posY)
{
    originalX = posX;
    originalY = posY;
    x = posX; y = posY;
    direction = STOP;
}

void Ball::Reset()
{
    x = originalX; y = originalY;
    direction = STOP;
}

void Ball::Move()
{
    switch (direction)
    {
    case STOP:
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UPLEFT:
        x--; y--;
        break;
    case DOWNLEFT:
        x--; y++;
        break;
    case UPRIGHT:
        x++; y--;
        break;
    case DOWNRIGHT:
        x++; y++;
        break;
    default:
        break;
    }
}

class Paddle
{
private:
    int x, y;
    int originalX, originalY;
public:
    Paddle() { x = y = 0; }
    Paddle(int posX, int posY) : Paddle() {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    inline void Reset() { x = originalX; y = originalY; }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }
    friend ostream& operator<<(ostream& o, Paddle c)
    {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }
};

class GameManager
{
private:
    int width, height;
    int score1, score2;
    int w_player1, w_player2;
    char up1, down1, up2, down2;
    bool quit;
    Ball* ball;
    Paddle* player1;
    Paddle* player2;
public:
    GameManager(int w, int h);
    ~GameManager() { delete ball, player1, player2; };
    void ScoreUp(Paddle* player);
    void Draw();
    void Input();
    void Logic();
    void Run();
    void Restart();
    void Win();
    void Results();
};

GameManager::GameManager(int w, int h)
{
    srand(time(NULL));
    quit = false;
    up1 = 'w'; up2 = 'i';
    down1 = 's'; down2 = 'k';
    score1 = score2 = 0;
    w_player1 = w_player2 = 0;
    width = w; height = h;
    ball = new Ball(w / 2, h / 2);
    player1 = new Paddle(1, h / 2 - 3);
    player2 = new Paddle(w - 2, h / 2 - 3);
}

void GameManager::ScoreUp(Paddle* player)
{
    if (player == player1)
        score1++;
    else if (player == player2)
        score2++;

    ball->Reset();
    player1->Reset();
    player2->Reset();
}

void GameManager::Draw()
{
    system("cls");
    cout << "\tPlayer1 moves with w a s d keys!" << endl;
    cout << "\tPlayer2 moves with i j k l keys!" << endl;
    cout << "\tThe player who collects 5 points wins the game" << endl;
    cout << "\tPress q if you want to exit the game.\n" << endl;
    for (int i = 0; i < width + 2; i++)
        cout << "\xB2";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ballx = ball->getX();
            int bally = ball->getY();
            int player1x = player1->getX();
            int player2x = player2->getX();
            int player1y = player1->getY();
            int player2y = player2->getY();

            if (j == 0)
                cout << "\xB2";

            if (ballx == j && bally == i)
                cout << "O"; //ball
            else if (player1x == j && player1y == i)
                cout << "\xDB"; //player1
            else if (player2x == j && player2y == i)
                cout << "\xDB"; //player2

            else if (player1x == j && player1y + 1 == i)
                cout << "\xDB"; //player1
            else if (player1x == j && player1y + 2 == i)
                cout << "\xDB"; //player1
            else if (player1x == j && player1y + 3 == i)
                cout << "\xDB"; //player1

            else if (player2x == j && player2y + 1 == i)
                cout << "\xDB"; //player2
            else if (player2x == j && player2y + 2 == i)
                cout << "\xDB"; //player2
            else if (player2x == j && player2y + 3 == i)
                cout << "\xDB"; //player2
            else
                cout << " ";

            if (j == width - 1)
                cout << "\xB2";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "\xB2";
    cout << endl;

    cout << "Score Player1: " << score1 << endl << "Score Player2: " << score2 << endl;
}

void GameManager::Input()
{
    ball->Move();

    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    if (_kbhit())
    {
        char current = _getch();
        if (current == up1)
            if (player1y > 0)
                player1->moveUp();
        if (current == up2)
            if (player2y > 0)
                player2->moveUp();
        if (current == down1)
            if (player1y + 4 < height)
                player1->moveDown();
        if (current == down2)
            if (player2y + 4 < height)
                player2->moveDown();

        if (ball->getDirection() == STOP)
            ball->randomDirection();

        if (current == 'q')
            quit = true;
    }
}

void GameManager::Logic()
{
    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    //left paddle
    for (int i = 0; i < 4; i++)
        if (ballx == player1x + 1)
            if (bally == player1y + i)
                ball->changeDirection((eDir)((rand() % 3) + 4));

    //right paddle
    for (int i = 0; i < 4; i++)
        if (ballx == player2x - 1)
            if (bally == player2y + i)
                ball->changeDirection((eDir)((rand() % 3) + 1));

    //bottom wall
    if (bally == height - 1)
        ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
    //top wall
    if (bally == 0)
        ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
    //right wall
    if (ballx == width - 1)
        ScoreUp(player1);
    //left wall
    if (ballx == 0)
        ScoreUp(player2);
}

void GameManager::Run()
{
    while (!quit)
    {
        Draw();
        Input();
        Logic();
        Win();
    }
}

void GameManager::Restart()
{
    quit = false;
    score1 = score2 = 0;
    ball->Reset();
    player1->Reset();
    player2->Reset();
}

void GameManager::Win()
{
    if (score1 == 5)
    {
        cout << "\nPlayer1 WIN!!!\n" << endl;
        w_player1++;
        quit = true;
    }
    if (score2 == 5)
    {
        cout << "\nPlayer2 WIN!!!\n" << endl;
        w_player2++;
        quit = true;
    }
}

void GameManager::Results()
{
    cout << "\n\tFINAL SCORE:" << endl;
    cout << "\tPlayer1 " << w_player1 << "  Player2 " << w_player2 << endl << endl;
}

int main()
{
    GameManager game(40, 20);
    int entry;

    game.Run();

    while (1)
    {
        cout << "\nDo you want to play again?\n1.YES\n2.NO\nEnter choice 1 or 2: ";
        cin >> entry;
        if (entry == 1)
        {
            game.Restart();
            game.Run();
        }
        else if (entry == 2)
            break;
        else
            cout << "Incorrect input, try again!!!(enter 1 or 2)" << endl << endl;
    }

    system("cls");
    game.Results();
    system("pause");
    return 0;
}