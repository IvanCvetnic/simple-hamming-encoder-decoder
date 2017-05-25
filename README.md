# simple-hamming-encoder-decoder
Simple console programs for encoding and decoding binary files using Huffman algorithm.<br />

## Makefile
Create executive programs by calling `make` command.
Remove all unnecessary files by calling `make clean` command. 

## Call programs:

### Huffencoder
```
./huffencoder [input_file] [huffman_table.txt] [output_file]
```	
- **`input_file`** 
	* any binary file that will be encoded
- **`huffman_table.txt`** 
	* table of **256** row, where each row represent huffman code for one byte in text format
	* first row represent huffman code for byte **0x00**, and last for **0xFF**
	* **`huffencoder`** creates this file and filled it
	* **`huffencoder`** first reads the entire **input_file** and parallel counts the frequency of the occurrence of each byte
	* that frequncies are used to generate binary codes for each of 256 bytes
- **`output_file`**
	* encoded **`input_file`**
	
### Huffdecoder
```
./huffdecoder [hiffman_table.txt] [input_file] [output_file]
```
## Remark
In some cases the **huffdecoder** will not be able to properly decode last byte.
## What will be added/fixed in the future:
- **huffdekoder** will be able to properly decode last byte in all cases
- code will be better optimized and it will have comments
