from itertools import product
from nis import cat
import os
from re import I
from shutil import which 
import os.path

#using a dictionary to display the main menu/file choices
file_choices = {"0": "Products", "1": "Customers", "2": "Order Details", "3": "Orders"}
menu = {"0.": "Display specific information","1.": "Add information","2.": "Delete information","3.":"Change information","4.": "List description & list price of all products","5.": "Search customers in a specific town", "6.": "Check order information by month", "7.": "Customer names for product code + specific month", "8.": "Value of best order for a product","9.": "Date of most valuable order ever","10.":"Quit"}

class Main:
    def __init__(self):
        print("Welcome to myware! Before using the program, please input the 4 files to be used!")
        self.products_filename = input("what is the product file: ")
        file_exists = os.path.exists(self.products_filename)
        while file_exists == False: #loop checking if file name entered exists in the directory
            self.products_filename = input("Please enter an existing file: ")
            file_exists = os.path.exists(self.products_filename)
        self.products = Products(self.products_filename) #each class stores the entire information of file as 2D dictionary

        self.customers_filename = input("What is the customer file: ")
        file_exists = os.path.exists(self.customers_filename)
        while file_exists == False:
            self.customers_filename = input("Please enter an existing file: ")
            file_exists = os.path.exists(self.customers_filename)
        self.customers = Customers(self.customers_filename)

        self.orderdetails_filename = input("What is the order detail file: ")
        file_exists = os.path.exists(self.orderdetails_filename)
        while file_exists == False:
            self.orderdetails_filename = input("Please enter an existing file: ")
            file_exists = os.path.exists(self.orderdetails_filename)
        self.orderdetails = OrderDetails(self.orderdetails_filename)
        
        self.orders_filename = input("what is the order file: ")
        file_exists = os.path.exists(self.orders_filename)
        while file_exists == False:
            self.orders_filename = input("Please enter an existing file: ")
            file_exists = os.path.exists(self.orders_filename)
        self.orders = Orders(self.orders_filename)
    
    def quit(self): #makes sure the information modified, added, or deleted reflects the same on the actual files after the program closes
        with open(self.products_filename, "w") as p:
            for i in self.products.items:
                mini = self.products.items[i]
                v = ""
                for j in mini:
                    val =   mini[j] + ',' 
                    v+=val
                v = v[:-1]+"\n" #in order to excluding the "," at the end
                p.write(v) #writes all the edited content back into the file
        with open(self.customers_filename, "w") as c:
            for i in self.customers.items:
                mini = self.customers.items[i]
                v = ""
                for j in mini:
                    val =   mini[j] + ',' 
                    v+=val
                v = v[:-1]+"\n"
                c.write(v)
        with open(self.orderdetails_filename, "w") as od:
            for i in self.orderdetails.items:
                mini = self.orderdetails.items[i]
                v = ""
                for j in mini:
                    val =   mini[j] + ',' 
                    v+=val
                v = v[:-1]+"\n"
                od.write(v)
        with open(self.orders_filename, "w") as o:
            for i in self.orders.items:
                mini = self.orders.items[i]
                v = ""
                for j in mini:
                    val =   mini[j] + ',' 
                    v+=val
                v = v[:-1]+"\n"
                o.write(v)
    
    def menu(self): #main menu
        flag = False
        option = ""
        while option != "10": #option 10 is to exit the program, once option = "10" def quit will be executed
            print("Here are the options:")
            for key, value in menu.items():
                print(key, value)
            option = input("Please choose an option: ")
            while (option.isdigit() == False) or int(option) < 0 or int(option) > 10: #checking if the option is valid
                if option.isdigit() == False: 
                    option = input("Please enter the number of the option: ") 
                elif int(option) < 0 or int(option) > 10:
                    option = input("Please enter an option that is available: ")
            if option == "0":
                print("Which file do you want to display?")
                for key, value in file_choices.items():
                    print(key, value)
                choose_file = input("Please choose the file: ")   
                if choose_file == "0":
                    choice = {"0": "Description", "1": "List Price", "2": "Quantity on Premises", "3" :"Reorder Level", "4": "Reorder Quantity", "5": "All", "6":"End"}
                    for k,v in choice.items():
                        print(k+". Display", v)
                    choicenum = input("Choose an option: ")
                    while (choicenum.isdigit() == False) or int(option) < 0 or int(option) > 6:
                        if choicenum.isdigit() == False:
                            choicenum = input("Please enter an existing option: ")
                        elif int(choicenum) > 6 or int(choicenum) < 0:
                            choicenum = input("Please enter an existing option: ")
                    while choicenum != "6":
                        product_code = input("Please enter a product code: ")
                        self.products.display_product_by_productcode(product_code, choicenum)
                        choicenum = input("Choose an option: ")
                elif choose_file == "1":
                    choice = {"0": "Customer Name", "1": "Street", "2": "Number", "3" :"Town", "4": "Potal code", "5": "Credit Limit", "6": "Current Balance", "7": "All", "8": " All Customers' Names", "9": "End"}
                    for k,v in choice.items():
                        print(k+". Display", v)
                    choicenum = input("Choose an option: ")
                    while (choicenum.isdigit() == False) or int(option) < 0 or int(option) > 8:
                        if choicenum.isdigit() == False:
                            choicenum = input("Please enter an existing option: ")
                        elif int(choicenum) > 8 or int(choicenum) < 0:
                            choicenum = input("Please enter an existing option: ")
                    if choicenum == "8":
                        self.customers.customer_names()
                    while choicenum != "9":
                        customer_code = input("Please enter a customer number: ")
                        self.customers.display_customer_by_customercode(customer_code, choicenum)
                        choicenum = input("Choose an option: ")
                elif choose_file == "2":
                    choice = {"0": "Product Code", "1": "Order Quantity", "2": "Order Price", "3" :"All", "4": "End"}
                    choicenum = input("Choose an option: ")
                    while (choicenum.isdigit() == False) or int(option) < 0 or int(option) > 4:
                        if choicenum.isdigit() == False:
                            choicenum = input("Please enter an existing option: ")
                        elif int(choicenum) > 4 or int(choicenum) < 0:
                            choicenum = input("Please enter an existing option: ")
                    while choicenum != "4":
                        order_number = input("Please enter an order number: ")
                        self.orderdetails.display_orderdetails_by_ordernumber(order_number, choicenum)
                        choicenum = input("Choose an option: ")
                elif choose_file == "3":
                    choice = {"0": "Order Date", "1": "Order Time", "2" :"All", "3": "End"}
                    for k,v in choice.items():
                        print(k+". Display", v)
                    choicenum = input("Choose an option: ")
                    while (choicenum.isdigit() == False) or int(option) < 0 or int(option) > 3:
                        if choicenum.isdigit() == False:
                            choicenum = input("Please enter an existing option: ")
                        elif int(choicenum) > 3 or int(choicenum) < 0:
                            choicenum = input("Please enter an existing option: ")
                    while choicenum != "3":
                        order_number = input("Please enter an order number: ")
                        customer_number = input("Please enter a customer number: ")
                        self.orders.display_ordersby_ordernumber(order_number, customer_number, choicenum)
                        choicenum = input("Choose an option: ")
            elif option == "1": 
                print("Which file do you want to add to?")
                for key, value in file_choices.items():
                    print(key, value)
                choose_file = input("Please choose the file: ")
                while (choose_file.isdigit() == False) or int(choose_file) < 0 or int(choose_file) > 3:
                    if choose_file.isdigit() == False:
                        choose_file = input("Please choose an existing option: ")
                    elif int(choose_file) > 3 or int(choose_file) < 0:
                        choicenum = input("Please choose an existing option: ")
                if choose_file == "0":
                    print('Enter the necessary information')
                    product_code = input("Product code: ")
                    description = input("Description: ")
                    list_price = input("List price: ")
                    qntyonpremises = input("Quantity on premises: ")
                    reorder_level = input("Reorder level: ")
                    reorder_qnty = input("Reorder quantity: ")
                    self.products.add_product(product_code, description, list_price, qntyonpremises, reorder_level, reorder_qnty)
                elif choose_file == "1":
                    print('Enter the necessary information')
                    customer_num = input("Customer number: ")
                    customner_name = input("Customer name: ")
                    street = input("Street: ")
                    number = input("Number: ")
                    town = input("Town: ")
                    postal_code = input("Postal code: ")
                    credit_limit = input("Credit limit: ")
                    curr_balance = input("Current balance: ")
                    self.customers.add_customer(customer_num, customner_name, street, number, town, postal_code, credit_limit, curr_balance) 
                elif choose_file == "2":
                    print('Enter the necessary information')
                    ordernum = input("Order number: ")
                    productcode = input("Produce code: ")
                    orderquantity = input("Order quantity: ")
                    orderprice = input("Order price: ")
                    self.orderdetails.add_orderitem(ordernum, productcode, orderquantity, orderprice) 
                elif choose_file == "3":
                    print('Enter the necessary information')
                    ordernum = input("Order number: ")
                    customer_num = input("Customer number: ")
                    orderdate = input("Order date: ")
                    ordertime = input("Order time: ")
                    self.orders.add_order(ordernum, customer_num, orderdate, ordertime) 
            elif option == "2":
                print("Select the file to enact the delete function")
                for key, value in file_choices.items():
                    print(key, value)
                choose_file = input("Please choose the file: ")
                while (choose_file.isdigit() == False) or int(choose_file) < 0 or int(choose_file) > 3:
                    if choose_file.isdigit() == False:
                        choose_file = input("Please choose an existing option: ")
                    elif int(choose_file) > 3 or int(choose_file) < 0:
                        choicenum = input("Please choose an existing option: ")
                if choose_file == "0":
                    productcode = input("Please enter the product code of the product you wish to delete: ")
                    self.products.del_product(productcode)
                elif choose_file == "1":
                    customernum = input("Please enter the customer number of the customer you wish to delete: ")
                    self.customers.del_customer(customernum)
                elif choose_file == "2":
                    ordernum = input("Please enter the order number of the order details you wish to delete: ")
                    self.orderdetails.del_orderdetails(ordernum)
                elif choose_file == "3":
                    ordernum = input("Please enter the order number of the order you wish to delete: ")
                    custnum = input("Please enter the customer number of the customer you wish to delete: ")
                    self.orders.del_orders(ordernum,custnum)
            elif option == "3":
                print("Select the file to enact the change function!")
                for key, value in file_choices.items():
                    print(key, value)
                choose_file = input("Please choose the file: ")
                while (choose_file.isdigit() == False) or int(choose_file) < 0 or int(choose_file) > 3:
                    if choose_file.isdigit() == False:
                        choose_file = input("Please choose an existing option: ")
                    elif int(choose_file) > 3 or int(choose_file) < 0:
                        choicenum = input("Please choose an existing option: ")
                if choose_file == "0":
                    productcode = input("Please enter the product code: ")
                    self.products.change_product(productcode)
                elif choose_file == "1":
                    custnum = input("Please enter the customer number: ")
                    self.customers.change_customer(custnum)
                elif choose_file == "2":
                    ordernum = input("Please enter the order number: ")
                    self.orderdetails.change_orderdetails(ordernum)
                elif choose_file == "3":
                    ordernum = input("Please enter the order number: ")
                    custnum = input("Please enter the customer number: ")
                    self.orders.change_orders(ordernum, custnum)
            elif option == "4":
                self.products.display_description_listprice()
            elif option == "5":
                town = input("Enter the town you want to search for: ")    
                self.customers.town(town)
            elif option == "6":
                month = input("You will be given the [product code, order quantity, order price, description] of all the orders that month!\nPlease enter the month in the format yyyy-mm: ")
                while len(month) != 7 or month.isalpha == True:
                    if len(month) != 7:
                        print("Please enter the date in the correct format!")
                        month = input("Please try again: ")
                    elif month.isalpha == True:
                        print("Please enter the date in the correct format!")
                        month = input("Please try again: ")
                ordernums = self.orders.find_ordersnumber_by_date(month)
                while ordernums == []: 
                    month = input("Please enter a date with orders: ")
                    ordernums = self.orders.find_ordersnumber_by_date(month)
                productnums = self.orderdetails.find_productcode_by_ordernum(ordernums)
                for i in range(len(productnums)):
                    productcode = productnums[i]["Product Code"]
                    description = self.products.find_descrip_by_productcode(productcode)
                    print(productcode,description,productnums[i]["Order Quantity"], productnums[i]["Order Price"])
            elif option == "7":
                print("All the customers who ordered the product during the entered month will be displayed")
                productcode = input("Enter the product code: ")
                date = input("Enter the date in the format yyyy-mm: ")
                ordernum = self.orderdetails.find_ordersnumber_by_month(productcode)
                while ordernum == []:
                    productcode = input("Enter an existing product code: ")
                    ordernum = self.orderdetails.find_ordersnumber_by_month(productcode)
                custnum = self.orders.find_ordersnumber_by_month(ordernum, date)
                while custnum == []:
                    date = input("Please enter a date(format yyyy-mm) in which the entered product was bought: ")
                    custnum = self.orders.find_ordersnumber_by_month(ordernum, date)
                self.customers.find_ordersnumber_by_month(custnum)
            elif option == "8":
                print("The entered product's best order value will be given!")
                best_order = input("Enter the name of the best product: ")
                productcode = self.products.bestorder(best_order)
                while productcode == []:
                    print("No such product has been found!")
                    best_order = input("Enter the name of the best product: ")
                    productcode = self.products.bestorder(best_order)
                print("This is the value of the best order of the product: ", self.orderdetails.best_order_productcode(productcode))
            elif option == "9":
                ordernum = self.orderdetails.date_most_valuable()  
                self.orders.max_val_order(ordernum)

        
