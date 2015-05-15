#!/usr/bin/python
# -*- coding: utf-8 -*-

import xlrd
import  xdrlib ,sys,os


#excel字段类型
STRING_TYPE = 1
INT_TYPE = 2
FLOAT_TYPE = 3

#表类型
SHEET_TYPE_IGNORE = 1
SHEET_TYPE_ONLY_CHECK = 2
SHEET_TYPE_CHECK_AND_WRITE = 3


#数据类型集
VALUE_TYPE_MAP = {STRING_TYPE:"字符串类型",INT_TYPE:"int型类型",FLOAT_TYPE:"浮点型数据"}
#非法字符集
EALLY_CHAR_MAP = {"*":"*", " ":" ", "?":"?"}

#打开表格
def open_excel(file):
    try:
        data = xlrd.open_workbook(file)
        return data
    except Exception,e:
        print "错误 打开 %s 表格失败" %(file)

#检查每个表是否正确
def check_sheet(data,keyMap):
    table = data.sheets();
    for sheet in table:
        result = []
        if not check_analysis_sheet_name(sheet.name,result):
            return False
        try:
            type = int(result[1])
        except Exception,e:
            print "错误 %s 表类型错误" %(sheet.name,type)
            return False
        if type != SHEET_TYPE_IGNORE:
            try:
                if not check_english_name(result[2]):
                    print "错误 %s 表对应的英文名错误" %(sheet.name)
                    return False
            except Exception,e:
                print "错误 %s 表名字对应的英文名解析异常" %(sheet.name)
                return False
            if keyMap.has_key(result[2]):
                print "错误 %s 表名字 %s 重复 " %s(sheet.name,result[2])
                return False
            sheetKeyArr = []
            if not check_sheet_all_cols(sheet,sheetKeyArr):
                return False
            else:
                keyMap[result[2]] = sheetKeyArr
        print "检查 %s 表完成" %(sheet.name) 
    return True

        

#判断字符名字是否含有中文以及是否合法
def check_english_name(name):
    if not len(name):
        return False
    for char in name:
        if u'\u4e00' <= char <= u'\u9fff':
            return False
        elif EALLY_CHAR_MAP.has_key(char):
            return False
    return True

#检查表名格式
def check_analysis_sheet_name(name,result):
    sheetName = name
    tag = '_'

    for checkTime in range(1,3):
        posIndex = sheetName.find(tag)
        if posIndex == -1:
            print "错误 %s 的表名有问题" %(name)
            return False
        result.append(sheetName[:posIndex])
        sheetName = sheetName[posIndex+1:]
    result.append(sheetName)
    return True

#获得谋列的数据值得范围(目前只针对整形)
def get_sheet_col_range(rangeStr,dataType,rangeArr):
    if not len(rangeStr):
        return False

    range = rangeStr
    tag = '-'
    posIndex = range.find(tag)
    if posIndex == -1 or (posIndex == len(range)-1) or (posIndex == 0):
        return False
    if dataType == INT_TYPE:
        try:
            rangeArr[0] = int(range[:posIndex])
            rangeArr[1] = int(range[posIndex+1:])
        except Exception,e:
            print str(e)
            return False
    elif dataType == FLOAT_TYPE:
        try:
            rangeArr[0] = double(range[:posIndex-1])
            rangeArr[1] = double(range[posIndex+1:])
        except Exception,e:
            print str(e)
            return False
    return True


#检查每一列的数据类型和范围是否正确
def check_sheet_col_type(sheet,col,sheetKeyArr):
    if col >= sheet.ncols:
        print "错误 %s 访问列数越界 %d" %(sheet.name,col)
        return False

    colArry = sheet.col_values(col)
    if len(colArry) <= 4:
        print "错误 %s 第 %d 列 的行数错误" %(sheet.name,col)
        return False
    if not check_english_name(colArry[1]):
        print "错误 %s 第 %d 列 的英文名字 %s 错误" %(sheet.name,col,colArry[1])
        return False

    dataType = int(colArry[2])
    if not VALUE_TYPE_MAP.has_key(dataType):
        print "错误 %s 第 %d 列 的数据类型 %d 非法" %(sheet.name,col,dataType)
        return False
    
    rangeArr = [0,0]
    checkFlag = False

    if dataType != 1:
        checkFlag = True
    if checkFlag and not get_sheet_col_range(colArry[3],dataType,rangeArr):
        print "错误 %s 第 %d 列 的数据范围区域非法" %(sheet.name,col)
        return False

    for index in range(4,len(colArry)):
        if checkFlag:
            if dataType == INT_TYPE:
                try:
                    if (int(colArry[index]) < rangeArr[0]) or (int(colArry[index]) > rangeArr[1]):
                        print "错误 %s 第 %d 列 第 %d 行 的数据值 %d 超出范围" %(sheet.name,col,index,int(colArry[index]))
                        return False
                except Exception,e:
                    print "错误 %s 第 %d 列 第 %d 行 的数据值类型不对" %(sheet.name,col,index)
                    return False
            elif dataType == FLOAT_TYPE:
                try:
                    if (float(colArry[index]) < rangeArr[0]) or (float(colArry[index]) > rangeArr[1]):
                        print "错误 %s 第 %d 列 第 %d 行 的数据值 %d 超出范围" %s(sheet.name,col,index,int(colArry[index]))
                        return False
                except Exception,e:
                    print "错误 %s 第 %d 列 第 %d 行 的数据值类型不对" %(sheet.name,col,index)
                    return False
            else:
                print "错误 %s 第 %d 列 的数据类型不对:" %s(sheet.name,col)
                return False
    sheetKeyArr.append(colArry[1])
    return True


