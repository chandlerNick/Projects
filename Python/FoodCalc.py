#Author: Nick Chandler
#Date: 2/28/2021
#Description: A5 Food tracker using TKinter to prompt dialogue boxes. Also with the ability to close and open the program multiple times before calculating the total counts for each data category.
#Note: This will create two files, one which holds food items and one which holds records

def main():
    """ This is the main function, contains the basic program script, calling other functions
    """
    
    #explain that calculating should be done only at the end of the day b/c it wipes the file.
    messagebox.showinfo("Information", "Calculating should only be done when all data is entered for the day!")
    #prompt for calculation or addition of food items (Y/N message)
    answer = messagebox.askyesno("Question", "Click [Yes] to calculate. Click [No] to add more items (up to 30)!")
    if answer == True:
        print("calc")
        day_calculate()
        
    elif answer == False:
        print("add") 
        food_entry = item_add() # entry function
        #Writes dictionary (new or updated) to food items file
        f= open('fooditems.txt', 'w')
        json.dump(food_entry, f)
        f.close()

#IF ADDITION OF ITEMS
def item_add():
    """ This function adds items to the file named 'day_diet_calculations'
        Preconditions: tkinter imported, count (variable seeing how many )
        Returns: a new or updated dictionary containing information about food items
    """
    
    item_add_window = tk.Tk()
    
    number_of_food = simpledialog.askinteger("Input", "Enter a number for how many food items you would like to enter!",
                                          parent = item_add_window, minvalue = 1, maxvalue = 30)
                               
    highest_entry = 0 # number of list entries (updated after reading the JSON load)
    ### DETERMINE WHETHER OR NOT FILE EXISTS
    fileexist = file_exist('fooditems.txt')
    
    #IF IT EXISTS, USE JSON LOAD TO GET DICTIONARY AS A VARIABLE
    if fileexist == True:
        #Run test, reading first line of file
        f = open('fooditems.txt', 'r')
        contenttest = f.readlines()
        f.close()
        print(contenttest)
        #create dictionary if file is empty
        if contenttest == []:
            one_entry = {}
            print("NO contents")
        #load contents ito a seperate dictionary if it exists
        else:
            with open('fooditems.txt', 'r') as read_file:
                x = json.load(read_file)
                for z in x.keys():
                    highest_entry += 1
            one_entry = {}
    
    ##IF FILE DOESNT EXIST
    elif fileexist == False:
        one_entry = {} #Dictionary to be saved with multiple food item entries
    
    ##TAKES USER INPUT FOR EACH CATEGORY OF MEASUREMENT
    for i in range(number_of_food):
        #integer dialogue saved to list (Calories)
        cal_entry = simpledialog.askinteger("Input", "How many calories in this item?")
        #integer dialogue saved to list (Protein- grams)
        prot_entry = simpledialog.askinteger("Input", "How many grams of protein in this item?")
        #integer dialogue saved to list (Carbs- grams)
        carb_entry = simpledialog.askinteger("Input", "How many grams of carbohydrate in this item?")
        #integer dialogue saved to list (Fat- grams)
        fat_entry = simpledialog.askinteger("Input", "How many grams of fat in this item?")
        
        one_entry['li'+str(i + highest_entry)] = [cal_entry, prot_entry, carb_entry, fat_entry] #Saves the data to a list within the dictionary

    #Adds dicitonaries if there are two
    if highest_entry > 0:
        final_dictionary = {**x, **one_entry}
        return final_dictionary
    #returns just one if there is only one dictionary
    else:
        return one_entry
        
#IF CALCULATION:
def day_calculate():
    """ This file reads the 'fooditems' file and totals the numbers.
        Saves the calculations into 'records' file via writing.
        Preconditions: imported datetime, there is something in fooditems.txt to calculate, imported json
        
    """
    print("dope")
    #read the food items file
    f = open('fooditems.txt', 'r')
    data = json.load(f)
    f.close()
    
    #Calculates totals for each category
    tot_cals = 0
    tot_pro = 0
    tot_carbs = 0
    tot_fat = 0
    for i in data:
        x = data.get(i)
        tot_cals += x[0]
        tot_pro += x[1]
        tot_carbs += x[2]
        tot_fat += x[3]
    
    #Name dictionary after date in m/d/y format
    r = datetime.datetime.now()  
    name = r.strftime('%x')
    name = {}
    
    #add data to dictionary
    name['Date'] = r.strftime('%x')
    name['calories'] = tot_cals
    name['protein'] = tot_pro
    name['carbs'] = tot_carbs
    name['fat'] = tot_fat
    print(name)
    
    #check existence of records file
    existence = file_exist('records.txt')
    if existence == True:
        f = open('records.txt', 'a')
        name = str(name) + '\n'
        f.write(name)
        f.close()
    elif existence == False:
        f = open('records.txt', 'w')
        name = str(name) + '\n'
        f.write(name)
        f.close()
    
    #wipe food items file
    f = open('fooditems.txt', 'w')
    f.close()

def file_exist(filename):
    """ Should look through the folder in which the program is written,
        determine if the file exists
        Preconditions: os imported
        Returns: a boolean value for file existence (File existance)
    """
    #determine if file exists
    exist = os.path.isfile(filename)
    return exist

if __name__ == "__main__": #Use of a conditional
    import tkinter as tk
    from tkinter import simpledialog
    from tkinter import messagebox
    import os
    import json
    import datetime
    main()
