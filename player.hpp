#pragma once
#include <Siv3D.hpp>
#include"Object.hpp"
#include"TextManager.hpp"
#include "Asc/Anime.hpp"
#include"Gamedata.hpp"

class Player : public Object
{
public:
	

	// ���̃t���[���̓���
	Point speed = { 0, 0 };

	// ���݂̌���
	Point movement;

	// �����蔻��
	Point size;

	// �`��̎l�p�`
	Point region;

	// �摜
	std::array<String, 4> textures;
	asc::AssetAnime Right;
	asc::AssetAnime Left;
	asc::AssetAnime Up;
	asc::AssetAnime Down;

	//�i�񂾋���
	Vec2 distance = {0,0};

	SceneManager<String, Gamedata>::Scene* Scene;

	Player(Point _pos, const Point _size, const Point _region, const std::array<String, 4> _textures, Point _movement)
	{
		pos = _pos;
		size = _size;
		region = _region;
		textures = _textures;
		movement = _movement;
		Right = asc::AssetAnime(textures[0], 4, 200);
		Right.start();
		Left = asc::AssetAnime(textures[1], 4, 200);
		Left.start();
		Up = asc::AssetAnime(textures[2], 4, 200);
		Up.start();
		Down = asc::AssetAnime(textures[3], 4, 200);
		Down.start();
	}

	void getVoid() const
	{
		return;
	}
	Rect getBody() const
	{
		return Rect(pos.x - size.x / 2, pos.y - size.y, size.x, size.y);
	}

	Rect getRegion() const
	{
		return Rect(pos.x - region.x / 2, pos.y - region.y, region.x, region.y);
	}

	Rect getFace() const
	{
		if (movement.y > 0)
		{
			return Rect(pos.x - 30, pos.y - 40, 50, 80);
		}
		else if (movement.y < 0)
		{
			return Rect(pos.x - 30, pos.y - 140, 50, 95);
		}
		if (movement.x > 0)
		{
			return Rect(pos.x - 10, pos.y - 35, 80, 50);
		}
		else if (movement.x < 0)
		{
			return Rect(pos.x - 80, pos.y - 35, 80, 50);
		}
		else
		{
			return Rect(pos.x - 10, pos.y - 40, 20, 80);
		}
	}

	Point getPos()
	{
		return pos;
	}


	void update(std::shared_ptr<Player>& player)
	{
		player->getVoid();
		Right.update();
		Left.update();
		Up.update();
		Down.update();
		speed = Point(0, 0);
		if (!TextManager::text->isActive())
		{
			if (Input::KeyUp.pressed)
			{
				speed.y = -5;
				distance.y++;
			}
			if (Input::KeyDown.pressed)
			{
				speed.y = 5;
				distance.y++;
			}
			if (Input::KeyRight.pressed)
			{
				speed.x = 5;
				distance.x++;
			}
			if (Input::KeyLeft.pressed)
			{
				speed.x = -5;
				distance.x++;
			}
			if (!speed.x == 0)
			{
				movement.x = speed.x;
			}
			if (!speed.y == 0)
			{
				movement.y = speed.y;
			}
			if (!speed.x == 0 && speed.y == 0)
			{
				movement.y = 0;
			}
			pos += speed;
		}
	}

	void draw()
	{
		//��l�����~�܂��Ă���Ƃ��̕`��@�ŏ��̌����ɂ���ĕ����Ă���
		//getBody().draw();
		if (speed.isZero())
		{
			if (movement.y < 0 || movement.isZero())
			{
				getRegion()(TextureAsset(textures[2]).uv(0.25, 0, 0.25, 1)).draw();
			}
			else if (movement.y > 0)
			{
				getRegion()(TextureAsset(textures[3]).uv(0.25, 0, 0.25, 1)).draw();
			}
			else if (movement.x > 0)
			{
				getRegion()(TextureAsset(textures[0]).uv(0.25, 0, 0.25, 1)).draw();
			}
			else if (movement.x < 0)
			{
				getRegion()(TextureAsset(textures[1]).uv(0.25, 0, 0.25, 1)).draw();
			}
		}
		//��l���������Ă���Ƃ��̕`��
		else if (speed.y >= 0 && speed.x == 0)
		{
			getRegion()(Down.get()).draw();
		}
		else if (speed.y <= 0 && speed.x == 0)
		{
			getRegion()(Up.get()).draw();
		}
		else if (speed.x <= 0 && speed.y == 0)
		{
			getRegion()(Left.get()).draw();
		}
		else if (speed.x >= 0 && speed.y == 0)
		{
			getRegion()(Right.get()).draw();
		}
		else if (speed.x > 0 && speed.y > 0)
		{
			getRegion()(Down.get()).draw();
		}
		else if (speed.x < 0 && speed.y > 0)
		{
			getRegion()(Down.get()).draw();
		}

		else if (speed.x < 0 && speed.y < 0)
		{
			getRegion()(Up.get()).draw();
		}
		else if (speed.x > 0 && speed.y < 0)
		{
			getRegion()(Up.get()).draw();
		}
	}
};