import textwrap
import unittest
from collections import defaultdict


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = puzzle_input.split("\n")
    simulator = BeamSimulator(grid)
    simulator.simulate()
    return simulator.get_split_count()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    grid = puzzle_input.split("\n")
    simulator = BeamSimulator(grid)
    simulator.simulate()
    return simulator.get_timeline_count()


class BeamSimulator:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._start_col = self._grid[0].index("S")

        self._beam_col_to_timeline_count = {}
        self._split_count = 0

    def simulate(self):
        self._beam_col_to_timeline_count = {self._start_col: 1}

        for y in range(1, self._height):
            row = self._grid[y]
            self._step_row(row)

    def get_split_count(self):
        return self._split_count

    def get_timeline_count(self):
        return sum(self._beam_col_to_timeline_count.values())

    def _step_row(self, row):
        new_beam_col_to_timeline_count = defaultdict(int)

        for x, count in self._beam_col_to_timeline_count.items():
            if row[x] == "^":
                self._split_count += 1
                new_beam_col_to_timeline_count[x - 1] += count
                new_beam_col_to_timeline_count[x + 1] += count
            else:
                new_beam_col_to_timeline_count[x] += count

        self._beam_col_to_timeline_count = new_beam_col_to_timeline_count


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
        .......S.......
        ...............
        .......^.......
        ...............
        ......^.^......
        ...............
        .....^.^.^.....
        ...............
        ....^.^...^....
        ...............
        ...^.^...^.^...
        ...............
        ..^...^.....^..
        ...............
        .^.^.^.^.^...^.
        ...............
        """
    ).strip()

    def test_part_one(self):
        expected_output = 21
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 40
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
