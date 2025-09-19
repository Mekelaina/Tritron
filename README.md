# Tritron
<br>
Tritron is a framework and virtual machine for Trit based computing. Built as both an expirament with the concept and a personal time killer. Please note the code is a heavy WIP and is provided <b>as is</b>. Bug reports and contributions are welcome, if you find this interesting or useful. But just know what you are getting into.

## What is a 'Trit'?
A trit (<b>Tr</b>inary Dig<b>it</b>) is the base 3 analogue to the bit that makes up most computing. However, instead of having 2 possible states like a bit (`0`, `1`), a trit has 3 (`0`, `1`, `2`). Thus making any system using trits '[Trinary](https://en.wikipedia.org/wiki/Ternary_numeral_system)'.
<br><br>
To be more specific, Tritron uses '[Balanced Trinary](https://en.wikipedia.org/wiki/Balanced_ternary)' where the 3 possible states are `-1`, `0`, and `1`. Using a balanced base has many interesting and useful properties, and there were even some [early computers](https://en.wikipedia.org/wiki/Setun) that had balenced ternary based architectures.
<br><br>
In Tritron, `-1` is False and `1` is True, with `0` being [logically unknown/uncertain](https://en.wikipedia.org/wiki/Three-valued_logic).

## Trytes and Repersentaions
A tryte is the trit version of a byte. However, at least in Tritron, 1 tryte is 6 trits. This was done both to make the amount of values stored in a tryte roughly comparible to that of a byte (729 possible states, or -364 to 364 including 0), and to make a single tryte repersentable in 2 bytes. (one byte is a tribble/3 trits). Each digit of a tribble is represented by two bits where:<br>
```
00 : 0
01 : 1
10 : Invalid
11 : -1
```
<br>The two highest bits in each byte of a tribble are always `00` and are effectivly unused. This is to keep both upper and lower tribbles sepereate in byte form which simplifies certain operations. Since most platforms just fit any data less thana byte into a byte, we dont really lose any memory efficiancy by doing it this way.<hr>

When writing numbers in balanced ternary, Tritron uses `T` to represent -1, as it looks like a mix of `-` and `1` if you squint, and it is easy to type. 
<br><br>
But what does -1 mean when a digit? Much as our familiar unbalanced bases, we can calculate the value by multiplying the digit by the base to the power of its position from the right minus 1. If we look at an example: `T01` it can be interpreted as: <br>
<pre>= -1(3<sup>2</sup>) + 0(3<sup>1</sup>) + 1(3<sup>0</sup>)
=   -9   +   0   +   1
=   -8</pre>

Counting is also similar to working with unbalanced bases, but starting with -1, then counting up. `TTT, TT0, TT1, T0T... 111`
<br> <br>
Tritron also allows for a base 27 hexidecimal analogue representation, called 'Tricunal' or 'tric' 0..9 are represented with numbers, 10..13 are A..D like in hexadecimal, and -1..-13 are Z..N, with Z being -1.
| Digit | Decimal Value | Trinary |
|-------|---------------|---------|
| N     | -13           | TTT     |
| O     | -12           | TT0     |
| P     | -11           | TT1     |
| Q     | -10           | T0T     |
| R     | -9            | T00     |
| S     | -8            | T01     |
| T     | -7            | T1T     |
| U     | -6            | T10     |
| V     | -5            | T11     |
| W     | -4            | 0TT     |
| X     | -3            | 0T0     |
| Y     | -2            | 0T1     |
| Z     | -1            | 00T     |
| 0     | 0             | 000     |
| 1     | 1             | 001     |
| 2     | 2             | 01T     |
| 3     | 3             | 010     |
| 4     | 4             | 011     |
| 5     | 5             | 1TT     |
| 6     | 6             | 1T0     |
| 7     | 7             | 1T1     |
| 8     | 8             | 10T     |
| 9     | 9             | 100     |
| A     | 10            | 101     |
| B     | 11            | 11T     |
| C     | 12            | 110     |
| D     | 13            | 111     |

## Getting started
If you want to run Tritron, clone the repo and run the build.sh script. Tritron was written on Windows 11 using gcc through MSYS2 and git bash. so it should run on most platforms, it does not use any 3rd party dependancies, nor any platform specific code (as of now)