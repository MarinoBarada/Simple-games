#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>

using namespace std;

class Player
{
public:
    int x, y;
    Player(int width) { x = width / 2; y = 0; };
    void Restart(int width) { x = width / 2; y = 0; };
};

class Lane
{
private:
    deque<bool> cars;
    bool right;
public:
    Lane(int width);
    void Move();
    bool CheckPos(int pos) { return cars[pos]; }
    void ChangeDirection() { right = !right; }
};

Lane::Lane(int width)
{
    for (int i = 0; i < width; i++)
        cars.push_front(true);
    right = rand() % 2;
}

void Lane::Move()
{
    if (right)
    {
        if (rand() % 10 == 1)
            cars.push_front(true);
        else
            cars.push_front(false);
        cars.pop_back();
    }
    else
    {
        if (rand() % 10 == 1)
            cars.push_back(true);
        else
            cars.push_back(false);
        cars.pop_front();
    }
}

class Game
{
private:
    bool quit;
    int numberOfLanes;
    int width;
    int score;
    Player* player;
    vector<Lane*> map;
public:
    Game(int w, int h);
    ~Game();
    void Draw();
    void Input();
    void Logic();
    void Run();
    int BestScore(int prevScore);
    void Restart();
};

Game::Game(int w = 20, int h = 10)
{
    numberOfLanes = h;
    width = w;
    quit = false;
    for (int i = 0; i < numberOfLanes; i++)
        map.push_back(new Lane(width));
    player = new Player(width);
}

Game::~Game()
{
    delete player;
    for (int i = 0; i < map.size(); i++)
    {
        Lane* current = map.back();
        map.pop_back();
        delete current;
    }
}

void Game::Draw()
{
    system("cls");
    cout << "\tPlayer moves with w a s d keys!" << endl;
    cout << "\tPress q if you want to exit the game.\n" << endl;
    for (int i = 0; i < numberOfLanes; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && (j == 0 || j == width - 1)) cout << "S";
            if (i == numberOfLanes - 1 && (j == 0 || j == width - 1)) cout << "F";
            if (map[i]->CheckPos(j) && i != 0 && i != numberOfLanes - 1)
                cout << "#";
            else if (player->x == j && player->y == i)
                cout << "V";
            else
                cout << " ";
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void Game::Input()
{
    if (_kbhit())
    {
        char current = _getch();
        if (current == 'a')
            player->x--;
        if (current == 'd')
            player->x++;
        if (current == 'w')
            player->y--;
        if (current == 's')
            player->y++;
        if (current == 'q')
            quit = true;
    }
}

void Game::Logic()
{
    for (int i = 1; i < numberOfLanes - 1; i++)
    {
        if (rand() % 10 == 1)
            map[i]->Move();
        if (map[i]->CheckPos(player->x) && player->y == i)
            quit = true;
    }
    if (player->y == numberOfLanes - 1)
    {
        score++;
        player->y = 0;
        cout << "\x07";
        map[rand() % numberOfLanes]->ChangeDirection();
    }
}

void Game::Run()
{
    while (!quit)
    {
        Input();
        Draw();
        Logic();
    }
}

int Game::BestScore(int prevScore)
{
    if (prevScore > score)
        return prevScore;
    else
        return score;
}

void Game::Restart()
{
    quit = false;
    player->Restart(width);
}

int main()
{
    srand(time(NULL));
    Game game(30, 5);
    int entry, bestScore = 0;

    game.Run();
    bestScore = game.BestScore(bestScore);
    cout << "Game over!" << endl;

    while (1)
    {
        cout << "\nDo you want to play again?\n1.YES\n2.NO\nEnter choice 1 or 2: ";
        cin >> entry;
        if (entry == 1)
        {
            game.Restart();
            game.Run();
            bestScore = game.BestScore(bestScore);
        }
        else if (entry == 2)
            break;
        else
            cout << "Incorrect input, try again!!!(enter 1 or 2)" << endl << endl;
    }

    system("cls");
    cout << "\n\tBEST SCORE: " << bestScore << endl << endl;;
    system("pause");
    return 0;
}