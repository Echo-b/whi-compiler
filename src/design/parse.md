## 语法分析设计

### 设计概要
#### 关于错误处理部分的设计
对于错误处理，我们主要将所有的错误类型定义在一个结构体中
```c
struct grammer_error{
  int errorkind;
  const char* str;
  // void (*handler) (int errorkind,int row, int col);
} errors[];
```
之所以将其分离开来，而不是直接在有错误的地方用`printf`打印的主要原因在于，尽量减少模块之间的耦合性。而且这样设计的好处还在于，我们可以在结构体中加入更多的特性，比如后期可能为每一个错误处理增加一个出错处理函数（如注释部分所示），当我们识别到具体的错误时就对其进行一定的处理达到识别多个错误的目的，而不是简单的识别一个错误然后直接退出，这样可以减少用户因多个错误导致的多次编译。

#### 关于非终结符解析函数部分的设计
而在函数解析部分，其实最重要的一个点就是递归调用的思想以及在合适的时机获取`token`，因此就需要明确`token`的获取时机，故我们对获取时机做出以下规定：
  1. 对于每一个子过程的调用都直接带着一个已经读入的`token`进行分析
  2. 当子过程调用结束时，要获取下一个`token`，用于下一个过程的分析识别

#### 辅助函数`match()`的设计
为了匹配识别我们的具体的`token`，在`helper.c`文件中加入了`match(Token_t hold, int expected)`函数，它主要的工作在于将`hold`和`expected`进行比较，然后返回判断结果，我并没有直接在文件中用`if`语句进行判断，主要理由在于分开有利于出错函数的插入和后续功能的增加，例如若我们想要在匹配到某一个`token`的时候，加入一些额外的输出信息，或者进行一些处理，那么就可以直接直接加入对应的模块，从而进一步与解析函数进行解耦合。另判断两个`token`是否相等这一功能使用比较频繁，因此封装为函数也更为合理。


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

### 识别过程
首先根据文法的`BNF`范式

![BNF](../../asserts/whi_bnf.png)

在具体解析的时候，我们需要根据文法的每一个非终结符。编写对应的解析函数。以变量声明为例

```c
/**
 * @brief 
 * X ::= var V {',' V}
 * parse variable definite
 * nothing on successful
 * call handle_error() function on unsuccessful 
 */
void parse_vardeclation(){
  Token_t hold_token = get_token(); // skip var keyword
  match(hold_token,TK_IDENTIFIER);
  hold_token = get_token();
  if(hold_token.type == TK_COMMA){
    while(hold_token.type != TK_SEMI){
      match(hold_token, TK_COMMA);
      hold_token = get_token();
      match(hold_token, TK_IDENTIFIER);
      hold_token = get_token();
    }
    putback(hold_token);
  }else {
    return;
  }
}
```
根据变量声明的文法`X ::= var V {',' V}`,在程序一开始我们会识别到一个`var`关键字，然后经过层级间的调用，进入到变量声明的解析。首先需要识别一个标识符，然后通过`get_token()`函数获取下一个`token`，判断是不是`,`，若是一个`,`号，那么证明我们需要继续对变量声明的解析，进入`while`循环，首先匹配识别一个`,`号，然后获取下一个`token`，匹配其是否为一个标识符，之后重复这个过程。当然这里其实多判断了一步，即识别到一个`,`号然后进入循环，又匹配其是否为`,`号，显得似乎有些重复，但是主要目的在于统一识别的形式，使整个过程与语法的描述更加的贴合，也更利于理解。而对于识别结束的判断，我们主要判断当前拥有的`hold_token`是否为`;`，若是那么证明我们对变量的解析结束，直接返回，匹配一下个过程，但需要注意的一点是因为我们当前的`token`是`;`，所以需要将提前读入的`;`号放入原`tokens`数组，即调用`putback()`函数。

### 语法解析的错误处理
当我们发现文法中出现语法错误，也即在合适的位置出现的不是我们所期待的`token`我们就需要报出错误，提示用户进行改正。而在错误处理这一部分，我主要定义了如下的错误类型，然后在每一个非终结符对应的解析函数的合适的位置插入错误处理函数`handle_error()`。我们需要将出错的行列信息和出错码传递给出错处理函数，其在内部调用`Log()`函数，进行一个简单的提示信息打印，为了更加的醒目，我为出错处理提示信息加上了颜色。

|错误类型种别|描述|
|-|-|
|`ERROR_x00`| `missing ;`|
|`ERROR_x01`|`declaration syntax error`|
|`ERROR_x02`|`division by zero`|
|`ERROR_x03`|`expression syntax error`|
|`ERROR_x04`|`variable undeclaration`|
|`ERROR_x05`|`while statement must have od`|
|`ERROR_x06`|`while statement must have do`|
|`ERROR_x07`|`if statement must have fi`|
|`ERROR_x08`|`expect (`|
|`ERROR_x09`|`missing )`|
|`ERROR_x10`|`declaration missing ','`|
|`ERROR_x11`|`unknown mistake`|
|`ERROR_x12`|`if statement must have else`|
|`ERROR_x13`|`if statement must have then`|
|`ERROR_x14`|`expect ':='`|
|`ERROR_x15`|`expect 'read' keyword`|
|`ERROR_x16`|`expect 'write' keyword`|
|`ERROR_x17`|`expect '~'`|
|`ERROR_x18`|`expect 'while' keyword`|
|`ERROR_x19`|`expect 'if' keyword`|
|`ERROR_x20`|`expect 'skip' keyword`|
|`ERROR_x21`|`expect a arithmetic operators such as '+','-','*','/'`|
|`ERROR_x22`|`expect a relational operator such as '=' and '<'`|
|`ERROR_x23`|`expect a decimial int number`|

此处的错误类型定义可能并未完全使用到，诸如`ERROR_x02`，是语义层面的错误，语法层面无法暂时未对此情况作出处理。最终的效果如下图所示：

![parse_result](../../asserts/parse_result.png)
