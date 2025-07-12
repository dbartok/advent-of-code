import textwrap
import unittest
import re


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    instructions = parse_puzzle_input(puzzle_input)
    filtered_instructions = [
        instruction for instruction in instructions if instruction[0] == "mul"
    ]
    return create_sum_from_instructions(filtered_instructions)


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    instructions = parse_puzzle_input(puzzle_input)
    return create_sum_from_instructions(instructions)


def parse_puzzle_input(puzzle_input):
    pattern = r"mul\((\d+),(\d+)\)|do\(\)|don\'t\(\)"
    instructions = []

    for match in re.finditer(pattern, puzzle_input):
        if match.group(1) is not None and match.group(2) is not None:
            instructions.append(("mul", int(match.group(1)), int(match.group(2))))
        else:
            instructions.append((match.group(0),))

    return instructions


def create_sum_from_instructions(instructions):
    total_sum = 0
    is_summing_enabled = True

    for instruction in instructions:
        if instruction[0] == "mul" and is_summing_enabled:
            total_sum += instruction[1] * instruction[2]
        elif instruction[0] == "do()":
            is_summing_enabled = True
        elif instruction[0] == "don't()":
            is_summing_enabled = False

    return total_sum


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
            xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
        """
        ).strip()
        expected_output = 161
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        puzzle_input = textwrap.dedent(
            """
            xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
        """
        ).strip()
        expected_output = 48
        self.assertEqual(expected_output, solve_part_two(puzzle_input))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
