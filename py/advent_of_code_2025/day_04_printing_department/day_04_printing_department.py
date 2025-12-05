import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = [list(row) for row in puzzle_input.splitlines()]
    optimizer = ForkliftOptimizer(grid)
    return optimizer.get_accessible_roll_count()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class ForkliftOptimizer:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])

    def get_accessible_roll_count(self):
        return sum(
            1
            for y in range(self._height)
            for x in range(self._width)
            if self._grid[y][x] == '@' and self._get_adjacent_roll_count(x, y) < 4
        )

    def _get_adjacent_roll_count(self, x, y):
        neighbors = [
            (x + dx, y + dy)
            for dy in (-1, 0, 1)
            for dx in (-1, 0, 1)
            if not (dx == 0 and dy == 0)
        ]
        return sum(
            1
            for nx, ny in neighbors
            if self._is_in_bounds(nx, ny) and self._grid[ny][nx] == '@'
        )

    def _is_in_bounds(self, x, y):
        return 0 <= x < self._width and 0 <= y < self._height


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
            ..@@.@@@@.
            @@@.@.@.@@
            @@@@@.@.@@
            @.@@@@..@.
            @@.@@@@.@@
            .@@@@@@@.@
            .@.@.@.@@@
            @.@@@.@@@@
            .@@@@@@@@.
            @.@.@@@.@.
        """
        ).strip()
        expected_output = 13
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
