import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    reports = parse_puzzle_input(puzzle_input)
    return len([report for report in reports if is_safe(report)])


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    reports = parse_puzzle_input(puzzle_input)
    return len([report for report in reports if is_safe_with_problem_dampener(report)])


def parse_puzzle_input(puzzle_input):
    return [list(map(int, line.split())) for line in puzzle_input.split('\n')]


def is_safe(report):
    differences = [report[i + 1] - report[i] for i in range(len(report) - 1)]
    return all(1 <= d <= 3 for d in differences) or all(-3 <= d <= -1 for d in differences)


def is_safe_with_problem_dampener(report):
    reports_with_one_element_removed = [report[:i] + report[i + 1:] for i in range(len(report))]
    return any(is_safe(report) for report in reports_with_one_element_removed)


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    PUZZLE_INPUT = textwrap.dedent("""
        7 6 4 2 1
        1 2 7 8 9
        9 7 6 2 1
        1 3 2 4 5
        8 6 4 4 1
        1 3 6 7 9
    """).strip()

    def test_part_one(self):
        expected_output = 2
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 4
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
