# TODO
# importing sys module
import sys

# defining the main function


def main():
    # taking height from user using height function
    height = Height()
    print_mario(height)

# implementing height function


def Height():
    # looping to make user cooprate
    while True:
        try:
            # if n is int try else go to except
            n = int(input("Height: "))
            try:
                # check the n is btween (0,9)
                if n > 0 and n < 9:
                    return n
            # passing if n < 0 or n>8
            except:
                pass
        except:
            pass

# implemanting print mario function


def print_mario(h):

    for i in range(h):
        # printing h-i-1 space on height i and printing i+1 # on height i and 2 spaces and the i+1 #es
        print(" " * (h-i-1) + "#"*(i+1) + "  " + "#"*(i+1))


"__name__" == "__main__"
main()