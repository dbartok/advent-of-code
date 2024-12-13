import textwrap
import unittest
from collections import deque
from pygame.math import Vector2


class HashableVector(Vector2):
    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, HashableVector):
            return self.x == other.x and self.y == other.y
        return False


Vector = HashableVector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = [list(row) for row in puzzle_input.splitlines()]
    garden_map = GardenPlotMap(grid)
    garden_map.identify_regions()
    return garden_map.get_total_price()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    pass


class GardenPlotMap:
    DIRECTIONS = [Vector(0, -1), Vector(0, 1), Vector(-1, 0), Vector(1, 0)]  # Up, Down, Left, Right

    def __init__(self, grid):
        self._grid = grid
        self._height = len(self._grid)
        self._width = len(self._grid[0])
        self._visited = set()
        self._regions = []

    def identify_regions(self):
        positions = [
            Vector(x, y) for y in range(self._height) for x in range(self._width)
        ]

        for position in positions:
            if position not in self._visited:
                region = self._get_region_at(position)
                self._regions.append(region)

    def get_total_price(self):
        total_price = 0

        for region_cells in self._regions:
            area = len(region_cells)
            perimeter = self._calculate_perimeter(region_cells)
            total_price += area * perimeter

        return total_price

    def _get_plant_at(self, position):
        return self._grid[int(position.y)][int(position.x)]

    def _is_in_bounds(self, position):
        return 0 <= position.x < self._width and 0 <= position.y < self._height

    def _get_region_at(self, start):
        queue = deque()
        queue.append(start)
        region = []
        self._visited.add(start)
        plant_type = self._get_plant_at(start)

        while queue:
            position = queue.popleft()
            region.append(position)

            valid_neighbor_positions = [
                neighbor_position
                for neighbor_position in self._get_neighbor_positions(position)
                if self._is_in_bounds(neighbor_position)
                   and neighbor_position not in self._visited
                   and self._get_plant_at(neighbor_position) == plant_type
            ]

            for neighbor_position in valid_neighbor_positions:
                self._visited.add(neighbor_position)
                queue.append(neighbor_position)

        return region

    def _get_neighbor_positions(self, position):
        return [position + direction for direction in self.DIRECTIONS]

    def _calculate_perimeter(self, region):
        return sum(
            1
            for position in region
            for neighbor_position in self._get_neighbor_positions(position)
            if not self._is_in_bounds(neighbor_position) or neighbor_position not in region
        )


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
            RRRRIICCFF
            RRRRIICCCF
            VVRRRCCFFF
            VVRCCCJFFF
            VVVVCJJCFE
            VVIVCCJJEE
            VVIIICJJEE
            MIIIIIJJEE
            MIIISIJEEE
            MMMISSJEEE
        """).strip()
        expected_output = 1930
        self.assertEqual(expected_output, solve_part_one(puzzle_input))

    def test_part_two(self):
        pass


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
