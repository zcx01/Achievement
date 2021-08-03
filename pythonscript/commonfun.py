# from typing import List
class EesyStr():
    @staticmethod
    def removeAt(s,index):
        temp=list(s)
        try:
            temp.pop(index)
        except:
            print("移除失败，索引超出范围")
        return "".join(temp)

    @staticmethod
    def removeOne(s,r):
        temp=list(s)
        try:
            temp.remove(r)
        except:
            print("移除失败")
        return "".join(temp)

    @staticmethod
    def removeAll(s,r):
        return s.replace(r,"")

    @staticmethod
    def chop(s):
        temp=list(s)
        try:
            temp.pop()
        except:
            print("删除失败，字符串为空")
        return "".join(temp)


