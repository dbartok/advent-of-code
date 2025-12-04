import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    return sum_invalid_ids(puzzle_input, is_sequence_repeated_twice)


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    return sum_invalid_ids(puzzle_input, is_sequence_repeated_n_times)


def sum_invalid_ids(puzzle_input, invalid_id_checker_func):
    sum_of_invalid_ids = 0
    ranges = puzzle_input.split(",")

    for r in ranges:
        start_str, end_str = r.split("-")
        start = int(start_str)
        end = int(end_str)
        sum_of_invalid_ids += sum(n for n in range(start, end + 1) if invalid_id_checker_func(n))

    return sum_of_invalid_ids


def is_sequence_repeated_twice(n) -> bool:
    s = str(n)
    length = len(s)

    if length % 2 != 0:
        return False

    half = length // 2
    return s[:half] == s[half:]


def is_sequence_repeated_n_times(n):
    s = str(n)
    length = len(s)

    for sub_len in range(1, length // 2 + 1):
        if length % sub_len != 0:
            continue

        repeats = length // sub_len

        if s[:sub_len] * repeats == s:
            return True

    return False


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
        11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124
        """
    ).strip()

    def test_part_one(self):
        expected_output = 1227775554
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 4174379265
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
