import textwrap
import unittest
import itertools


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    schematics = parse_input(puzzle_input)
    solver = LockAndKeySolver(schematics)
    return solver.count_valid_pairs()


def parse_input(input_data):
    blocks = input_data.strip().split("\n\n")
    return [block.splitlines() for block in blocks]


class LockAndKeySolver:
    def __init__(self, schematics):
        self._schematics = schematics

        # Assume uniform height and width
        first_schematic = self._schematics[0]
        self._height = len(first_schematic)
        self._width = len(first_schematic[0])

    def count_valid_pairs(self):
        lock_heights = [
            self._calculate_heights(schematic)
            for schematic in self._schematics
            if schematic[0][0] == "#"
        ]
        key_heights = [
            self._calculate_heights(schematic)
            for schematic in self._schematics
            if schematic[0][0] != "#"
        ]

        return sum(
            1
            for lock, key in itertools.product(lock_heights, key_heights)
            if self._fits(lock, key)
        )

    def _calculate_heights(self, schematic):
        heights = []

        for col_index in range(self._width):
            column = "".join(row[col_index] for row in schematic)
            heights.append(column.count("#"))

        return heights

    def _fits(self, lock, key):
        for l_height, k_height in zip(lock, key):
            if l_height + k_height > self._height:
                return False
        return True


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")


class TestAdventOfCode(unittest.TestCase):
    def test_part_one(self):
        puzzle_input = textwrap.dedent(
            """
            #####
            .####
            .####
            .####
            .#.#.
            .#...
            .....
            
            #####
            ##.##
            .#.##
            ...##
            ...#.
            ...#.
            .....
            
            .....
            #....
            #....
            #...#
            #.#.#
            #.###
            #####
            
            .....
            .....
            #.#..
            ###..
            ###.#
            ###.#
            #####
            
            .....
            .....
            .....
            #....
            #.#..
            #.#.#
            #####
            """
        ).strip()
        expected_output = 3
        self.assertEqual(expected_output, solve_part_one(puzzle_input))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
