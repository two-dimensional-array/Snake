/*
 * snake.cpp
 *
 *  Created on: 5 лип. 2023 р.
 *      Author: PC
 */
#include <stdint.h>
#include <list>
#include "snake.hpp"

static std::list<SPoint> snake = {{0, 0}};
SPoint gAple;

static SPoint Move(EMoveDirection direction, SPoint point)
{
	switch(direction)
	{
		case EMoveDirection::Up:
		{
			point.y = (point.y == 0) ? kMaxPoint.y : point.y - 1;
			break;
		}
		case EMoveDirection::Down:
		{
			point.y = (point.y < kMaxPoint.y) ? point.y + 1 : 0;
			break;
		}
		case EMoveDirection::Left:
		{
			point.x = (point.x == 0) ? kMaxPoint.x : point.x - 1;
			break;
		}
		case EMoveDirection::Right:
		{
			point.x = (point.x < kMaxPoint.x) ? point.x + 1 : 0;
			break;
		}
	}

	return point;
}

void SnakeReset()
{
	snake = {{0, 0}};
}

bool SnakeMove(EMoveDirection direction)
{
	SPoint head(Move(direction, snake.back()));

	for (SPoint point : snake)
	{
		if (point == head)
		{
			SnakeReset();
			return true;
		}
	}

	snake.push_back(head);

	if (head != gAple)
	{
		snake.pop_front();
		return false;
	}
	else if (snake.size() == kMaxSnakeSize)
	{
		SnakeReset();
	}

	return true;
}

void SnakeGenerateAple(uint32_t rnd)
{
	uint32_t idx = rnd % (32 - snake.size());

	gAple.x = 0;
	gAple.y = 0;

	uint8_t i = 0;

	while (i < idx)
	{
		if (gAple.x < kMaxPoint.x)
		{
			++gAple.x;
		}
		else
		{
			gAple.x = 0;
			++gAple.y;
		}

		++i;

		for (SPoint point : snake)
		{
			if (point == gAple)
			{
				--i;
				break;
			}
		}
	}
}

void DrawSnake(std::function<void(SPoint&)> draw)
{
	for (SPoint point : snake)
	{
		draw(point);
	}
}
