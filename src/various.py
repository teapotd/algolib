#!!DONT-HASH
input().split(' ') # Read and split into words
print('abc', end='') # Print without newline

>>> from fractions import *
>>> Fraction(16, -10)
Fraction(-8, 5)
>>> Fraction(123)
>>> Fraction()
Fraction(0, 1)
>>> Fraction('3/7')
>>> Fraction('7e-6')
>>> Fraction(2.25)
Fraction(9, 4)
>>> Fraction(1.1)
Fraction(2476979795053773, 2251799813685248)
>>> Fraction('1/2') * Fraction('4/3')
>>> Fraction(16, 5).numerator,denominator

>>> from decimal import *
>>> getcontext().prec = 28
>>> Decimal(10)
>>> Decimal('3.14')
>>> Decimal(3.14)
Decimal('3.1400000000000001243449787580175...')
>>> Decimal((0, (3, 1, 4), -2))
Decimal('3.14')
>>> Decimal(str(2.0 ** 0.5))
>>> Decimal(2) ** Decimal('0.5')
>>> Decimal('NaN')
>>> Decimal('-Infinity')
