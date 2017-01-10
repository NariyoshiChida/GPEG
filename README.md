# Generalized Parsing Expression Grammars (GPEGs)
This is the source code repository for GPEGs.

## Install
`make`

## Examples
```
./generalized_packrat_main > math_parser.cc
Expression
	<- Sum

Sum
	<- Product ( ( '+' / '-' ) Product )*

Product
	<- Value ( ( '*' / '/' / '%' ) Value )*

Value
	<- [0-9]+
	/ [A-Za-z0-9_]+
	/ '(' Expression ')'
```

```
./generalized_packrat_main > ambiguous.cc
S <- 'a' S | 'a' S 'b' S | ''
```







