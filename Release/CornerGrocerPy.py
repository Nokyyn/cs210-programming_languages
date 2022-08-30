import re
import string

def ReadSalesData():  # reads sales data from input .txt file and return a dictionary of item occurences
    f = open("CornerGrocerInputFile.txt")
    lines = f.read().splitlines()
    f.close()
    items = {}

    for ln in lines:
        if ln not in items.keys():
            items[ln] = 1
        else:
            items[ln] += 1

    return items
    
def PrintDailySales():  # print the full list of all items sold for the day
    items = ReadSalesData()  # could not, for some reason, get a global items dictionary to update correctly, circumvented through repeated ReadSalesData() calls

    for item in items:
        print("{}: {}".format(item, items[item]))  # print each item and its number of occurences

def GetItemSales(v):  # receive an item to search for, and return number of sales
    items = ReadSalesData()

    if v in items:
       return items[v]
    else:
        return 0


def WriteSalesData():  # write sales data to new file in the format "itemName itemCount" per line
    f = open("frequency.dat", 'w')

    items = ReadSalesData()

    for item in items:
        f.write("{} {}\n".format(item, str(items[item])))

    f.close()