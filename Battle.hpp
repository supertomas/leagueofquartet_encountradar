# pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Enemy.hpp"
# include "Gamedata.hpp"
#include"Battle_Escape_Com.hpp"
#include"Special_Com.hpp"
# include "TextManager.hpp"
#include"Status.hpp"
#include"Title.hpp"
enum class mode
{
	comandMenu, skiimenu, target, escape, statusMessage
};

class AllBattle : public SceneManager<String, Gamedata>::Scene
{
public:
	int AttackP;
	int DefenceP;
	int MetalDefence;
	int SpeedP;
	Status status;
	Array<EnemyData> enemies;
	String Firstmessage;
	String escapeMessage;
	mode ModeScreen = mode::comandMenu;
	std::vector<String> Scene;
	std::unique_ptr <Images> Image;
	Battle_Escape_Com battle_com;
	Sound townM;
	Sound BattleM;

	int escapeRandom()
	{
		return Random(0, 1);
	}

	String playerAction(String action)
	{
		if (m_data->Hp > 0)
		{
			if (action == L"��������")
			{
				int Enemydamage = AttackP - enemies[target].Defence;
				if (Enemydamage > 0)
				{
					enemies[target].Hp = enemies[target].Hp - Enemydamage;
					return Format(L"�A�x���̂�������", enemies[target].type, L"��\n", Enemydamage, L"�|�C���g�̃_���[�W��^�����B");
				}
				else if (Enemydamage <= 0)
				{
					return Format(L"�A�x���̂�������   ������\n", enemies[target].type, L"�Ƀ_���[�W��^�����Ȃ��B");
				}
			}
			else if (action == L"����������")
			{
				if (AttackP < status.AttackPUp(m_data->Level) + 8 + m_data->Level)
				{
					AttackP = Min(AttackP + 4 + m_data->Level, status.AttackPUp(m_data->Level) + 8 + m_data->Level);
					m_data->Mp -= 3;
					return Format(L"�A�x���� ���������� ������\n���������� ���傤���傤 !");
				}
				else
				{
					return Format(L"�A�x���� ���������� ������\n�������A����ȏケ�������� �͏オ��Ȃ�");
				}
			}

			else if (action == L"�΂������")
			{
				m_data->Mp -= 5;
				for (uint32 i = 0; i < enemies.size(); i++)
				{
					int Enemydamage = AttackP - m_data->Level * 2 - enemies[i].Defence;
					if (Enemydamage > 0)
					{
						enemies[i].Hp = enemies[i].Hp - Enemydamage;
					}
					else
					{

					}
				}
				return Format(L"�A�x���̂΂������\n�G�S�̂Ƀ_���[�W��^�����B");
			}

			else if (action == L"�z�[�v")
			{
				if (DefenceP < status.DefencePUp(m_data->Level) + 5 + m_data->Level)
				{
					m_data->Mp -= 3;
					DefenceP = Min(DefenceP + 3 + m_data->Level, status.AttackPUp(m_data->Level) + 5 + m_data->Level);
					return Format(L"�A�x���̓z�[�v �̂��������ƂȂ���\n�ڂ�����͂����������B");
				}
				else
				{
					return Format(L"�A�x���̓z�[�v �̂��������ƂȂ��� \n�������A����ȏ�ڂ������ �͏オ��Ȃ�");
				}

			}

			else if (action == L"�\�j�b�N�W���u")
			{
				m_data->Mp -= 4;
				int Enemydamage = AttackP - m_data->Level * 3 - enemies[target].Defence;
				if (Enemydamage > 0)
				{
					enemies[target].Hp = enemies[target].Hp - Enemydamage;
					SpeedP += 6;
					return Format(L"�A�x���̃\�j�b�N�W���u !!  �G��",Enemydamage,L"�_���[�W\n��^���A����ɃA�x���̑f���������������B");
				}
				else
				{
					return Format(L"�A�x���̃\�j�b�N�W���u!  �G�̓_���[�W��\n�󂯂Ȃ��������A�A�x���̑f�����͂��������B");
				}
			}
			else if (action == L"�߂�����")
			{
				m_data->Mp = Min(status.MaxMp(m_data->Level),m_data->Mp + 8);
				return Format(L"�A�x���͂߂������������B\nMP�������ӂ� !");
			}
			else if (action == L"���[��")
			{
				m_data->Mp -= 3;
				m_data->Hp = Min(status.MaxHp(m_data->Level), m_data->Hp + 15);
				return Format(L"�A�x���� ���[�� �̂��������ƂȂ���\nHP�� �����ӂ� �����B");
			}
			else if (action == L"�ɂ���")
			{
				return Format(L"�A�x���� �킴 �������Ȃ�");
			}

			else
			{
				// �����̊ԈႢ�łǂ̋Z�ɂ�����������Ȃ�������.
				return L"�A�x���� �ځ[���� ���Ă���";
			}
		}
		else
		{
			return Format(L"�A�x���ɐ키�͎͂c���Ă��Ȃ�...");
		}
	}


