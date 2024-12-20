import textwrap
import unittest


def solve_part_one(puzzle_input):
    """
    Solve part one of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part one
    """
    compactor = DiskCompactor(puzzle_input)
    compactor.compact()
    return compactor.get_checksum()


def solve_part_two(puzzle_input):
    """
    Solve part two of the Advent of Code puzzle.

    :param puzzle_input: The input data as string
    :return: Solution for part two
    """
    compactor = WholeFileDiskCompactor(puzzle_input)
    compactor.compact()
    return compactor.get_checksum()


class DiskCompactor:
    def __init__(self, disk_map: str):
        self._disk_map = disk_map
        self._file_sizes, self._space_sizes = self._parse_disk_map()

        # List to store (file_id, file_size) tuples
        self._new_disk_layout = []

    def compact(self):
        # Start by placing the first file
        self._new_disk_layout.append((0, self._file_sizes[0]))

        file_to_move_index = len(self._file_sizes) - 1
        remaining_file_size = self._file_sizes[file_to_move_index]
        space_index = 0
        remaining_space_size = self._space_sizes[space_index]
        while space_index < file_to_move_index - 1:
            if remaining_space_size == 0:
                # Write file that was originally after this space
                file_after_space_index = space_index + 1
                self._new_disk_layout.append(
                    (file_after_space_index, self._file_sizes[file_after_space_index])
                )

                # Move onto next space
                space_index += 1
                remaining_space_size = self._space_sizes[space_index]

            # Write the file chunk to the current space
            write_size = min(remaining_file_size, remaining_space_size)
            self._new_disk_layout.append((file_to_move_index, write_size))
            remaining_file_size -= write_size
            remaining_space_size -= write_size

            if remaining_file_size == 0:
                # Move onto previous file (we process the files backwards)
                file_to_move_index -= 1
                remaining_file_size = self._file_sizes[file_to_move_index]

        # Write final chunk of last file
        self._new_disk_layout.append((file_to_move_index, remaining_file_size))

    def get_checksum(self):
        expanded_layout = []

        # Expand the new disk layout to get actual blocks
        for file_id, file_size in self._new_disk_layout:
            expanded_layout.extend([file_id] * file_size)

        # Calculate checksum by summing the position * file_id for each block
        checksum = sum(
            position * file_id for position, file_id in enumerate(expanded_layout)
        )
        return checksum

    def _parse_disk_map(self):
        file_sizes = []
        space_sizes = []

        for i in range(len(self._disk_map)):
            if i % 2 == 0:  # Even indices (0, 2, 4, ...) are file sizes
                file_sizes.append(int(self._disk_map[i]))
            else:  # Odd indices (1, 3, 5, ...) are space sizes
                space_sizes.append(int(self._disk_map[i]))

        # Add extra 0 space at the end as padding
        space_sizes.append(0)

        return file_sizes, space_sizes


class WholeFileDiskCompactor(DiskCompactor):
    def __init__(self, disk_map: str):
        super().__init__(disk_map)
        self._file_ids_in_new_order = list(range(0, len(self._file_sizes)))

    def compact(self):
        # Iterate files in reverse order (starting with the highest file ID) and move if possible
        for file_id in range(len(self._file_sizes) - 1, -1, -1):
            self._move_file_id_if_possible(file_id)

        # Create new disk layout
        for space_size, file_id in zip(self._space_sizes, self._file_ids_in_new_order):
            self._new_disk_layout.append(
                (file_id, self._file_sizes[file_id])
            )  # Add file
            self._new_disk_layout.append((0, space_size))  # Add space with ID 0

    def _move_file_id_if_possible(self, file_id):
        file_size = self._file_sizes[file_id]
        num_extra_spaces_before_file = (
            self._file_ids_in_new_order.index(file_id) - file_id
        )
        file_index_adjusted_with_extra_spaces = file_id + num_extra_spaces_before_file
        # Try to find a span of free space that can fit the current file
        for space_index in range(file_index_adjusted_with_extra_spaces):
            space_size = self._space_sizes[space_index]

            # If the space can fit the file, move the file to this space
            if space_size >= file_size:
                # Adjust spaces at origin of move
                combined_space_size = (
                    self._space_sizes[file_index_adjusted_with_extra_spaces - 1]
                    + file_size
                    + self._space_sizes[file_index_adjusted_with_extra_spaces]
                )
                del self._space_sizes[file_index_adjusted_with_extra_spaces]
                self._space_sizes[file_index_adjusted_with_extra_spaces - 1] = (
                    combined_space_size
                )

                # Adjust spaces at destination of move
                self._space_sizes[space_index] -= file_size
                self._space_sizes.insert(space_index, 0)

                # Adjust file ID order
                self._file_ids_in_new_order.remove(file_id)
                self._file_ids_in_new_order.insert(space_index + 1, file_id)

                break


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
        2333133121414131402
    """
    ).strip()

    def test_part_one(self):
        expected_output = 1928
        self.assertEqual(expected_output, solve_part_one(self.PUZZLE_INPUT))

    def test_part_two(self):
        expected_output = 2858
        self.assertEqual(expected_output, solve_part_two(self.PUZZLE_INPUT))


if __name__ == "__main__":
    # unittest.main() # Uncomment to run unit tests
    main()
