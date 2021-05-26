from cs50 import get_int

# Get height
height = 0
while height < 1 or height > 8:
    height = get_int("Enter a height between 1 and 8: ")

# Print piramid
n = 1
while n <= height:
    spaces = " " * (height - n)
    row = n * "#"
    print(spaces + row + "  " + row)
    n = n + 1