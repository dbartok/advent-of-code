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
    available_patterns, desired_designs = parse_input(puzzle_input)
    designer = TowelDesigner(available_patterns, desired_designs)
    return designer.count_total_ways_to_form_all_designs()


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
        return sum(1 for design in self._desired_designs if self._count_ways_to_form_design(design) > 0)

    def count_total_ways_to_form_all_designs(self):
        return sum(self._count_ways_to_form_design(design) for design in self._desired_designs)

    def _count_ways_to_form_design(self, design):
        # Dynamic Programming approach to count how many ways the design can be formed
        design_length = len(design)
        ways = [0] * (design_length + 1)  # ways[i] is the number of ways to form design[:i]
        ways[0] = 1  # Base case: empty design can always be formed in one way

        # Iterate over each position in the design
        for end_index in range(1, design_length + 1):
            for start_index in range(end_index):
                if ways[start_index] > 0 and design[start_index:end_index] in self._available_patterns:
                    ways[end_index] += ways[start_index]

        return ways[design_length]  # The number of ways to form the entire design


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    PUZZLE_INPUT = textwrap.dedent("""
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

    def test_part_one(self):
        expected_output = 6
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 16
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
