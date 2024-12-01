import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    lines = puzzle_input.split("\n")

    first_list = []
    second_list = []

    for line in lines:
        first_location_id, second_location_id = map(int, line.split())

        first_list.append(first_location_id)
        second_list.append(second_location_id)

    first_list.sort()
    second_list.sort()

    return sum(abs(a - b) for a, b in zip(first_list, second_list))


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    def test_part_one(self):
        puzzle_input = textwrap.dedent("""
            3   4
            4   3
            2   5
            1   3
            3   9
            3   3
        """).strip()
        expected_output = 11
        self.assertEqual(solve_part_one(puzzle_input), expected_output)

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
