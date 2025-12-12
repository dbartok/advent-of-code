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
        total_sum += buyer.get_most_recent_secret_number()
    return total_sum


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    input_secret_numbers = parse_input(puzzle_input)
    buyers = [MonkeyBuyer(secret_number) for secret_number in input_secret_numbers]
    delta_sequence_to_final_price_dicts = get_delta_sequence_to_final_price_dicts(
        buyers
    )

    # Create a set to store all unique 4-number sequences encountered across all buyers
    all_delta_sequences_union = set()
    for delta_sequence_to_final_price_dict in delta_sequence_to_final_price_dicts:
        all_delta_sequences_union.update(delta_sequence_to_final_price_dict.keys())

    return max(
        sum(
            seq_dict.get(sequence, 0)
            for seq_dict in delta_sequence_to_final_price_dicts
        )
        for sequence in all_delta_sequences_union
    )


def parse_input(input_string):
    return [int(line.strip()) for line in input_string.strip().splitlines()]


def get_delta_sequence_to_final_price_dicts(buyers):
    delta_sequence_to_final_price_dicts = []

    for buyer in buyers:
        buyer.generate_secret_numbers(2000)
        secret_numbers = buyer.get_secret_numbers()
        prices = [num % 10 for num in secret_numbers]

        price_delta_calculator = PriceDeltaCalculator(prices)
        delta_sequence_to_final_price_dict = (
            price_delta_calculator.get_delta_sequence_to_final_price_dict()
        )
        delta_sequence_to_final_price_dicts.append(delta_sequence_to_final_price_dict)

    return delta_sequence_to_final_price_dicts


class PriceDeltaCalculator:
    def __init__(self, prices):
        self.prices = prices
        self.deltas = [prices[i + 1] - prices[i] for i in range(len(prices) - 1)]

    def get_delta_sequence_to_final_price_dict(self):
        # Create a dictionary where the keys are 4-number sequences of deltas and the values are the final price
        delta_sequence_to_final_price_dict = {}
        for i in range(len(self.deltas) - 3):
            delta_sequence = tuple(self.deltas[i: i + 4])
            # Each index i in the deltas array corresponds to i + 1 in the prices array, because there is no delta for the first price
            index_conversion_between_deltas_and_prices = 1
            final_price = self.prices[
                i + 3 + index_conversion_between_deltas_and_prices
                ]

            # Track the first occurrence
            if delta_sequence not in delta_sequence_to_final_price_dict:
                delta_sequence_to_final_price_dict[delta_sequence] = final_price

        return delta_sequence_to_final_price_dict


class MonkeyBuyer:
    def __init__(self, initial_secret_number):
        self._secret_numbers = [initial_secret_number]

    def generate_secret_numbers(self, n):
        for _ in range(n):
            self._apply_transformation()

    def get_most_recent_secret_number(self):
        return self._secret_numbers[-1]

    def get_secret_numbers(self):
        return self._secret_numbers

    def _apply_transformation(self):
        new_secret_number = self._secret_numbers[-1]

        # Step 1: Multiply by 64, XOR, then prune
        new_secret_number = (new_secret_number * 64) ^ new_secret_number
        new_secret_number %= 16777216

        # Step 2: Divide by 32, XOR, then prune
        new_secret_number = (new_secret_number // 32) ^ new_secret_number
        new_secret_number %= 16777216

        # Step 3: Multiply by 2048, XOR, then prune
        new_secret_number = (new_secret_number * 2048) ^ new_secret_number
        new_secret_number %= 16777216

        self._secret_numbers.append(new_secret_number)


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
        puzzle_input = textwrap.dedent(
            """
            1
            2
            3
            2024
            """
        ).strip()
        expected_output = 23
        self.assertEqual(expected_output, solve_part_two(puzzle_input))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