class Products:
    def __init__(self, filename):
        self.items = {}
        rf = open(filename, 'r')
        for line in rf:
            info = line.split(",")
            if len(info) == 6:
                temp_producecode_products = (info[0].strip())
                self.items[temp_producecode_products] = {"Product Code": info[0].strip(), "Description": info[1].strip(), "List Price": info[2].strip(), "Quantity on Premises": info[3].strip(),"Reorder Level": info[4].strip(), "Reorder Quantity": info[5].strip()}
        if list(self.items.keys())[0] == "ProductCode":
            self.items.pop("ProductCode")
            

    def display_product_by_productcode(self, code, choicenum): #displays information about the product which the user wishes to see
        choice = {"0": "Description", "1": "List Price", "2": "Quantity on Premises", "3" :"Reorder Level", "4": "Reorder Quantity", "5": "Display all", "6": "Quit"}
        if code in self.items:
            if 0 <= int(choicenum) < 5:
                choicename = choice[choicenum]
                product = self.items[code]
                print("Here is the product's " + choicename +":", product[choicename]) 
            elif choicenum == "5":
                print(self.items[code])
        else: 
            print("The product code doesn't exist!")
    
    def display_description_listprice(self): #displays the product description and list price
        for i in self.items:
            print(self.items[i]["Description"],self.items[i]["List Price"])
    
    def add_product(self, productcode, description, listprice, qntyonpremises, reorderlvl, reorderqnty): 
        self.items[productcode] =  {"Product Code": productcode, "Description": description, "List Price": listprice, "Quantity on Premises": qntyonpremises, "Reorder Level": reorderlvl, "Reorder Quantity": reorderqnty}

    def del_product(self, productcode): #deletes the product 
        if productcode in self.items:
            self.items.pop(productcode)
            print("Product has been deleted!")
        else:
            print("The product code doesn't exist!")
    
    def change_product(self, productcode): #deals with making changes within the product file
        choice = {"1": "Description", "2": "List Price", "3": "Quantity on Premises", "4" :"Reorder Level","5": "Reorder Quantity"}
        if productcode in self.items:
            print("Here is the current state of information: ",self.items[productcode]) #displays the row corresponding to the product code and shows all the information it has currently
            for key, value in choice.items():
                print(key+".",value)
            option = input("What would you like to change: ") #the user picks an option based on what changes they want to make within that specfic row
            if option == "1":
                new_description = input("Enter the new description: ")
                self.items[productcode]["Description"] = new_description
            elif option == "2":
                new_listprice = input("Enter the new list price: ")
                self.items[productcode]["List Price"] = new_listprice
            elif option == "3":
                new_qntyonpremises = input("Enter the new quantity on premises: ")
                self.items[productcode]["Quantity on Premises"] = new_qntyonpremises
            elif option == "4": 
                new_reorderlvl = input("Enter the new reorder level: ")
                self.items[productcode]["Reorder Level"] = new_reorderlvl
            elif option == "5":
                new_reorderqnty = input("enter the new reorder quantity: ")
                self.items[productcode]["Reorder Quantity"] = new_reorderqnty
        else:
           print("The product code doesn't exist!")
    
    def bestorder(self, description): #checks for the best order 
        best_order = []
        for i in self.items:
            if self.items[i]["Description"] == description:
                best_order.append(self.items[i]["Product Code"])
        return(best_order)
    
    def find_descrip_by_productcode(self, productcode): 
        return self.items[productcode]["Description"]
    
