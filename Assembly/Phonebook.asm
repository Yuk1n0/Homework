;***********************定义数据段****************************
DATAS SEGMENT
    MESSAGE  DB 'PLEASE INPUT YOUR NAME:',13,10,'$'
    MESSAGE1 DB 'PLEASE INPUT YOUR TELEPHONE NUMBER:',13,10,'$'
    MESSAGE2 DB 'NAME                     TEL.',13,10,'$'
    MESSAGE4 DB '*************************************',13,10,'$'
    MESSAGE5 DB 'PLEASE SELECT THE OPERATION:',13,10,'$'
    MESSAGE6 DB '1:INPUT  2:PRINT  3: SEARCH 4: EXIT',13,10,'$'
    MESSAGE7 DB 'PLEASE INPUT THE NAME.',13,10,'$'
    MESSAGE8 DB 'THERE IS NOT  THE NAME.',13,10,'$'
    MESSAGE9 DB 'YOU INPUT THE WRONG NUMBER.',13,10,'$'
    MESSAGE10 DB '------------------------------------',13,10,'$'
    MESSAGE3 DB 'YOU SHOULD INPUT SOME LETTERS.',13,10,'$'
    MESSAGE11 DB 'YOU SHOULD INPUT A---Z OR a----z',13,10,'$'
    MESSAGE12 DB 'YOU SHOULD INPUT 0---9',13,10,'$'
    BIAOJI    DW 0
    MAXLEN    DB 21
    INBUFLEN  DB ?
    INBUF     DB 21 DUP(20H)
    MAXLEN1    DB 9
    INBUFLEN1  DB ?
    INBUF1     DB 9 DUP(20H)
    OUTLINE  DB 50 DUP(33 DUP(20H)) 
DATAS ENDS

;***********************定义代码段****************************
CODES SEGMENT
MAIN PROC FAR
    ASSUME CS:CODES,DS:DATAS
START:
    PUSH DS
    SUB AX,AX
    PUSH AX
    MOV AX,DATAS
    MOV DS,AX
    MOV DI,0
    MOV BL,0
 
;*******************接受输入姓名和电话号码*********************
FIRST:
    CALL HUANHANG
    CALL XINGHAO  
    MOV AH,9H
    MOV DX,OFFSET MESSAGE
    INT 21H
    CALL XINGHAO
    CALL INPUTNAME
    CALL HUANHANG
    CALL XUXIAN
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE1
    INT 21H
    CALL XINGHAO
    CALL INPHONENUMBER
    CALL HUANHANG
    CALL XUXIAN
    CALL XUANXIANG
 
;******************对电话号码按照姓名排序并且输出***************
SECOND:
    CALL HUANHANG
    CALL XUXIAN
    MOV AH,9H
    MOV DX,OFFSET MESSAGE2
    INT 21H
    CALL XUXIAN
    CMP BL,1
    JE  ZHUANYI
    CALL PAIXU
ZHUANYI:    
    CALL PRINTLINE
    CALL HUANHANG
    CALL XUANXIANG

;***********接受用户输入的姓名并且显示电话号码*******************
THIRD:
    CALL HUANHANG
    CALL SEARCH
    CALL XUANXIANG 
    
;*************************退出程序*****************************
FOUR:

    MOV AH,4CH
    INT 21H
MAIN ENDP

;*********************接受用户输入的姓名************************
INPUTNAME PROC NEAR
NEXTSTEP2:    
    CALL GETNAME

;********************检测是否输入了字符*************************
    CMP INBUFLEN,0
    JE ERROR1
    JMP CHECKONE  
ERROR1:
    CALL HUANHANG
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE3
    INT 21H
    CALL XINGHAO
    CALL HUANHANG
    JMP NEXTSTEP2

;********************检测用输入的是否是字母*********************
CHECKONE:
   MOV CH,0
   MOV CL,INBUFLEN
  MOV SI,0
LOOPP:   
   CMP INBUF[SI],41H
   JB ERRORA
   CMP INBUF[SI],5BH
   JB NEXTSTEPL
   CMP INBUF[SI],61H
   JB   ERRORA
   CMP INBUF[SI],7BH
   JB NEXTSTEPL
   JMP ERRORA
NEXTSTEPL:   
   INC SI
   LOOP LOOPP
   MOV SI,0
   JMP NEXTSTEP
ERRORA:
    CALL HUANHANG
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE11
    INT 21H
    CALL XINGHAO
    JMP NEXTSTEP2
    
;*******************把有效的名字送入INBUF中***********************
NEXTSTEP:
    MOV CH,0
    MOV CL,25
    SUB CL,INBUFLEN
    INC BL
