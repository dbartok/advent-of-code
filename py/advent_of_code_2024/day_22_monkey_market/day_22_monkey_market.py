import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    input_secret_numbers = parse_input(puzzle_input)

    total_sum = 0
    for secret_number in input_secret_numbers:
        buyer = MonkeyBuyer(secret_number)
        buyer.generate_secret_numbers(2000)
        total_sum += buyer.get_secret_number()
    return total_sum


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(input_string):
    # Split input into lines and convert each line to an integer
    return [int(line.strip()) for line in input_string.strip().splitlines()]


class MonkeyBuyer:
    def __init__(self, initial_secret_number):
        self._secret_number = initial_secret_number

    def generate_secret_numbers(self, n):
        for _ in range(n):
            self._apply_transformation()

    def get_secret_number(self):
        return self._secret_number

    def _apply_transformation(self):
        # Step 1: Multiply by 64, XOR, then prune
        self._secret_number = (self._secret_number * 64) ^ self._secret_number
        self._secret_number %= 16777216

        # Step 2: Divide by 32, XOR, then prune
        self._secret_number = (self._secret_number // 32) ^ self._secret_number
        self._secret_number %= 16777216

        # Step 3: Multiply by 2048, XOR, then prune
        self._secret_number = (self._secret_number * 2048) ^ self._secret_number
        self._secret_number %= 16777216


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
            1
            10
            100
            2024
        """
        ).strip()
        expected_output = 37327623
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
