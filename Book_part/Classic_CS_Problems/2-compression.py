class CompressedGene:
    def __init__(self, gene: str) -> None:
        self._compressed(gene)

    def _compressed(self, gene: str) -> None:
        # if len(gene)== 0: return None
        self.bit_seq: int = 1
        for item in gene.upper():
            self.bit_seq <<= 2
            if item == 'A': self.bit_seq |= 0b00
            elif item == 'C': self.bit_seq |= 0b01
            elif item == 'G': self.bit_seq |= 0b10
            elif item == 'T': self.bit_seq |= 0b11
            else:
                raise ValueError(f"Invalid gene input: {gene}")

    def decompress(self) -> str:
        gene: str = ""
        for i in range(0, self.bit_seq.bit_length() - 1, 2):
            bits: int = self.bit_seq >> i & 0b11
            if bits == 0b00: gene += 'A'
            elif bits == 0b10: gene += 'G'
            elif bits == 0b11: gene += 'T'
            elif bits == 0b01: gene += 'C'
            else:
                raise ValueError(f"Invalid bit seq: {self.bit_seq}")
        return gene[::-1]

    def __str__(self) -> str:
        return self.decompress()


if __name__ == "__main__":
    from sys import getsizeof

    o_string: str = "TATATATATATATATATATCGCGCGCCGCGCGCGCGCC"
    print("Original size: ", getsizeof(o_string))
    compressed: CompressedGene = CompressedGene(o_string)
    print("Compressed size: ", getsizeof(compressed.bit_seq))
    print("Decompress is successful: ", o_string == str(compressed))