ZHUANYINAME:    
    MOV BH,INBUF[SI]
    MOV OUTLINE[DI],BH
    INC DI
    INC SI
    DEC INBUFLEN
    JNZ ZHUANYINAME
KONGGE: 
    MOV  OUTLINE[DI],20H
    INC  DI  
    LOOP KONGGE
    RET
INPUTNAME ENDP

;**************接受用户输入电话号码并且存入INBUF1中**************
GETNUMBER PROC NEAR
    MOV SI,0
    LEA DX,MAXLEN1
    MOV AH,0CH
    MOV AL,0AH
    INT 21H
    RET
GETNUMBER ENDP

;**************接受用户输入的姓名并且存入INBUF中*****************
GETNAME PROC NEAR
    MOV SI,0
    LEA DX,MAXLEN
    MOV AH,0CH
    MOV AL,0AH
    INT 21H
    RET
GETNAME ENDP

;*******************接受用户输入的电话号码***********************
INPHONENUMBER PROC NEAR
NEXTSTEP3:    
    CALL GETNUMBER

;*********************检测是否输入了字符************************
    CMP INBUFLEN1,0
    JE ERROR2
    JMP CHECKTWO
ERROR2:
    CALL HUANHANG
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE3
    INT 21H
    CALL XINGHAO
    CALL HUANHANG
    JMP NEXTSTEP3
    
;*********************检测是否输入的是数字**********************
CHECKTWO:
   MOV CH,0
   MOV CL,INBUFLEN1
   MOV SI,0
LOOPP1:   
   CMP INBUF1[SI],30H
   JB ERRORA1
   CMP INBUF1[SI],3AH
   JB NEXTSTEPL1
   JMP ERRORA1
NEXTSTEPL1:   
   INC SI
   LOOP LOOPP1
   MOV SI,0
   JMP NEXTSTEP1
ERRORA1:
    CALL HUANHANG
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE12
    INT 21H
    CALL XINGHAO
    JMP NEXTSTEP3
    
;********************把有效电话号码放进INBUF1中******************
NEXTSTEP1:
    MOV CH,0
    MOV CL,8
    SUB CL,INBUFLEN1
ZHUANYIPHONE:    
    MOV BH,INBUF1[SI]
    MOV OUTLINE[DI],BH
    INC DI
    INC SI
    DEC INBUFLEN1
    JNZ ZHUANYIPHONE
    CMP CL,0
    JE LASTNUMBER
KONGGE1:
    MOV OUTLINE[DI],20H
    INC DI
    LOOP KONGGE1
LASTNUMBER:  
    RET
INPHONENUMBER ENDP

;********************把姓名及电话号码显示到屏幕上*******************
PRINTLINE PROC NEAR
    PUSH BX
    MOV SI,0 
LOOP1:
    MOV CX,33
SHUCHU:
    MOV DL,OUTLINE[SI]
    MOV AH,02H
    INT 21H
    INC SI
    LOOP SHUCHU
    CALL HUANHANG
    CALL XUXIAN
    DEC BL
    JNZ LOOP1
    POP BX
    RET
PRINTLINE ENDP

;***********************回车并且换行过程***************************
HUANHANG PROC NEAR
    MOV DL,0DH
    MOV AH,02H
    INT 21H
    MOV DL,0AH
    MOV AH,02H
    INT 21H
    RET
HUANHANG ENDP

;***********************用冒泡排序对名字进行排序********************
PAIXU  PROC NEAR
    PUSH BX
    PUSH AX
    PUSH DI
    MOV BH,0

SORT1:
    DEC BL
    MOV CX,BX
    PUSH CX
    MOV DI,CX
    MOV BIAOJI,0

SORT:
    MOV CX,20
    MOV SI,BIAOJI    

LOOP3:
    MOV AL,OUTLINE[SI]
    CMP AL,OUTLINE[SI+33]
    JB NEXT3
    JA  NEXT2
    INC SI
    LOOP LOOP3
    JMP NEXT3
NEXT2:
    CALL JIAOHUAN
NEXT3:
    ADD BIAOJI,33
    DEC DI
    JNZ  SORT
    POP CX
    LOOP SORT1
    POP DI
    POP AX
    POP BX
    RET
PAIXU  ENDP

;*******************两个姓名及电话号码进行交换*******************
JIAOHUAN PROC NEAR
   PUSH AX
   PUSH CX
   MOV CX, 33
   MOV SI,BIAOJI
LOOP4:
   MOV AL,OUTLINE[SI]
   MOV AH,OUTLINE[SI+33]
   MOV OUTLINE[SI+33],AL
   MOV OUTLINE[SI],AH
   INC SI
   LOOP LOOP4 
   POP CX
   POP AX
   RET 
