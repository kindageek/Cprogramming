# My_printf.c

This program is a custom implementation of `printf()` function in C programming language. It was made as a project for Qwant and Silicon Valley Qwasar coding school. 

The program uses basic functions such as `write()` to implement standard output. It returns the length of the input and supports the following specifiers:

- %d - int
- %o - octal
- %u - unsigned int
- %x - hexadecimal
- %s - string
- %c - char
- %p - *void
- %% - percent('%') symbol

## The custom implementations consist of:

- `my_printf()` → custom printf()
- `my_putchar()` → custom putchar()
- `my_putstr()` → custom puts(), prints a string to stdout using for loop and my_putchar()
- `my_strlen()` → custom strlen()
- `my_itoa()` → custom itoa()
- `my_ultoa()` → custom ultoa()

## Other functions:

- `checkFormat()` → checks if the input string has invalid specifiers other than 'd, o, u, x, s, c, p, %'
- `my_reverse()` → custom function to reverse a string

## Conclusion

As a result of this project, I gained much more understanding about printing functions and using low-level programming language and basic functions to implement popular ones. This understanding helped me to do the next project [My_ls](https://github.com/SanzharNussipbek/Cprogramming/tree/master/My_ls).
