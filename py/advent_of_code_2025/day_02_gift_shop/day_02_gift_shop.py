import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    sum_of_invalid_ids = 0
    ranges = puzzle_input.split(",")

    for r in ranges:
        start_str, end_str = r.split("-")
        start = int(start_str)
        end = int(end_str)
        sum_of_invalid_ids += sum(n for n in range(start, end + 1) if is_invalid_id(n))

    return sum_of_invalid_ids


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def is_invalid_id(n) -> bool:
    s = str(n)
    length = len(s)

    if length % 2 != 0:
        return False

    half = length // 2
    return s[:half] == s[half:]


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
            11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124
            """
        ).strip()
        expected_output = 1227775554
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
