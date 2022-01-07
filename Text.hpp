#pragma once
#include"Object.hpp"
class Text
{
public:

	bool onFinish = false;
	int32 duration = 40;
	Stopwatch stopwatch;
	String flag;
	Font font;
	int32 messageIndex;
	Array<String> messages;
	int32 index;
	bool all;
	Array<Array<String>> scenario = 
	{
		Array<String>
		{
			L"�Z��A�u�������́@��������ā@�����[�I\nSiv3D ���@�����Ɓ@�݂������@�R�[�h��",
			L"����@�������@�Ђ傤��������\n���񂪂����@�Ȃ炵����@�ł���񂾁I�v"
		},
		Array<String>
		{
			L"�s�G���u���� ���ɏo��񂾂ȁB\n�����炵�� �ł��� �⃂���X�^�[��",
			L"���݂� �܂��Ă��邼 !�v"
		},
		Array<String>
		{
			L"�Z��B�u������ ���Ȃ�������� �����ł��\n���������X�^�[���������Ă���B",
			L"�͂₭�s��Ɉ����z���������̂��ȁv"
		},
		Array<String>
		{
			L"�Z��C�u�A�x���B�C�G���[�Ƃ̃o�g����\n���ނ񂾂�!?  �����Ȃ�A",
			L"��������k�̍����ɂ���͂����� !!�v"
		},
		Array<String>
		{
			L"�A�x���u���� �� �Q�邩�E�E�v",
			L"flag Break"
		},
		Array<String>
		{
			L"���A���[�u���̂��� �����X�^�[���ł邯�� \n���Ȃ��� �p���[������Γ|����͂���",
			L"���ꂽ��Ƃ̃x�b�h�ŋx�ނƂ�����B�v"
		},
		Array<String>
		{
			L"���������΂������ĂȁB���̂��� �ʂ�Ȃ�\n�񂾁B���܂Ȃ����ׂ̓����s���Ă���B",
		},
		
		Array<String>
		{
			L"�A���X�u�C�G���[����̒�����󂯂�\n�̂ˁB ����Ȃ炤�ł��߂���",
			L" ���̂킽���ƃo�g�����܂��� !�v",
			L"flag Arisu"
		},
		Array<String>
		{
			L"�C�G���[�u���̉���|���ɗ����̂�...\n���������y���܂��Ă���� !�v",
			L"flag Yellow"
		},
		Array<String>
		{
			L"�G���Q��ł������Ă����炳������\n����ł��ɂ��邵���Ȃ���",
			L"����ɂ����Ƃ������� �˔\�������...."
		},
		Array<String>
		{
			L"�A���X�u�Ȃ��Ȃ�����ˁB\n���̕�����B�v"
		},
		Array<String>
		{
			L"�h�i���h�u�ڂ���������o�g���ł��B\n�����܂��� �Ƃ��{�[�� !!!�v",
			L"flag Donald"
		},
		Array<String>
		{
			L"�C�G���[�u���Ƃ̃o�g���ɒ��݂������̂�\n�k�̍����܂ł��� !!�v"
		},
		Array<String>
		{
			L"�h�i���h�u�C�G���[��2�̂̃����X�^�[\n���]���Ă��܂��B ���x�����グ��",
			L"�S�̍U���̋Z���o��������\n������������܂���v"
		},
		Array<String>
		{
			L"�`�������W���[�u���̃C�G���[���Ă��...\n �����炶���������o�Ȃ�������",
			L"���O���S���Ē��񂾕��������� �I�v"
		}
	};

	

	Text();

	String getFlag()
	{
		String flag2;
		flag2 = flag;
		flag = L"";
		return flag2;
	}

	Rect frame() const;

	void text();

	void update();

	void draw() const;

	void start(int32 phrase);

	bool isActive() const;

	void start(const Array<String> &text);
};
