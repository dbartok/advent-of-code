import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    rules, updates = parse_input(puzzle_input)
    updates_checker = UpdatesChecker(rules, updates)
    return updates_checker.get_sum_of_ordered_updates()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


def parse_input(puzzle_input):
    rules_section, updates_section = puzzle_input.split('\n\n')

    rules = []
    for line in rules_section.splitlines():
        x, y = map(int, line.split('|'))
        rules.append((x, y))

    updates = []
    for line in updates_section.splitlines():
        updates.append(list(map(int, line.split(','))))

    return rules, updates


class UpdatesChecker:
    def __init__(self, rules, updates):
        self.rules = rules
        self.updates = updates

    def _is_ordered(self, update):
        update_page_to_index = {page: index for index, page in enumerate(update)}
        return all(
            update_page_to_index[x] <= update_page_to_index[y] for x, y in self.rules
            if x in update_page_to_index and y in update_page_to_index
        )

    @staticmethod
    def _get_middle_page(update):
        return update[len(update) // 2]

    def get_sum_of_ordered_updates(self):
        ordered_updates = [update for update in self.updates if self._is_ordered(update)]
        return sum(self._get_middle_page(update) for update in ordered_updates)


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
            47|53
            97|13
            97|61
            97|47
            75|29
            61|13
            75|53
            29|13
            97|29
            53|29
            61|53
            97|53
            61|29
            47|13
            75|47
            97|75
            47|61
            75|61
            47|29
            75|13
            53|13

            75,47,61,53,29
            97,61,53,29,13
            75,29,13
            75,97,47,61,53
            61,13,29
            97,13,75,29,47
        """).strip()
        expected_output = 143
        self.assertEqual(solve_part_one(puzzle_input), expected_output)

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
