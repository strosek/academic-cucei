#!/bin/python3
"""
Class that implements solution to Leetcode Problem at:
https://leetcode.com/problems/different-ways-to-add-parentheses/

MIT License

Copyright (c) [year] [fullname]

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
import collections
import re
from typing import List, Any


class Solution:
    """Implement solution to AddParenteses problem. """
    def diff_ways_to_compute(self, expression):
        """
        Generate a list of strings with the possible ways of adding parentheses.

        Parameters:
            expression - String with mathematical expression

        Returns:
            List of expressions with added parentheses.
        """
        operands: List[str] = re.findall(r'\d+', expression)
        operators = re.findall(r'[\+\-\*]', expression)

        # n-1 opening/closing parentheses lists, for n operands
        opening_parentheses = [1,1,1,0]
        closing_parentheses = [0,0,0,3]

        expressions = []

        expression_builder_list = []
        # Build expression and append to the list of expressions
        i = 0
        for operator in operators:
            expression_builder_list.append(opening_parentheses[i] * '(')
            expression_builder_list.append(operands[i])
            expression_builder_list.append(closing_parentheses[i] * ')')

            if i < len(operators):
                expression_builder_list.append(operators[i])

            i += 1

        expression_builder_list.append(opening_parentheses[i] * '(')
        expression_builder_list.append(operands[i])
        expression_builder_list.append(closing_parentheses[i] * ')')

        expressions.append(''.join(expression_builder_list))

        return expressions


def main():
    """ Run program with some inputs. """
    solution = Solution()
    print('Running test for Add Parentheses problem ...')
    print(solution.diff_ways_to_compute('2*3-4*5'))


main()
