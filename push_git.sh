#!/bin/bash
echo "******1.本次变更的文件列表*******"
git status -s
echo "******2.git    add    开始*******"
git add .
if [ $? -eq 0 ];then
	echo "git add 成功."
else
	echo "git add 失败！"
	exit
fi
echo "******3.git  commit  开始*******"
date_time=`date +"%Y-%m-%d %H:%M:%S"`
git commit -m "$date_time"
if [ $? -eq 0 ];then
        echo "git commit 成功. 备注为:$date_time"
else
        echo "git commit 失败！"
        exit
fi
echo "******4.git   push  开始*******"
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
