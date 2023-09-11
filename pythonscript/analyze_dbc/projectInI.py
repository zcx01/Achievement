#矩阵行数配置
msg_line_subNet = 0
msg_line_sender = 1
msg_line_messageId = 4
msg_line_sendingMode = 2
msg_line_cycle = 3
msg_line_lenght = 5
msg_line_Recevier = 6
msg_line_frame = 9

sig_line_subNet = 0
sig_line_Sender = 1
sig_line_name = 2
sig_line_chineseName = 3
sig_line_messageId = 4
sig_line_cycle = 5
sig_line_startBit = 6
sig_line_length = 7
sig_line_factor = 8
sig_line_Offset = 9
sig_line_min=10
sig_line_max=11
sig_line_dataType=12
sig_line_unit=13
sig_line_enum=14
sig_line_initValue=15
sig_line_invalidValue=17
sig_line_Recevier=20

def getStartBit(sheel,row,getValueInt):
    return getValueInt(sheel, row, sig_line_startBit)

def isWriteSig(sheel,row,getValue):
    return True

#项目配置
PC_PWD="123456"
PROJECT_ID='c385ev'
CHANNEL =0
ignore_init_send =True
PowerSig = {'BcmPwrStsFb':'2','IbBrkPedlStsGb':'101','BcmDrvrDoorSts':'1'}
main_can = "CAN1"
local_machine_Sender=['CDC']
SubNet_Frame ={'ICAN':14,'RCAN':0,'ISCAN':0,"HCAN":14} 
VFrameFormat={'StandardCAN':0,'ExtendedCAN':1,'StandardCAN_FD':14,'ExtendedCAN_FD':15}
Sig_Matrix='5_Matrix'
Message_Matrix='4_OverView'
MSB=False
ISUSEDBCENUM=False
SubNet_Channel={'ICAN':"CAN1",'RCAN':'CAN0','ISCAN':'CAN0','HCAN':'CAN2',"Other":'CAN1'}
File_SubNet={}
Jira_Project = "BGS"
SETSTR='/Set'
WRITEWHITE=True