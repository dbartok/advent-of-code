import textwrap
import unittest
import itertools
from collections import defaultdict

from pygame.math import Vector2 as Vector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = puzzle_input.splitlines()
    antenna_map = AntennaMap(grid)
    antenna_map.calculate_antinode_positions()
    return antenna_map.get_unique_antinode_count()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class AntennaMap:
    def __init__(self, grid):
        self._grid = grid
        self._height = len(grid)
        self._width = len(grid[0])
        self._antenna_positions = self._parse_antenna_positions()
        self._antinode_positions = set()

    def calculate_antinode_positions(self):
        for frequency, positions in self._antenna_positions.items():
            self._process_antenna_pairs(positions)

    def get_unique_antinode_count(self):
        valid_antinode_positions = {
            (x, y) for x, y in self._antinode_positions
            if 0 <= x < self._width and 0 <= y < self._height
        }
        return len(valid_antinode_positions)

    def _parse_antenna_positions(self):
        positions = defaultdict(list)
        [
            positions[cell].append(Vector(x, y))
            for y, row in enumerate(self._grid)
            for x, cell in enumerate(row)
            if cell.isalnum()
        ]
        return positions

    def _process_antenna_pairs(self, positions):
        [
            self._antinode_positions.update(
                [(antinode1_position.x, antinode1_position.y), (antinode2_position.x, antinode2_position.y)]
            )
            for antenna1_position, antenna2_position in itertools.combinations(positions, 2)
            for antinode1_position, antinode2_position in
            [self._calculate_antinode_positions(antenna1_position, antenna2_position)]
        ]

    def _calculate_antinode_positions(self, antenna1_position, antenna2_position):
        delta = antenna1_position - antenna2_position
        antinode1_position = antenna1_position + delta
        antinode2_position = antenna2_position - delta

        return Vector(antinode1_position.x, antinode1_position.y), Vector(antinode2_position.x, antinode2_position.y)


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
            ............
            ........0...
            .....0......
            .......0....
            ....0.......
            ......A.....
            ............
            ............
            ........A...
            .........A..
            ............
            ............
        """).strip()
        expected_output = 14
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
