import textwrap
import unittest
from heapq import heappop, heappush
from pygame.math import Vector2


class HashableComparableVector(Vector2):
    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        if isinstance(other, HashableComparableVector):
            return self.x == other.x and self.y == other.y
        return False

    def __lt__(self, other):
        if isinstance(other, HashableComparableVector):
            return (self.x, self.y) < (other.x, other.y)
        return False


Vector = HashableComparableVector


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    grid = [list(row) for row in puzzle_input.splitlines()]
    reindeer_maze = ReindeerMaze(grid)
    reindeer_maze.traverse()
    return reindeer_maze.get_best_score()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    grid = [list(row) for row in puzzle_input.splitlines()]
    reindeer_maze = ReindeerMaze(grid)
    reindeer_maze.traverse()
    return reindeer_maze.get_num_tiles_part_of_at_least_one_best_path()


class ReindeerMaze:
    # Directions are in the order of East, North, West, South (counterclockwise)
    DIRECTIONS = [Vector(1, 0), Vector(0, -1), Vector(-1, 0), Vector(0, 1)]
    EAST_DIRECTION_INDEX = 0

    def __init__(self, grid):
        self._grid = grid
        self._start_position = self._find_position("S")
        self._end_position = self._find_position("E")

        self._best_score = float("inf")
        self._best_path_tiles = set()

    def _find_position(self, char):
        for y, row in enumerate(self._grid):
            for x, cell in enumerate(row):
                if cell == char:
                    return Vector(x, y)

    def traverse(self):
        # Priority queue will store tuples of (score, path, direction)
        priority_queue = []
        heappush(priority_queue, (0, [self._start_position], self.EAST_DIRECTION_INDEX))
        # Dictionary to track best score for each state (position + direction)
        state_to_best_score_so_far = {}

        while priority_queue:
            current_score, current_path, current_direction_index = heappop(
                priority_queue
            )
            current_position = current_path[-1]
            current_state = (current_position, current_direction_index)

            # Avoid revisiting the same state if a better score was already found
            # We explicitly continue if another equal score was found so that we identify all best paths
            if (
                    current_state in state_to_best_score_so_far
                    and state_to_best_score_so_far[current_state] < current_score
            ):
                continue
            state_to_best_score_so_far[current_state] = current_score

            # If we reach the endpoint, check if we found a better path
            if current_position == self._end_position:
                if current_score < self._best_score:
                    self._best_score = current_score
                    # All best path tiles so far are invalid, start from scratch
                    self._best_path_tiles.clear()
                    self._best_path_tiles.update(current_path)
                elif current_score == self._best_score:
                    # Existing best path tiles stay valid, add current path
                    self._best_path_tiles.update(current_path)

            # Move forward
            forward_position = (
                    current_position + self.DIRECTIONS[current_direction_index]
            )
            if self._grid[int(forward_position.y)][int(forward_position.x)] != "#":
                heappush(
                    priority_queue,
                    (
                        current_score + 1,
                        current_path + [forward_position],
                        current_direction_index,
                    ),
                )

            # Turn left (counterclockwise)
            new_direction_index = (current_direction_index + 1) % 4
            heappush(
                priority_queue,
                (
                    current_score + 1000,
                    current_path + [current_position],
                    new_direction_index,
                ),
            )

            # Turn right (clockwise)
            new_direction_index = (current_direction_index - 1) % 4
            heappush(
                priority_queue,
                (
                    current_score + 1000,
                    current_path + [current_position],
                    new_direction_index,
                ),
            )

    def get_best_score(self):
        return self._best_score

    def get_num_tiles_part_of_at_least_one_best_path(self):
        return len(self._best_path_tiles)


def main():
    with open("./input.txt") as f:
        puzzle_input = f.read().strip()

    part_one_result = solve_part_one(puzzle_input)
    print(f"Part One: {part_one_result}")

    part_two_result = solve_part_two(puzzle_input)
    print(f"Part Two: {part_two_result}")


class TestAdventOfCode(unittest.TestCase):
    FIRST_EXAMPLE = textwrap.dedent(
        """
        ###############
        #.......#....E#
        #.#.###.#.###.#
        #.....#.#...#.#
        #.###.#####.#.#
        #.#.#.......#.#
        #.#.#####.###.#
        #...........#.#
        ###.#.#####.#.#
        #...#.....#.#.#
        #.#.#.###.#.#.#
        #.....#...#.#.#
        #.###.#.#.#.#.#
        #S..#.....#...#
        ###############
        """
    ).strip()

    SECOND_EXAMPLE = textwrap.dedent(
        """
        #################
        #...#...#...#..E#
        #.#.#.#.#.#.#.#.#
        #.#.#.#...#...#.#
        #.#.#.#.###.#.#.#
        #...#.#.#.....#.#
        #.#.#.#.#.#####.#
        #.#...#.#.#.....#
        #.#.#####.#.###.#
        #.#.#.......#...#
        #.#.###.#####.###
        #.#.#...#.....#.#
        #.#.#.#####.###.#
        #.#.#.........#.#
        #.#.#.#########.#
        #S#.............#
        #################
        """
    ).strip()

    def test_part_one_first_example(self):
        expected_output = 7036
        self.assertEqual(expected_output, solve_part_one(self.FIRST_EXAMPLE))

    def test_part_one_second_example(self):
        expected_output = 11048
        self.assertEqual(expected_output, solve_part_one(self.SECOND_EXAMPLE))

    def test_part_two_first_example(self):
        expected_output = 45
        self.assertEqual(expected_output, solve_part_two(self.FIRST_EXAMPLE))

    def test_part_two_second_example(self):
        expected_output = 64
        self.assertEqual(expected_output, solve_part_two(self.SECOND_EXAMPLE))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
