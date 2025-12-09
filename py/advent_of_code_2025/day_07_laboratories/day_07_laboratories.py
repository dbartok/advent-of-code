import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = puzzle_input.split("\n")
    return BeamSimulator(grid).count_splits()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class BeamSimulator:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._start_col = self._grid[0].index("S")

    def count_splits(self):
        beam_cols = {self._start_col}
        total_split_count = 0

        for y in range(1, self._height):
            beam_cols, s = self._step_row(beam_cols, self._grid[y])
            total_split_count += s

        return total_split_count

    def _step_row(self, beams, row):
        new_beam_cols = set()
        split_count = 0

        for x in beams:
            if row[x] == "^":
                split_count += 1
                new_beam_cols.add(x - 1)
                new_beam_cols.add(x + 1)
            else:
                new_beam_cols.add(x)

        return new_beam_cols, split_count


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
        ).strip("\n")
        expected_output = 21
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
