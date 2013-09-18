#ifndef _BOARD_H_
#define _BOARD_H_

#include "cell.h"
#include "piece.h"

class Board
{
private:
  //Uint8 *refCount;
private:
#if DEBUG
  mutable char boardString[10][20];
#endif
  const Dimensions dimensions;
  const SIDE_t sides;
  const Uint8 nPieces;
  Piece *winner;
  Cell *cells;
  vector<Piece> *pieces;
  Piece **flags;
  vector<Piece *> out;
  Uint8 turn;
  
protected:
  int ejectPiece(Piece * const p, const Uint8 o);
  const bool canAttack(Piece * const p, Cell * const c) const;
  const bool canHandOff(Piece * const p, Cell * const c) const;
  virtual void ejectedPiece(Piece * const p, const Uint8 o) const 
  {
#if DEBUG
    toString();
#endif
  };
  virtual void playedIn(Piece * const p, Cell * const c) const 
  {
#if DEBUG
    toString();
#endif
  };
  virtual void moved(Piece * const p, Cell * const c) const 
  {
#if DEBUG
    toString();
#endif
  };
  virtual void handedOff(Piece * const p1, Piece * const p2) const 
  {
#if DEBUG
    toString();
#endif
  };
public:
  const char * const toString() const;
  const Dimensions &getDim() const {return dimensions;};
  const SIDE_t getSides() const {return sides;};
  const Uint8 getNumPieces() const {return nPieces;};
  Piece * const playIn(Piece * const p, Cell * const loc);
  Piece * const nextIn(const SIDE_t s) const;
  const bool move(Piece * const src, Cell * const dest);
  const bool handOff(Piece * const p1, Piece * const p2);
  Cell * const getCell(const Point &p) const;
  Cell * const getCell(Piece * const p) const;
  Piece * const getPiece(const Uint8 num, const SIDE_t s) const {return (num>nPieces || s>=sides || num == 0)? NULL:&(pieces[s][num-1]);};
  /*const Piece * const getPiece(const Uint8 num, const SIDE_t s) const
  {
    return const_cast<const Piece * const>((num>nPieces || s>sides || num == 0)? NULL:&pieces[s][num-1]);
  };
  */
  const Point getPoint(Cell * const c) const;
  const vector<Cell *> getValid(Piece * const p) const;
  const vector<Cell *> getValid(Cell * const c) const;
  Piece * const won() const {return winner;};
  const Uint8 getTurn() const {return turn;};
  const bool cellHere(Cell * const c) const  {return c >= cells && c < cells + int(dimensions.x().val*dimensions.y().val);};
  const SIDE_t whosTurn() const {return turn % getSides();};
  //TODO FIX THIS! v   it should return a reference! possibly iterators
  vector<Piece> &getPieceList(const SIDE_t s) const {return pieces[s];};
  
public:
  Board(Dimensions d=Point(10, 10), SIDE_t nSides=2, Uint8 nP=5, Cell * const c=NULL, vector<Piece> * const p=NULL);
  Board(const Board& other);
  Board& operator= (Board other);
  ~Board();
};



#endif