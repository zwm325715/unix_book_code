#!/bin/bash
#项目根目录
BASE_PATH=`readlink -f \`dirname $0\``
#build脚本
BUILD_SH=$BASE_PATH/build.sh
#build目录
BUILD_PATH=$BASE_PATH/build
#bin目录
BIN_PATH=$BASE_PATH/bin
#CmakeList.txt
CMAKELIST_PATH=$BASE_PATH/CMakeLists.txt

function echo_info() {
  echo -e "[build.sh][INFO] $@" 
}

function echo_err() {
  echo -e "[build.sh][ERROR] $@" 
}

function echo_err_tab_prefix() {
  echo -e "[build.sh][ERROR] \t$@" 
}
#0表示成功，1表示失败
function check_command(){
    if [ $? -eq 0 ];then
      echo_info "$1成功."
    else
      echo_info "$1失败！"
      exit
    fi
}

# 编译
function compile() {
    if [ ! -d $BUILD_PATH ];then
        echo_info "0.******创建目录:$BUILD_PATH******"
        mkdir -p $BUILD_PATH
    fi    
    cd $BUILD_PATH

    echo_info "1.******开始编译******"
    echo_info "compile=$1"
    # 没有传参数时就是编译所有
    if [ -z "$1" ];then
      echo_info "----编译所有章节----"
      cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCHAPTER=all "$BASE_PATH"
    else #否则编译对应的参数章节
      echo_info "----编译第${1}章节----"
      cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCHAPTER="$1" "$BASE_PATH"   
    fi
    
    check_command "cmake编译" 

    echo_info "2.******开始make******"
    make 
    check_command "make生成目标文件"
    
}

function clean() {
    if [ -d $BUILD_PATH ];then
        echo_info "-----1.开始删除build目录:$BUILD_PATH-----"
        rm -rf $BUILD_PATH
        check_command "删除build目录" 
    fi
    if [ -d $BIN_PATH ];then
        echo_info "-----2.开始删除bin目录:$BIN_PATH-----"
        rm -rf $BIN_PATH
        check_command "删除bin目录" 
    fi
}

function main(){
    if [ $# -ne 1 -a $# -ne 2 ];then
       echo_err "只支持1或2个参数，支持的参数列表如下:"
       echo_err_tab_prefix "gen:编译所有;gen num:编译num章节"
       echo_err_tab_prefix "clean:清除编译的文件"
       exit
    fi
    # 第一个参数
    case "$1" in
    "gen")
      #$2:表示只编译哪个章节，all表示全部
      compile "$2"
      ;;
    # 其他(任意字符串)
    "clean")
      clean
      ;;
    *)
      echo_err "不支持该参数$1!"
      echo_info "Usage ...:"
      echo_info "    gen : 编译所有"
      echo_info "    gen num: 编译第num个章节(num是个数字)"
      echo_info "    clean:清除编译的文件"
      ;;  
    esac
}

main "$@"

