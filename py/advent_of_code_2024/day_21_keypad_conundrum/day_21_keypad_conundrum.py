import textwrap
import unittest
from functools import cache
from pygame.math import Vector2 as Vector

NUM_ROBOTS_PART_ONE = 2
NUM_ROBOTS_PART_TWO = 25


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    return solve_for_number_of_robots(puzzle_input, NUM_ROBOTS_PART_ONE)


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    return solve_for_number_of_robots(puzzle_input, NUM_ROBOTS_PART_TWO)


def solve_for_number_of_robots(puzzle_input, num_robots):
    codes = puzzle_input.splitlines()
    return sum(
        KeypadSolver(code, num_robots).calculate_min_length() * int(code[:3])
        for code in codes
    )


class KeypadSolver:
    def __init__(self, code, num_robots):
        self.code = code
        self.num_robots = num_robots

        """
        +---+---+---+
        | 7 | 8 | 9 |
        +---+---+---+
        | 4 | 5 | 6 |
        +---+---+---+
        | 1 | 2 | 3 |
        +---+---+---+
            | 0 | A |
            +---+---+
        """
        self.NUMERIC_PAD_POSITIONS = {
            "7": Vector(0, 0),
            "8": Vector(0, 1),
            "9": Vector(0, 2),
            "4": Vector(1, 0),
            "5": Vector(1, 1),
            "6": Vector(1, 2),
            "1": Vector(2, 0),
            "2": Vector(2, 1),
            "3": Vector(2, 2),
            "0": Vector(3, 1),
            "A": Vector(3, 2),
        }

        """
            +---+---+
            | ^ | A |
        +---+---+---+
        | < | v | > |
        +---+---+---+
        """
        self.DIRECTIONAL_PAD_POSITIONS = {
            "^": Vector(0, 1),
            "A": Vector(0, 2),
            "<": Vector(1, 0),
            "v": Vector(1, 1),
            ">": Vector(1, 2),
        }

        self.DIRECTIONS = {
            "^": Vector(-1, 0),
            "v": Vector(1, 0),
            "<": Vector(0, -1),
            ">": Vector(0, 1),
        }

    def calculate_min_length(self):
        return self._calculate_min_length_recursive(self.code, 0)

    @cache
    def _calculate_min_length_recursive(self, desired_output, current_robot):
        char_to_position = self._get_char_to_position(current_robot)
        current_position = char_to_position["A"]
        total_minimum_length = 0

        for char in desired_output:
            next_position = char_to_position[char]
            valid_paths = self._get_valid_paths(
                current_position, next_position, char_to_position
            )

            # We are past the number of robots (current_robot starts from zero), so this is the "human" stage, who just types out the sequence
            if current_robot == self.num_robots:
                total_minimum_length += len(valid_paths[0])
            # This is a "robot" stage, let's find the best possible length
            else:
                total_minimum_length += min(
                    self._calculate_min_length_recursive(move, current_robot + 1)
                    for move in valid_paths
                )
            current_position = next_position

        return total_minimum_length

    def _get_char_to_position(self, current_depth):
        # The first pad (depth 0) is a numpad, rest are directional pads
        if current_depth == 0:
            return self.NUMERIC_PAD_POSITIONS

        return self.DIRECTIONAL_PAD_POSITIONS

    def _get_valid_paths(self, start, end, char_to_position):
        delta = end - start
        delta_x, delta_y = int(delta.x), int(delta.y)

        horizontal_component = "^" * abs(delta_x) if delta_x < 0 else "v" * delta_x
        vertical_component = "<" * abs(delta_y) if delta_y < 0 else ">" * delta_y

        paths = []

        # Check moving horizontally and then vertically
        if start + Vector(delta_x, 0) in char_to_position.values():
            paths.append(horizontal_component + vertical_component)

        # Check moving vertically and then horizontally
        if start + Vector(0, delta_y) in char_to_position.values():
            paths.append(vertical_component + horizontal_component)

        # Return the paths with the 'A' appended
        return ["".join(p) + "A" for p in paths]


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
        029A
        980A
        179A
        456A
        379A
    """
    ).strip()

    def test_part_one(self):
        expected_output = 126384
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 154115708116294
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
