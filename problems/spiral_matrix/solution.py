from enum import Enum

# create an enumeration of directions
Direction = Enum('Direction', r'RIGHT,DOWN,LEFT,UP'.split(',')) 

class Solution:
    def yieldSpiralIndex(self, nRows: int, nCols: int) -> Tuple[int]:
        r'''
         Yields the next index to the spiral matrix given its height
         `nRows` and width `nCols`.
         '''
        # initialize the row, column offsets
        rowOff = 0
        colOff = 0
        # initialize the ending row, column
        rowEnd = (nRows - 1)
        colEnd = (nCols - 1)
        # initialize the direction
        dir = Direction.RIGHT

        while True:
            # base case:
            if (rowOff > rowEnd) or (colOff > colEnd):
                return
            # inductive steps:
            # if moving to the right
            if (dir == Direction.RIGHT):
                # yield each column at this beginning row, forwards
                for iCol in range(colOff, colEnd + 1):
                    yield (rowOff, iCol)
                # start after this row henceforth
                rowOff += 1
                # turn clockwise
                dir = Direction.DOWN
            # if moving down
            elif (dir == Direction.DOWN):
                # yield each row at this ending column, forwards
                for iRow in range(rowOff, rowEnd + 1):
                    yield (iRow, colEnd)
                # finish before this column henceforth
                colEnd -= 1
                # turn clockwise
                dir = Direction.LEFT
            # if moving to the left
            elif (dir == Direction.LEFT):
                # yield each column at this ending row, backwards
                for iCol in range(colEnd, (colOff - 1), -1):
                    yield (rowEnd, iCol)
                # finish before this row henceforth
                rowEnd -= 1
                # turn clockwise
                dir = Direction.UP
            # if moving up
            elif (dir == Direction.UP):
                # yield each row at this beginning column, backwards
                for iRow in range(rowEnd, (rowOff - 1), -1):
                    yield (iRow, colOff)
                # finish before this column henceforth
                colOff += 1
                # turn clockwise
                dir = Direction.RIGHT
        # while True
    # end def yieldSpiralIndex(self, int, int)

    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        r'''
         Returns all the elements in the array `matrix` in spiral order.
         '''
        # get length of matrix for #rows
        nRows = len(matrix)
        # use the length of the first row for #cols
        nCols = len(matrix[0])
        # create the generator `yielder`
        yielder = self.yieldSpiralIndex(nRows, nCols)
        # use the yielder to create the array
        return [matrix[iRow][iCol] for (iRow, iCol) in yielder]
    # end def spiralOrder(self, List[List[int]])
# end Solution
