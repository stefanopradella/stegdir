# stegdir

**stegdir** is a utility that transforms binary files into a structure of directories using base64url encoding.
The encoded data is encoded into base64url and then used to build a folder tree that can be parsed in the decoding process.
### Why should I do that?
If you have a PC where files are automatically encrypted when moved to an external drive, chances are that the folder names are not encrypted. This way, you can move data across systems even if you don't have the decryption software installed.

### Limitations
- Encoding and decoding will likely be very slow due to the filesystem overhead in managing lots of directories
- Encoding data in base64 format adds a significant overhead in terms of space

### Notes on the implementation
- The main implementation remains the one made with MATLAB functions. This is because, in the context I described above, I didn't have the possibility to run arbitrary programs other than the one allowed by the system policy
- Using the C code generated from the base64 MATLAB utility is extremely inefficient and unnecessary, the C implementation was only made for educational purposes and to ensure digital continuity across the core function that performs encoding and decoding