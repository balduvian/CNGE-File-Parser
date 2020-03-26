# CNGE-File-Parser

### Adds an easy way to insert data into your game

This uses the proprietary CNGE file reading language which as of now has no official name. It's very simple, unnamed and untyped. All elements are separated with whitespace. Adding tags is optional.

 #### Elements

Token | Meaning
---|---
`word` `Word` `w0rd` | tag
`34` `-12` | int
`2.45` `.33` | float
`"a string"` | string
`'a'` `'\n'` | char
`[]` `[2 5 7]` `[['a' 'b'] ['c']]` | array
`{}` `{3 "hello"}` | struct

#### Todo

- [ ] add token factories for all primitive data types
- [ ] have tokens evaluate the value of their data
- [ ] separate ints and floats
- [ ] re-add the parser for tokens
- [ ] profit