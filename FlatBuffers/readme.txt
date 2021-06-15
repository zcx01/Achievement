-------------------------生成工具-------------------------
1、git clone https://github.com/google/flatbuffers
2、进入flatbuffers一级目录
3、如果需要，可以指定安装目录：cmake -DCMAKE_INSTALL_PREFIX=`pwd`/develop/ 或者 修改cmake文件，加入：SET(CMAKE_INSTALL_PREFIX < install_path >) 要加在 PROJECT(< project_name>) 之后。
4、cmake .
5、make 
6、make install
参考链接
https://blog.csdn.net/huangjiazhi_/article/details/103262814

本地目录
file:///../home/chengxiongzhu/Works/flatbuffers/flatbuffers

--------------------使用生成代码---------------------------
1、依赖文件
file:///./模式文件.txt

2、编译依赖文件
cd flatbuffers/samples
./../flatc --cpp Monster.fbs

3、结果
工具会生成monster_generated.h

------------------使用生成的文件-----------------------------
1、包含文件
1)包含flatbuffers/include/flatbuffers中的所有头文件
2)包含刚刚生存的文件

2、写入参考
file:///./写.txt

3、读取参考
file:///./读.txt

4、修改接受的数据
file:///./修改.txt

5.
