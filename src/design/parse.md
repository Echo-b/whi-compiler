## 语法分析设计

### 递归下降法分析与设计
考虑要素
1. 对于每一个子过程的调用都直接带着一个已经读入的`token`进行分析
2. 当子过程调用结束时，要获取下一个`token`，用于下一个过程的分析识别

### 识别条件的判断
当读入一个`token`,需要判断要调用那一个子过程来进行识别，本质上就是对每一个非终结符求`FIRST`集，然后根据不同的符号，匹配进入不同的识别过程，下面是`WHI`语言的文法的非终结符的`FIRST`集

| 非终结符 | FIRST集          |
| -------- | -------------- |
| P        |`{var, skip, read, write, if, while, id(FIRST(C))}`|
| X        |`{var}`|
| L        |`{skip, read, write, if, while, id(FIRST(C))}`|
| S        |`{skip, read, write, if, while, id(FIRST(C))}`|
| E        |`{num(FIRST(G)), id(FIRST(C)), (, ~}`|
| TS       |`{+, -}`|
| T        |`{num(FIRST(G)), id(FIRST(C)), (, ~}`|
| FS       |`{*, /}`|
| F        |`{num(FIRST(G)), id(FIRST(C)), (, ~}`|
| D1       |`{=, <}`|
| D        |`{num(FIRST(G)), id(FIRST(C)), (, ~}`|
| N        |`{num(FIRST(G))}`|
| V        |`{id(FIRST(C))}`|
| G        |`{num(FIRST(G))}`|
| C        |`{id(FIRST(C))}`|

其中，`num(FIRST(G)), id(FIRST(C))`分别对应着`TK_NUM,TK_IDENTIFIER`，也即当终结符为`G,C`时，我们调用函数`match(Token_t hold, Token_t expected)`来检查当前`token`是否相匹配。