	void battle(String action)
	{
		// ������\�[�g����ƃ^�[�Q�b�g�悪�ς�邽�ߎg�p���Ȃ�.
		// std::sort(enemies.begin(), enemies.end(), [](const EnemyData& a, const EnemyData& b) { return a.Speed < b.Speed; });

		// std::pair<int32, int32> ��<�X�s�[�h, enemies�̓Y����>�̃f�[�^��\��.
		// { 10, 1 } �Ȃ�enemies[1].Speed��10�ł��邱�ƂɂȂ�.
		Array<std::pair<int32, int32>> characters;

		for (uint32 i = 0; i < enemies.size(); i++)
		{
			characters.emplace_back(enemies[i].Speed, i);
		}

		// enemies�̑����characters���\�[�g.
		std::sort(characters.begin(), characters.end(), [](const std::pair<int32, int32>& a, const std::pair<int32, int32>& b) { return a.first > b.first; });

		Array<String> messages;
		bool player = false;

		if (action == L"�ɂ���")
		{
			messages.push_back(L"�������ɂ����Ȃ��B");
		}

		// enemies�ł͂Ȃ�characters����.
		for (uint32 i = 0; i < characters.size(); i++)
		{
			// ����ȍ~ i �̑���� index ���g���̂ŗv���ӁI
			const int32 speed = characters[i].first;
			const int32 index = characters[i].second;
		
			if (SpeedP > speed && player == false && m_data->Hp > 0)
			{
				messages.push_back(playerAction(action));
				player = true;
			}
			else if (player == false)
			{
				messages.push_back(playerAction(action));
			}
			if (enemies[index].Hp > 0)
			{
				// ��x�ϐ��Ɋi�[���Ȃ���if�����ƂɈႤ�Z���o�Ă��܂�.
				const String choice = enemies[index].action[Random(0u, enemies[index].action.size() - 1)];

				if (choice == L"���݂�")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0,m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�̂��݂��������� !\n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W"));
						//SoundAsset(L"damage").playMulti();
					}
					else if(Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂��݂��������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B"));
					}
					
				}

				else if (choice == L"��������")
				{
					int Playerdamage = enemies[index].Attack - 5 - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�̂����傤�������� !\n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W"));
						//SoundAsset(L"damage").playMulti();
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂����傤�������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B"));
					}
				}
				else if (choice == L"�߂Ƃ�")
				{
					enemies[index].Attack += 5;
					messages.push_back(Format(enemies[index].type, L"�� �߂Ƃ� �������B\n", enemies[index].type, L"�̍U���͂����������B"));
				}
				else if (choice == L"��������")
				{
					messages.push_back(Format(enemies[index].type, L"�͂����������Ă���B"));
				}
				else if (choice == L"������")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�� ������ ��������\n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W���󂯂�"));
						//SoundAsset(L"damage").playMulti();
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂����� �������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B"));
					}
				}
				else if (choice == L"�l�q")
				{
					messages.push_back(Format(enemies[index].type, L"�͂悤�����݂Ă���B"));
				}
				else if (choice == L"���[��")
				{
					enemies[index].Hp = Min(10, enemies[index].Hp + 8);
					messages.push_back(Format(enemies[index].type, L"�� ���[�� �̂������\n���ƂȂ����B"));
					messages.push_back(Format(enemies[index].type, L"�͂����ӂ������B"));
				}

				else if (choice == L"���[��2")
				{
					enemies[index].Hp = Min(46, enemies[index].Hp + 10);
					messages.push_back(Format(enemies[index].type, L"�� ���[�� �̂������\n���ƂȂ����B"));
					messages.push_back(Format(enemies[index].type, L"�͂����ӂ������B"));
				}

				else if (choice == L"���[��3")
				{
					enemies[index].Hp = Min(65, enemies[index].Hp + 10);
					messages.push_back(Format(enemies[index].type, L"�� ���[�� �̂������\n���ƂȂ����B"));
					messages.push_back(Format(enemies[index].type, L"�͂����ӂ������B"));
				}
				else if (choice == L"�˂΂˂�")
				{
					SpeedP -= 5;
					messages.push_back(Format(enemies[index].type, L"�� �˂΂˂� �̉t���o�����B"));
					messages.push_back(Format(L"����݂��� ���΂₳ ��\n�������Ă��܂����B"));
				}

				else if (choice == L"�Ƃ����b�V��")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�̂Ƃ����b�V�� !\n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W"));
						//SoundAsset(L"damage").playMulti();
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂Ƃ����b�V��!  ������\n�A�x���̓_���[�W���󂯂Ȃ������B�B"));
					}
					m_data->Hp = m_data->Hp - Playerdamage;
					
				}

				else if (choice == L"���b�N�K�[�h")
				{
					if (rock_limit_defence == false)
					{
						MetalDefence = enemies[index].Defence + 10;
						rock_limit_defence = true;
					}
					if (enemies[index].Defence < MetalDefence)
					{
						enemies[index].Defence = Min(enemies[index].Defence + 5, MetalDefence);
						messages.push_back(Format(enemies[index].type, L"�̃��b�N�K�[�h !!\n", enemies[index].type, L"�̖h��͂����������B"));
					}
					else
					{

						messages.push_back(Format(enemies[index].type, L"�̃��b�N�K�[�h !!"));
						messages.push_back(Format(L"�������A����ȏ�", enemies[index].type, L"\n�̖h��͂͂�����Ȃ��B"));
					}
				}

				else if (choice == L"�̂�������")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�͂̂��������Ă����B\n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W"));
						//SoundAsset(L"damage").playMulti();
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B"));
					}
				}
				else if(choice == L"�{�f�B�[�v���X")
				{
					int Playerdamage = enemies[index].Attack - 3 - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�̃{�f�B�[�v���X�B\n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W��"));
						messages.push_back(L"�h��͂��������Ă��܂����B");
						//SoundAsset(L"damage").playMulti();
						DefenceP = Max(8, DefenceP - 4);
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̃{�f�B�[�v���X !  \n�A�x���̓_���[�W���󂯂Ȃ�������"));
						messages.push_back(L"�h��͂��������Ă��܂����B");
						DefenceP = Max(8,DefenceP - 4);
					}
				}
				else if(choice == L"�t���A")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�� ������� �t���A \n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W���󂯂�"));
						//SoundAsset(L"fire").playMulti();
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B�B"));
					}
				}

				else if (choice == L"���m�o�X")
				{
					if (DefenceP > 5)
					{
						messages.push_back(Format(enemies[index].type, L"�� ���m�o�X�̂������ �I"));
						messages.push_back(Format(L"�A�x���� �h��͂� �������Ă��܂���"));
						DefenceP = Max(5, DefenceP - 4);
					}
					else
					{
						messages.push_back(Format(enemies[index].type, L"�� ���m�o�X�̂������ �I"));
						messages.push_back(L"�������A�A�x���� �h��� \n�͏\���������Ă���B");
					}
				}
				else if (choice == L"���f�̓�")
				{
					if (AttackP > 19)
					{
						messages.push_back(Format(enemies[index].type, L"�� ���f�̓�"));
						messages.push_back(L"�A�x���� �݂�傤���� \n�U���͂���������");
						AttackP = Max(19,AttackP - 8);
					}
					else
					{
						messages.push_back(Format(enemies[index].type, L"�� ���f�̓�"));
						messages.push_back(L"�������A�A�x���� �U���� \n�͏\���������Ă���B");
					}
				}

				else if (choice == L"�C�����[�W�����_���X")
				{
					if (AttackP > 14)
					{
						messages.push_back(Format(enemies[index].type, L"�� �C�����[�W�����_���X"));
						messages.push_back(L"�A�x���� �݂�傤���� \n�U���͂���������");
						AttackP = Max(14, AttackP - 6);
					}
					else
					{
						messages.push_back(Format(enemies[index].type, L"�� �C�����[�W�����_���X"));
						messages.push_back(L"�������A�A�x���� �U���� \n�͏\���������Ă���B");
					}
				}

				else if (choice == L"�ΐ���")
				{
					int Playerdamage = enemies[index].Attack - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�� �ΐ��� �������� \n�A�x����", Playerdamage, L"�|�C���g�̃_���[�W���󂯂�"));
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̉ΐ��� �������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B�B"));
					}
				}
				else if (choice == L"�����̃p���`")
				{
					int Playerdamage = enemies[index].Attack - 6 - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�� �����̃p���`\n", Playerdamage, L"�|�C���g�̃_���[�W���󂯂�"));
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B�B"));
					}
				}

				else if (choice == L"��")
				{
					int Playerdamage = enemies[index].Attack - 5- DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�� ���@�̏���ӂ��Ă����B\n", Playerdamage, L"�|�C���g�̃_���[�W���󂯂�"));
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�� ���@�̏���ӂ��Ă����B !  \n�������A�x���̓_���[�W���󂯂Ȃ������B�B"));
					}
				}
				else if (choice == L"�X�e�b�v")
				{
					messages.push_back(Format(enemies[index].type, L"�̓X�e�b�v ���͂��߂��B \n",enemies[index].type,L"�̂��΂₳�����������B"));
					enemies[index].Speed += 8;
				}
				else if (choice == L"�{���e�b�N�X")
				{
					int Playerdamage = enemies[index].Attack - 4 - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						SpeedP -= 3;
						messages.push_back(Format(enemies[index].type, L"�� �{���e�b�N�X \n�A�x����" ,Playerdamage,L"�|�C���g�̃_���[�W���󂯂��B"));
						messages.push_back(L"����ɂ��т�ăA�x����\n�f�������������� �c ");
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B"));
					}
				}
				else if (choice == L"�͂ǂ��V���b�g")
				{
					int Playerdamage = enemies[index].Attack + 3 - DefenceP;
					if (Playerdamage > 0)
					{
						m_data->Hp = Max(0, m_data->Hp - Playerdamage);
						messages.push_back(Format(enemies[index].type, L"�� �K�E �͂ǂ��V���b�g\n�A�x����",Playerdamage,L"�|�C���g�̃_���[�W���󂯂��B"));
						messages.push_back(Format(L"�����", enemies[index].type,L"�̍U���͂����������B"));
						enemies[index].Attack += 4;
					}
					else if (Playerdamage <= 0)
					{
						messages.push_back(Format(enemies[index].type, L"�̂������� !  ������\n�A�x���̓_���[�W���󂯂Ȃ������B"));
						messages.push_back(Format(L"������", enemies[index].type, L"�̍U���͂����������B"));
						enemies[index].Attack += 4;
					}
				}
				else
				{
					// �����̊ԈႢ�łǂ̋Z�ɂ�����������Ȃ�������.

					messages.push_back(Format(enemies[index].type, L"�� �ځ[���� ���Ă���"));
				}
			}
		}

		TextManager::text->start(messages);
		//turnFinish = true;
	}

	void resetTarget()
	{
		// target�悪����łȂ������ׂ�.
		// ����ł�����A���[�v�ŉE�ׂ�Ɉړ�����.
		for (uint32 index = 0; index < enemies.size(); index++)
		{
			const int32 newTarget = (target + index) % enemies.size();

			if (enemies[newTarget].Hp > 0)
			{
				target = newTarget;

				break;
			}
		}
	}

	void targetUpdate()
	{
		if (Input::KeyRight.clicked)
		{
			// �^�[�Q�b�g���E�Ɉړ����A�v�f���𒴂��Ă����炻��ɍ��킹��.
			target = Min<int32>(target + 1, enemies.size() - 1);

			// target�悪����łȂ������ׂ�.
			// ����ł�����A���[�v�ŉE�ׂ�Ɉړ�����.
			for (uint32 index = 0; index < enemies.size(); index++)
			{
				const int32 newTarget = (target + index) % enemies.size();

				if (enemies[newTarget].Hp > 0)
				{
					target = newTarget;

					break;
				}
			}
		}

		if (Input::KeyLeft.clicked)
		{
			// �^�[�Q�b�g�����Ɉړ����A0�ɂȂ�����0�ɍ��킹��.
			target = Max<int32>(target - 1, 0);

			// target�̈ړ��悪����łȂ������ׂ�.
			// ����ł�����A���[�v�ō��ׂ�Ɉړ�����.
			for (uint32 index = 0; index < enemies.size(); index++)
			{
				// ���̒l�ɏ�]�Z�͎g���Ȃ��̂�enemies.size()�𑫂��āA�K�����̐��ɂȂ�悤�ɂ���.
				const int32 newTarget = (target - index + enemies.size()) % enemies.size();

				if (enemies[newTarget].Hp > 0)
				{
					target = newTarget;
					break;
				}
			}
		}
	}

	bool win() const
	{
		bool win = true;

		for (uint32 i = 0; i < enemies.size(); ++i)
		{
			// ��l�ł������c���Ă��� win �ł͂Ȃ�
			if (enemies[i].Hp > 0)
			{
				win = false;
			}
		}

		return win;
	}

	bool lose() const
	{
		// �v���C���[�����񂾂�Q�[���I�[�o�[

		return m_data->Hp <= 0;
	}

	void update() override
	{
		BattleM.play();

		// �u�܂��̂������ꂽ�v�\�����͉��������Ȃ�.
		if (timer.ms() < 1000)
		{
			return;
		}

		// ����͕K���K�v�Ȃ̂�Main.cpp�Ɉړ�
		TextManager::text->update();

		// TextManager�N�����͉������Ȃ�.
		if (TextManager::text->isActive() == true)
		{
			return;
		}

		// finish��true�ɂȂ�����V�[���J��
		for (auto& i : Scene)
		{
			if (finish == true)
			{
				//�������������Q�[���I�[�o�[�ɑJ�ڂ���.
				//�������������̎��͌��̃t�B�[���h�ɖ߂�.
				if (lose())
				{
					changeScene(L"Gameover");
					BattleM.pause();
				}
				else
				{
					changeScene(i);
					BattleM.pause();
					townM.play();
				}
				return;
			}
		}


			
		// �s�k����
		if (lose())
		{
			TextManager::text->start({ L"�A�x���� �͂��Ă��܂��� ..." });

			finish = true;

			return;
		}

		// ��������
		if (win())
		{
			int32 allExp = 0;
			int32 allMoney = 0;
		
			for (uint32 i = 0; i < enemies.size(); i++)
			{
				allExp += enemies[i].Exp;
				allMoney += enemies[i].money;
			}

			m_data->Exp += allExp;
			Array<String> messages;
			messages.push_back(L"�G�����������B");
			messages.push_back(Format(allExp, L"�|�C���g�̂������񂿂������Ƃ�"));
			messages.push_back(Format(allMoney, L"�[�j�[�������Ƃ�"));
			if (status.LevelUp(m_data->Exp,m_data->Level))
			{
				ModeScreen = mode::statusMessage;
				messages.push_back(Format(L"�A�x���̃��x�������������B"));
				messages.push_back(Format(L"���ꂼ��̃X�e�[�^�X�����������B"));
				m_data->Level += 1;
				m_data->Hp = status.MaxHp(m_data->Level);
				m_data->Mp = status.MaxMp(m_data->Level);
			}


			if (status.getSkill(m_data->Level) == 1 && m_data->skillmessages[0] == false)
			{
				messages.push_back(Format(L"�A�x���̓z�[�v�̂��������o�����B"));
				m_data->skillmessages[0] = true;
			}

			else if (status.getSkill(m_data->Level) == 2 && m_data->skillmessages[1] == false)
			{
				messages.push_back(Format(L"�A�x���̓\�j�b�N�W���u���o�����B"));
				m_data->skillmessages[1] = true;
			}

			else if (status.getSkill(m_data->Level) == 3 && m_data->skillmessages[2] == false)
			{
				messages.push_back(Format(L"�A�x���� �΂��������o�����B"));
				m_data->skillmessages[2] = true;
			}
			if (ModeScreen == mode::statusMessage)
			{
				statusMessage.setList(
				{
					Format(L"�ő�HP    +",status.MaxHp(m_data->Level) - status.MaxHp(m_data->Level - 1),L"    ",status.MaxHp(m_data->Level))
					,Format(L"�ő�MP    +",status.MaxMp(m_data->Level) - status.MaxMp(m_data->Level - 1),L"    ",status.MaxMp(m_data->Level))
					,Format(L"�U����    +",status.AttackPUp(m_data->Level) - status.AttackPUp(m_data->Level - 1),L"    ",status.AttackPUp(m_data->Level))
					,Format(L"�h���    +",status.DefencePUp(m_data->Level) - status.DefencePUp(m_data->Level - 1),L"    ",status.DefencePUp(m_data->Level))
					,Format(L"�f����    +",status.SpeedPUp(m_data->Level) - status.SpeedPUp(m_data->Level - 1),L"    ",status.SpeedPUp(m_data->Level))
				});
			}
			finish = true;
			if (enemies[0].type == L"�A���X")
			{
				m_data->Arisu_finish = true;
			}

			if (enemies.size() == 2 && enemies[1].type == L"�h�i���h")
			{
				m_data->Donald_finish = true;
			}
			TextManager::text->start(messages);

			return;
		}

		// �R�}���h���j���[�̎��̑���
		if (ModeScreen == mode::comandMenu)
		{
			battle_com.update();
			if (Input::KeyEnter.clicked)
			{
				SoundAsset(L"�J�[�\����").playMulti();
				if (battle_com.selected() == L"��������")
				{
					battle_com.setItem({ L"��������", L"�Ƃ���",L"",L""/*, L"�䂤����", L"�A�C�e��"*/ });
				}
				else if (battle_com.selected() == L"�ɂ���")
				{
					if (escapeMessage == L"��������")
					{
						if (escapeRandom() == 1)
						{
							TextManager::text->start({ L"���܂��ɂ����ꂽ" });
							finish = true;
						}
						else
						{
							battle(L"�ɂ���");
							ModeScreen = mode::comandMenu;
						}
					}
					else if (escapeMessage == L"�������Ȃ�")
					{
						TextManager::text->start({L"������ �����Ă̓_���� !!"});
						ModeScreen = mode::comandMenu;
					}
				}
				else if (battle_com.selected() == L"��������")
				{
					ModeScreen = mode::target;

					// ����battle���Ă΂��Ɉ�x�A�ϐ��Ɋi�[����.
					targetCommand = L"��������";

					// ������Ă΂Ȃ��Ƃǂ��Ȃ邩����Ă݂�Ƃ�����������Ȃ�.
					resetTarget();
				}

				else if (battle_com.selected() == L"�Ƃ���")
				{
					ModeScreen = mode::skiimenu;
					skill_com.setList({ L"����������",L"���[��",L"�߂�����" });
					if (status.getSkill(m_data->Level) == 1)
					{
						skill_com.setList({ L"����������",L"���[��", L"�߂�����",L"�z�[�v" });
					}

					else if (status.getSkill(m_data->Level) == 2)
					{
						skill_com.setList({ L"����������",L"���[��", L"�߂�����",L"�z�[�v" ,L"�\�j�b�N�W���u" });
					}

					else if (status.getSkill(m_data->Level) == 3)
					{
						skill_com.setList({ L"����������",L"���[��", L"�z�[�v",L"�߂�����",L"�\�j�b�N�W���u",L"�΂������" });
					}
				}
			}
			if (Input::KeySpace.clicked)
			{
				SoundAsset(L"�L�����Z��").playMulti();
				battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
			}

			return;
		}

		// �X�L�����j���[�̎��̑���
		if (ModeScreen == mode::skiimenu)
		{
			skill_com.update();

			if (Input::KeyEnter.clicked)
			{
				SoundAsset(L"�J�[�\����").playMulti();
				if (skill_com.selected() == L"����������")
				{
					if (m_data->Mp >= 3)
					{
						battle(L"����������");
						ModeScreen = mode::comandMenu;
					}
					else
					{
						TextManager::text->start({ L"MP������Ȃ� !" });
					}
				}

				if (skill_com.selected() == L"�΂������")
				{
					if (m_data->Mp >= 5)
					{
						ModeScreen = mode::comandMenu;
						battle(L"�΂������");
					}
					else
					{
						TextManager::text->start({ L"MP������Ȃ� !" });
					}
				}

				if (skill_com.selected() == L"���[��")
				{
					if (m_data->Mp >= 3)
					{
						ModeScreen = mode::comandMenu;
						battle(L"���[��");
					}
					else
					{
						TextManager::text->start({ L"MP������Ȃ� !" });
					}
				}

				if (skill_com.selected() == L"�z�[�v")
				{
					if (m_data->Mp >= 3)
					{
						ModeScreen = mode::comandMenu;
						battle(L"�z�[�v");
					}
					else
					{
						TextManager::text->start({ L"MP������Ȃ� !" });
					}
				}
				if (skill_com.selected() == L"�\�j�b�N�W���u")
				{
					if (m_data->Mp >= 4)
					{
						ModeScreen = mode::target;
						targetCommand = L"�\�j�b�N�W���u";
						resetTarget();
					}
					else
					{
						TextManager::text->start({ L"MP������Ȃ� !" });
					}
				}
				if (skill_com.selected() == L"�߂�����")
				{
					ModeScreen = mode::comandMenu;
					battle(L"�߂�����");
				}
			}
			if (Input::KeySpace.clicked)
			{
				SoundAsset(L"�L�����Z��").playMulti();
				ModeScreen = mode::comandMenu;
			}

			return;
		}

		// �^�[�Q�b�g�I�����̑���
		if (ModeScreen == mode::target)
		{
			targetUpdate();

			if (Input::KeyEnter.clicked)
			{
				// �ϐ��Ɋi�[�����̂� "��������" �ȊO���^�[�Q�b�g������悤��.
				battle(targetCommand);
				ModeScreen = mode::comandMenu;
			}

			if (Input::KeySpace.clicked)
			{
				SoundAsset(L"�L�����Z��").playMulti();
				ModeScreen = mode::comandMenu;
			}
		}
	}

	void draw() const override
	{
		Graphics::SetBackground(Color(15, 15, 15));
		Image->draw();
		//getBody()(TextureAsset(texture)).draw();
		for (uint32 i = 0; i < enemies.size(); i++)
		{
			enemies[i].draw();
		}
		battle_com.draw();

		if (ModeScreen == mode::skiimenu)
		{
			skill_com.draw();
		}

		if (ModeScreen == mode::statusMessage)
		{
			statusMessage.draw();
		}

		if (ModeScreen == mode::target)
		{
			const Triangle cursor({ 270, 220 }, { 330, 220 }, { 300, 260 });
			
			if (enemies.size() == 1)
			{
				cursor.movedBy(300 * 1, 0).draw(Palette::Black);
			}
			else
			{
				cursor.movedBy(300 * target, 0).draw(Palette::Black);
			}

			
		}

		const Rect frame(10, 20, 200, 210);

		frame.draw();
		frame.stretched(2).drawFrame(2, 0, Palette::Black);
		frame.stretched(-2).drawFrame(2, 0, Palette::Black);
		font(L"  �A�x��", L"\n\nHP    ", m_data->Hp, L"\nMP   ", m_data->Mp, L"\nLv :   ", m_data->Level).draw(20, 20, Palette::Black, 0.7);

		TextManager::text->draw();

		if (timer.ms() < 1000)
		{
			const Rect alert(250, 550, 760, 170);

			alert.draw();
			alert.stretched(2).drawFrame(2, 0, Palette::Black);
			alert.stretched(-2).drawFrame(2, 0, Palette::Black);
			font(Firstmessage).draw(310, 570, Palette::Black, 1.2);
		}
	}
	private:
		bool rock_limit_defence = false;
		bool finish = false;
		Skill_Com skill_com;
		StatusMessage statusMessage;
		String targetCommand;
		int32 target = 0;
		Stopwatch timer = Stopwatch(true);
		Font font = Font(28);
		bool turnFinish = false;

};



class Battle :public AllBattle
{
public:

	void init()
	{
		
		AttackP = status.AttackPUp(m_data->Level);
		DefenceP = status.DefencePUp(m_data->Level);
		SpeedP = status.SpeedPUp(m_data->Level);
		townM = SoundAsset(L"Town");
		SoundAsset(L"Town").setVolume(0.2);
		BattleM = SoundAsset(L"BattleM");
		SoundAsset(L"BattleM").setVolume(0.2);
		battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, L"forest"));
		const auto enemyNumber = Random(1u, 2u);
		escapeMessage = String(L"��������");
		Firstmessage = String( L"�����X�^�[�������ꂽ");
		for (uint32 i = 0; i < enemyNumber; i++)
		{
			uint32 typeNumber = Random(1, 3);
			
			//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
			if (enemyNumber == 1)
			{
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(L"���[�E���t", 15, 15, 9, 10, 13, 8, { L"���݂�",L"�߂Ƃ�",L"��������" }, { 500,250 }, { 250,250 }));
				}
				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(L"�[���V", 20, 7, 8, 12, 11, 9, { L"�˂΂˂�",L"������",L"��������" }, { 500 ,250 }, { 250,250 }));
				}
				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(L"�L�����b�g�}��", 12, 8, 6, 7, 10, 5, { L"������",L"�l�q",L"���[��" }, { 500 ,250 }, { 250,250 }));
				}
			}
			else
			{
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(L"���[�E���t", 15, 15, 9, 10, 13, 8, { L"���݂�",L"�߂Ƃ�",L"��������" }, { 200 + i * 300,250 }, { 250,250 }));
				}
				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(L"�[���V", 20, 7, 8, 12, 11, 9, { L"�˂΂˂�",L"������",L"��������" }, { 200 + i * 300,250 }, { 250,250 }));
				}
				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(L"�L�����b�g�}��", 12, 8, 6, 7, 10, 5, { L"������",L"�l�q",L"���[��" }, { 200 + i * 300,250 }, { 250,250 }));
				}
			}
			
		}

		Scene.push_back(String(L"FirstField"));
	}
};
	// �ς�����悤�Ɍ����邪�A���ۂɂ͏��Ԃ����ւ�������.
	// �����ꂽ�L�[���S�̐U�蕪������ mode ���S�ɕς��Ĉ�A�̏������c�Ɍ��₷��.
	
class Battle2 :public AllBattle
{
public:

	void init()
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, L"rockBackground"));
		AttackP = status.AttackPUp(m_data->Level);
		DefenceP = status.DefencePUp(m_data->Level);
		SpeedP = status.SpeedPUp(m_data->Level);
		townM = SoundAsset(L"Town");
		SoundAsset(L"Town").setVolume(0.2);
		BattleM = SoundAsset(L"BattleM");
		SoundAsset(L"BattleM").setVolume(0.2);
		battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
		Firstmessage = String( L"�����X�^�[�������ꂽ" );
		escapeMessage = String(L"��������");
		const auto enemyNumber = Random(1u, 2u);

		for (uint32 i = 0; i < enemyNumber; i++)
		{
			uint32 typeNumber = Random(1, 3);
			if (enemyNumber == 1)
			{
				//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(L"���[�E���t", 24, 17, 9, 13, 15, 10, { L"���݂�",L"�߂Ƃ�",L"��������" }, { 500 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(L"���^���G�b�O", 15, 5, 17, 11, 18, 8, { L"�̂�������",L"���b�N�K�[�h" }, { 500 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(L"�Ƃ��{�[��", 20, 10, 7, 17, 16, 15, { L"�Ƃ����b�V��",L"�l�q" ,L"��������" }, { 500 ,250 }, { 250,250 }));
				}

			}
			else
			{
				//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(L"���[�E���t", 24, 17, 9, 13, 15, 10, { L"���݂�",L"�߂Ƃ�",L"��������" }, { 200 + i*300 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(L"���^���G�b�O", 15, 5, 17, 11, 18, 8, { L"�̂�������",L"���b�N�K�[�h"}, { 200 + i*300 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(L"�Ƃ��{�[��", 20, 10, 7, 17, 16, 15, { L"�Ƃ����b�V��",L"�l�q" ,L"��������" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}
			}
		}

		Scene.push_back(String(L"SecondField"));
	}
};

class Battle3 :public AllBattle
{
public:

	void init()
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, L"rockBackground"));
		AttackP = status.AttackPUp(m_data->Level);
		DefenceP = status.DefencePUp(m_data->Level);
		SpeedP = status.SpeedPUp(m_data->Level);
		townM = SoundAsset(L"Town");
		SoundAsset(L"Town").setVolume(0.2);
		BattleM = SoundAsset(L"BattleM");
		SoundAsset(L"BattleM").setVolume(0.2);
		battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
		escapeMessage = String(L"��������");
		Firstmessage = String(L"�����X�^�[�������ꂽ");
		const auto enemyNumber = Random(2u, 3u);

		for (uint32 i = 0; i < enemyNumber; i++)
		{
			uint32 typeNumber = Random(1, 4);

				//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
				if (typeNumber == 1)
				{
					enemies.push_back(EnemyData(L"���[�E���t", 37, 23, 9, 20, 23, 15, { L"���݂�",L"�߂Ƃ�",L"��������" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 2)
				{
					enemies.push_back(EnemyData(L"���^���G�b�O", 18, 5, 20, 16, 29, 11, { L"�̂�������",L"���b�N�K�[�h",L"�l�q" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}

				else if (typeNumber == 3)
				{
					enemies.push_back(EnemyData(L"�Ƃ��{�[��", 30, 10, 7, 24, 25, 20, { L"�Ƃ����b�V��",L"�l�q" ,L"��������" }, { 200 + i * 300 ,250 }, { 250,250 }));
				}
				else if (typeNumber == 4)
				{
					enemies.push_back(EnemyData(L"�[���V", 40, 7, 8, 18, 21, 18, { L"�˂΂˂�",L"������",L"��������" }, { 200 + i * 300,250 }, { 250,250 }));
				}
		}

		Scene.push_back(String(L"ThirdField"));
	}
};
class Arisu :public AllBattle
{
public:

	void init()
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, L"forest"));
		Firstmessage = String( L"���@�g���̃A���X��\n�������������Ă���" );
		AttackP = status.AttackPUp(m_data->Level);
		DefenceP = status.DefencePUp(m_data->Level);
		SpeedP = status.SpeedPUp(m_data->Level);
		townM = SoundAsset(L"Town");
		SoundAsset(L"Town").setVolume(0.2);
		BattleM = SoundAsset(L"BattleM");
		SoundAsset(L"BattleM").setVolume(0.2);
		battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
		escapeMessage = String(L"�������Ȃ�");
		//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
		enemies.push_back(EnemyData(L"�A���X", 42, 15, 12, 18, 35, 20, { L"�t���A", L"���m�o�X" ,L"���[��2",L"��"}, { 500 ,250 }, { 155,235 }));
		Scene.push_back(String(L"FirstField"));
	}

private:

};

class Donald :public AllBattle
{
public:

	void init()
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, L"rockBackground"));
		Firstmessage = String(L"�s�G���̃h�i���h��\n�������������Ă���");
		escapeMessage = String(L"�������Ȃ�");
		AttackP = status.AttackPUp(m_data->Level);
		DefenceP = status.DefencePUp(m_data->Level);
		SpeedP = status.SpeedPUp(m_data->Level);
		townM = SoundAsset(L"Town");
		SoundAsset(L"Town").setVolume(0.2);
		BattleM = SoundAsset(L"BattleM");
		SoundAsset(L"BattleM").setVolume(0.2);
		battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
		//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
		enemies.push_back(EnemyData(L"�Ƃ��{�[��", 24, 10, 7, 20, 13, 15, { L"�Ƃ����b�V��",L"�l�q" }, { 200 ,250 }, { 250,250 }));
		enemies.push_back(EnemyData(L"�h�i���h", 53, 18, 13, 24, 52, 20, { L"�����̃p���`", L"�C�����[�W�����_���X" ,L"�ΐ���",L"�X�e�b�v" }, { 500 ,250 }, { 155,235 }));

		Scene.push_back(String(L"SecondField"));
	}

private:

};
class Yellow :public AllBattle
{
public:

	void init()
	{
		Image = std::make_unique<Images>(Images({ 0,0 }, { 1200,750 }, L"rockBackground"));
		Firstmessage = String( L"�C�G���[���������������Ă����B");
		escapeMessage = String(L"�������Ȃ�");
		AttackP = status.AttackPUp(m_data->Level);
		DefenceP = status.DefencePUp(m_data->Level);
		SpeedP = status.SpeedPUp(m_data->Level);
		townM = SoundAsset(L"Town");
		SoundAsset(L"Town").setVolume(0.2);
		BattleM = SoundAsset(L"BattleM");
		SoundAsset(L"BattleM").setVolume(0.2);
		battle_com.setItem({ L"��������",L"�ɂ���",L"",L"" });
		//�����@������@���O HP �X�s�[�h�@�ڂ�����́@���������́@�o���l�@��
		enemies.push_back(EnemyData(L"���[�E���t", 35, 26, 10, 21, 20, 20, { L"���݂�",L"�߂Ƃ�",L"��������" }, { 200 ,250 }, { 250,250 }));
		enemies.push_back(EnemyData(L"�C�G���[", 65, 20, 15, 28, 60, 40, { L"�t���A", L"�{���e�b�N�X",  L"�͂ǂ��V���b�g", L"���f�̓�" ,L"���[��3"}, { 500 ,250 }, { 155,235 }));
		enemies.push_back(EnemyData(L"���^���G�b�O", 21, 5, 22, 18, 20, 20, { L"�̂�������",L"���b�N�K�[�h" ,L"�{�f�B�[�v���X" }, { 800 ,250 }, { 250,250 }));

		Scene.push_back(String(L"Clear"));
	}
};



class GameOver :public SceneManager<String, Gamedata>::Scene
{
public:

	Font font = Font(60);
	Status status;

	void draw() const override
	{
		//Graphics::SetBackground(Palette::Blue);
		font(texts[0]).drawCenter(600, 300);
		font(texts[1]).drawCenter(600, 500);
	}
	void update() override
	{
		if (Input::KeySpace.clicked)
		{
			changeScene(L"In3");
			m_data->pos = { 0,400 };
			m_data->Hp = status.MaxHp(m_data->Level)/2;
			m_data->Mp = status.MaxMp(m_data->Level)/2;
		}
	}
private:
	const Array<String> texts = {
	 L"Game Over",
	 L"Please click Enter"
	};
};

class Break :public SceneManager<String, Gamedata>::Scene
{
public:

	void draw() const override
	{
		Graphics::SetBackground(Palette::Blue);
		font(text).drawCenter(600, 300);
	}

	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"In3");
			m_data->Hp = status.MaxHp(m_data->Level), m_data->Mp = status.MaxMp(m_data->Level);
		}
	}

private:
	const String text = L"Please click Enter";
	Font font = Font(60);
	Status status;
	Sound breakM, townM;
};