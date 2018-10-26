#!/bin/python3
'''
Class that implements solution to Leetcode Problem at:
https://leetcode.com/problems/different-ways-to-add-parentheses/
'''

'''
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
'''

import re

class Solution:
    '''Implement solution to AddParenteses problem. '''

    def add_parentheses(self, expression, initial_length):
        ''' Generate list with add parentheses for providad expresson. '''
        pass

    def diff_ways_to_compute(self, expression):
        '''
        Generate a list of strings with the possible ways of adding parentheses.

        Parameters:
            expression - String with mathematical expression

        Returns:
            List of expressions with added parentheses.
        '''
        n_operators = len(re.findall('[+-*]', expression))
        return self.add_parentheses(expression, n_operators)

def main():
    ''' Run program with some inputs. '''
    solution = Solution()
    solution.diff_ways_to_compute('2*3-4*5')
