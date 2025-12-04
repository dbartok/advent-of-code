import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    return sum(get_max_joltage_from_bank(line, 2) for line in puzzle_input.splitlines())


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    return sum(get_max_joltage_from_bank(line, 12) for line in puzzle_input.splitlines())


def get_max_joltage_from_bank(digits, count):
    result = []
    start = 0
    remaining = count
    n = len(digits)

    while remaining > 0:
        # Look for the max digit in the window where enough digits remain to complete selection
        end = n - remaining + 1
        max_digit = max(digits[start:end])
        # Pick the first occurrence of that max digit
        i = digits.index(max_digit, start, end)
        result.append(max_digit)
        start = i + 1
        remaining -= 1

    return int("".join(result))


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
        987654321111111
        811111111111119
        234234234234278
        818181911112111
        """
    ).strip()

    def test_part_one(self):
        expected_output = 357
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 3121910778619
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
