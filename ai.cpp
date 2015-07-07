#include "tetris.h"

#include <iostream>
using namespace std;

bool Tetris::useAI() const
{
    return ai;
}

void Tetris::aiMove()
{
    if (pos > 0) {
        goRight();
        pos--;
    } else if (pos < 0) {
        goLeft();
        pos++;
    }
    if (rot > 0) {
        rotate();
        rot--;
    }
}

void Tetris::toggleAI()
{
    ai = !ai;
}

int Tetris::getMaxLeft(int status)
{
    int n = 0;
    Piece* left = currPiece->clone();
    for (int i = 0; i < status; i++)
        left->rotate();
    while (!isBlocked(left)) {
        left->goLeft();
        n++;
    }
    delete left;
    return n;
}

int Tetris::getMaxRight(int status)
{
    int n = 0;
    Piece* right = currPiece->clone();
    for (int i = 0; i < status; i++)
        right->rotate();
    while (!isBlocked(right)) {
        right->goRight();
        n++;
    }
    delete right;
    return n;
}

int Tetris::estimate(const Piece* p)
{
    int score = 0;
    int highest = 0;
    int xcoord;
    int g_diff;
    int l_diff;
    int zigzag;
    map<Point, Grid, Point> piece;
    map<Point, Grid, Point> temp;
    map<Point, Grid, Point>::const_iterator it;
    vector<int> cnt = xcount;
    vector<int> alt = altit;
    vector<int>::const_iterator cit;
    Piece* down = p->clone();
    while(!isBlocked(down))
        down->goDown();
    down->goUp();

    piece = down->getPiece();
    temp = piece;
    for (it = piece.begin(); it !=piece.end(); it++) {
        Point pt(it->first.x, it->first.y - 1);
        cnt[it->first.y]++;
        if (alt[it->first.x] < it->first.y)
            alt[it->first.x] = it->first.y;
        if (it->first.y > 0 && board[pt].isEmpty() && temp[pt].isEmpty())
            score -= DEF_PENALTY_HOLE;
        if (highest < it->first.y) {
            highest = it->first.y;
            xcoord = it->first.x;
        }
    }
    g_diff = highest - altitude;
    l_diff = highest;
    if (g_diff > 0)
        score -= DEF_PENALTY_HEIGHT * g_diff;
    score -= DEF_PENALTY_LOC_HEIGHT * l_diff;
    for (cit = cnt.begin(); cit != cnt.end(); cit++)
        if (*cit == width)
            score += DEF_BONUS_ERASION;
    for (cit = alt.begin(); cit != alt.end() - 1; cit++)
        zigzag += *cit > *(cit+1) ? *cit - *(cit+1) : *(cit+1) - *cit;
    score -= DEF_PENALTY_ZIGZAG * zigzag;
    delete down;
    return score;
}

void Tetris::calcHeuristic()
{
    int x;
    int best = -10000;
    for (int k = 0; k < currPiece->getNumStatus(); k++) {
        Piece* p = currPiece->clone();
        for (int r = 0; r < k; r++)
            p->rotate();
        x = 0;
        int l = getMaxLeft(k);
        int r = getMaxRight(k);
        for (int i = 0; i < l; i++) {
            p->goLeft();
            x--;
        }
        for (int i = 0; i < l + r - 1; i++) {
            p->goRight();
            int score = estimate(p);
            if (score > best) {
                best = score;
                pos = x + i + 1;
                rot = k;
            }
        }
        delete p;
    }
}
