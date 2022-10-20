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
        # printing h-i-1 space on height i
        print(" " * (h-i-1), end="")
        # printing i+1 # on height i
        print("#"*(i+1))


"__name__" == "__main__"
main()