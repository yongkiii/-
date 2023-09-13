#include "Document.h"

 Document* Document:: singleton;

 //단일체 형성 하나의 폼의 생성을 위해서 싱글톤으로 형성
 Document* Document::GetSingleton()
 {
	 if (singleton == 0)
	 {
		 srand((unsigned)time(0)); // 랜덤시드설정
		 singleton = new Document();

	 }
	 return singleton;
 }
 //도표를 만드는 초기 상태라고 보면 된다. 이게 시작 버튼
 void Document::MakeDiagram() 
 {
	 next->SetPosition(SX, SY); // next 벽돌 설정
	 now->SetPosition(SX, SY); // now 벽돌 설정
	 
	 
	 // now 좌표를 시작 좌표로 이동
 }
 //왼쪽으로 이동하는데 1. 이동 가능여부 함수 2. 실제 블록이 움직이는 함수(DIAGRAM)
 bool Document::MoveLeft()
 {
	 if (MoveEnable(now,-1,0))
	 {
		 now->Move(-1, 0);
		 return true;
	 }
	 return false;
	 //now의 좌표를 1감소
 }

 bool Document::MoveRight()
 {
	 if (MoveEnable(now,1,0))
	 {
		 now->Move(1, 0);
		 return true;
	 }
	 return false;
	 
	 //now 좌표를 1 증가
 }
 bool  Document::MoveDown(bool* is_end)
 {
	 *is_end = false;
	 if (MoveEnable(now,0,1))
	 {
		 now->Move(0, 1);
		 return true;
	 }
	 else
	 {
		 int bnum = now->GetBNUM();
		 block bl = now->GetBlock(true);
		 int x = now->GetX();
		 int y = now->GetY();
		 board->AddBlock(bnum, bl, x, y);
	 }
	 ChangeDiagram();
	 block bl = now->GetBlock(true);
	 int x = now->GetX();
	 int y = now->GetY();
	 if (board->lsCrush(bl, x, y))
	 {
		 *is_end = true;
	 }
	 return false;

 }
 //현재 위치는 다이어그램에서 가지고 있다.
 Document::Document() 
 {
	now = new Diagram();
	next = new Diagram();
	board = new Board();
	MakeDiagram();
 }
 //현재 시간
 Diagram* Document::GetNow()
 {
	 return now;
 }
 bool Document::MoveEnable(Diagram* now, int cx, int cy,bool is_turn)
 {	
	 block bl = now->GetBlock(is_turn);
	 if (is_turn)
	 {
		 bl = now->GetBlock();
	 }
	 int x = now->GetX() + cx;
	 int y = now->GetY() + cy;
	 
	 return board->lsCrush(bl, x, y) == false;

	

 }
 void Document::ChangeDiagram()
 {
	 now->SetPosition(next);
	 next->SetPosition(SX,SY);

 }
 bool Document::MoveTurn()
 {
	 if (MoveEnable(now, 0, 0, true))
	 {
		 now->Turn();
		 return true;
	 }
	 return false;
 }
 Diagram* Document::GetNext()
 {
	 return next;
 }
 bs_arr Document::GetBoard()
 {
	 return board->GetBoardSpace();
 }