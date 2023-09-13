#include "Document.h"

 Document* Document:: singleton;

 //����ü ���� �ϳ��� ���� ������ ���ؼ� �̱������� ����
 Document* Document::GetSingleton()
 {
	 if (singleton == 0)
	 {
		 srand((unsigned)time(0)); // �����õ弳��
		 singleton = new Document();

	 }
	 return singleton;
 }
 //��ǥ�� ����� �ʱ� ���¶�� ���� �ȴ�. �̰� ���� ��ư
 void Document::MakeDiagram() 
 {
	 next->SetPosition(SX, SY); // next ���� ����
	 now->SetPosition(SX, SY); // now ���� ����
	 
	 
	 // now ��ǥ�� ���� ��ǥ�� �̵�
 }
 //�������� �̵��ϴµ� 1. �̵� ���ɿ��� �Լ� 2. ���� ����� �����̴� �Լ�(DIAGRAM)
 bool Document::MoveLeft()
 {
	 if (MoveEnable(now,-1,0))
	 {
		 now->Move(-1, 0);
		 return true;
	 }
	 return false;
	 //now�� ��ǥ�� 1����
 }

 bool Document::MoveRight()
 {
	 if (MoveEnable(now,1,0))
	 {
		 now->Move(1, 0);
		 return true;
	 }
	 return false;
	 
	 //now ��ǥ�� 1 ����
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
 //���� ��ġ�� ���̾�׷����� ������ �ִ�.
 Document::Document() 
 {
	now = new Diagram();
	next = new Diagram();
	board = new Board();
	MakeDiagram();
 }
 //���� �ð�
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