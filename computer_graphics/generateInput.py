#!/usr/bin/python

import random

m = random.randint(1, 10);
n = random.randint(1, 10);
p = random.randint(1, 10);

print(m, n)
print(p, m)
print()

i = 0
while i < n:
  j = 0
  while j < m:
    print(random.randint(-5, 100), end=' ')
    j += 1
  print()
  i += 1

print()

i = 0
while i < m:
  j = 0
  while j < p:
    print(random.randint(-1000, 1000), end=' ')
    j += 1
  print()
  i += 1

