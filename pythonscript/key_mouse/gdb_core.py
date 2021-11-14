import sys
from key_mouse import *

keyStr('cd prebuilts/ic/')
keyStr('ntoaarch64-gdb bin/ic_service ../../ic_service.core',10)
keyStr('set solib-search-path lib/')
keyStr('bt')