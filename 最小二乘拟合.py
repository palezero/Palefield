#coding=utf-8
from matplotlib import pyplot as plt
import numpy as np
x=[1,2,3,4,5,6,7,8]#samplepoint_x
y=[2,4,6,3,8,9,12,15]#samplepoint_y
len1=len(x)
len2=len(y)
if(len1!=len2):
    print 'error'
else:
    leng=len1
    x_y=[float(ii) for ii in [x[i]*y[i] for i in range(leng)]]
    x_x=[float(ii) for ii in [x[i]*x[i] for i in range(leng)]]
    y_y=[float(ii) for ii in [y[i]*y[i] for i in range(leng)]]
    k=(leng*sum(x_y)-sum(x)*sum(y))/(leng*sum(x_x)-sum(x)*sum(x))
    b=(sum(x_x)*sum(y)-sum(x)*sum(x_y))/(leng*sum(x_x)-sum(x)*sum(x))
    plt.plot(x,y,'o')
    x_area=np.linspace(min(x),max(x),2)
    plt.plot(x_area,x_area*k+b)
    plt.show()
