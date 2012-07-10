Rubymm-interpeter
=================

An educational interpreter for Ruby-- meta-language

This project is simply an interpreter for a small sub-set of Ruby language. It is only for educational purposes.

Features
--------

Currently Ruby-- can recognize and execute this features:

 * **Commands:** assignment, `while`, `if...else`, `puts`, `gets`
 * **Literals:** strings, numbers, bools and nils
 * **Aritmetic operators:** `+`, `-`, `*`, `/`, `%`
 * **String operators:** `+`, `*` (`String * Number`, repeat left string x times)
 * **Bool operators:** `or`, `and`
 * **Compare operators:** `==`, `!=`, `<=`, `>=`, `<`, `>`
 * **Functions:** with params and return value (also recursive)

Build
-----

For build Ruby-- interpeter you need [Code::Blocks](http://www.codeblocks.org/) IDE (GNU Autotools support is desiderabile).

### Dependencies

* [Flex](http://flex.sourceforge.net/) a lexical analyzer
