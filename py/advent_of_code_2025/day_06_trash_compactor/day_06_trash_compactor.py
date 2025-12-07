import textwrap
import unittest
import math


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    lines = puzzle_input.splitlines()
    grid = [line.split() for line in lines]

    total = 0
    for col in zip(*grid):
        op = col[-1]
        nums = [int(x) for x in col[:-1]]
        if op == "+":
            total += sum(nums)
        else:
            total += math.prod(nums)
    return total


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    def test_part_one(self):
        puzzle_input = textwrap.dedent(
            """
            123 328  51 64 
             45 64  387 23 
              6 98  215 314
            *   +   *   +  
            """
        ).strip("\n")

        expected = 33210 + 490 + 4243455 + 401
        self.assertEqual(expected, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
