import copy
import sys
import re


rule1=r'^[arc]".+"(?:(?:\((?:\d+|-\d+),(?:\d+|-\d+)\))*)$'#judge whether the input is inputed according to right structure
compiledRule1=re.compile(rule1)
#r1=compiledRule1.match(inp)

rule2=r'^[arc]".+"$'#judge whether 'a'/'r'/'c' command only has name without no points
compiledRule2=re.compile(rule2)
# r2=compiledRule2.match(inp)

rule3=r'^[arc]".+"(?:\((?:\d+|-\d+),(?:\d+|-\d+)\))$'#judge whether 'a'/'r'/'c' command only has name and one point
compiledRule3=re.compile(rule3)
#r3=compiledRule3.match(inp)

# test whether one input is legal
def inputTest(inp):                       
    inp=re.sub( r' ','' ,inp) #remove " "
    if inp=='':
        errStr="Error: the input should not be blank"+'\n'
        sys.stderr.write(errStr)
        return 0
    if inp[0]=='g' and len(inp)!=1:
        errStr="Error:'g' command should not be followed other characters"+'\n'
	sys.stderr.write(errStr)
	return 0
    elif inp[0]=='g' and len(inp)==1:
        return 1		
    else:
            
	r1=compiledRule1.match(inp)
	if r1==None:
            errStr="Error: the input is invalid"+'\n'
            sys.stderr.write(errStr)
	    return 0
	else:
	    r2=compiledRule2.match(inp) 
	    r3=compiledRule3.match(inp)
	    if r2!=None:
                    
		if inp[0]=='a' or inp[0]=='c':
                    errStr="Error:'a' or 'c' specified for a street that needs at least two points"+'\n'
		    sys.stderr.write(errStr)
		else:
		    return 1
	    elif r3!=None:
		if inp[0]=='r':
                    errStr='Error:'r' specified for a street to be removed does not need and coordinates'+'\n'
		    sys.stderr.write(errStr)
		    return 0
		else:
		    errStr='Error: Incomplete coordinates in a street,no end point'+'\n'
		    sys.stderr.write(errStr)
		    return 0
	    else:
                    #print inp
		return 1

rule4=r'(?<=").+(?=")' #find the street's name
compiledRule4=re.compile(rule4)
rule5=r'(?<=\()(?:\d+|-\d+)|(?:\d+|-\d+)(?=\))'#find the coordinate
compiledRule5=re.compile(rule5)

rule6=r'(())'

def storeInput(inp):
    inpTem=[]
    inpCom=re.sub( r' ','' ,inp) #remove " "
    inpTem.append(inpCom[0])
    if inpCom[0]=='g':
        return inpTem
    else:
        r4=compiledRule4.findall(inpCom)
        name=r4
        inpTem.append(name[0])
        
        if inpCom[0]=='a'or inpCom[0]=='c':
            r5=compiledRule5.findall(inpCom)
            pointTem=r5
            flag=0
            for i in pointTem:
                if flag==0:
                    temP=float(i)
                    flag+=1
                else:
                    inpTem.append((temP,float(i)))
                    flag=0
            return inpTem
        else:
            return inpTem


def same(cacInp,inputStr):
    for i in range(0,len(cacInp)):
        if cacInp[i][1]==inputStr[1]:
            return i          
    return 'false'
    
#judge the content the cacInpA
def addNum(inp):
    n=0
    for i in inp:
        if i[0]=='a':
            n+=1
    return n

