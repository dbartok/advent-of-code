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
    # Build raw grid of characters
    grid = puzzle_input.splitlines()
    width = len(grid[0])
    height = len(grid)

    # Extract blocks of contiguous non-separator columns
    blocks_column_indices = []
    start = 0
    for x in range(width):
        if all(grid[y][x] == " " for y in range(height)):
            blocks_column_indices.append(range(start, x))
            start = x + 1

    # Add the last block
    blocks_column_indices.append(range(start, width))

    total = 0
    for block_column_indices in blocks_column_indices:
        # Operator is bottom row, first column
        op = grid[height - 1][block_column_indices[0]]

        nums = []
        for y in block_column_indices:
            digits = [grid[x][y] for x in range(height - 1)]
            digits = "".join(d for d in digits if d != " ")
            nums.append(int(digits))

        if op == "+":
            total += sum(nums)
        else:
            total += math.prod(nums)

    return total


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    PUZZLE_INPUT = textwrap.dedent(
        """
        123 328  51 64 
         45 64  387 23 
          6 98  215 314
        *   +   *   +  
        """
    ).strip("\n")

    def test_part_one(self):
        expected = 33210 + 490 + 4243455 + 401
        self.assertEqual(expected, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected = 1058 + 3253600 + 625 + 8544
        self.assertEqual(expected, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
