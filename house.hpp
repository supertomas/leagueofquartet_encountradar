#pragma once
#include <Siv3D.hpp>
#include"Player.hpp"
#include"Object.hpp"
#include"Gamedata.hpp"
class House : public Object
{
public:
	SceneManager<String, Gamedata>::Scene* Scene;
	House()
	{
	
	}
	House(Point _pos, Point _region, Point _shadow, Point _door, Point _size, int32 _adjust, String _texture, SceneManager<String, Gamedata>::Scene* _Scene)
	{
		pos = _pos;
		size = _size;
		texture = _texture;
		region = _region;
		shadow = _shadow;
		door = _door;
		Scene = _Scene;
		adjust = _adjust;
	}

	Rect getRegion() const
	{
		return Rect(pos.x + shadow.x - region.x / 2, pos.y + shadow.y - region.y, region.x, region.y);
	}

	Rect getBody() const
	{
		return Rect(pos.x - size.x + adjust, pos.y - size.y, size.x , size.y);
	}

	Rect getDoor()
	{
		return Rect(pos.x - door.x , pos.y , door.y, 10);
		//door.y�̓h�A�̕�
	}

	bool intersect_Wall(std::shared_ptr<Player>& player)
	{
		return player->getBody().intersects(getBody());
	}

	bool intersectWithDoor(std::shared_ptr<Player>& player)
	{
		return player->getBody().intersects(getDoor());
	}

	void draw()
	{
		
		getRegion()(TextureAsset(texture)).draw();
		/*getBody().draw();
		getDoor().draw(Palette::Red);*/
	}
private:
	Point region, size;
	Point shadow;
	String texture;
	Point door;
	int32 adjust;
};

class House01 : public House
{
public :
	House01(Point _pos, Point _region, Point _shadow, Point _door, Point _size, int32 _adjust, String _texture, SceneManager<String, Gamedata>::Scene* _Scene)
		: House(_pos, _region, _shadow, _door, _size, _adjust, _texture, _Scene)
	{}
	void update(std::shared_ptr<Player>& player) override
	{
		if (intersect_Wall(player))
		{
			player->pos -= player->speed;
		}
		if (intersectWithDoor(player) && player->movement.y < 0)
		{
			Scene->m_data->pos = { -290,720 };

			Scene->changeScene(L"In");
			Scene->m_data->movement = player->movement;
		}
	}

};

class House02 : public House
{
public :
	House02(Point _pos, Point _region, Point _shadow, Point _door, Point _size, int32 _adjust, String _texture, SceneManager<String, Gamedata>::Scene* _Scene)
		: House(_pos, _region, _shadow, _door, _size, _adjust, _texture, _Scene)
	{}
	void update(std::shared_ptr<Player>& player) override
	{
		if (intersect_Wall(player))
		{
			player->pos -= player->speed;
		}
		if (intersectWithDoor(player) && player->movement.y < 0)
		{
			Scene->m_data->pos = { -290,720 };
			Scene->changeScene(L"In2");
			Scene->m_data->movement = player->movement;
		}
	}

};

class House03 : public House
{
public:
	House03(Point _pos, Point _region, Point _shadow, Point _door, Point _size, int32 _adjust, String _texture, SceneManager<String, Gamedata>::Scene* _Scene)
		: House(_pos, _region, _shadow, _door, _size, _adjust, _texture, _Scene)
	{}
	void update(std::shared_ptr<Player>& player) override
	{
		if (intersect_Wall(player))
		{
			player->pos -= player->speed;
		}
		if (intersectWithDoor(player) && player->movement.y < 0)
		{
			Scene->m_data->pos = { -260, 620};
			Scene->changeScene(L"In3");
			Scene->m_data->movement = player->movement;
		}
	}

};