#Serial between stm32 and linux on board
import serial.tools.list_ports
import time
import numpy as np
import sys
while(1):
    try:
        plist = list(serial.tools.list_ports.comports())  # serial struct
        if len(plist)<=0:
            print 'not found```'
        else:
            plist_0=list(plist[0])
            serialName=plist_0[0]
            serial_0=serial.Serial(serialName,9600,timeout=0.01)#default serialname,baudrate,timeout
            print 'Finding Serials:>>',serial_0.name
            while True:
                a=raw_input()
                if(len(a)>0):
                    a = list(a)
                    if((len(a)==4)and(a[0]=='0')and(a[1]=='x')):#HEXsend
                        if(len(a)==4):
                            temp1=(a[2]+a[3])
                            serial_0.write(temp1.decode("hex"))
                            time.sleep(0.01)
                            temp=serial_0.read()
                            print ('0x%s')%temp.encode("hex")

                    else:
                        #if(len(a)==1):#charsend
                        for i in a:
                            serial_0.write(i.encode("utf-8"))
                        print serial_0.read(len(a)).decode("utf-8")

    except(serial.serialutil.SerialException)://During offline
        while(1):
             try:
                list(serial.tools.list_ports.comports())
             except(serial.serialutil.SerialException):
                 print len(plist[0])
             else:
                 print "Stm32 is rebooting..."
                 break

