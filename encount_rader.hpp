#pragma once
# include <Siv3D.hpp> 

constexpr int32 CellSize = 64;

constexpr Size CellSizeXY{ 64, 64 };
// bool, char , int, float, double -> �l�n��
// std::string, String, Array, std::vector, Grid, Texture, Image, Rect, Circle
// �Q�ƁA�ύX���Ȃ��Ȃ� const �Q��
bool vector_finder(const Array<int>& vec, int number) {
	return (std::find(vec.begin(), vec.end(), number) != vec.end());
}


class DirectionCell
{
public:

	DirectionCell(const Point& _pos, int _cell_index) :
		m_pos(_pos),
		m_cell_index(_cell_index)
	{

	}

	ColorF getColor() const
	{
		if (m_cell_index < 2)
		{
			return Palette::White;
		}
		else if (m_cell_index == 2)
		{
			return Palette::Red;
		}
		else // cell_index == 3
		{
			return Palette::Blue;
		}
	}

	void draw() const
	{
		Rect(m_pos, CellSizeXY).draw(getColor());
	}

	int getCellIndex() const
	{
		return m_cell_index;
	}

private:

	Point m_pos;

	int m_cell_index;
};


class CellManager
{
public:

	CellManager()
	{
		generate();
	}

	void generate()
	{
		cell.clear();

		for (;;)
		{
			save = Random(0, 3);
			if (!vector_finder(rands, save))
			{
				rands.push_back(save);
			}
			if (rands.size() == 4)
			{
				cell.push_back(DirectionCell({ 1000,30 },rands[0]));
				cell.push_back(DirectionCell({ 1064,94 },rands[1]));
				cell.push_back(DirectionCell({ 1000,158 },rands[2]));
				cell.push_back(DirectionCell({ 936,94 },rands[3]));
				rands.clear();
				break;
			}
		}
	}

	void draw() const
	{
		for (auto& i : cell)
		{
			i.draw();
		}
	}

	String check(int playerCellID)
	{
		String color;
		if (playerCellID != 4)
		{
			for (size_t i = 0; i < 4; i++)
			{
				if (playerCellID == i)
				{
					if ((cell[i].getCellIndex() == 0 || cell[i].getCellIndex() == 1))
					{
						color = L"White";
						return color;
					}
					else if (cell[i].getCellIndex() == 2)
					{
						color = L"Red";
						return color;
					}
					else if (cell[i].getCellIndex() == 3)
					{
						color = L"Blue";
						return color;
					}
					else
					{
						color = L"";
						return color;
					}
				}
			}
		}
		else
		{
			color = L"";
			return color;
		}
	}

private:
	std::vector<int> rands;
	int save;
	Array<DirectionCell> cell;
};

class encount_radar
{
public:
	bool Battle_Scene = false;
	void update(CellManager& cellManager, Vec2& changeBattle, Vec2& player_distance)
	{
		if(Input::KeyUp.pressed)
		{
			m_cellID = 0;
			if (cellManager.check(m_cellID) == L"Red")
			{
				if (!reset)
				{
					save_distance_red = player_distance;
					player_distance = { 0,0 };
					reset = true;
				}
			}
			else if (cellManager.check(m_cellID) == L"White")
			{
				is_input_white = true;
				if (!reset && !save_distance_white.isZero())
				{
					player_distance = save_distance_white;
					reset = true;
				}
			}
			
		}
		else if (Input::KeyRight.pressed)
		{
			m_cellID = 1;
			if (cellManager.check(m_cellID) == L"Red")
			{
				if (!reset)
				{
					save_distance_red = player_distance;
					player_distance = { 0,0 };
					reset = true;
				}
			}
			else if (cellManager.check(m_cellID) == L"White")
			{
				is_input_white = true;
				if (!reset && !save_distance_white.isZero())
				{
					player_distance = save_distance_white;
					reset = true;
				}
			}
		}
		else if (Input::KeyDown.pressed)
		{
			m_cellID = 2;
			if (cellManager.check(m_cellID) == L"Red")
			{
				if (!reset)
				{
					save_distance_red = player_distance;
					player_distance = { 0,0 };
					reset = true;
				}
			}
			else if (cellManager.check(m_cellID) == L"White")
			{
				is_input_white = true;
				if (!reset && !save_distance_white.isZero())
				{
					player_distance = save_distance_white;
					reset = true;
				}
			}
		}
		else if (Input::KeyLeft.pressed)
		{
			m_cellID = 3;
			if (cellManager.check(m_cellID) == L"Red")
			{
				if (!reset)
				{
					save_distance_red = player_distance;
					player_distance = { 0,0 };
					reset = true;
				}
			}
			else if (cellManager.check(m_cellID) == L"White")
			{
				is_input_white = true;
				if (!reset && !save_distance_white.isZero())
				{
					player_distance = save_distance_white;
					reset = true;
				}
			}
		}
		else
		{
			m_cellID = 4;
			if (!save_distance_red.isZero())
			{
				player_distance = save_distance_red;
			}
			if (is_input_white)
			{
				save_distance_white = player_distance;
				is_input_white = false;
				reset = false;
			}
		}

		Change_timer.start();

		if (Change_timer.s() > 5)
		{
			cellManager.generate();

			Change_timer.reset();
		}
		if (cellManager.check(m_cellID) == L"White")
		{
			if (player_distance.x > changeBattle.x || player_distance.y > changeBattle.y)
			{
				Battle_Scene = true;
				reset = false;
			}
		}
		else if (cellManager.check(m_cellID) == L"Red")
		{
			if (player_distance.x > 30 || player_distance.y > 30)
			{
				Battle_Scene = true;
				reset = false;
			}
		}
		else if (cellManager.check(m_cellID) == L"Blue")
		{
			if (player_distance.x > 2000 || player_distance.y > 2000)
			{
				Battle_Scene = true;
				reset = false;
			}
		}
	}

	void draw() const
	{
		const Point center{ 1032, 126 };

		const Point Offset[5] =
		{
			{ 0, -CellSize },
			{ CellSize, 0 },
			{ 0, CellSize },
			{ -CellSize, 0 },
			{ 0, 0 },
		};

		const Point pos = center + Offset[m_cellID];

		Circle(pos, 20).draw(Palette::Black);
	}

	int32 getCellID() const
	{
		return m_cellID;
	}

private:


	// �� 0, �� 1, �� 2, �� 3, ���S 4
	int32 m_cellID = 0;

	Vec2 save_distance_red = { 0,0 };
	Vec2 save_distance_white = { 0,0 };
	bool reset = false;
	bool is_input_white = false;
	Stopwatch Change_timer;
};


