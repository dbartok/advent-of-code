import textwrap
import unittest
import itertools


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    equations = parse_input(puzzle_input)
    solver = CalibrationEquationSolver(equations)
    return solver.find_valid_equations()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(puzzle_input):
    equations = []
    for line in puzzle_input.strip().splitlines():
        test_value_str, numbers_str = line.split(": ")
        test_value = int(test_value_str)
        numbers = list(map(int, numbers_str.split(" ")))
        equations.append((test_value, numbers))
    return equations


class CalibrationEquationSolver:
    def __init__(self, equations):
        self.equations = equations  # List of tuples, each containing (test_value, numbers)

    def find_valid_equations(self):
        sum_of_valid_test_values = 0

        for test_value, numbers in self.equations:
            num_operators = len(numbers) - 1
            operator_combinations = itertools.product(['+', '*'], repeat=num_operators)

            for operator_combination in operator_combinations:
                if self._evaluate_expression(numbers, operator_combination) == test_value:
                    sum_of_valid_test_values += test_value
                    break  # Stop after finding a valid solution for this equation

        return sum_of_valid_test_values

    @staticmethod
    def _evaluate_expression(numbers, operators):
        result = numbers[0]
        for i in range(1, len(numbers)):
            if operators[i - 1] == '+':
                result += numbers[i]
            elif operators[i - 1] == '*':
                result *= numbers[i]
        return result


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
            190: 10 19
            3267: 81 40 27
            83: 17 5
            156: 15 6
            7290: 6 8 6 15
            161011: 16 10 13
            192: 17 8 14
            21037: 9 7 18 13
            292: 11 6 16 20
        """).strip()
        expected_output = 3749
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
