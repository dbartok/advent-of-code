import textwrap
import unittest
from itertools import combinations


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    total_press_count = 0
    for line in puzzle_input.splitlines():
        diagram, buttons, _ = parse_line(line)
        total_press_count += calculate_fewest_presses(diagram, buttons)
    return total_press_count


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_line(line):
    # Example:
    # [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
    parts = line.split()

    # Diagram
    diagram_raw = parts[0]  # "[.##.]"
    diagram = [c == "#" for c in diagram_raw[1:-1]]

    # Everything after the diagram until the final {} are buttons
    button_parts = parts[1:-1]  # (3) (1,3) (2) (2,3) (0,2) (0,1)
    buttons = []
    for bp in button_parts:
        assert bp[0] == "(" and bp[-1] == ")"
        inner = bp[1:-1].strip()
        buttons.append(tuple(int(x) for x in inner.split(",")))

    joltage_raw = parts[-1]  # "{3,5,4,7}"
    joltage = tuple(int(x) for x in joltage_raw[1:-1].split(","))

    return diagram, buttons, joltage


def calculate_fewest_presses(diagram, buttons):
    """
    Treat each button as pressable only 0 or 1 time.
    Check subsets by increasing size until the target diagram is matched.
    """

    numbers = range(len(diagram))

    for subset_size in range(len(buttons) + 1):
        for buttons_pressed in combinations(buttons, subset_size):
            lights = [0] * len(numbers)

            for button in buttons_pressed:
                for light_index in button:
                    lights[light_index] ^= 1

            if lights == diagram:
                return subset_size


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
            [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
            [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
            [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
        """
        ).strip()
        self.assertEqual(7, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
