/*
 * snake.hpp
 *
 *  Created on: 5 лип. 2023 р.
 *      Author: PC
 */

#ifndef INC_SNAKE_HPP_
#define INC_SNAKE_HPP_

#include <functional>

enum class EMoveDirection
{
	Up,
	Down,
	Left,
	Right
};

struct SPoint
{
	uint32_t x;
	uint32_t y;

	bool operator == (const SPoint& point)
	{
		return ((x == point.x) && (y == point.y));
	}

	bool operator != (const SPoint& point)
	{
		return ((x != point.x) || (y != point.y));
	}
};

const SPoint kMaxPoint = {15, 1};
const uint32_t kMaxSnakeSize = (kMaxPoint.x + 1) * (kMaxPoint.y + 1);
extern SPoint gAple;

void SnakeReset();
bool SnakeMove(EMoveDirection direction);
void SnakeGenerateAple(uint32_t rnd);
void DrawSnake(std::function<void(SPoint&)> draw);

#endif /* INC_SNAKE_HPP_ */
