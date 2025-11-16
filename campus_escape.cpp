#include <iostream>
#include <ctime>
using namespace std;

char **createMap(int h, int w);
void destroyMap(char **map, int h);
bool inBounds(int r, int c, int h, int w);
bool isWalkable(char ch);
void fillRooms(char **map, int h, int w);
void randomEmptyCell(char **map, int h, int w, int *rr, int *cc);
void placeRandom(char **map, int h, int w, char ch);
void render(char **map, int h, int w,
            int pr, int pc, int php, int patk, int buffHits, int moves,
            const char *inv, int invSize, int enemiesAlive);
char readInput();
void tryPickupItem(char **map, int r, int c, char *inventory, int *invSize);
void useItem(char *inventory, int *invSize, int slot, int *php, int *buffHits);
bool hasKey(const char *inventory, int *invSize);
bool movePlayer(char **map, int h, int w, int *pr, int *pc, char dir,
                char *inventory, int *invSize, int *php, int patk, int *buffHits, int *enemiesR, int *enemiesC,
                int *enemiesHP, int *enemiesATK, bool *enemiesAlive, int enemyCount, bool *reachedExit);
int enemyAt(int r, int c, int *enemiesR, int *enemiesC, bool *enemiesAlive, int n);
void resolveCombat(int *php, int patk, int *buffHits, int *ehp, int eatk);
void moveEnemies(char **map, int h, int w, int pr, int pc, int *enemiesR, int *enemiesC, int *enemiesHP, int *enemiesATK,
                 bool *enemiesAlive, int enemyCount, int *php, int patk, int *buffHits);

int main()
{
    srand(time(0));

    int H = 20, W = 30;
    int pr, pc, php = 100, patk = 5, buffHits = 0, moves = 0; // дефиниции/полета за Играч
    char inventory[6];
    int invSize = 0;

    unsigned short ALL_ENEMIES = 4; // definicii za LOSHITe
    bool enemiesAlive[ALL_ENEMIES];
    int enemiesR[ALL_ENEMIES], enemiesC[ALL_ENEMIES], enemiesHP[ALL_ENEMIES], enemiesATK[ALL_ENEMIES];
    char **map = createMap(H, W);
    fillRooms(map, H, W);

    for (int i = 0; i < ALL_ENEMIES; i++)
    {
        int r, c;
        randomEmptyCell(map, H, W, &r, &c); // TODO
        map[r][c] = (i % 2 == 0 ? '@' : '&');
        enemiesR[i] = r;
        enemiesC[i] = c;
        enemiesHP[i] = (i % 2 == 0 ? 7 : 5);
        enemiesATK[i] = (i % 2 == 0 ? 2 : 3);
        enemiesAlive[i] = true;
    }

    placeRandom(map, H, W, 'C');
    placeRandom(map, H, W, 'S');
    placeRandom(map, H, W, 'K');
    placeRandom(map, H, W, 'X');

    randomEmptyCell(map, H, W, &pr, &pc);

    bool reachedExit = false;
    while (!reachedExit && php > 0)
    {
        // system("clear"); // добавете ili system("CLS")
        int enemiesAliveCount = 0;
        for (int i = 0; i < ALL_ENEMIES - 1; i++)
        {
            if (enemiesAlive[i] == true)
            {
                enemiesAliveCount++;
            }
        }

        render(map, H, W, pr, pc, php, patk, buffHits, moves, &inventory[0], invSize, enemiesAliveCount);
        cout << "Move (WASD) / U [1-6] for inventory /  Q to quit:";
        char cmd = readInput();

        if (cmd == 'Q' || cmd == 'q')
        {
            break;
        }

        if (cmd == 'U' || cmd == 'u')
        {
            cout << "Slot :";
            int slot;
            cin >> slot;
            useItem(inventory, &invSize, slot, &php, &buffHits);
        }
        else
        {
            if (movePlayer(map, H, W, &pr, &pc, cmd, inventory, &invSize, &php, patk,
                           &buffHits, enemiesR, enemiesC, enemiesHP, enemiesATK, enemiesAlive, 0, &reachedExit))
            {
                moveEnemies(map, H, W, pr, pc, enemiesR, enemiesC, enemiesHP, enemiesATK, enemiesAlive, enemiesAliveCount, &php, patk, &buffHits);
                moves++;
            }
        }
    }
    if (php < 0)
    {
        cout << "Game over! You ran out of HP.\n";
    }
    else if (reachedExit)
    {
        cout << "You reached the exit and escaper the campus! \n";
    }
    else
    {
        cout << "Game quit.\n";
    }

    destroyMap(map, H);
    return 0;
}