class Customers:
    def __init__(self, filename):
        self.items = {}
        rf = open(filename, 'r')
        for line in rf:
            info = line.split(",")
            if len(info) == 8:
                temp_custnum_customer = (info[0].strip())
                self.items[temp_custnum_customer] = {"Customer Number": info[0].strip(), "Customer Name": info[1].strip(), "Street": info[2].strip(), "Number": info[3].strip(),"Town": info[4].strip(), "Postal Code": info[5].strip(), "Credit Limit": info[6].strip(), "Current Balance": info[7].strip()}
        if list(self.items.keys())[0] == "CustomerNumber":
            self.items.pop("CustomerNumber")
            

    def customer_names(self): #this prints all the customers' names
        print("Here are all the customer's names")
        for v in self.items.values():
            print(v)

    def display_customer_by_customercode(self, customer_num, choicenum): #displays customer information that the user chooses to see
        choice = {"0": "Customer Name", "1": "Street", "2": "Number", "3" :"Town", "4": "Postal code", "5": "Credit Limit", "6": "Current Balance", "7": " All", "8": "All Customers' Names","9": "Quit"}
        if customer_num in self.items:
            if int(choicenum) < 7:
                choicename = choice[choicenum]
                customer = self.items[customer_num]
                print("Here is the customer's " + choicename +":", customer[choicename])
            elif choicenum == "7":
                print(self.items[customer_num])
        else:
            print("No such customer exists!")
    
    def add_customer(self, custnum, custname, street, number, town, postalcode, creditlimit, currbalance):#adds information for a new customer
        self.items[custnum] =  {"Customer Number": custnum, "Customer Name": custname, "Street": street, "Number": number, "Town": town, "Postal Code": postalcode, "Credit Limit": creditlimit, "Current Balance": currbalance}

    def del_customer(self, custnum): #deletes a customer
        if custnum in self.items:
            self.items.pop(custnum)
            print("Customer has been deleted!")
        else:
            print("No such customer's exists!")
    
    def change_customer(self, custnum): #makes whatever changes the user chooses to make to the existing customer
        choice = {"1": "Customer Name", "2": "Street", "3" :"Number", "4": "Town", "5": "Postal Code", "6": "Credit Limit", "7": "Current Balance"}
        if custnum in self.items:
            print("Here is the current state of information: ",self.items[custnum])
            for key, value in choice.items():
                print(key+". ",value)
            option = input("What would you like to change: ")
            if option == "1":
                new_custname = input("Enter the new customer name: ")
                self.items[custnum]["Customer Name"] = new_custname
            elif option == "2":
                new_street = input("Enter the new street: ")
                self.items[custnum]["Street"] = new_street
            elif option == "3":
                new_number = input("Enter the new number: ")
                self.items[custnum]["Number"] = new_number
            elif option == "4": 
                new_town = input("Enter the new town: ")
                self.items[custnum]["Town"] = new_town
            elif option == "5":
                new_postalcode = input("Enter the new postal code: ")
                self.items[custnum]["Postal Code"] = new_postalcode
            elif option == "6":
                new_creditlimit = input("Enter new credit limit: ")
                self.items[custnum]["Credit Limit"] = new_creditlimit
            elif option == "7":
                new_currbalance = input("Enter new current balance: ")
                self.items[custnum]["Current Balance"] = new_currbalance
        else:
            print("No such customer exists!")
    
    def town(self, town): #gives the names of those living in the town which the user inputs
        flag = False
        for i in self.items:
            if town == self.items[i]["Town"]:
                print(self.items[i]["Customer Name"])
                flag = True
        if flag == False:
            print("No such town exists!")
    
    def find_ordersnumber_by_month(self, custnum): #prints out the names of all the customers who ordered on a specific date
        custname = []
        for i in self.items:
            for j in custnum:
                if j == self.items[i]["Customer Number"]:
                        custname.append(self.items[i]["Customer Name"])  
        print("Here are all the customers for the entered product code and date: ")
        print(custname)

