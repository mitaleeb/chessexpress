/**
 * board.c - contains implementations of functions that do actions upon a
 * representation of the chessboard.
 * 
 * @author Dean Biskup and Mitalee Bharadwaj
 * 
 * University of Illinois, ADSL (ECE 395), 2019
 */

#include <stdlib.h>
#include "board.h"

/* declare some static helper functions */
static int isValidMove(board_t* board, int player, pos_t fromPos, pos_t toPos);
static int isDiagonal(pos_t fromPos, pos_t toPos);
static int isValidMoveKnight(pos_t fromPos, pos_t toPos);
static int isValidMovePawn(pos_t fromPos, pos_t toPos, int color);

board_t newBoard() {
  board_t fresh;
  // clear all the squares
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {
      fresh.squares[i][j] = CLEAR;
    }
  }

  // fill in the relevants squares with the pieces - 32 total
  for (i = 0; i < BOARD_SIZE; i++) {
    // fill in pawns across the columns
    fresh.squares[i][ROW_2] = PIECE(WHITE, PAWN);
    fresh.squares[i][ROW_7] = PIECE(BLACK, PAWN);
  }

  fresh.squares[COL_A][ROW_1] = PIECE(WHITE, ROOK);
  fresh.squares[COL_A][ROW_8] = PIECE(BLACK, ROOK);
  fresh.squares[COL_B][ROW_1] = PIECE(WHITE, KNIGHT);
  fresh.squares[COL_B][ROW_8] = PIECE(BLACK, KNIGHT);
  fresh.squares[COL_C][ROW_1] = PIECE(WHITE, BISHOP);
  fresh.squares[COL_C][ROW_8] = PIECE(BLACK, BISHOP);
  fresh.squares[COL_D][ROW_1] = PIECE(WHITE, QUEEN);
  fresh.squares[COL_D][ROW_8] = PIECE(BLACK, QUEEN);
  fresh.squares[COL_E][ROW_1] = PIECE(WHITE, KING);
  fresh.squares[COL_E][ROW_8] = PIECE(BLACK, KING);
  fresh.squares[COL_F][ROW_1] = PIECE(WHITE, BISHOP);
  fresh.squares[COL_F][ROW_8] = PIECE(BLACK, BISHOP);
  fresh.squares[COL_G][ROW_1] = PIECE(WHITE, KNIGHT);
  fresh.squares[COL_G][ROW_8] = PIECE(BLACK, KNIGHT);
  fresh.squares[COL_H][ROW_1] = PIECE(WHITE, ROOK);
  fresh.squares[COL_H][ROW_8] = PIECE(BLACK, ROOK);

  return fresh;
}

int makeMove(board_t* board, int player, pos_t fromPos, pos_t toPos) {
  if (isValidMove(board, player, fromPos, toPos)) {
    return makeMoveNoCheck(board, fromPos, toPos);
  }
  return 0; // not a valid move, so we failed
}

int makeMoveNoCheck(board_t* board, pos_t fromPos, pos_t toPos) {
  int fromCol = fromPos.col;
  int fromRow = fromPos.row;

  board->squares[toPos.col][toPos.row] = board->squares[fromCol][fromRow];
  board->squares[fromCol][fromRow] = CLEAR;
  return 1;
}

int isValidMove(board_t* board, int player, pos_t fromPos, pos_t toPos) {
  int data, rank, color, cor;

  // can't move outside of the board
  if (fromPos.col >= BOARD_SIZE || fromPos.col < 0 || fromPos.row >= BOARD_SIZE 
      || fromPos.row < 0 || toPos.col >= BOARD_SIZE || toPos.col < 0
      || toPos.row >= BOARD_SIZE || toPos.row < 0) {
    return 0;
  }

  // get some data
  data = board->squares[fromPos.col][fromPos.row];
  rank = RANK(data);
  color = PLAYER(data);
  
  // fail if the player is incorrect
  if (color != player) {
    return 0;
  }

  // can't move to the same square
  if (toPos.col == fromPos.col && toPos.row == fromPos.row) {
    return 0;
  }

  // check if it is a valid move for the rank of piece
  cor = 0;
  if (rank == KING) {
    if (abs(fromPos.col - toPos.col) > 1 || abs(fromPos.row - toPos.row) > 1) {
      return 0;
    }
  } else if (rank == QUEEN) {
    if (fromPos.col == toPos.col || fromPos.row == toPos.col 
        || isDiagonal(fromPos, toPos)) {
      cor = 1;
    }
  } else if (rank == ROOK) {
    if (fromPos.col == toPos.col || fromPos.row == toPos.row) {
      cor = 1;
    }
  } else if (rank == BISHOP) {
    if (isDiagonal(fromPos, toPos)) {
      cor = 1;
    }
  } else if (rank == KNIGHT) {
    if (isValidMoveKnight(fromPos, toPos)) {
      cor = 1;
    }
  } else if (rank == PAWN) {
    if (isValidMovePawn(fromPos, toPos, color)) {
      cor = 1;
    }
  }
  if (cor == 0) {
    return 0; // was not a valid move
  }

  // cannot move into a square with your own piece
  int toData = board->squares[toPos.col][toPos.row];
  if (PLAYER(toData) == color) {
    return 0;
  }

  // cannot move through pieces unless knight
  if (rank != KNIGHT) {
    // @TODO
  }

  return 1; // passed everything!
}

int isDiagonal(pos_t fromPos, pos_t toPos) {
  return abs(fromPos.col - toPos.col) == abs(fromPos.row - toPos.row);
}

int isValidMoveKnight(pos_t fromPos, pos_t toPos) {
  int valid = 0;
  if (abs(toPos.col - fromPos.col) == 2 && abs(toPos.row - fromPos.row) == 1) {
    valid = 1;
  } else if (abs(toPos.col - fromPos.col) == 1 && abs(toPos.row - fromPos.row) == 2) {
    valid = 1;
  }
  return valid;
}

int isValidMovePawn(pos_t fromPos, pos_t toPos, int color) {
  int valid = 0;
  // @TODO:
  return valid;
}
