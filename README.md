# cobsm
Modified reduced COBS codec for messages of less than 255 bytes.

COBS can be used for framing data in a stream. It removes all 0x00 data elements from the original array. The cost is only one additional data element. A frame can then be delimited using 0x00 as a token.

## Features

This implementation of COBS is intended for small packets on platforms with limited memory and processing.

Only a single buffer is used. Encoding and decoding is done in place with minimal data movement.

This approach is a small modification from the algorithm developed by [Craig McQueen](http://craig.mcqueen.id.au/) which he implented in [Python](https://pythonhosted.org/cobs/cobsr-intro.html)
