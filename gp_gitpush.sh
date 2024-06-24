#!/bin/bash
echo "******git   push  开始*******"
#至少循环1次
condition=1
#模拟do-while
while [ $condition -eq 1 ]
do
        git push origin master
        if [ $? -ne 0 ];then
                echo "git push失败！继续尝试中..."
        else
                condition=0
        fi
done
echo "******git 提交成功！***********"
