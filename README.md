# stegdir

**stegdir** is a utility that transforms binary files into a structure of directories using base64url encoding.
The encoded data is encoded into base64url and then used to build a folder tree that can be parsed by the decoding software.
### Why should I do that?
If you have a PC where files are automatically encrypted when moved to an external drive, chances are that the folder names are not encrypted. This way, you can move data across systems even if you don't have the decryption software installed.

### Limitations
- Encoding and decoding will likely be very slow due to the filesystem overhead in managing lots of directories
- Encoding data in base64 format adds a significant overhead in terms of space