class OrderDetails:
    def __init__(self, filename):
        self.items = {}
        rf = open(filename, 'r')
        for line in rf:
            info = line.split(",")
            if len(info) == 4:
                temp_oncn_orderdetails = (info[0].strip())
                self.items[temp_oncn_orderdetails] = {"Order Number": info[0].strip(), "Product Code": info[1].strip(), "Order Quantity": info[2].strip(), "Order Price": info[3].strip()}
        if list(self.items.keys())[0] == "OrderNumber":
            self.items.pop("OrderNumber")

    def display_orderdetails_by_ordernumber(self, order_number, choicenum): #displays information about a specfic order that the user chooses to see
        choice = {"0": "Product Code", "1": "Order Quantity", "2": "Order Price", "3" :"Display all", "4": "Quit"}
        if order_number in self.items:
            if int(choicenum) < 3:
                choicename = choice[choicenum]
                ordernum = self.items[order_number]
                print("Here is the order's " + choicename +":", ordernum[choicename]) 
            elif choicenum == "3":
                print(self.items[order_number])
        else:
            print("The order number doesn't exist!")
    
    def find_productcode_by_ordernum(self, ordernums): #gets the order number
        orders_on_day = []
        for i in self.items:
            if i in ordernums:
                orders_on_day.append(self.items[i])
        return orders_on_day

    def add_orderitem(self, ordernum, productcode, orderquantity, orderprice): #adds a new order to the order file
        self.items[ordernum] =  {"Order Number": ordernum, "Product Code": productcode, "Order Quantity": orderquantity, "Order Price": orderprice}

    def del_orderdetails(self, ordernum): #deletes the order
        if ordernum in self.items:
            self.items.pop(ordernum)
            print("Order details have been deleted!")
        else:
            print("The order number doesn't exist!")
    
    def change_orderdetails(self, ordernum): #makes changes that the user wishes to make within the exsiting order
        choice = {"Product Code": "1", "Order Quantity": "2", "Order Price": "3"}
        if ordernum in self.items:
            print("Here is the current state of information: ",self.items[ordernum])
            for key, value in choice.items():
                print(key+". ",value)
            option = input("What would you like to change: ")
            if option == "1":
                new_productcode = input("Enter the new product code: ")
                self.items[ordernum]["Product Code"] = new_productcode
            elif option == "2":
                new_orderqnty = input("Enter the new order quantity: ")
                self.items[ordernum]["Order Quantity"] = new_orderqnty
            elif option == "3":
                new_orderprice = input("Enter the new order price: ")
                self.items[ordernum]["Order Price"] = new_orderprice
        else:
            print()
    
    def find_ordersnumber_by_month(self, productcode): #gets the customer numbers
        ordersnum = []
        for i in self.items:
            if self.items[i]["Product Code"] == productcode:
                ordersnum.append(self.items[i]["Order Number"])
        return ordersnum
    
    def best_order_productcode(self, productcode): #best order depending on productcode, product code
        flag = False
        best_orders = {}
        for i in self.items:
            for p in productcode:
                if p == self.items[i]["Product Code"]:
                    flag = True
                    sum = float(self.items[i]["Order Quantity"])*float(self.items[i]["Order Price"])
                    best_orders[i] = sum
        if flag == False:
            print("No such product code exists in our order detail's file!")
        else:
            max_sum = max(best_orders.values())
            for i in best_orders:
                if best_orders[i] == max_sum:
                        best_order = best_orders[i]
                        best_order_format = "{:.2f}".format(best_order)
                        return(best_order_format)
                        

    def date_most_valuable(self): #Q10
        numbers = {}
        for i in self.items:
            sum = float(self.items[i]["Order Quantity"])*float(self.items[i]["Order Price"])
            numbers[i] = sum
        max_sum = max(numbers.values())
        for i in numbers:
            if numbers[i] == max_sum:
                return i

