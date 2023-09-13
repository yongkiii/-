#include "Document.h"

 Document* Document:: singleton;

 //����ü ���� �ϳ��� ���� ������ ���ؼ� �̱������� ����
 Document* Document::GetSingleton()
 {
	 if (singleton == 0)
	 {
		 singleton = new Document();

	 }
	 return singleton;
 }
 //��ǥ�� ����� �ʱ� ���¶�� ���� �ȴ�. �̰� ���� ��ư
 void Document::MakeDiagram() 
 {
	 now->SetPosition(SX, SY);
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
	 MakeDiagram();
	 return false;

 }
 //���� ��ġ�� ���̾�׷����� ������ �ִ�.
 Document::Document() 
 {
	 now = new Diagram();
 }
 //���� �ð�
 Diagram* Document::GetNow()
 {
	 return now;
 }
 bool Document::MoveEnable(Diagram* now, int cx, int cy)
 {
	 int x = now->GetX() + cx;
	 int y = now->GetY() + cy;
	 if ((x >= 0) && (x < BOARD_COL) && (y >= 0) && (y < BOARD_ROW))
	 {
		 return true;
	 }
	 else
		 return false;
 }