JIAOHUAN  ENDP

;***************查询一个名字并显示与其匹配的电话号码****************
SEARCH PROC NEAR
  PUSH SI
  PUSH DI
  PUSH AX
  PUSH BX
 
  CALL XINGHAO
  MOV AH,9H
  MOV DX,OFFSET MESSAGE7
  INT 21H
  CALL XINGHAO
  MOV BH,0

;**********************检测有几个号码重名***************************
XUNHUAN:
  CALL GETNAME
  
  CMP INBUFLEN,0
    JE ERROR12
    JMP CHECKONEAB  
ERROR12:
    CALL HUANHANG
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE3
    INT 21H
    CALL XINGHAO
    CALL HUANHANG
    JMP XUNHUAN

;**********************检测用输入的是否是字母********************   
CHECKONEAB:
   MOV CH,0
   MOV CL,INBUFLEN
  MOV SI,0
LOOPPAB:   
   CMP INBUF[SI],41H
   JB ERRORAB
   CMP INBUF[SI],5BH
   JB NEXTSTEPLA
   CMP INBUF[SI],61H
   JB   ERRORAB
   CMP INBUF[SI],7BH
   JB NEXTSTEPLA
   JMP ERRORA

NEXTSTEPLA:   
   INC SI
   LOOP LOOPPAB
   MOV SI,0
   JMP NEXTSTEPAB
ERRORAB:
    CALL HUANHANG
    CALL XINGHAO
    MOV AH,9H
    MOV DX,OFFSET MESSAGE11
    INT 21H
    CALL XINGHAO
    JMP XUNHUAN
    
NEXTSTEPAB:    
  CALL HUANHANG
  CALL XUXIAN
  MOV AH,9H
  MOV DX,OFFSET MESSAGE2
  INT 21H
  CALL XUXIAN
  MOV BIAOJI,0

LOOPB: 
  MOV CX,20
  MOV SI,0
  MOV DI, BIAOJI
  MOV CL,INBUFLEN

;************************比较有效的字母****************************
  LOOPA:
  MOV AL,INBUF[SI]
  CMP AL,OUTLINE[DI]
  JNE NEXTA 
  INC SI
  INC DI
  DEC  CL
  JNZ  LOOPA
  
 ;************************其余的和空格比较*************************
  MOV CX,20
  SUB CL,INBUFLEN
 LOOPM:
  CMP OUTLINE[DI],20H
  JNE NEXTA
  INC DI
  LOOP LOOPM
  INC BH
  MOV CX,33
  MOV SI,BIAOJI

;**********************输出要查找的名字及电话号码******************
LOOPC:
  MOV DL,OUTLINE[SI]
  MOV AH,02H
  INT 21H
  INC SI
  LOOP LOOPC
  CALL HUANHANG
  CALL XUXIAN
NEXTA:
  ADD BIAOJI,33
  DEC BL
  JNZ LOOPB

;********************检测是否存在要查询的电话号码********************
  CMP BH,0
  JNE NEXTP
  CALL HUANHANG
  MOV AH,9H
  MOV DX,OFFSET MESSAGE8
  INT 21H
NEXTP:  
  POP BX
  POP AX
  POP DI 
  POP SI
  RET
SEARCH ENDP

;***********************进行选择操作的过程***************************
XUANXIANG PROC NEAR
NEXTL:
  CALL XINGHAO
  MOV AH,9H
  MOV DX,OFFSET MESSAGE5
  INT 21H
  MOV AH,9H
  MOV DX,OFFSET MESSAGE6
  INT 21H
  CALL XINGHAO
  MOV AH,01H
  INT 21H
  CMP AL,31H
  JNE EXIT1
  JMP  FIRST
  EXIT1:CMP AL,32H
  JNE EXIT2
  JMP  SECOND
  EXIT2:CMP AL,33H
  JNE EXIT3
  JMP  THIRD
  EXIT3:CMP AL,34H
  JNE EXIT
  JMP  FOUR
 EXIT: CALL HUANHANG
  CALL XINGHAO
  MOV AH,9H
  MOV DX,OFFSET MESSAGE9
  INT 21H
  CALL XINGHAO
  JMP NEXTL
  RET
XUANXIANG ENDP

;******************************输出*********************************
XINGHAO PROC NEAR
    MOV AH,9H
    MOV DX,OFFSET MESSAGE4
    INT 21H
    RET 
XINGHAO ENDP

;******************************输出*********************************
XUXIAN PROC NEAR
    MOV AH,9H
    MOV DX,OFFSET MESSAGE10
    INT 21H
    RET 
XUXIAN ENDP

CODES ENDS
      END START