char **createMap(int h, int w)
{
    char **arr = new char *[h];
    for (int i = 0; i < h; i++)
    {
        arr[i] = new char[w];
        for (int j = 0; j < w; j++)
        {
            arr[i][j] = '#'; // steni na kartata
        }
    }
    return arr;
};

void destroyMap(char **map, int h)
{
    for (int i = 0; i < h; i++)
    {
        delete[] map[i]; // iztrivame vseki red / masiv ot stoinosti CHAR
        map[i] = nullptr;
    }
    delete[] map;
    map = nullptr;
};

bool inBounds(int r, int c, int h, int w)
{
    return (r >= 0 && r < h && c >= 0 && c < w);
};

bool isWalkable(char ch)
{
    return (ch == '.' || ch == 'C' || ch == 'S' || ch == 'K' || ch == 'X');
}

void fillRooms(char **map, int h, int w)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == 0 || i == h - 1 || j == 0 || j == w - 1)
            {
                map[i][j] = '#'; // steni na kartata
            }
            else
            {
                map[i][j] = '.'; // plochki
            }
        }
    }
};

void randomEmptyCell(char **map, int h, int w, int *rr, int *cc)
{
    do
    {
        *rr = rand() % h; // присвояваме стойността на произволно число към стойността на указателя rr
        *cc = rand() % w;
    } while (map[*rr][*cc] != '.');
};

void placeRandom(char **map, int h, int w, char ch)
{
    int r, c;
    randomEmptyCell(map, h, w, &r, &c);
    map[r][c] = ch;
};

void render(char **map, int h, int w, int pr, int pc, int php, int patk, int buffHits, int moves, const char *inv, int invSize, int enemiesAlive)
{
    // system("clear"); // system("CLS");

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == pr && j == pc) /// pr  i pc
            {
                cout << 'P';
            }
            else
            {
                cout << map[i][j];
            }
        }
        cout << '\n';
    }
    cout << "HP: " << php << "| ATK: " << patk;
    if (buffHits > 0)
        cout << " Buff:" << buffHits;
    cout << " Moves:" << moves;
    cout << " Enemies:" << enemiesAlive << endl;
    cout << "Items[";
    for (int i = 0; i < invSize; i++)
    {
        cout << inv[i] << ",";
    }
    cout << "]\n";
    cout << "player = [" << pr << "][" << pc << "]\n";
};

char readInput()
{
    char ch;
    cin >> ch;
    return ch;
};

void tryPickupItem(char **map, int r, int c, char *inventory, int *invSize)
{
    char dot = map[r][c];
    if (dot == 'C' || dot == 'S' || dot == 'K')
    {
        if ((*invSize) < 6)
        { // max 6 elementa kato urujia
            inventory[*invSize] = dot;
            (*invSize)++;
            map[r][c] = '.';
            cout << "Took the item :" << dot << " !! \n";
        }
        else
        {
            cout << "The inventory is full";
        }
    }
};

const int HP_CAP = 20;
void useItem(char *inventory, int *invSize, int slot, int *php, int *buffHits)
{
    if (slot < 0 || slot > *invSize)
    {
        cout << "Invalid slot !\n";
        return;
    }
    char item = inventory[slot - 1];
    if (item == 'C')
    {
        *php = (*php + 5) > HP_CAP ? *php + 5 : HP_CAP;
        cout << "You drank coffee. HP =" << *php << "\n";
        for (int i = slot - 1; i < *invSize - 1; i++)
        {
            inventory[i] = inventory[i + 1];
        }
        (*invSize)--;
    }
    else if (item == 'S')
    {
        *buffHits = 3;
        cout << "You used a SUPER POWER ! +2 ATK For next 3 hits ! \n";
        for (int i = slot - 1; i < *invSize - 1; i++)
        {
            inventory[i] = inventory[i + 1];
        }
        (*invSize)--;
    }
    else if (item == 'K')
    {
        cout << "You already have the KEY ! \n";
        return;
    }
};

bool hasKey(const char *inventory, int *invSize)
{
    for (int i = 0; i < *invSize - 1; i++)
    {
        if (inventory[i] == 'K')
        {
            return true;
        }
    }
    return false;
};

