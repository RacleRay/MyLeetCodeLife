
// a % b 得到 a 中不能被 b 整除的部分。这部分再与 b 计算二者的最大公因数。
// 合理。注意一般使得 a > b
int gcd(int a, int b) {
    return b == 0 ? a: gcd(b, a % b);
}

// 最小公倍数数，除掉最大共因数，合理。
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}


// 扩展欧几里得算法: 看不懂
// ax + by = gcd(a, b) 同时求得 x, y
int xGCD(int a, int b, int &x, int &y) {
    if (!b) {  // b == 0
        x = 1, y = 0;
        return a;
    }

    int x1, y1;
    int gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}