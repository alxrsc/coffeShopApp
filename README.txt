Project's architecture -  Coffee Shop App

-> Locations Directory
	- Individual Directory for each location
		- csv for personel
		- csv for stock
		- csv for orders

-> Classes Directory
	-> Employee Class
		-> atributes
			- firstName, lastName
			- working hours
			- salary per hour
		-> methods
			
	-> Barista Class extends Employee
		-> atributes
			- INHERITED
		-> methods
			- makeCoffee(string coffeeType, string milkType)
	deleted	- recieveOrder(<map> lastOrder)
			- prepareOrder(<map> lastOrder)
	deleted	- sendOrder(<map> order)
	-> Server Class
		-> atributes
			- INHERITED	
			- <map> lastOrder (product:count)
		-> methods
			- takeOrder()
			- forwardOrder(<map> lastOrder)
			- serveOrder(<map> products)
			- serveBill(string paymentType, int total)
			- recievePayment(string paymentType, int total)
	-> Manager Class
		-> atributes
			- INHERITED

		-> methods
			- changeShift(Employee* employee)
			- addPersonel(Employee* employee)
			- removePersonel(Employee* employee)	
			- closeDay()			

	-> Client Class (keep the client in the account until he pays unpaid orders)
		-> atributes
			- int fidelityScore
		-> methods
			- order()
			- requestBill(string paymentType)
			- payBill(string paymentType)
		
	-> CSVHandler
		-> methods
			- writeEmployee(Employee* employee)
			- deleteEmployee(Employee* employee)
			- editEmployee(Employee* employee)
			- addStock(<map> productsToAdd)
			- removeStock(<map> productsToRemove)
			- readStock()
			- checkStock(string product)
			- writeOrder(<map> productsOrdered, string clientFirstName, string clientLastName, int total)
			- calculateFidelityScore(string clientFirstName, string clientLastName)
			- readSalariesForToday(int date)
			- readDaysProfit(int date) 
			
-------------------------------

Methods:

~ makeCoffee(string coffeeType, string milkType) -> may return an error if the type of coffe is not available in stock, open another pack of beans if there is not enough in the existing one, similar for milkType

~ recieveOrder(<map> lastOrder) -> take the order from the server

~ prepareOrder(<map> lastOrder) -> execute the order, remove the products from the csv, and call the method to send it to the server

~ sendOrder(<map> order) -> send the order to the server

~ takeOrder() -> returns a map of products ordered and count of each product that will be stored in the server object

~ forwardOrder(<map> lastOrder) -> take the order to the barista

~ serveOrder(<map> products) -> return 0 if there is no error in delivering the order and empty servers queue

~ serveBill(string paymentType, int total) -> take bill to table

~ changeShift(Employee* employee) -> change the working hours of the respective employee (including manager) and rewrite in personel csv

~ addPersonel(Employee* employee) -> add the employee to the csv with his respective data

~ removePersonel(Employee* employee) -> the employee from the csv with his respective data	

~ closeDay() -> create the report for the days profit

~ requestBill(string paymentType) -> signal the server to bring the bill

~ payBill(string paymentType) -> print a message with the table, sum paid and payment method

~ order() -> enter a list of wished products

~ writeEmployee(Employee* employee)

~ deleteEmployee(Employee* employee)

~ editEmployee(Employee* employee)

~ addStock(<map> productsToAdd)

~ removeStock(<map> productsToRemove)

~ readStock() -> read the stock and order anything with quantity <=0 and send costs to the daily calculator

~ checkStock(string product) -> return true or false depending on the products availability

~ writeOrder(<map> productsOrdered, string clientFirstName, string clientLastName, int total, int date)

~ calculateFidelityScore(string clientFirstName, string clientLastName) -> search for his orders by name, calculate based on client's spending

~ readSalariesForToday(int date) -> read from personel.csv to consider costs to profit

~ readDaysProfit(int date) -> search for orders with respective date and calculate the profit considering salaries 