#检查所有列的数据类型和范围是否正确 
def check_sheet_all_cols(sheet,sheetKeyArr):
    rowNum = sheet.nrows  
    colNum = sheet.ncols
    if not (rowNum and colNum):
        print "错误 %s 的行或者列为空" %(sheet.name)
        return False
    for col in range(0,colNum):
        if not check_sheet_col_type(sheet,col,sheetKeyArr):
            return False
    return True


#生成xml的声明部分
def write_xml_declaration():
    xmlCode = "<?xml version='1.0' encoding='UTF-8'?>\n"
    return xmlCode


#生成xmlsheet节点中的每一个元素
def write_xml_row(sheet,xmlCode,keyArr):
    result =[False,xmlCode]
    if sheet.nrows <= 4:
        print  "错误 %s 表中无任何数据" %(sheet.name)
        return result
    for colIndex in range(4,sheet.nrows):
        colArr = sheet.row_values(colIndex)
        for index in range(0,len(colArr)):
            xmlCode += "\t\t"
            keyName = keyArr[index]
            keyValue = colArr[index]
            xmlCode += "<%s>" %(keyName)
            xmlCode += str(keyValue)
            xmlCode += "</%s>" %(keyName)
            xmlCode += "\n"
    result[0] = True
    result[1] = xmlCode
    return result
     



#生成xml中的sheet部分
def write_xml_sheet_node(sheet,xmlCode,keyMap):
    resultCode = [False,xmlCode]
    result = []
    if not check_analysis_sheet_name(sheet.name,result):
        return False
    try:
        type = int(result[1])
    except Exception,e:
        print "错误 %s 表类型错误" %(sheet.name,type)
        return resultCode 
    if type == SHEET_TYPE_CHECK_AND_WRITE:
        try:
            if not check_english_name(result[2]):
                print "错误 %s 表对应的英文名错误" %(sheet.name)
                return resultCode 
        except Exception,e:
            print "错误 %s 表名字对应的英文名解析异常" %(sheet.name)
            return resultCode 
        if not keyMap.has_key(result[2]):
            print "错误 %s 表没有对应的字段" %s(sheet.name)
            return resultCode 
        keySheetName = result[2]
        
        xmlCode += "\t"
        xmlCode += "<%s>" %(keySheetName)
        xmlCode += "\n"

        result_Code =  write_xml_row(sheet,xmlCode,keyMap[result[2]])
        xmlCode = result_Code[1]
       
        xmlCode += "\t"
        xmlCode += "</%s>" %(keySheetName)
        xmlCode += "\n"

        resultCode[0] = True
        resultCode[1] = xmlCode
        print "生成 %s 表节点完成" %(sheet.name) 
    return resultCode


    

#生成xml的剩余部分
def write_xml_root(data,keyMap):
    xmlCode = "\n"
    xmlCode += "<root>\n"
    
    table = data.sheets();
    for sheet in table:
        result = write_xml_sheet_node(sheet,xmlCode,keyMap)
        xmlCode = result[1]
    xmlCode += "</root>"
    return xmlCode


def main():
    reload(sys)  
    sys.setdefaultencoding('utf8')
    
    keyMap = {}
    data = open_excel("test.xlsx")
    if not check_sheet(data,keyMap):
        return
    
    xmlName = "test.xml"
    os.remove(xmlName)

    xml_fp = file(xmlName, "wb")
    
    xml_fp.write(write_xml_declaration())
    xml_fp.write(write_xml_root(data,keyMap))

    xml_fp.close()


if __name__=="__main__":
    main()
