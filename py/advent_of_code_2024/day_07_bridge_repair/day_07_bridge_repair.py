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
    solver = CalibrationEquationSolver(equations, ["+", "*"])
    return solver.get_sum_of_valid_test_values()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    equations = parse_input(puzzle_input)
    solver = CalibrationEquationSolver(equations, ["+", "*", "||"])
    return solver.get_sum_of_valid_test_values()


def parse_input(puzzle_input):
    equations = []

    for line in puzzle_input.strip().splitlines():
        test_value_str, numbers_str = line.split(": ")
        test_value = int(test_value_str)
        numbers = list(map(int, numbers_str.split(" ")))
        equations.append((test_value, numbers))

    return equations


class CalibrationEquationSolver:
    def __init__(self, equations, operators):
        self._equations = (
            equations  # List of tuples, each containing (test_value, numbers)
        )
        self._operators = operators  # List of operators (e.g., ['+', '*', '||'])

    def get_sum_of_valid_test_values(self):
        sum_of_valid_test_values = 0

        for test_value, numbers in self._equations:
            num_operators = len(numbers) - 1
            operator_combinations = itertools.product(
                self._operators, repeat=num_operators
            )

            if any(
                    CalibrationEquationSolver._evaluate_expression(
                        numbers, operator_combination
                    )
                    == test_value
                    for operator_combination in operator_combinations
            ):
                sum_of_valid_test_values += test_value

        return sum_of_valid_test_values

    @staticmethod
    def _evaluate_expression(numbers, operators):
        result = numbers[0]

        for i in range(1, len(numbers)):
            operator = operators[i - 1]

            if operator == "+":
                result += numbers[i]
            elif operator == "*":
                result *= numbers[i]
            elif operator == "||":
                result = int(str(result) + str(numbers[i]))

        return result


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
        190: 10 19
        3267: 81 40 27
        83: 17 5
        156: 15 6
        7290: 6 8 6 15
        161011: 16 10 13
        192: 17 8 14
        21037: 9 7 18 13
        292: 11 6 16 20
        """
    ).strip()

    def test_part_one(self):
        expected_output = 3749
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 11387
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