cacInpA=[] #globalstore the streets to caculate 
def inputCommand():
    flagInp=0 #loop flag 
    flagG=0 #judge the whether 'g' is a valide input 
       
    flagA=0 #judge the number of different 'a' 
    flagC=0 #judge 'c' has been inputed 1 time 
    flagR=0; #judge 'c' has been inputed 1 time
    
    while flagInp==0:
        inputStr=raw_input() ##raw_input can return string            
        test=inputTest(inputStr)
        grap=addNum(cacInpA)
        if grap<2:
            flagG=0
        else:
            flagG=1
        if grap==0:
            flagA=0
        else:
            flagA=1
        if test==1:
            inputStr=storeInput(inputStr)
            if inputStr[0]=='g' and flagG==0:
                errStr="Error: You must input at lest two different 'a' commands before input 'g'"+'\n'
                sys.stderr.write(errStr)
                continue
            elif inputStr[0]=='g' and flagG==1:                
                break
            elif inputStr[0]=='a':
                if same(cacInpA,inputStr)!='false' and same(cacInpA,inputStr)!=None:
                    errStr='Error: This street has been existed, please input again'+'\n'
                    sys.stderr.write(errStr)
                    continue
                
                cacInpA.append(inputStr)
                
                
            elif inputStr[0]=='c':
                if flagA==0:
                    errStr="Error:You must input 'c' befor you have inputed at least one 'a'"+'\n'
                    sys.stderr.write(errStr)
                    continue
                else:               

                    flagCa=same(cacInpA,inputStr)
                    if flagCa=='false':
                        errStr="Error: This street does not exist"+'\n'
                        sys.stderr.write(errStr)
                        continue
                    else:
                        inputStr[0]='a'
                        cacInpA[flagCa]=inputStr
 
            elif inputStr[0]=='r':
                if flagA==0:
                    errStr="Error:You must input 'r' befor you have inputed at least one 'a'"+'\n'
                    sys.stderr.write(errStr)
                    continue
                else:
                    flagRa=same(cacInpA,inputStr)   
                    if flagRa=='false':
                        errStr="Error: This street does not exist"+'\n'
                        sys.stderr.write(errStr)
                        continue
                    else:
                        del cacInpA[flagRa]

    return cacInpA     

             
def parallel(s1Ver1,s1Ver2,s2Ver1,s2Ver2): #s1Ver1=(1,2) s1Ver1[0]=1 s1Ver1[1]=2
    vec1=[s1Ver1[0]-s1Ver2[0],s1Ver1[1]-s1Ver2[1]]
    vec2=[s2Ver1[0]-s2Ver2[0],s2Ver1[1]-s2Ver2[1]]                            
    if abs(vec1[0]*vec2[1]-vec2[0]*vec1[1])<0.0000001:
        for i in [s1Ver1,s1Ver2]:
            for j in [s2Ver1,s2Ver2]:
                if i[0]==j[0] and i[1]==j[1]:
                    return (1,(i[0],i[1])) #if 1, parallerl
        return (1,0)
    else:
        for i in [s1Ver1,s1Ver2]:
            for j in [s2Ver1,s2Ver2]:
                if i[0]==j[0] and i[1]==j[1]:
                    return (0,(i[0],i[1])) #if 1, parallerl
        return (0,0) #if 0, not parallerl
#determine whether the intersection is in the two edgess
def inOrOut(x,y,s1Ver1,s1Ver2,s2Ver1,s2Ver2):
    if x!=s1Ver1[0]:
        temp1=(x-s1Ver1[0])*(x-s1Ver2[0])
    else:
        temp1=(y-s1Ver1[1])*(y-s1Ver2[1])
    if x!=s2Ver1[0]:
        temp2=(x-s2Ver1[0])*(x-s2Ver2[0])
    else:
        temp2=(y-s2Ver1[1])*(y-s2Ver2[1])
    if temp1<=0 and temp2<=0:
        return 1
    else:
        return 0
    
def intersection(s1Ver1,s1Ver2,s2Ver1,s2Ver2):
    vec1=[s2Ver1[0]-s1Ver1[0],s2Ver1[1]-s1Ver1[1]]
    vec2=[s2Ver2[0]-s1Ver1[0],s2Ver2[1]-s1Ver1[1]]
    area1=vec1[0]*vec2[1]-vec1[1]*vec2[0] #acd
    if area1==0:     
        temp1=inOrOut(s1Ver1[0],s1Ver1[1],s1Ver1,s1Ver2,s2Ver1,s2Ver2)
        if temp1==1:
            interTow=s1Ver1
            return interTow
        else:
            return 0 
    vec1=[s2Ver1[0]-s1Ver2[0],s2Ver1[1]-s1Ver2[1]]
    vec2=[s2Ver2[0]-s1Ver2[0],s2Ver2[1]-s1Ver2[1]]
    area2=vec1[0]*vec2[1]-vec1[1]*vec2[0] #cdb
    if area2==0:
        temp2=inOrOut(s1Ver2[0],s1Ver2[1],s1Ver1,s1Ver2,s2Ver1,s2Ver2)
        if temp2==1:
            interTow=s1Ver2
            return interTow
        else:
            return 0       
    flag=area1*area2
    if flag<0:
        vec1=[s1Ver1[0]-s2Ver1[0],s1Ver1[1]-s2Ver1[1]]
        vec2=[s1Ver2[0]-s2Ver1[0],s1Ver2[1]-s2Ver1[1]]
        area3=vec1[0]*vec2[1]-vec1[1]*vec2[0] #abc
        if area3==0:
            temp3=inOrOut(s2Ver1[0],s2Ver1[1],s1Ver1,s1Ver2,s2Ver1,s2Ver2)
            if temp3==1:
                interTow=s2Ver1
                return interTow
            else:
                return 0  
        vec1=[s1Ver1[0]-s2Ver2[0],s1Ver1[1]-s2Ver2[1]]
        vec2=[s1Ver2[0]-s2Ver2[0],s1Ver2[1]-s2Ver2[1]]
        area4=vec1[0]*vec2[1]-vec1[1]*vec2[0] #abd
        if area4==0:
            temp4=inOrOut(s2Ver2[0],s2Ver2[1],s1Ver1,s1Ver2,s2Ver1,s2Ver2)
            if temp4==1:
                interTow=s2Ver2
                return interTow
            else:
                return 0            
        flag=area3*area4
        if flag<0:
            #caculate the coordinate of the intersection
            k=area1/(area4-area3)
            dx=k*(s1Ver2[0]-s1Ver1[0])
            dy=k*(s1Ver2[1]-s1Ver1[1])
            x=s1Ver1[0]+dx
            y=s1Ver1[1]+dy
            temp5=inOrOut(x,y,s1Ver1,s1Ver2,s2Ver1,s2Ver2)
            if temp5==1:
                interTow=(x,y)
                return interTow
            else:
                return 0
        else:
            return 0
    else:
        return 0

    

