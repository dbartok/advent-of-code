import textwrap
import unittest
from collections import defaultdict, deque


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
    rules, updates = parse_input(puzzle_input)
    updates_checker = UpdatesChecker(rules, updates)
    return updates_checker.get_sum_of_reordered_updates()


def parse_input(puzzle_input):
    rules_section, updates_section = puzzle_input.split("\n\n")

    rules = []
    for line in rules_section.splitlines():
        x, y = map(int, line.split("|"))
        rules.append((x, y))

    updates = []
    for line in updates_section.splitlines():
        updates.append(list(map(int, line.split(","))))

    return rules, updates


class UpdatesChecker:
    def __init__(self, rules, updates):
        self._rules = rules
        self._updates = updates

    def _is_ordered(self, update):
        update_page_to_index = {page: index for index, page in enumerate(update)}
        return all(
            update_page_to_index[x] <= update_page_to_index[y]
            for x, y in self._rules
            if x in update_page_to_index and y in update_page_to_index
        )

    def _get_topological_sorted_update(self, update):
        page_to_following_pages = defaultdict(list)
        page_to_preceding_page_count = defaultdict(int)

        relevant_rules = [(x, y) for x, y in self._rules if x in update and y in update]

        for x, y in relevant_rules:
            page_to_following_pages[x].append(y)
            page_to_preceding_page_count[y] += 1

        initial_pages_with_no_preceding_page = [
            page for page in update if page_to_preceding_page_count[page] == 0
        ]
        pages_with_no_preceding_page_queue = deque(initial_pages_with_no_preceding_page)
        sorted_update = []

        while pages_with_no_preceding_page_queue:
            page = pages_with_no_preceding_page_queue.popleft()
            sorted_update.append(page)

            for following_page in page_to_following_pages[page]:
                page_to_preceding_page_count[following_page] -= 1
                if page_to_preceding_page_count[following_page] == 0:
                    pages_with_no_preceding_page_queue.append(following_page)

        return sorted_update

    @staticmethod
    def _get_middle_page(update):
        return update[len(update) // 2]

    def get_sum_of_ordered_updates(self):
        ordered_updates = [
            update for update in self._updates if self._is_ordered(update)
        ]
        return sum(self._get_middle_page(update) for update in ordered_updates)

    def get_sum_of_reordered_updates(self):
        reordered_updates = [
            self._get_topological_sorted_update(update)
            for update in self._updates
            if not self._is_ordered(update)
        ]
        return sum(self._get_middle_page(update) for update in reordered_updates)


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
    """
    ).strip()

    def test_part_one(self):
        expected_output = 143
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 123
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
