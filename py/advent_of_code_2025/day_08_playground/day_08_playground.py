import textwrap
import unittest
from math import sqrt
from itertools import combinations
from operator import itemgetter
from math import prod


def solve_part_one(puzzle_input, num_pairs_to_connect=1000):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :param num_pairs_to_connect: The number of pairs to try to connect until the algorithm terminates
    :return: Solution for part one
    """
    points = [tuple(map(int, line.split(","))) for line in puzzle_input.strip().splitlines()]
    simulator = CircuitSimulator(points)
    simulator.connect_closest_pairs(num_pairs_to_connect)
    return simulator.get_product_of_largest_three_components()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class CircuitSimulator:
    def __init__(self, points):
        self._points = points
        self._n = len(points)

        # Union-Find data structure
        self._point_id_to_parent_id = list(range(self._n))
        self._root_id_to_component_size = [1] * self._n

    def connect_closest_pairs(self, max_nodes_to_connect):
        edges = []
        for i, j in combinations(range(self._n), 2):
            distance = self._get_distance(self._points[i], self._points[j])
            edges.append((i, j, distance))
        edges.sort(key=itemgetter(2))

        for n in range(0, max_nodes_to_connect):
            i, j, _ = edges[n]
            self._union(i, j)

    def get_product_of_largest_three_components(self):
        # Collect sizes of all components
        roots = [self._find(i) for i in range(self._n)]
        root_to_component_size = {}
        for root in roots:
            root_to_component_size[root] = self._root_id_to_component_size[root]
        sizes = sorted(root_to_component_size.values(), reverse=True)

        return prod(sizes[:3])

    def _find(self, x):
        if self._point_id_to_parent_id[x] != x:
            self._point_id_to_parent_id[x] = self._find(self._point_id_to_parent_id[x])
        return self._point_id_to_parent_id[x]

    def _union(self, x, y):
        x_root, y_root = self._find(x), self._find(y)
        if x_root == y_root:
            return

        self._point_id_to_parent_id[y_root] = x_root
        self._root_id_to_component_size[x_root] += self._root_id_to_component_size[y_root]

    @staticmethod
    def _get_distance(a, b):
        dx, dy, dz = a[0] - b[0], a[1] - b[1], a[2] - b[2]
        return sqrt(dx * dx + dy * dy + dz * dz)


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
            162,817,812
            57,618,57
            906,360,560
            592,479,940
            352,342,300
            466,668,158
            542,29,236
            431,825,988
            739,650,466
            52,470,668
            216,146,977
            819,987,18
            117,168,530
            805,96,715
            346,949,466
            970,615,88
            941,993,340
            862,61,35
            984,92,344
            425,690,689
        """
        ).strip()
        expected_output = 40
        self.assertEqual(expected_output, solve_part_one(puzzle_input, 10))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
