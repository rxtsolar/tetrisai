#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <map>
#include <vector>

const int DEF_WIDTH = 10;
const int DEF_HEIGHT = 20;
const int DEF_PERIOD = 10;
const int DEF_OFFSET = 5;

const int DEF_PENALTY_HOLE = 10;
const int DEF_PENALTY_HEIGHT = 4;
const int DEF_PENALTY_LOC_HEIGHT = 5;
const int DEF_PENALTY_ZIGZAG = 0;
const int DEF_BONUS_ERASION = 8;

enum Color {EMPTY, RED, YELLOW, MAGENTA, BLUE, CYAN, GREEN, ORANGE, WHITE};
enum Kind {I, J, L, O, S, T, Z};

struct Point {
    int x;
    int y;

    Point();
    Point(int, int);
    bool operator==(const Point&) const;
    bool operator<(const Point&) const;
    Point& operator=(const Point&);
    bool operator()(const Point&, const Point&) const;
};

struct Grid {
    Color color;
    Grid();
    Grid(Color);
    bool isEmpty() const;
    bool isFrozen() const;
    Grid& operator=(const Grid&);
};

class Piece {
public:
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    std::map<Point, Grid, Point> getPiece() const;
    Color getColor() const;
    int getNumStatus() const;
    virtual void rotate() = 0;
    virtual Piece* clone() const = 0;
    virtual void draw() const;
protected:
    int x;
    int y;
    int status;
    int num_status;
    Kind kind;
    Color color;
    std::map<Point, Grid, Point> piece;
};

class PieceI : public Piece {
public:
    PieceI(const PieceI&);
    PieceI(int, int);
    void rotate();
    PieceI* clone() const;
    void draw() const;
};

class PieceJ : public Piece {
public:
    PieceJ(const PieceJ&);
    PieceJ(int, int);
    void rotate();
    PieceJ* clone() const;
    void draw() const;
};

class PieceL : public Piece {
public:
    PieceL(const PieceL&);
    PieceL(int, int);
    void rotate();
    PieceL* clone() const;
    void draw() const;
};

class PieceO : public Piece {
public:
    PieceO(const PieceO&);
    PieceO(int, int);
    void rotate();
    PieceO* clone() const;
    void draw() const;
};

class PieceS : public Piece {
public:
    PieceS(const PieceS&);
    PieceS(int, int);
    void rotate();
    PieceS* clone() const;
    void draw() const;
};

class PieceT : public Piece {
public:
    PieceT(const PieceT&);
    PieceT(int, int);
    void rotate();
    PieceT* clone() const;
    void draw() const;
};

class PieceZ : public Piece {
public:
    PieceZ(const PieceZ&);
    PieceZ(int, int);
    void rotate();
    PieceZ* clone() const;
    void draw() const;
};

class Tetris {
public:
    Tetris();
    ~Tetris();
    void rotate();
    void goDown();
    void goLeft();
    void goRight();
    int getPeriod() const;
    int getWidth() const;
    int getHeight() const;
    int getOffset() const;
    void togglePause();
    void restart();
    bool isPaused() const;
    bool isStopped() const;
    void draw() const;
    void drawInfo() const;

    bool useAI() const;
    void toggleAI();
    void aiMove();
private:
    bool pause;
    bool stop;
    int period;
    int width;
    int height;
    int altitude;
    int offset;
    int score;
    std::vector<int> xcount;
    std::vector<int> ycount;
    std::vector<int> altit;
    std::map<Point, Grid, Point> board;
    Piece* currPiece;
    Piece* nextMove;
    Kind nextKind;

    void initBoard();
    void initPiece();
    void freeze();
    void erase();
    bool isBlocked();
    bool isBlocked(const Piece*);
    bool tryToMove();
    bool checkLost();
    Kind randPiece();

    bool ai;
    int pos;
    int rot;

    void calcHeuristic();
    int getMaxLeft(int);
    int getMaxRight(int);
    int estimate(const Piece*);
};

#endif
