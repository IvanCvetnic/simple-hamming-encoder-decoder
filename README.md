# simple-hamming-encoder-decoder
Simple console programs for encoding and decoding binary files using Hamming algorithm.<br />

## Makefile
Create executive programs by calling `make` command.
Remove all unnecessary files by calling `make clean` command. 

## Call programs:

### Huffkoder
```
./huffkoder [input_file] [huffman_table.txt] [output_file]
```	
- **`input_file`** 
	* any binary file that will be encoded
- **`huffman_table.txt`** 
	* **`huffkoder`** creates this file and filled it
	* table of **256** row, where each row represent huffman code for one byte in text format
	* first row represent huffman code for byte **0x00**, and last for **0xFF**
- **`output_file`**
	* encoded **`input_file`**
	
### Huffdekoder
```
./huffdekoder [hiffman_table.txt] [input_file] [output_file]
```
## Remark
In some cases huffdekder the **huffdekoder** will not be able to decode well last byte.