def repeat(rep,ver):
    for r in rep:        
        if (abs(ver[1]-r[1][1])<0.01) and (abs(ver[0]-r[1][0])<0.01):
            return 1    
    return 0
##### branch function  #####
#test two whether two vertexes are the same one and return the vertexe
def exist (rep,ver):
    for r in rep:
        if (abs(ver[1]-rep[r][1])<0.01) and (abs(ver[0]-rep[r][0])<0.01):
            return [r,rep[r]]
    return 0

def getVec(cacInpA):
    result=[]
    cacInt={} #store all vertexes  cacInt={1:(1,2),2:(3,4)}
    segTwo={}
    flagInt=0
    n=1 #number the vertexes
    flagIn=0
    flagExi=0
    flagTwo=0
    rep=[] #store the intersections one fixed street for judge whether the new caculated intersection or vertex has existed,if true:drop them,if not add
    strInt={} #store the vertexes of every streets strInt={'str1':{1:(1,2),2:(3,4)},'str2':{(1,2),2:(3,4),3:(5,9),..}}
    for s in range(0,len(cacInpA)):
        #print cacInpA[s][1],"!!!!!!!!!!!!!!!!!"
        strInt[cacInpA[s][1]]={}
        segTwo[cacInpA[s][1]]=[]
        #print strInt,'()()()()()()()()('
    
    for i in range(0,len(cacInpA)):
        cacTem=copy.copy(cacInpA)
        cacTem.pop(i)
        for j in range(0,len(cacTem)):
            inpA=cacInpA[i][2:]   #A street's name is cacInpA[i][1]   
            inpB=cacTem[j][2:] #B street's name is cacTem[j][1]
            for A in range(0,len(inpA)-1):
                for B in range(0,len(inpB)-1):
                    flagPar=parallel(inpA[A],inpA[A+1],inpB[B],inpB[B+1])
                    if  flagPar[1]==0:
                        if flagPar[0]==1:
                            continue
                        else:
                            flagVer=intersection(inpA[A],inpA[A+1],inpB[B],inpB[B+1])
                            if flagVer==0:
                                continue
                    else:
                        flagVer=flagPar[1]
                        
                    flagIn=1
                             
                    if flagTwo==0:
                        segTwo[cacInpA[i][1]].append([inpA[A],inpA[A+1]])
                        falgTwo=1
                               
                    flagEqu=repeat(rep,inpA[A])
                    flagExi=exist(cacInt,inpA[A])
                    if (flagEqu==0 or flagEqu==None) and flagExi==0:
                        strInt[cacInpA[i][1]][n]=inpA[A]
                        cacInt[n]=inpA[A]
                        rep.append([n,inpA[A]])
                        n+=1
                    elif (flagEqu==0 or flagEqu==None) and flagExi!=0:
                        strInt[cacInpA[i][1]][flagExi[0]]=flagExi[1]
                        rep.append([flagExi[0],flagExi[1]])

                    flagEqu=repeat(rep,inpA[A+1])
                    flagExi=exist(cacInt,inpA[A+1])
                    if (flagEqu==0 or flagEqu==None) and flagExi==0:
                        strInt[cacInpA[i][1]][n]=inpA[A+1]
                        cacInt[n]=inpA[A+1]
                        rep.append([n,inpA[A+1]])
                        n+=1
                    elif(flagEqu==0 or flagEqu==None) and flagExi!=0:
                        strInt[cacInpA[i][1]][flagExi[0]]=flagExi[1]
                        rep.append([flagExi[0],flagExi[1]])     

                    flagEqu=repeat(rep,flagVer)
                    flagExi=exist(cacInt,flagVer)                           
                    if (flagEqu==0 or flagEqu==None) and flagExi==0:
                        strInt[cacInpA[i][1]][n]=flagVer
                        cacInt[n]=flagVer
                        rep.append([n,flagVer])
                        n+=1
                    elif(flagEqu==0 or flagEqu==None) and flagExi!=0:
                        strInt[cacInpA[i][1]][flagExi[0]]=flagExi[1]
                        rep.append([flagExi[0],flagExi[1]])
            if flagIn==1:
                flagTwo=0
                flagIn=0

                rep=[]
    result.append(strInt)
    result.append(cacInt)
    result.append(segTwo)
    return result
