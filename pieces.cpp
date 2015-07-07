#include <GL/gl.h>
using namespace std;

#include "tetris.h"

PieceI::PieceI(const PieceI& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceI::PieceI(int width, int height)
{
    status = 0;
    x = width/2;
    y = height - 1;
    color = RED;
    piece[Point(x, y)] = color;
    piece[Point(x, y-1)] = color;
    piece[Point(x, y-2)] = color;
    piece[Point(x, y-3)] = color;
    num_status = 2;
}

void PieceI::rotate()
{
    piece.clear();
    if (status == 0) {
        piece[Point(x-2, y-1)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x+1, y-1)] = color;
        status = 1;
    } else if (status == 1) {
        piece[Point(x, y)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x, y-2)] = color;
        piece[Point(x, y-3)] = color;
        status = 0;
    }
}

PieceI* PieceI::clone() const
{
    return new PieceI(*this);
}

void PieceI::draw() const
{
    glColor3f(0.9, 0.0, 0.0);
    Piece::draw();
}


PieceJ::PieceJ(const PieceJ& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceJ::PieceJ(int width, int height)
{
    status = 0;
    x = width/2;
    y = height - 1;
    color = YELLOW;
    piece[Point(x, y)] = color;
    piece[Point(x, y-1)] = color;
    piece[Point(x, y-2)] = color;
    piece[Point(x-1, y-2)] = color;
    num_status = 4;
}

void PieceJ::rotate()
{
    piece.clear();
    if (status == 0) {
        piece[Point(x, y-2)] = color;
        piece[Point(x-1, y-2)] = color;
        piece[Point(x-2, y-2)] = color;
        piece[Point(x-2, y-1)] = color;
        status = 1;
    } else if (status == 1) {
        piece[Point(x-2, y-2)] = color;
        piece[Point(x-2, y-1)] = color;
        piece[Point(x-2, y)] = color;
        piece[Point(x-1, y)] = color;
        status = 2;
    } else if (status == 2) {
        piece[Point(x-2, y)] = color;
        piece[Point(x-1, y)] = color;
        piece[Point(x, y)] = color;
        piece[Point(x, y-1)] = color;
        status = 3;
    } else if (status == 3) {
        piece[Point(x, y)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x, y-2)] = color;
        piece[Point(x-1, y-2)] = color;
        status = 0;
    }
}

PieceJ* PieceJ::clone() const
{
    return new PieceJ(*this);
}

void PieceJ::draw() const
{
    glColor3f(0.6, 0.6, 0.0);
    Piece::draw();
}


PieceL::PieceL(const PieceL& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceL::PieceL(int width, int height)
{
    status = 0;
    x = width/2;
    y = height - 1;
    color = MAGENTA;
    piece[Point(x-1, y)] = color;
    piece[Point(x-1, y-1)] = color;
    piece[Point(x-1, y-2)] = color;
    piece[Point(x, y-2)] = color;
    num_status = 4;
}

void PieceL::rotate()
{
    piece.clear();
    if (status == 0) {
        piece[Point(x+1, y)] = color;
        piece[Point(x, y)] = color;
        piece[Point(x-1, y)] = color;
        piece[Point(x-1, y-1)] = color;
        status = 1;
    } else if (status == 1) {
        piece[Point(x+1, y-2)] = color;
        piece[Point(x+1, y-1)] = color;
        piece[Point(x+1, y)] = color;
        piece[Point(x, y)] = color;
        status = 2;
    } else if (status == 2) {
        piece[Point(x-1, y-2)] = color;
        piece[Point(x, y-2)] = color;
        piece[Point(x+1, y-2)] = color;
        piece[Point(x+1, y-1)] = color;
        status = 3;
    } else if (status == 3) {
        piece[Point(x-1, y)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x-1, y-2)] = color;
        piece[Point(x, y-2)] = color;
        status = 0;
    }
}

PieceL* PieceL::clone() const
{
    return new PieceL(*this);
}

void PieceL::draw() const
{
    glColor3f(1.0, 0.0, 0.8);
    Piece::draw();
}


