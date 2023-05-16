从qt官网上下载源码
https://account.qt.io/s/downloads

编译qt源码
mkdir qt_build; cd qt_build
repo init -u ssh://git.i-tetris.com:29418/apps/gladius/qnx/changan/c385/manifest -b master -m qt.xml --no-repo-verify --repo-url=ssh://git.i-tetris.com:29418/repo --repo-branch=repo-1 --depth=1
repo sync
source ./set_env.sh
cd build_script/qt
vim ./Makefile // 编译 debug 则将config命令行（第54行）-release改为-debug
make qt5 && make install

替换源码注意
把 qt_build\qnx文件夹下的文件更新到源码中

代码提交记录
https://git.i-tetris.com/q/project:cores/kiara/third-party/qt_everywhere