#pragma once
#include<Siv3D.hpp>
class Gamedata
{
public:
	Point pos = {0,400};//��l���̍ŏ��̏����l
	int32 Hp = 35, Mp = 16, Exp = 0, Level = 1, Gold = 0;//��l���̍ŏ��̃X�e�[�^�X
	Point movement = {0,0};
	Array<bool> skillmessages = {
		false,
		false,
		false
	};
	bool Firstmessage = false;
	bool Donald_finish = false;
	bool Arisu_finish = false;

private:

};