def deleteDuplicate(list):
    resultList=[]
    for item in list:
        if not item in resultList:
            resultList.append(item)   
    return resultList
   
def vertexLine(segTwoFli,strInt):
    strEdgeTem={}
    strEdgeSum=[]
    temp=0
    for i in segTwoFli.keys():
        for j in segTwoFli[i]:
            for m in strInt[i].keys():   
                temp1=parallel(j[0],strInt[i][m],strInt[i][m],j[1])
                if temp1[0]==1:
                    temp2=(strInt[i][m][0]-j[0][0])*(strInt[i][m][0]-j[1][0])
                    temp3=(strInt[i][m][1]-j[0][1])*(strInt[i][m][1]-j[1][1])
                    if temp3<=0 and temp2<=0:
                        if j[0][0]==j[1][0] or j[0][1]==j[1][1]:
                            strEdgeTem[m]=int(strInt[i][m][0]+strInt[i][m][1])
                        else:
                            strEdgeTem[m]=int(strInt[i][m][0])
            temp=sorted(strEdgeTem.iteritems(),key=lambda d:d[1])
            strEdgeSum.append([temp])
            strEdgeTem={}
    return strEdgeSum
def edge(strEdgeSum):
    Tem=[]
    for i in range(0,len(strEdgeSum)):
       
        for j in strEdgeSum[i]:
            k=0
            for m in j:                           
                if k!=0:
                    strTem=(str(temKey),str(m[0]))
                    Tem.append(strTem)
                k=1
                temKey=m[0]
    return Tem
            
def outputFormat(cacInt):
    tempOut={}
    for i in cacInt.keys():
        if int(cacInt[i][0])-cacInt[i][0]!=0:
            temp1=cacInt[i][0]
        else:
            temp1=int(cacInt[i][0])
        if int(cacInt[i][1])-cacInt[i][1]!=0:
            temp2=cacInt[i][1]
        else:
            temp2=int(cacInt[i][1])
        tempOut[i]=(temp1,temp2)
    return tempOut

def output(strInt,cacInt,segTwo):
    segTwoFli={}
    for s in segTwo.keys():
        segTwoFli[s]=[]
    for i in segTwo.keys():
        segTwoFli[i]=deleteDuplicate(segTwo[i])         
    strEdgeSum=vertexLine(segTwoFli,strInt)
    sumEdge=edge(strEdgeSum)
    print "V %d" %(len(cacInt))
    sys.stdout.flush()
    edgeAll = "E {"
    k=0
    n=len(sumEdge)
 
    if n ==0:
        print "E {}"
	sys.stdout.flush()
    else:            
        for i in sumEdge:
            k+=1
            if k!=n:
                edgeAll = edgeAll + '<' + str(int(i[0])-1) + ',' + str(int(i[1])-1) + '>' + ','
            
            else:
                edgeAll = edgeAll + '<' + str(int(i[0])-1) + ',' + str(int(i[1])-1) + '>' + '}'
        print "%s" %(edgeAll)
        sys.stdout.flush()
while 1:
    actInput=inputCommand()
    result=getVec(actInput)  
    output(result[0],result[1],result[2])

              
                
                

       

   
    
 
