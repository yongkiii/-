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
 bool  Document::MoveDown()
 {
	 if (MoveEnable(now,0,1))
	 {
		 now->Move(0, 1);
		 return true;
	 }
	 ChangeDiagram();
	 return false;

 }
 //���� ��ġ�� ���̾�׷����� ������ �ִ�.
 Document::Document() 
 {
	now = new Diagram();
	next = new Diagram();
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
	 for (int xi = 0; xi < DW; xi++)
	 {
		 for (int yi = 0; yi < DH; yi++)
		 {
			 if (((x + xi) < 0) || ((x+xi) >= BOARD_COL) || ((y+yi)>BOARD_ROW) )
			 {
				 if (bl[yi][xi] == 1)
				 {
					 return false;
				 }
			 }
		 }
	 }
	 return true;
	 if ((x >= 0) && (x < BOARD_COL) && (y >= 0) && (y < BOARD_ROW))
	 {
		 return true;
	 }
		 return false;
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