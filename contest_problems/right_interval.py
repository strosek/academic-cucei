#!/bin/python3
"""
Class that implements solution to Leetcode Problem at:
https://leetcode.com/problems/find-right-interval/

MIT License

Copyright (c) 2018 Erick Daniel Corona

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE
    SOFTWARE.
"""


# Definition for an interval.
class Interval:
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e

class Solution:
    @staticmethod
    def search_right(starts, start):
        """
        Implements binary search that returns right element if it exists.
        :param starts: List of start-index.
        :param start: End element of i-interval.
        :return: Index of right interval.
        """
        print(starts)
        print('Search {0}'.format(start))

        found_index = -1
        n_starts = len(starts)
        index = (n_starts - 1) // 2
        prev_index = index
        while found_index == -1 and index < n_starts:
            if starts[index][0] == start:
                found_index = starts[index][1]
                break
            else:
                if start < starts[index][0]:
                    # Search left.
                    prev_index = index
                    index = index - index - index // 2
                else:
                    # Search right.
                    prev_index = index
                    index = index + index - index // 2

                # If bisecting results in the same index, not found, break.
                if prev_index == index:
                    break

        # If not found, pick the next element to the last index found.
        if found_index == -1 and index < n_starts - 1:
            print("Prev: {0}".format(prev_index))
            found_index = prev_index + 1

        print('Found: {0}'.format(found_index))

        return found_index

    def findRightInterval(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        starts = []
        
        # Add starts and indexes to array, and sort it.
        for i, interval in enumerate(intervals):
            starts.append([interval.start, i])

        # Sort array.
        starts.sort(key=lambda x : x[0])

        right_intervals = []
        for interval in intervals:
            right_intervals.append(self.search_right(starts, interval.end))

        print("Solution: {0}".format(right_intervals))

        return right_intervals


def main():
    print('Solution ...')
    s = Solution()
    s.findRightInterval([Interval(1, 2), Interval(2, 3), Interval(0,3), Interval(3,4), Interval(5,9)])


main()
