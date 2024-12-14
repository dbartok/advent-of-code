import textwrap
import unittest
import re
import operator
from pygame.math import Vector2 as Vector
from collections import namedtuple
from functools import reduce


def solve_part_one(puzzle_input, width=101, height=103):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :param width: Width of the area that the robots are in
    :param height: Height of the area that the robots are in
    :return: Solution for part one
    """
    robots = parse_input(puzzle_input)
    simulation = RobotSimulation(robots, width, height)
    simulation.simulate(100)
    return simulation.calculate_safety_factor()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


Robot = namedtuple('Robot', ['pos', 'vel'])


def parse_input(puzzle_input):
    robots = []

    # Regex pattern to match "p=x,y v=x,y"
    pattern = r"p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)"
    lines = puzzle_input.splitlines()
    for line in lines:
        x, y, vx, vy = map(int, re.match(pattern, line).groups())
        robot = Robot(pos=Vector(x, y), vel=Vector(vx, vy))
        robots.append(robot)

    return robots


class RobotSimulation:
    def __init__(self, robots, width, height):
        self._robots = robots
        self._width = width
        self._height = height

    def simulate(self, num_steps):
        for _ in range(num_steps):
            # Create new list of robots with updated positions
            self._robots = [
                Robot(
                    pos=robot.pos + robot.vel,
                    vel=robot.vel
                )
                for robot in self._robots
            ]

            # Wrap around the edges of the space
            self._robots = [
                Robot(
                    pos=Vector(robot.pos.x % self._width, robot.pos.y % self._height),
                    vel=robot.vel
                )
                for robot in self._robots
            ]

    def calculate_safety_factor(self):
        quadrants = self._count_robots_in_quadrants()
        return reduce(operator.mul, quadrants, 1)

    def _count_robots_in_quadrants(self):
        quadrants = [0, 0, 0, 0]  # [top-left, top-right, bottom-left, bottom-right]
        mid_x = self._width // 2
        mid_y = self._height // 2

        for robot in self._robots:
            x, y = robot.pos
            # Skip robots on the middle row or middle column
            if x == mid_x or y == mid_y:
                continue
            # Count robots in the quadrants
            if x < mid_x and y < mid_y:
                quadrants[0] += 1
            elif x >= mid_x and y < mid_y:
                quadrants[1] += 1
            elif x < mid_x and y >= mid_y:
                quadrants[2] += 1
            elif x >= mid_x and y >= mid_y:
                quadrants[3] += 1

        return quadrants


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    def test_part_one(self):
        puzzle_input = textwrap.dedent("""
            p=0,4 v=3,-3
            p=6,3 v=-1,-3
            p=10,3 v=-1,2
            p=2,0 v=2,-1
            p=0,0 v=1,3
            p=3,0 v=-2,-2
            p=7,6 v=-1,-3
            p=3,0 v=-1,-2
            p=9,3 v=2,3
            p=7,3 v=-1,2
            p=2,4 v=2,-3
            p=9,5 v=-3,-3
        """).strip()
        expected_output = 12
        self.assertEqual(expected_output, solve_part_one(puzzle_input, 11, 7))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
