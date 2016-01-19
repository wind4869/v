#!/bin/bash

# 变量
author="wind4869" # 变量名和等号之间不能有空格
echo $author

author="haoyouqiang" # 重定义变量
echo ${author} # 好的编程习惯

# 字符串可以用单引号，也可以用双引号，也可以不用引号
str=string
echo ${str}

# 单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的
# 单引号字串中不能出现单引号（对单引号使用转义符后也不行）
echo '${author}'

# 双引号里可以有变量
# 双引号里可以出现转义字符
echo "Hello, I know the author is '${author}' !"

# 字符串操作
greeting="hello, "$author" !"
another_greeting="hello, ${author} !"
echo $greeting $another_greeting
echo ${#author} # 获得字符串长度
echo ${author:1:4} # 获得子字符串

gexpr index ${author} "hao" # 查找子字符串
gexpr length ${author}
gexpr substr ${author} 1 4 # ???

# if语句
if [ ! -f learn.sh ]; then
    echo "file exists !"
elif [ ! -d ./消息通知 ]
then
    echo "dir exists !"
else
    echo "nothing exists !"
fi

i=5
if [[ $i > 3 ]] && [[ $i < 7 ]]; then
    echo "(3, 7)"
elif [ $i -le 3 ]; then
    echo "-le 3"
else
    echo "-ge 7"
fi

# case语句
case ${author} in
    haoyouqiang ) echo "case: haoyouqiang"
    ;;
    wind4869 ) echo "case: wind4869"
    ;;
    * ) echo "case: bad option"
esac

# for循环
for skill in C C++ Java
do
    echo "I am good at ${skill}Script"
done

for file in `ls ~`; do echo ${file}; done

for ((i=0; $i < 10; i+=1)); do echo $i; done

# while循环
i=0
while [ $i -lt 10 ]
do
    echo $i
    ((i+=1))
done

# until循环
until [ $i -ge 10 ]; do
    echo $i
    ((i+=1))
done

# 死循环
# while :; do :;done # :表示空语句
# for ((;;))