PieceO::PieceO(const PieceO& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceO::PieceO(int width, int height)
{
    status = 0;
    x = width/2;
    y = height - 1;
    color = BLUE;
    piece[Point(x, y)] = color;
    piece[Point(x-1, y)] = color;
    piece[Point(x-1, y-1)] = color;
    piece[Point(x, y-1)] = color;
    num_status = 1;
}

void PieceO::rotate()
{
    return;
}

PieceO* PieceO::clone() const
{
    return new PieceO(*this);
}

void PieceO::draw() const
{
    glColor3f(0.0, 0.0, 0.9);
    Piece::draw();
}


PieceS::PieceS(const PieceS& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceS::PieceS(int width, int height)
{
    status = 0;
    x = width/2;
    y = height - 1;
    color = CYAN;
    piece[Point(x-1, y)] = color;
    piece[Point(x-1, y-1)] = color;
    piece[Point(x, y-1)] = color;
    piece[Point(x, y-2)] = color;
    num_status = 2;
}

void PieceS::rotate()
{
    piece.clear();
    if (status == 0) {
        piece[Point(x, y)] = color;
        piece[Point(x-1, y)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x-2, y-1)] = color;
        status = 1;
    } else if (status == 1) {
        piece[Point(x-1, y)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x, y-2)] = color;
        status = 0;
    }
}

PieceS* PieceS::clone() const
{
    return new PieceS(*this);
}

void PieceS::draw() const
{
    glColor3f(0.3, 0.8, 0.9);
    Piece::draw();
}


PieceT::PieceT(const PieceT& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceT::PieceT(int width, int height)
{
    status = 0;
    x = width/2 - 1;
    y = height - 1;
    color = GREEN;
    piece[Point(x, y)] = color;
    piece[Point(x, y-1)] = color;
    piece[Point(x, y-2)] = color;
    piece[Point(x+1, y-1)] = color;
    num_status = 4;
}

void PieceT::rotate()
{
    piece.clear();
    if (status == 0) {
        piece[Point(x+1, y-1)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x, y-2)] = color;
        status = 1;
    } else if (status == 1) {
        piece[Point(x, y-2)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x, y)] = color;
        piece[Point(x-1, y-1)] = color;
        status = 2;
    } else if (status == 2) {
        piece[Point(x-1, y-1)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x+1, y-1)] = color;
        piece[Point(x, y)] = color;
        status = 3;
    } else if (status == 3) {
        piece[Point(x, y)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x, y-2)] = color;
        piece[Point(x+1, y-1)] = color;
        status = 0;
    }
}

PieceT* PieceT::clone() const
{
    return new PieceT(*this);
}


void PieceT::draw() const
{
    glColor3f(0.0, 0.9, 0.0);
    Piece::draw();
}


PieceZ::PieceZ(const PieceZ& p)
{
    x = p.x;
    y = p.y;
    kind = p.kind;
    color = p.color;
    piece = p.piece;
    status = p.status;
    num_status = p.num_status;
}

PieceZ::PieceZ(int width, int height)
{
    status = 0;
    x = width/2;
    y = height - 1;
    color = ORANGE;
    piece[Point(x, y)] = color;
    piece[Point(x, y-1)] = color;
    piece[Point(x-1, y-1)] = color;
    piece[Point(x-1, y-2)] = color;
    num_status = 2;
}

void PieceZ::rotate()
{
    piece.clear();
    if (status == 0) {
        piece[Point(x-2, y)] = color;
        piece[Point(x-1, y)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x, y-1)] = color;
        status = 1;
    } else if (status == 1) {
        piece[Point(x, y)] = color;
        piece[Point(x, y-1)] = color;
        piece[Point(x-1, y-1)] = color;
        piece[Point(x-1, y-2)] = color;
        status = 0;
    }
}

PieceZ* PieceZ::clone() const
{
    return new PieceZ(*this);
}

void PieceZ::draw() const
{
    glColor3f(0.9, 0.5, 0.0);
    Piece::draw();
}

