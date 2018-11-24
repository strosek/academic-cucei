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
from random import choice


class Solution:

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self.nums = nums

    def pick(self, target):
        """
        :type target: int
        :rtype: int
        """
        start_idx = self.nums.index(target)

        list_size = len(self.nums)
        if list_size == 1:
            return 0

        indexes_list = []

        i = 0
        while i < list_size:
            if self.nums[i] == target:
                start_idx = i
                while i < list_size and self.nums[i] == target:
                    i += 1

                end_idx = i
                indexes_list.extend(range(start_idx, end_idx))
            i += 1

        return choice(indexes_list)


def main():
    print("Solution testing ...")
    solution = Solution([1,2,3,3,3, 2, 3, 2, 3, 3, 3, 4])
    print(solution.pick(3))

main()

