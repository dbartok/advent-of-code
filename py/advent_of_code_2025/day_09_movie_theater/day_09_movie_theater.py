import textwrap
import unittest
from itertools import combinations


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    points = [tuple(map(int, line.split(","))) for line in puzzle_input.splitlines()]
    return calculate_max_area(points)


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def calculate_max_area(points):
    max_area = 0
    for (x1, y1), (x2, y2) in combinations(points, 2):
        area = (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1)
        if area > max_area:
            max_area = area
    return max_area


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
            7,1
            11,1
            11,7
            9,7
            9,5
            2,5
            2,3
            7,3
        """
        ).strip()
        expected_output = 50
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
