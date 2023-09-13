#pragma once
class Diagram //테트리스 실제 블록들을 설정하는 곳
{
private:

	int x;
	int y;
public:
	Diagram();
	void SetPosition(int x, int y);
	void Move(int cx, int cy);
	int GetX()const;
	int GetY()const;

};

