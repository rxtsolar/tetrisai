#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <ctime>
#include <iostream>
using namespace std;

#include "tetris.h"

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(int xx, int yy)
{
    x = xx;
    y = yy;
}

bool Point::operator==(const Point& p) const
{
    return x == p.x && y == p.y;
}

bool Point::operator<(const Point& p) const
{
    return y == p.y ? x < p.x : y < p.y;
}

Point& Point::operator=(const Point& p)
{
    x = p.x;
    y = p.y;
    return *this;
}

bool Point::operator()(const Point& p1, const Point& p2) const
{
    return p1 < p2;
}


Grid::Grid()
{
    color = EMPTY;
}

Grid::Grid(Color c)
{
    color = c;
}

bool Grid::isEmpty() const
{
    return color == EMPTY;
}

bool Grid::isFrozen() const
{
    return color == WHITE;
}

Grid& Grid::operator=(const Grid& g)
{
    color = g.color;
    return *this;
}


void Piece::goUp()
{
    map<Point, Grid, Point> after;
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++)
        after[Point(it->first.x, it->first.y+1)] = it->second;
    piece = after;
    y++;
}

void Piece::goDown()
{
    map<Point, Grid, Point> after;
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++)
        after[Point(it->first.x, it->first.y-1)] = it->second;
    piece = after;
    y--;
}

void Piece::goLeft()
{
    map<Point, Grid, Point> after;
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++)
        after[Point(it->first.x-1, it->first.y)] = it->second;
    piece = after;
    x--;
}

void Piece::goRight()
{
    map<Point, Grid, Point> after;
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++)
        after[Point(it->first.x+1, it->first.y)] = it->second;
    piece = after;
    x++;
}

map<Point, Grid, Point> Piece::getPiece() const
{
    return piece;
}

Color Piece::getColor() const
{
    return color;
}

int Piece::getNumStatus() const
{
    return num_status;
}

void Piece::draw() const
{
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++) {
        glPushMatrix();
        glTranslatef(it->first.x + 0.5, it->first.y + 0.5, 0.5);
        glutSolidCube(0.9);
        glPopMatrix();
    }
}


Tetris::Tetris()
{
    srand(time(0));
    initBoard();
    nextKind = randPiece();
    initPiece();
}

Tetris::~Tetris()
{
    delete currPiece;
}

void Tetris::rotate()
{
    if (pause || stop)
        return;
    nextMove = currPiece->clone();
    nextMove->rotate();
    if (isBlocked() && !tryToMove()) {
        delete nextMove;
    } else {
        delete currPiece;
        currPiece = nextMove;
    }
    nextMove = 0;
}

void Tetris::goDown()
{
    if (pause || stop)
        return;
    nextMove = currPiece->clone();
    nextMove->goDown();
    if (isBlocked()) {
        delete nextMove;
        freeze();
        erase();
        delete currPiece;
        initPiece();
    } else {
        delete currPiece;
        currPiece = nextMove;
    }
    nextMove = 0;
}

void Tetris::goLeft()
{
    if (pause || stop)
        return;
    nextMove = currPiece->clone();
    nextMove->goLeft();
    if (isBlocked()) {
        delete nextMove;
    } else {
        delete currPiece;
        currPiece = nextMove;
    }
    nextMove = 0;
}

void Tetris::goRight()
{
    if (pause || stop)
        return;
    nextMove = currPiece->clone();
    nextMove->goRight();
    if (isBlocked()) {
        delete nextMove;
    } else {
        delete currPiece;
        currPiece = nextMove;
    }
    nextMove = 0;
}

int Tetris::getPeriod() const
{
    return period;
}

int Tetris::getWidth() const
{
    return width;
}

int Tetris::getHeight() const
{
    return height;
}

int Tetris::getOffset() const
{
    return offset;
}

void Tetris::togglePause()
{
    pause = !pause;
}

void Tetris::restart()
{
    initBoard();
    nextKind = randPiece();
    initPiece();
}

bool Tetris::isPaused() const
{
    return pause;
}

bool Tetris::isStopped() const
{
    return stop;
}

void Tetris::initBoard()
{
    pause = true;
    stop = false;
    ai = true;
    period = DEF_PERIOD;
    width = DEF_WIDTH;
    height = DEF_HEIGHT;
    offset = DEF_OFFSET;
    score = 0;
    altitude = 0;
    board.clear();
    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
            board[Point(i, j)] = Grid();
    xcount.clear();
    ycount.clear();
    altit.clear();
    xcount.resize(height);
    ycount.resize(width);
    altit.resize(width);
}