class Orders:
    def __init__(self, filename):
        self.items = {}
        rf = open(filename, 'r')
        for line in rf:
            info = line.split(",")
            if len(info) == 4: 
                temp_ordernumber_customer = (info[0].strip(),info[1].strip())
                self.items[temp_ordernumber_customer] = {"Order Number": info[0].strip(), "Customer Number": info[1].strip(), "Order Date": info[2].strip(), "Order Time": info[3].strip()}
        if list(self.items.keys())[0][0] == "OrderNumber" and list(self.items.keys())[0][1] == "CustomerNumber": #does not go in here
            self.items.pop(("OrderNumber","CustomerNumber"))


    def display_ordersby_ordernumber(self, ordernum, customernum, choicenum): #code would have to be both order number and customer number
        choice = {"0": "Order Date", "1": "Order Time", "2" :"Display all", "3": "Quit"}
        if (ordernum,customernum) in self.items:
            if int(choicenum) < 2:
                choicename = choice[choicenum]
                orders = self.items[(ordernum,customernum)]
                print("Here is the order's " + choicename +":", orders[choicename]) 
            elif choicenum == "2":
                print(self.items[(ordernum,customernum)])
        else:
            print("The order number and customer number don't exist in combination!")

    def add_order(self, ordernum, customernum, orderdate, ordertime): #adds a new order within the order file
        self.items[(ordernum,customernum)] =  {"Order Number": ordernum, "Customer Number": customernum, "Order Date": orderdate, "Order Time": ordertime}

    def del_orders(self, ordernum, custnum):
        if ordernum+custnum in self.items:
            self.items.pop((ordernum,custnum))
            print("Order has been deleted!")
        else:
            print("The order number and customer number don't exist in combination!")

    def change_orders(self, ordernum, custnum): #makes whatever changes that the user wishes to make within an existing order
        choice = { "Order Date": "1", "Order Time": "2"}
        if ordernum+custnum in self.items:
            print("Here is the current state of information: ",self.items[(ordernum,custnum)])
            for key, value in choice.items():
                print(key+". ",value, "\n")
            option = input("What would you like to change: ")
            if option == "1":
                new_orderdate = input("Enter the new order date: ")
                self.items[(ordernum,custnum)]["Order Date"] = new_orderdate
            elif option == "2":
                new_ordertime = input("Enter the new order time: ")
                self.items[(ordernum,custnum)]["Order Price"] = new_ordertime
        else:
            print("The order number and customer number don't exist in combination!")
    
    def find_ordersnumber_by_date(self, date): #gets the orders placed on a specific day
        orders_on_day = []
        for i in self.items:
            if self.items[i]["Order Date"][:7] == date: 
                orders_on_day.append(self.items[i]["Order Number"])
        return orders_on_day
    
    def find_ordersnumber_by_month(self, ordernum, month): #gets the customer numbers
        cust_num = []
        for i in self.items:
            for j in ordernum:
                if j == self.items[i]["Order Number"]: 
                    if self.items[i]["Order Date"][:7] == month:
                        cust_num.append(self.items[i]["Customer Number"])  
        return cust_num
    
    def max_val_order(self, ordernum): #displays the date when the most valuable order was placed
        flag = False
        for i in self.items:
            if ordernum == self.items[i]["Order Number"]:
                flag = True
                print("This is when the most valuable order was: ")
                print(self.items[i]["Order Date"])
        if flag == False:
            print("Order number does not exist!")

m = Main()
m.menu()
m.quit()