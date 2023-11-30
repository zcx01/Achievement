#矩阵行数配置
msg_line_subNet = 'A'
msg_line_sender = 'B'
msg_line_messageId = 'C'
msg_line_sendingMode = 'E'
msg_line_cycle = 'E'
msg_line_lenght = 'D'
msg_line_Recevier = 'H'
msg_line_frame = 'I'

sig_line_subNet = 'A'
sig_line_Sender = 'B'
sig_line_name = 'C'
sig_line_chineseName = 'D'
sig_line_messageId = 'E'
sig_line_cycle = 'F'
sig_line_bytes_segment ='G'
sig_line_startBit = 'H'
sig_line_length = 'I'
sig_line_factor = 'J'
sig_line_Offset = 'K'
sig_line_min='L'
sig_line_max='M'
sig_line_dataType='N'
sig_line_unit='O'
sig_line_enum='P'
sig_line_initValue='Q'
sig_line_invalidValue='R'
sig_line_Recevier='U'
sig_line_Project='AN'

def getStartBit(sheel,row,getValueInt):
    startPos =  getValueInt(sheel, row, sig_line_startBit)
    segmentPos =  getValueInt(sheel, row, sig_line_bytes_segment)
    return segmentPos*8*8+startPos

def isWriteSig(sheel,row,getValue):
    content = getValue(sheel,row,sig_line_Project)
    return '无' not in content

#项目配置
PC_PWD="123456"
PROJECT_ID='c385ev'
CHANNEL =0
ignore_init_send =True
PowerSig = {'BCM_PowerStatusFeedback':'2'}
main_can = "CAN1"
local_machine_Sender=['THU']
SubNet_Frame ={'INFOCAN':14,'RCAN':0,'CDC私CAN':0,"DATACAN":14} 
VFrameFormat={'StandardCAN':0,'ExtendedCAN':1,'StandardCAN_FD':14,'ExtendedCAN_FD':15}
SubNet_Channel={'INFOCAN':"CAN1",'RCAN':'CAN0','CDC私CAN':'CAN0','DATACAN':'CAN2',"Other":'CAN1'}
File_SubNet={"1DATACAN":"DATACAN","2CDC私CAN":"CDC私CAN","3INFOCAN":"INFOCAN",'CAN1':"INFOCAN",'CAN0':"CDC私CAN"} #用于dbc导入
Sig_Matrix='4_Matrix'
Message_Matrix='3_OverView'
MSB=False
ISUSEDBCENUM=False
Jira_Project = "HUR"
SETSTR='/Set'
WRITEWHITE=False
GOOGLESIGTOPICID="1v4y6DCyc3wnzaY8AdIi51jg4hQnV1Ip8J051WbIGUcc"