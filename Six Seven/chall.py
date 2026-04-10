from Crypto.Util.strxor import strxor
from secrets import flag
import os

assert flag[:8] == b"DawgCTF{"

def gen(start):
    return  (((6 * 7) * (start - 6) * 7) + ((start * 6) - 7) * (start ^ 6)) % 255

def encrypt(message):
    start = os.urandom(1);
    key = start;
    for i in range(1, len(message)):
        key += gen(key[i-1]).to_bytes(1, "big")
    return strxor(key, message)

ct = encrypt(flag)
print("ct =", ct.hex())
