# Coin

A lightweight program for UNIX systems for converting single or multiple hex/decimal/binary values at once. Includes a few optional flags for desired output. 

Also inludes a file hexdump, straight to your terminal.


### Prerequisites
You need makefile to compile the program
```
sudo apt install make
```
and C compiler
```
sudo apt install gcc
```
After installing these packets, type command ```make``` in the directory where this program is.
### After compiling the program

Write the following command to see the list of available commands
```
./coin --h
```

### Examples

Let's convert some hexadecimal values into decimal and binary values

``` bash
vtothek@ubuntu ~ $ coin -hd 9F
159 
```
You can also chain values to get multiple conversions 
``` bash
vtothek@ubuntu ~ $ coin -hd 9F 800A FFA
159 32778 4090
```
Binary conversion
``` bash
vtothek@ubuntu ~ $ coin -hb 9F 800A FFA
10011111 1000000000001010 111111111010 
```
Invalid imput example 
``` bash
vtothek@ubuntu ~ $ coin -hb 9F 800A FFA 9G
10011111 1000000000001010 111111111010 Invalid input 
```

#### Optional flags
You can also print the input values, use custom delimiter and print values vertically

Original input values with `--ov` flag
``` bash
vtothek@ubuntu ~ $ coin -hd 9F 800A FFA 9G --ov
9F=159 800A=32778 FFA=4090 9G=Invalid input 
```

Custom input/output delimiter with `--cd` flag
``` bash
vtothek@ubuntu ~ $ coin -hd 9F 800A FFA 9G --ov --cd::
9F::159 800A::32778 FFA::4090 9G::Invalid input
```

Vertical output with `--v` flag
``` bash
vtothek@ubuntu ~ $ coin -hd 9F 800A FFA 9G --ov --cd:: --v
9F::159 
800A::32778 
FFA::4090 
9G::Invalid input
```

### File hexdump 

You can print colored file hexadump into console   


### Youtube demo
https://www.youtube.com/watch?v=-IPx8CzpF5A&
