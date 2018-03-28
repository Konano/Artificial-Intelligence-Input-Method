## 文件夹说明

`bin`：可执行程序和数据文件

`src`：源文件

`data`：程序输入输出

## 源程序说明

`bin/pinyin.exe`：基于字的二元模型的转换程序。使用指令：`pinyin.exe <input_path> <output_path>`

`bin/pinyin_2.exe`：基于词的二元模型的转换程序。使用指令：`pinyin_2.exe <input_path> <output_path>`

`bin/diff.exe`：比较程序，通过比较求得程序转换的准确率，需要提供一个标准文件。使用指令：`diff.exe <origin_path> <output_path>`

`src/character`：基于字的二元模型的转换程序源码。

`src/word`：基于词的二元模型的转换程序源码。