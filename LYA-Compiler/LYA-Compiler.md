# LYA-Compiler

Compiler for the Subset of C Based on C++

## Files

* **0 prog-resource.txt**	源程序
  **1 prog-step1.txt**		去注释后的
  **2 prog-clear.txt**		预处理完成的
  **3 lexical.txt**		词法分析结果存储
  **4 grammar.txt**		原始语法
  **5 ll1_grammar.txt**	符合ll1文法的语法
  **6 ad_grammar.txt**    处理完成的语法
  **7 vn_vtlist.txt**     终结符,非终结符
  **8 first_follow.txt**    first,follow集
  **9 mtable.txt**			预测分析表
  **10 stack_content.txt**    输出栈内信息文件
  **11 symbol_table.txt**    符号表存储文件
  **12 middle_code.txt**    中间代码输出
  **13 ad_midcode.txt**   优化中间代码

## Programs

* **main** 主函数
* **global** 定义文件读取操作，以及后续各阶段所使用的数据结构
* **pretreat** 预处理，包括删除注释、多余空格，消除左递归，提取公共左因子
* **lexical-analysis**  词法分析，识别源程序中的单词符号并修改标识符
* **symbol** 构造符号表，用于语义分析
* **grammar-analysis** 语法分析，构造first集follow集，生成预测分析表及语法分析树，遍历语法分析树生成中间代码
* **optimize** 对中间代码进行优化