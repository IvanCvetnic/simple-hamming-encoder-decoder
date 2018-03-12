# simple-huffman-encoder-decoder
Simple console programs for encoding and decoding binary files using Huffman algorithm.<br />

## Makefile
Create executive programs by calling `make` command.<br />
Remove all unnecessary files by calling `make clean` command. 

## Call programs:

### Huffencoder
```
./huffencoder [input_file.*] [huffman_table.txt] [output_file.bin]
```
- **`input_file.*`** 
	* file that will be encoded
- **`huffman_table.txt`**
	* table of **256** rows, where each row represent huffman code for one byte in text format
	* first row represent huffman code for byte **0x00**, and last for **0xFF**
	* ```./huffencoder``` creates this file and fills it
	* name for this file can be arbitrary
- **`output_file.bin`**
	* encoded **`input_file.*`**
	* name for this file can be arbitrary
	
#### Description:	
This program first passes trough the entire **`input_file.*`** by reading it byte by byte, and counts frequency of occurrence of each different byte. Then, by using counted frequencies and huffman algorithm, program creates binary huffman code for each of 256 bytes. Bytes with higher frequency of occurrence in **`input_file.*`** will have less bits in it's huffman code and vice versa. Huffman code for every byte is written in **`huffman_table.txt`** in text format. First row has code for byte **0x00**, second for byte **0x01**, and so on to the last for byte **0xFF**. At the end, program by using generated huffman table and **`input_file.*`** creates **`output_file.bin`**.

#### Example:
- **`input.txt :`**</br>
	```
	aaaabbbcc
	```
	
- ```$ ./huffcoder input.txt table.txt coded.bin```
- **`table.txt :`**</br>
	```
	1001		//1st row (byte 0x00)
	10001		//2nd row (byte 0x01)
	...
	0		//98th row (ascii a)
	11		//99th row (ascii b)
	101		//100th row (ascii c)
	...
	```
- **`coded.bin :`** </br>
	(showed in binary foramt, if you run program in linux use command ```xxd -b coded.bin```) </br>
	```
	00001111 11101101
	```
		
### Huffdecoder
```
./huffdecoder [huffman_table.txt] [input_file.bin] [output_file.*]
```
## Remark
In some cases the **`./huffdecoder`** will not be able to properly decode last byte.
## What will be added/fixed in the future:
- **`./huffdecoder`** will be able to properly decode last byte in all cases
- code will be better optimized and it will have comments
