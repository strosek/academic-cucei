#!/bin/python3
"""
Class that implements solution to Leetcode Problem at:
https://leetcode.com/problems/random-pick-index/

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
    def search_right(starts, end):
        return 0

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
            # Search interval, if not found, add -1 to solutions
            # If not found, but a valid start to the right exists, return the
            # first index to the right.
            #bin_search(starts, interval.search())
            right_intervals.append(self.search_right(starts, interval.end))

        print(right_intervals)

        return right_intervals

def main():
    print('Solution ...')
    s = Solution()
    s.findRightInterval([Interval(1, 2), Interval(2, 3), Interval(0,3)])


main()

