"""
计算Pi值

圆面积: (PI * R^2)   外切正方形面积：4 * R^2

MonteCarlo模拟计算两者比值： MC = (PI * R^2) / (4 * R^2) = PI / 4
"""

import random
import sys
from collections import namedtuple

Point = namedtuple('Point', ['x', 'y'])


def within_circle(point: Point) -> bool:
    return point.x ** 2 + point.y ** 2 <= 0.25;


def main(n_points: int) -> None:
    n_circle = 0
    for i in range(n_points):
        sample = Point(random.uniform(-0.5, 0.5), random.uniform(-0.5, 0.5))
        if within_circle(sample):
            n_circle += 1

    sys.stdout.write("估计值： %.4f \n" % (n_circle / n_points * 4))

    return


if __name__ == "__main__":
    main(100000)