bool movePlayer(char **map, int h, int w, int *pr, int *pc, char dir,
                char *inventory, int *invSize, int *php, int patk, int *buffHits, int *enemiesR, int *enemiesC,
                int *enemiesHP, int *enemiesATK, bool *enemiesAlive, int enemyCount, bool *reachedExit)
{

    int dr = 0, dc = 0;
    switch (toupper(dir)) // swithc uzpolzvame toupper()
    {
    case 'W':
        dr = -1;
        break;
    case 'S':
        dr = 1;
        break;
    case 'A':
        dc = -1;
        break;
    case 'D':
        dc = 1;
        break;
    default:
        return false;
    }

    int nc = *pc + dc;
    int nr = *pr + dr;
    char dest = map[nr][nc];
    if (dest == '#')
    {
        return false;
    }

    tryPickupItem(map, nr, nc, inventory, invSize);

    int eidx = enemyAt(nr, nc, enemiesR, enemiesC, enemiesAlive, enemyCount);

    if (eidx != -1)
    { // ne go pravim s (eidx) samo zashoto 0 e false i shte podminem loshiq na tazi poziciq v masivite
        resolveCombat(php, patk, buffHits, &enemiesHP[eidx], enemiesATK[eidx]);
        if (enemiesHP[eidx] <= 0)
        {
            enemiesAlive[eidx] = false;
            map[nr][nc] = '.';
        }
        else if (*php <= 0)
        {
            return true;
        }
    }

    if (inBounds(nr, nc, h, w) && isWalkable(map[nr][nc])) // za popravka
    {
        if (dest == 'X')
        {
            if (hasKey(inventory, invSize))
            {
                *reachedExit = true;
                return true;
            }
            else
            {
                cout << "Oops ! You need a key ! \n";
                return false;
            }
        }
        else
        {
            map[*pr][*pc] = '.'; // tuk promenqme starata stoinost na Igracha s prazno pole
            *pr = nr;
            *pc = nc;
            map[*pr][*pc] = 'P'; // zamenqme novata stoinost na stupenoto pole sus P
        }
    }

    // *pr = nr;
    // *pc = nc;
    return true;
};

int enemyAt(int r, int c, int *enemiesR, int *enemiesC, bool *enemiesAlive, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (enemiesAlive[i] && enemiesR[i] == r && enemiesC[i] == c)
        { // proverqvame dali loshiq suotvetstva na poleto na igracha
            return i;
        }
    }
    return -1; // vrushatame -1 zashtoto ako vurnem 0 toava enemy at 0 index ! Vnimavai
};

void resolveCombat(int *php, int patk, int *buffHits, int *ehp, int eatk)
{
    while (*php > 0 && *ehp > 0)
    {
        int dmg = patk + ((*buffHits) > 0 ? 2 : 0);
        *ehp -= dmg;
        if (*buffHits > 0)
        {
            (*buffHits)--;
        }
        *php = *php - eatk; // tuk namalqme kruvta
    }
};

void moveEnemies(char **map, int h, int w, int pr, int pc, int *enemiesR, int *enemiesC, int *enemiesHP, int *enemiesATK,
                 bool *enemiesAlive, int enemyCount, int *php, int patk, int *buffHits)
{
    // vuv tazi funkciq/method pr i pc sa prosto nashite user red i kolona kato cqlata funkciq e za Enemy losh igrach
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemiesAlive[i])
            continue; // ako stoinosta za loshiq e false = 0 => suotvetno produlji kum sledvashtata iteraciq na bloka
        int dr = 0, dc = 0;
        int dist = abs(enemiesR[i] - pr) + abs(enemiesC[i] - pc); // dis = vector toi=[9][1]  nie[5][1]  5

        if (dist <= 5)
        {
            if (abs(pr - enemiesR[i]) > abs(pc - enemiesC[i]))
            { //    abs(1-9)4. [5][] > [][0]   => 8  loshiqt Enemy idva kum nas kato suotvetno zavisi dali po dalech na visochina ili duljina
                dr = (pr > enemiesR[i] ? 1 : -1);
            }
            else
            {
                dc = (pc > enemiesC[i] ? 1 : -1);
            }
        }
        else
        {
            int r = rand() % 4; // random movement of losh chovek
            if (r == 0)
                dr = -1;
            if (r == 1)
                dr = 1;
            if (r == 2)
                dc = -1;
            if (r == 3)
                dc = -1;
        }
        int nr = enemiesR[i] + dr;
        int nc = enemiesC[i] + dc;
        if (!inBounds(nr, nc, h, w))
            continue;
        if (nr == pr && nc == pc)
        {
            resolveCombat(php, patk, buffHits, &enemiesHP[i], enemiesATK[i]);
            if (enemiesHP[i] <= 0)
            {
                enemiesAlive[i] = false;
            }
            continue;
        }

        if (map[nr][nc] == '.')
        {
            map[enemiesR[i]][enemiesC[i]] = '.'; // iskame ubitiqt ni Enemy Лош да остане само на прах
            enemiesR[i] = nr;
            enemiesC[i] = nc;
            map[nr][nc] = '@'; // символ за враг
        }
    }
};