void Tetris::initPiece()
{
    nextMove = 0;
    switch (nextKind) {
    case I:
        currPiece = new PieceI(width, height);
        break;
    case J:
        currPiece = new PieceJ(width, height);
        break;
    case L:
        currPiece = new PieceL(width, height);
        break;
    case O:
        currPiece = new PieceO(width, height);
        break;
    case S:
        currPiece = new PieceS(width, height);
        break;
    case T:
        currPiece = new PieceT(width, height);
        break;
    case Z:
        currPiece = new PieceZ(width, height);
        break;
    default:
        break;
    }
    nextKind = randPiece();
    if (ai)
        calcHeuristic();
    if (checkLost())
        stop = true;
}

void Tetris::freeze()
{
    map<Point, Grid, Point> piece = currPiece->getPiece();
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++) {
        board[it->first] = Grid(WHITE);
        xcount[it->first.y]++;
        ycount[it->first.x]++;
        if (altit[it->first.x] < it->first.y)
            altit[it->first.x] = it->first.y;
        if (altitude < it->first.y)
            altitude = it->first.y;
    }
}

void Tetris::erase()
{
    int cnt = 0;
    for (int k = 0; k < height; k++) {
        while (xcount[k] == width) {
            cnt++;
            altitude--;
            for (int j = k; j < height - 1; j++) {
                xcount[j] = xcount[j+1];
                for (int i = 0; i < width; i++)
                    board[Point(i, j)] = board[Point(i, j+1)];
            }
            for (int i = 0; i < width; i++) {
                ycount[i]--;
                board[Point(i, height-1)] = EMPTY;
            }
            xcount[height-1] = 0;
        }
    }
    score += cnt*cnt*100;
    cout << score << endl;
}

bool Tetris::isBlocked()
{
    map<Point, Grid, Point> piece = nextMove->getPiece();
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++) {
        if (it->first.x < 0 || it->first.x >= width ||
                it->first.y < 0 || it->first.y >=height)
            return true;
        if (board[it->first].isFrozen())
            return true;
    }
    return false;
}

bool Tetris::isBlocked(const Piece* p)
{
    map<Point, Grid, Point> piece = p->getPiece();
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++) {
        if (it->first.x < 0 || it->first.x >= width ||
                it->first.y < 0 || it->first.y >=height)
            return true;
        if (board[it->first].isFrozen())
            return true;
    }
    return false;
}

bool Tetris::tryToMove()
{
    nextMove->goLeft();
    if (isBlocked()) {
        nextMove->goRight();
        nextMove->goRight();
        if (isBlocked()) {
            nextMove->goRight();
            if (isBlocked())
                return false;
        }
    }
    return true;
}

bool Tetris::checkLost()
{
    map<Point, Grid, Point> piece = currPiece->getPiece();
    map<Point, Grid, Point>::const_iterator it;
    for (it = piece.begin(); it != piece.end(); it++) {
        if (it->first.x < 0 || it->first.x >= width ||
                it->first.y < 0 || it->first.y >=height)
            return true;
        if (board[it->first].isFrozen())
            return true;
    }
    return false;
}

Kind Tetris::randPiece()
{
    int n;
    n = rand() % 7;
    switch (n) {
        case 0:
            return I;
        case 1:
            return J;
        case 2:
            return L;
        case 3:
            return O;
        case 4:
            return S;
        case 5:
            return T;
        case 6:
            return Z;
        default:
            return I;
    }
}

void Tetris::draw() const
{
    map<Point, Grid, Point>::const_iterator it;
    map<Point, Grid, Point> piece = currPiece->getPiece();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, height, 0.0);
    glVertex3f(width, height, 0.0);
    glVertex3f(width, 0.0, 0.0);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    for (it = board.begin(); it != board.end(); it++) {
        if (it->second.isFrozen()) {
            glPushMatrix();
            glTranslatef(it->first.x + 0.5, it->first.y + 0.5, 0.5);
            glutSolidCube(0.9);
            glPopMatrix();
        }
    }
    currPiece->draw();
}

void Tetris::drawInfo() const
{
    Piece* tempPiece;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 4.0, 0.0);
    glVertex3f(4.0, 4.0, 0.0);
    glVertex3f(4.0, 0.0, 0.0);
    glEnd();
    switch (nextKind) {
    case I:
        tempPiece = new PieceI(4, 4);
        break;
    case J:
        tempPiece = new PieceJ(4, 4);
        break;
    case L:
        tempPiece = new PieceL(4, 4);
        break;
    case O:
        tempPiece = new PieceO(4, 4);
        break;
    case S:
        tempPiece = new PieceS(4, 4);
        break;
    case T:
        tempPiece = new PieceT(4, 4);
        break;
    case Z:
        tempPiece = new PieceZ(4, 4);
        break;
    default:
        break;
    }
    tempPiece->draw();
    delete tempPiece;
}
