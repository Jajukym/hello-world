#libraries
import sys; print(sys.version)
import xml.sax
from xlwt import Workbook, Formula, easyxf #create a workbook
import xlwt #write to an existing workbook
import xlrd #read an existing workbook

#EQF1259 App Procedure read

a = xlrd.open_workbook("./EQF1259 App Procedures.xlsx") #open the created excel file

b = a.sheet_by_index(0) #select first sheet
c = a.sheet_by_index(1)
d = a.sheet_by_index(2)

#TracVia Web Procedure create
wb = Workbook() #create a workbook
sheet1 = wb.add_sheet('Sheet1') #Procedure
sheet2 = wb.add_sheet('Sheet2') #Revision
style0 = easyxf('pattern: pattern solid,fore_colour red;') #cell styling
sheet2.col(2).width = 7000 #column width
sheet2.write(0,0,('REV 0'), style0)
sheet2.write(0,1,'20171116')
sheet2.write(0,2,'Preliminary')
sheet2.write(0,3,'ID_0')


#Parse .xml file
class Device( xml.sax.ContentHandler ):
   def __init__(self):
      self.CurrentData = ""
      self.consolePartNumber = ""
      self.mcuChipName = ""
      self.equipmentType = ""
      self.systemUnitType = ""
      self.BuildModelString = "" 
      self.TypeName = ""
      #self.Enabled = ""
	  
	  
	  
   # Call when an element starts
   def startElement(self, tag, attributes):
      self.CurrentData = tag
      if tag == "Config":
         print "*************Part Inspection Procedure*************\n"
      #elif tag == "FeatureItem":
         #print "*************Feature Items**************\n"
         #feature = attributes["xsi:type"]
         #print "Feature:", feature
		 
		 
		 
    # Call when a character is read
   def characters(self, content):
      if self.CurrentData == "consolePartNumber":
         self.consolePartNumber = content
      elif self.CurrentData == "mcuChipName":
         self.mcuChipName = content
      elif self.CurrentData == "equipmentType":
         self.equipmentType = content
      elif self.CurrentData == "systemUnitType":
         self.systemUnitType = content
      elif self.CurrentData == "BuildModelString":
         self.BuildModelString = content
      elif self.CurrentData == "TypeName":
         self.TypeName = content
      #elif self.CurrentData == "Enabled":
         #self.Enabled = content
		 
         
   # Call when an elements ends
   def endElement(self, tag):
      if self.CurrentData == "consolePartNumber":
         print "Part Number:", self.consolePartNumber, "\n"
      elif self.CurrentData == "mcuChipName":
         print "Processor:", self.mcuChipName, "\n"
      elif self.CurrentData == "systemUnitType":
         print "Unit Measure:", self.systemUnitType, "\n"
      elif self.CurrentData == "equipmentType":
         print "Product:", self.equipmentType, "\n"
      elif self.CurrentData == "BuildModelString":
         print "Part Name:", self.BuildModelString, "\n"
      elif self.CurrentData == "TypeName":
         print "Display:", self.TypeName, "\n"
      #elif self.CurrentData == "Enabled":
         #print "Enabled:", self.Enabled, "\n"
      self.CurrentData = ""

  
  
  
if ( __name__ == "__main__"):

   # enter the .xml file name including ".xml"
   filename = raw_input("Enter File Name:\n")
      
   # create an XMLReader
   parser = xml.sax.make_parser()
   
   # turn off namepsaces
   parser.setFeature(xml.sax.handler.feature_namespaces, 0)

   
   
   
   # override the default ContextHandler
   Handler = Device()
   parser.setContentHandler( Handler )
   
   parser.parse(filename)

#e = b.cell(0,0).value
f = c.cell(0,1).value #header of column
g = c.cell(1,1).value #get one cell value preferred method!!!
h = d.cell(1,1).value
#dt = xlrd.xdate_as_tuple(d,b.datemode) #convert a date in cell
print f
print h
print g

#print sum(a) #and their sum
#print dt



sheet1.write(0,13,f)
sheet1.write(2,13,h+g) #writing to cells





#for i in xrange(10): #function of writing 1-10 in column 0 sheet2
    #sheet2.write(i,0,i)
#sheet2.write(10,0,Formula('SUM(A1:A10)'),style2) #adding column 0 and adding the style2

wb.save('TrackVia Web Procedures.xls') #save created workbook

#Remove me when done with project
#End = raw_input()
