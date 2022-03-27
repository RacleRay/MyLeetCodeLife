from secrets import token_bytes
from typing import Tuple

ENDIANNESS = "big"


def random_key(length):
    tb = token_bytes(length)
    return int.from_bytes(tb, ENDIANNESS)  # 大端


def encrypt(user_key: str) -> Tuple[int, int]:
    origin_bytes = user_key.encode("utf-8")
    origin_key = int.from_bytes(origin_bytes, ENDIANNESS)
    dummy = random_key(len(origin_bytes))
    encrypted = origin_key ^ dummy
    return encrypted, dummy


def decrypt(encrypted, dummy):
    origin_key = encrypted ^ dummy
    origin_bytes = origin_key.to_bytes((origin_key.bit_length() + 7) // 8,
                                       ENDIANNESS)
    return origin_bytes.decode("utf-8")


if __name__ == "__main__":
    key1, key2 = encrypt("One Time Pad!")
    result: str = decrypt(key1, key2)
    print(result)