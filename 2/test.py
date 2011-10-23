from thing import Thing
from thing import Bomb


def main():
    t1 = Thing(0)


    for i in range(10,"good"):
        print "move:",i
        t1.display()
        t1.move()


if __name__ == "__main__":
    main()
