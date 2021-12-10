# PRTBruteforce - v1.0.3

## Description
**PRTBruteforce** is a fast bruteforce library that allows you to implement bruteforce technique in any C/C++ program at ease. This library makes it possible to start bruteforce from a particular point, and also the ability to include character sets this library provides or even use your custom set of characters.

Following GIF is the output of the [sample code](https://github.com/AkshayMohan/PRTBruteforce/blob/master/Examples/sample.c) provided under [Examples](https://github.com/AkshayMohan/PRTBruteforce/tree/master/Examples).

![sample.c-Output](https://raw.githubusercontent.com/AkshayMohan/PRTBruteforce/master/Examples/sample.c-output.gif)

## Documentation
Documentation can be found on the [Wiki](https://github.com/AkshayMohan/PRTBruteforce/wiki).

## Changelogs
v1.0.3 - 10th of December, 2021
- Fixed possible segmentation fault issue, thanks to the [issue report #1](https://github.com/AkshayMohan/PRTBruteforce/issues/1).

v1.0.2 - 31st of May, 2018.
- Improved bruteforce_update (it is even more faster now).
- Changed 'char *' to 'const char *' on arguments 'data' and 'startString' of function 'bruteforce_init'.
- Added more support for C++.
- Added support for 64-bit.

v1.0.1 - 12th of May, 2018.
- Fixed memory overflow issue for C++.
- Better include guard name.
- Proper function declarations.

v1.0.0 - 1st of May, 2018.
- Initial release.

### TO-DO
Future updates will be supporting in-built multiple masks. For now, bruteforce with mask can be done explicitly.

## LICENSE
Licensed under MIT.
