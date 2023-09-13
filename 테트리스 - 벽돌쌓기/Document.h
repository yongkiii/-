#pragma once
#include "Diagram.h" // 테트리스 전체적인 판때기 구성
#include "Board.h"
#define SX 5
#define SY 0

#define BOARD_SX 70
#define BOARD_SY 50
#define MY_WIDTH 15
#define MY_HEIGHT 15
#define MY_RX(x) (BOARD_SX+(x)*MY_WIDTH)
#define MY_RY(y) (BOARD_SY+(y)*MY_HEIGHT)
#define NEXT_SX 300
#define MY_NRX(x) (NEXT_SX+(x)*MY_WIDTH)
#define MY_NRY(y) MY_RY(y)

#define DIAGRAM_WIDTH 4
#define DIAGRAM_HEIGHT 4
#define DW DIAGRAM_WIDTH
#define DH DIAGRAM_HEIGHT
#define BOARD_COL 10
#define BOARD_ROW 18
#define TID_DROP 1032

class Document
{
private:
	Diagram* now;
	Diagram* next;
	Board* board;
	static Document* singleton;
public:
	static Document* GetSingleton();
	void MakeDiagram(); //시작 위치로 이동
	void ChangeDiagram();
	bool MoveLeft();
	bool MoveRight();
	bool MoveDown(bool *is_end);
	bool MoveTurn();
	Diagram* GetNow();
	Diagram* GetNext();
	bool MoveEnable(Diagram* now, int cx, int cy, bool is_turn=false);
	bs_arr GetBoard();
private:
	Document();
};

