import textwrap
import unittest
import itertools
from collections import defaultdict


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    connections = parse_input(puzzle_input)
    network = NetworkMap(connections)
    return network.get_count_of_triad_sets_including_chief_historian()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    connections = parse_input(puzzle_input)
    network = NetworkMap(connections)
    network.find_largest_clique()
    return network.get_largest_clique_password()


def parse_input(puzzle_input):
    return [tuple(connection.split("-")) for connection in puzzle_input.splitlines()]


class NetworkMap:
    def __init__(self, connections):
        self._node_to_neighbor_nodes = defaultdict(set)
        self._build_graph(connections)

        self._largest_clique = []
        self._visited = set()

    def get_count_of_triad_sets_including_chief_historian(self):
        return sum(
            1
            for triad in itertools.combinations(self._node_to_neighbor_nodes.keys(), 3)
            if self._is_triad_connected(triad)
            and any(computer.startswith("t") for computer in triad)
        )

    def find_largest_clique(self):
        self._largest_clique = self._find_largest_clique_backtracking(
            [], self._node_to_neighbor_nodes.keys()
        )

    def get_largest_clique_password(self):
        return self._get_clique_password(self._largest_clique)

    def _build_graph(self, connections):
        for computer1, computer2 in connections:
            self._node_to_neighbor_nodes[computer1].add(computer2)
            self._node_to_neighbor_nodes[computer2].add(computer1)

    def _is_triad_connected(self, triad):
        computer1, computer2, computer3 = triad
        return (
            computer2 in self._node_to_neighbor_nodes[computer1]
            and computer3 in self._node_to_neighbor_nodes[computer1]
            and computer3 in self._node_to_neighbor_nodes[computer2]
        )

    def _find_largest_clique_backtracking(
        self, current_clique, neighbors_of_current_clique
    ):
        largest_clique = current_clique

        for new_node_in_clique in neighbors_of_current_clique:
            new_clique = current_clique + [new_node_in_clique]

            if self._get_clique_password(new_clique) in self._visited:
                continue
            self._visited.add(self._get_clique_password(new_clique))

            neighbors_of_new_clique = [
                node
                for node in neighbors_of_current_clique
                if node != new_node_in_clique
                and node in self._node_to_neighbor_nodes[new_node_in_clique]
            ]
            largest_clique_including_new_node = self._find_largest_clique_backtracking(
                new_clique, neighbors_of_new_clique
            )

            if len(largest_clique_including_new_node) > len(largest_clique):
                largest_clique = largest_clique_including_new_node

        return largest_clique

    def _get_clique_password(self, clique):
        return ",".join(sorted(clique))


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
        kh-tc
        qp-kh
        de-cg
        ka-co
        yn-aq
        qp-ub
        cg-tb
        vc-aq
        tb-ka
        wh-tc
        yn-cg
        kh-ub
        ta-co
        de-co
        tc-td
        tb-wq
        wh-td
        ta-ka
        td-qp
        aq-cg
        wq-ub
        ub-vc
        de-ta
        wq-aq
        wq-vc
        wh-yn
        ka-de
        kh-ta
        co-tc
        wh-qp
        tb-vc
        td-yn
    """
    ).strip()

    def test_part_one(self):
        expected_output = 7
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = "co,de,ka,ta"
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
