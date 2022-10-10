#Author: Nick Chandler
#Date: 1/15/2021
#Description: A1- Money Translator, gives proportional donation amounts

#Pseduocode
#UI Explanation -output
print("This is a program which calculates the proportional donation amount\nbetween a very wealthy person and you or an average person.\n")
#Networth of avg person input -entry
avgnet= int(input("Your or an avg. person's net worth. Use whole numbers and no commas: "))
#Name of Rich Donor -entry
richname= input("Enter the name of the person making the donation (not you): ")
#Multiplier explanation
print("*In this program there is a net worth multiplier for billions and millions,\nenter something like 123.4 for 123.4 billion.*")
#Net worth of donor -entry
richnet1= float(input(richname + " net worth: "))
#Net worth multiplier -entry
multiplier= input(richname+ " net worth multiplier, enter 'm'/'b' for millions/billions: ")
bn= "b" or "B"
mn= "m" or "M"
if multiplier==bn:
    richnet2= richnet1 * 1000000000
else:
    richnet2= richnet1 * 1000000
#Written out net worth -output
print("{:0,.2f}".format(float(richnet2)), "is", richname,"'s net worth.")
#Rich donation amount -entry
richdonate= float(input("Enter the donation amount: "))
# % of net worth and proportion calculation
rdprop= richdonate / richnet2
avgequal= rdprop * avgnet
#Proportional donation output
print("A $","{:0,.2f}".format(float(richdonate))," donation for someone with a net worth of: ","{:0,.2f}".format(float(richnet2)),"\n is the same as a $","{:0,.2f}".format(float(avgequal)),"donation for someone with a net worth of: $","{:0,.2f}".format(float(avgnet)),"!")

