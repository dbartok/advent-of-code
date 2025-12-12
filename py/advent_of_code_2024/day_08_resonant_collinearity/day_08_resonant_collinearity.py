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
    grid = puzzle_input.splitlines()
    antenna_map = ResonantAntennaMap(grid)
    antenna_map.calculate_antinode_positions()
    return antenna_map.get_unique_antinode_count()


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
        return len(self._antinode_positions)

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
                [
                    (antinode_position.x, antinode_position.y)
                    for antinode_position in self._calculate_antinode_positions(
                    antenna1_position, antenna2_position
                )
                ]
            )
            for antenna1_position, antenna2_position in itertools.combinations(
            positions, 2
        )
        ]

    def _calculate_antinode_positions(self, antenna1_position, antenna2_position):
        delta = antenna1_position - antenna2_position
        antinode_positions = [antenna1_position + delta, antenna2_position - delta]
        return [
            antinode
            for antinode in antinode_positions
            if self._is_within_bounds(antinode)
        ]

    def _is_within_bounds(self, position):
        return 0 <= position.x < self._width and 0 <= position.y < self._height


class ResonantAntennaMap(AntennaMap):
    def _calculate_antinode_positions(self, antenna1_position, antenna2_position):
        delta = antenna1_position - antenna2_position
        antinode_positions = []

        antinode_positions.extend(
            self._get_antinode_positions_in_direction(antenna1_position, delta, 1)
        )
        antinode_positions.extend(
            self._get_antinode_positions_in_direction(antenna2_position, delta, -1)
        )

        return antinode_positions

    def _get_antinode_positions_in_direction(self, start_position, delta, direction):
        antinode_positions = []
        delta_multiplier = 0

        while self._is_within_bounds(
                position := start_position + delta * direction * delta_multiplier
        ):
            antinode_positions.append(position)
            delta_multiplier += 1

        return antinode_positions


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
        """
    ).strip()

    def test_part_one(self):
        expected_output = 14
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 34
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
