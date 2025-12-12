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
    planner = GardenPlotPlanner(grid)
    planner.identify_regions()
    return planner.get_total_price()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    grid = [list(row) for row in puzzle_input.splitlines()]
    planner = GardenPlotPlannerWithDiscount(grid)
    planner.identify_regions()
    return planner.get_total_price()


class GardenPlotPlanner:
    DIRECTIONS = [
        Vector(0, -1),
        Vector(0, 1),
        Vector(-1, 0),
        Vector(1, 0),
    ]  # Up, Down, Left, Right

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
            perimeter = self._get_perimeter(region_cells)
            total_price += area * perimeter

        return total_price

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

    def _get_plant_at(self, position):
        return self._grid[int(position.y)][int(position.x)]

    def _get_neighbor_positions(self, position):
        return [position + direction for direction in self.DIRECTIONS]

    def _is_in_bounds(self, position):
        return 0 <= position.x < self._width and 0 <= position.y < self._height

    def _get_perimeter(self, region):
        return sum(
            1
            for position in region
            for neighbor_position in self._get_neighbor_positions(position)
            if not self._is_in_bounds(neighbor_position)
            or neighbor_position not in region
        )


class GardenPlotPlannerWithDiscount(GardenPlotPlanner):
    def get_total_price(self):
        total_price = 0

        for region_cells in self._regions:
            area = len(region_cells)
            num_sides = self._get_num_sides(region_cells)
            total_price += area * num_sides

        return total_price

    def _get_num_sides(self, region):
        num_sides = 0

        for direction in self.DIRECTIONS:
            edge_positions = self._get_edge_positions_in_direction(region, direction)
            num_sides += self._get_num_islands(edge_positions)

        return num_sides

    def _get_edge_positions_in_direction(self, region, direction):
        edge_positions = set()

        for position in region:
            neighbor_position = position + direction
            if not self._is_in_bounds(neighbor_position) or self._get_plant_at(
                    neighbor_position
            ) != self._get_plant_at(position):
                edge_positions.add(neighbor_position)

        return edge_positions

    def _get_num_islands(self, positions):
        visited = set()
        num_islands = 0

        for start_position in positions:
            if start_position not in visited:
                self._flood(start_position, positions, visited)
                num_islands += 1

        return num_islands

    def _flood(self, start_position, positions, visited):
        queue = deque()
        queue.append(start_position)

        while queue:
            current_position = queue.popleft()

            valid_neighbor_positions = [
                neighbor_position
                for neighbor_position in self._get_neighbor_positions(current_position)
                if neighbor_position in positions and neighbor_position not in visited
            ]

            for neighbor_position in valid_neighbor_positions:
                visited.add(neighbor_position)
                queue.append(neighbor_position)


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
        """
    ).strip()

    def test_part_one(self):
        expected_output = 1930
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 1206
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
