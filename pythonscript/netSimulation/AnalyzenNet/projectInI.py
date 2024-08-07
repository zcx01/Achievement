Sig_Matrix='THUEDC_To_ADC'
CANTYPE="APA"
HEADFILNE=".h"
SOURCE='.c'
BUILDINGBLOCKSBEGIN='//[begin]'
BUILDINGBLOCKEND='//[end]'
ISUSEDBCENUM=True

#矩阵行数配置
if CANTYPE == "ADAS":
    sig_line_subNet = 'A'
    sig_line_Sender = 'B'
    sig_line_name = 'F'
    sig_line_chineseName = 'G'
    sig_line_messageId = 'H'
    sig_line_cycle = 'I'
    sig_line_start_by_byte = 'J'
    sig_line_length_byte='K'
    sig_line_length_bits = 'L'
    sig_line_factor = 'M'
    sig_line_Offset = 'N'
    sig_line_min='O'
    sig_line_max='p'
    sig_line_dataType='Q'
    sig_line_unit='R'
    sig_line_initValue='T'
    sig_line_invalidValue='U'
    sig_line_Recevier='X'
elif CANTYPE == "APA":
    sig_line_subNet = 'A'
    sig_line_Sender = 'B'
    sig_line_name = 'F'
    sig_line_chineseName = 'G'
    sig_line_messageId = 'H'
    sig_line_cycle = 'I'
    sig_line_start_by_byte = 'J'
    sig_line_length_byte='K'
    sig_line_length_bits = ''
    sig_line_factor = 'L'
    sig_line_Offset = 'M'
    sig_line_min='N'
    sig_line_max='O'
    sig_line_dataType='P'
    sig_line_unit='Q'
    sig_line_initValue='S'
    sig_line_invalidValue='T'
    sig_line_Recevier='W'

'''
检测到中文中有expand_fields中的字段，就把信号展开
把信号名称中expand_flag字段替换成索引
检测到的信号的sig_line_start_by_byte必须是第一个信号的开始字节
'''
expand_fields = ['Xn','Yn']
expand_flag = 'n'