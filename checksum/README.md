# checksum

Checksum validation for [Intel Hex (wiki)](https://en.wikipedia.org/wiki/Intel_HEX) files

## Intel checksum

The [two's complement (wiki)](https://en.wikipedia.org/wiki/Two%27s_complement) of the sum of the decoded byte values

### Example

`:0300300002337A1E`

the sum of the decoded byte values is: `03 + 00 + 30 + 00 + 02 + 33 + 7A = E2`

The [two's complement](#complement) of `E2` is `1E`.

## Usage

```bash
$ python3 checksum.py
```

---

<span id="complement"></span>
## `Two's complement`

It's a method of using binary to represent a signed number. 

- The two's complement of `non-negative` number is:

    Represented by its ordinary binary representation. 

- The  two's complement of `negative` number is: 

    The bits in the corresponding positive are inverted and then added 1 to the resulting value.

### Example

```bash
5            -> 00000101
Not operator -> 11111010
# Add 1
-5           -> 11111011
```

In `Python`

```python
a = 5              # 00000101
b = (a ^ 0xff) + 1 # 11111011
```
