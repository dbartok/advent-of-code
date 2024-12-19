import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    available_patterns, desired_designs = parse_input(puzzle_input)
    designer = TowelDesigner(available_patterns, desired_designs)
    return designer.count_possible_designs()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(input_data):
    parts = input_data.split('\n\n')
    available_patterns = parts[0].split(', ')
    desired_designs = parts[1].splitlines()
    return available_patterns, desired_designs


class TowelDesigner:
    def __init__(self, available_patterns, desired_designs):
        self._available_patterns = set(available_patterns)  # Use set for fast lookup
        self._desired_designs = desired_designs

    def count_possible_designs(self):
        return sum(1 for design in self._desired_designs if self._can_form_design(design))

    def _can_form_design(self, design):
        # Dynamic Programming approach to check if the design can be formed
        design_length = len(design)
        can_form_up_to = [False] * (design_length + 1)  # can_form_up_to[i] is True if design[:i] can be formed
        can_form_up_to[0] = True  # Base case: empty design can always be formed

        # Iterate over each position in the design
        for end_index in range(1, design_length + 1):
            for start_index in range(end_index):
                if can_form_up_to[start_index] and design[start_index:end_index] in self._available_patterns:
                    can_form_up_to[end_index] = True
                    break

        return can_form_up_to[design_length]  # Whether the entire design can be formed


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
            r, wr, b, g, bwu, rb, gb, br

            brwrr
            bggr
            gbbr
            rrbgbr
            ubwu
            bwurrg
            brgr
            bbrgwb
        """).strip()
        expected_output = 6
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
