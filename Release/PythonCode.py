FILENAME = "items.txt" #assigns FILENAME to items.txt

def readFile(FILENAME): 
    '''
    Gets the list of lines read in from the file in raw form.
    @param - the filename to read in (must be in same directory as the Source.cpp!)
    @return - the list of lines
    '''
    
    lines = None
    
    #opens FILENAME to read.
    with open(FILENAME, "r") as file:
        lines = file.readlines()

    return lines;


def getInventory():
    '''
    Get the inventory read in from the file.
    @return - dictionary of inventory in the form {item : frequency}
    '''
    
    # Dictionary of {item : frequency} 
    inventory = {}
    
    #reading FILENAME declared previously
    items = readFile(FILENAME)

    # Loop through the list of items
    for item in items:
        
        # Remove the newline character at end of line. 
        # SEE https://www.delftstack.com/howto/python/python-remove-newline-from-string/
        #using the .strip feature to remove the newline character.
        item = item.strip() 

        # Update existing frequency; otherwise add item to dictionary
        if item in inventory:
            inventory[item] += 1; # accumulate to the dictionary item
        else:
            inventory[item] = 1;
    #return inventory after it has been iterated from loop.        
    return inventory;

    
def determineInventory():
    #call getInventory func and assign it to inventory
    inventory = getInventory()

    #loops through the inventory dict and prints item followed by freq
    for item, freq in inventory.items():
        print(item, freq)

    # loop through the dictionary's keys and values
    # SEE https://stackoverflow.com/questions/3294889/iterating-over-dictionaries-using-for-loops
    # print the output


def determineFrequency(freq):
    # Get the inventory
    #inventory = getInventory.get(freq);
    
    # Access the item from the inventory
    # SEE https://www.w3schools.com/python/python_dictionaries_access.asp
    
    #simply return getInventory func and use .get to retern freq var.
    return getInventory().get(freq)
    

def output():
    # Very similar to determineInventory 
    # Loop through the dictionary and write to the frequency.dat file
    # SEE https://www.w3schools.com/python/python_file_write.asp

    #we open open frequency.dat file and w to write to it.
    f = open("frequency.dat", "w")
    #We call the getInventory func and assign it to inventory
    inventory = getInventory()
    #for loops through inventory dict and writes to frequency.dat
    for item, freq in inventory.items():
        #writes item
        f.write(item)
        #writes a space between item and freq
        f.write(' ')
        #because freq is an int var '%d' is used as a placeholder as we write freq then finish w/ a new line for next loop iteration.
        f.write('%d' % freq + '\n')


    