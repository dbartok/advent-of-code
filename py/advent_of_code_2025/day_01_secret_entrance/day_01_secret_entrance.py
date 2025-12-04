import textwrap
import unittest

STARTING_POSITION = 50


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    position = STARTING_POSITION
    zero_count = 0

    for line in puzzle_input.splitlines():
        direction = line[0]
        distance = int(line[1:])
        if direction == "L":
            position = (position - distance) % 100
        else:
            position = (position + distance) % 100
        if position == 0:
            zero_count += 1

    return zero_count


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    position = STARTING_POSITION
    zero_count = 0

    for line in puzzle_input.splitlines():
        direction = line[0]
        distance = int(line[1:])
        step = -1 if direction == "L" else 1

        for _ in range(distance):
            position = (position + step) % 100
            if position == 0:
                zero_count += 1

    return zero_count


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
        L68
        L30
        R48
        L5
        R60
        L55
        L1
        L99
        R14
        L82
        """
    ).strip()

    def test_part_one(self):
        expected_output = 3
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 6
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
