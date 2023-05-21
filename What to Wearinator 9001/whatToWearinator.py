import sqlite3
import os
import random
import requests

#get weather data from weather API
def get_weather_data(api_key, city):
    url = f"http://api.openweathermap.org/data/2.5/weather?q={city}&appid={api_key}"
    response = requests.get(url)
    data = response.json()
    return data

class Clothing:
    #init database
    def __init__(self, reset=True):

        if reset:
            os.remove("cloths.db")

        self.conn = sqlite3.connect("cloths.db")
        self.conn.commit()

    #create tables
    def create_tables(self):

        #Hat
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Hats(
                HAT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                HAT_DISC TEXT NOT NULL,
                HAT_COLOUR TEXT NOT NULL,
                HAT_TEMP TEXT NOT NULL);
                ''')

        #Shirt
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Shirts(
                SHIRT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                SHIRT_DISC TEXT NOT NULL,
                SHIRT_COLOUR TEXT NOT NULL,
                SHIRT_TEMP TEXT NOT NULL);
                ''')

        #Pants
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Pants(
                PANT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                PANT_DISC TEXT NOT NULL,
                PANT_COLOUR TEXT NOT NULL,
                PANT_TEMP TEXT NOT NULL);
                ''')

        #Jacket
        self.conn.execute('''
            CREATE TABLE IF NOT EXISTS Jackets(
                JACKET_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                JACKET_DISC TEXT NOT NULL,
                JACKET_COLOUR TEXT NOT NULL,
                JACKET_TEMP TEXT NOT NULL);
                ''')

        self.conn.commit()

    #insert row into table
    def add_table(self, table, CAP, disc, colour, temp):
        query = f'''
            INSERT INTO {table} ({CAP}_DISC, {CAP}_COLOUR, {CAP}_TEMP)
            VALUES (?, ?, ?)
        '''
        self.conn.execute(query, (disc, colour, temp))
        self.conn.commit()
    
    #display table
    def display_table(self, table):
        query = f'''
            SELECT * FROM {table}
        '''
        result = self.conn.execute(query).fetchall()

        print("")
        if result:
            print(f"{table} Table:")
            print("ID | DISC             | COLOUR    | TEMP")
            print("----------------------------------------")
            for row in result:
                id, disc, colour, temp = row
                print(f"{id:<2} | {disc:<16} | {colour:<9} | {temp}")

        else:
            print(f"No data found in the {table} table.")
        print("")

    #get random hat
    def get_hat(self, temp):
        query = "SELECT HAT_DISC, HAT_COLOUR FROM Hats WHERE HAT_TEMP=?"
        cursor = self.conn.execute(query, (temp,))
        hats = cursor.fetchall()
        cursor.close()

        if hats:
            random_hat = random.choice(hats)
            hat_disc, hat_colour = random_hat
            print(f"Hat    | {hat_disc:<16} | {hat_colour}")
        else:
            print(f"No hat found with temperature '{temp}'.")
    
    #get random shirt
    def get_shirt(self, temp):
        query = "SELECT SHIRT_DISC, SHIRT_COLOUR FROM Shirts WHERE SHIRT_TEMP=?"
        cursor = self.conn.execute(query, (temp,))
        shirts = cursor.fetchall()
        cursor.close()

        if shirts:
            random_shirt = random.choice(shirts)
            shirt_disc, shirt_colour = random_shirt
            print(f"Shirt  | {shirt_disc:<16} | {shirt_colour}")
        else:
            print(f"No Shirt found with temperature '{temp}'.")

    #get random pants
    def get_pants(self, temp):
        query = "SELECT PANT_DISC, PANT_COLOUR FROM Pants WHERE PANT_TEMP=?"
        cursor = self.conn.execute(query, (temp,))
        shirts = cursor.fetchall()
        cursor.close()

        if shirts:
            random_pants = random.choice(shirts)
            pants_disc, pants_colour = random_pants
            print(f"Pants  | {pants_disc:<16} | {pants_colour}")
        else:
            print(f"No Pants found with temperature '{temp}'.")

    #get random jacket
    def get_jacket(self, temp):
        query = "SELECT JACKET_DISC, JACKET_COLOUR FROM Jackets WHERE JACKET_TEMP=?"
        cursor = self.conn.execute(query, (temp,))
        shirts = cursor.fetchall()
        cursor.close()

        if shirts:
            random_jacket = random.choice(shirts)
            jacket_disc, jacket_colour = random_jacket
            print(f"Jacket | {jacket_disc:<16} | {jacket_colour}")
        else:
            print(f"No Jacket found with temperature '{temp}'.")

    #delete a row from a table using ID
    def delete_item(self, table, CAP, id):
        query = f"DELETE FROM {table} WHERE {CAP}_ID=?"
        self.conn.execute(query, (id,))
        self.conn.commit()

    #menu system
    def main():
        clothing = Clothing(False)
        clothing.create_tables()
        while True:
            print("\nMenu:")
            print("1. Add a new item")
            print("2. Delete item")
            print("3. Display all tables")
            print("4. Generate a random outfit by temperature")
            print("5. Exit")

            choice = input("Enter your choice (1-5): ")

            if choice == "1":
                print("\nItem Menu:")
                print("1. Add a new Hat")
                print("2. Add a new Shirt")
                print("3. Add a new pair of Pants")
                print("4. Add a new Jacket")
                print("5. Back")

                item = input("Enter your choice (1-5): ")

                if item == "1":
                    name = input("Enter the Hats name: ").strip()
                    colour = input("Enter the Hats color: ").strip()
                    temperature = input("Enter the Hats weather: ").strip()
                    clothing.add_table("Hats", "HAT", name, colour, temperature)

                if item == "2":
                    name = input("Enter the Shirts name: ").strip()
                    colour = input("Enter the Shirts color: ").strip()
                    temperature = input("Enter the Shirts weather: ").strip()
                    clothing.add_table("Shirts", "SHIRT", name, colour, temperature)

                if item == "3":
                    name = input("Enter the Pants name: ").strip()
                    colour = input("Enter the Pants color: ").strip()
                    temperature = input("Enter the Pants weather: ").strip()
                    clothing.add_table("Pants", "PANT", name, colour, temperature)

                if item == "4":
                    name = input("Enter the Jackets name: ").strip()
                    colour = input("Enter the Jackets color: ").strip()
                    temperature = input("Enter the Jackets weather: ").strip()
                    clothing.add_table("Jackets", "JACKET", name, colour, temperature)

            elif choice == "2":
                clothing.display_table("Hats")
                clothing.display_table("Shirts")
                clothing.display_table("Pants")
                clothing.display_table("Jackets")

                print("\nItem Menu:")
                print("1. Delete a Hat")
                print("2. Delete a Shirt")
                print("3. Delete a pair of Pants")
                print("4. Delete a Jacket")
                print("5. Back")

                item = input("Enter your choice (1-5): ")

                if item == "1":
                    id = input("Enter the Hats ID: ")
                    clothing.delete_item("Hats", "HAT",id)
                
                elif item == "2":
                    id = input("Enter the Shirts ID: ")
                    clothing.delete_item("Shirts", "SHIRT",id)

                elif item == "3":
                    id = input("Enter the Pants ID: ")
                    clothing.delete_item("Pants", "PANT",id)

                elif item == "4":
                    id = input("Enter the Jackets ID: ")
                    clothing.delete_item("Jackets", "JACKET",id)   

            elif choice == "3":
                clothing.display_table("Hats")
                clothing.display_table("Shirts")
                clothing.display_table("Pants")
                clothing.display_table("Jackets")
            
            elif choice == "4":
                api_key = "d9d94b6807846f7c9dae85931da43d6d" #API key
                city = input("Enter a City name: ")
                weather_data = get_weather_data(api_key, city)
                data = weather_data
                kelvin = data['main']['temp']
                temperature = round(kelvin - 273.15,2)
                if float(temperature) > 24.0:
                    temp = "Hot"
                elif float(temperature)  > 15.0:
                    temp = "Warm"
                elif float(temperature)  > 0.0:
                    temp = "Light"
                elif float(temperature)  > -6.0:
                    temp = "Cool"
                else:
                    temp = "Cold"

                print(f"\nGenerating Outfit for {temp} Weather!\n")
                
                clothing.get_hat(temp)
                clothing.get_shirt(temp)
                clothing.get_pants(temp)
                if temp != "Hot":
                    clothing.get_jacket(temp)


            elif choice == "5":
                break
            
            else:
                print("Invalid choice. Please try again.")

        #original clothing insertion

        #clothing.add_table("Hats", "HAT", "Mesh Hat", "White", "Hot")
        #clothing.add_table("Hats", "HAT", "Baseball Cap", "White", "Warm")
        #clothing.add_table("Hats", "HAT", "Bucket Hat", "Green", "Light")
        #clothing.add_table("Hats", "HAT", "Beanie", "Black", "Cool")
        #clothing.add_table("Hats", "HAT", "Racoon Hat", "Brown", "Cold")

        #clothing.add_table("Shirts", "SHIRT", "Sports Shirt", "Blue", "Hot")
        #clothing.add_table("Shirts", "SHIRT", "T Shirt", "Purple", "Warm")
        #clothing.add_table("Shirts", "SHIRT", "Button Up", "Yellow", "Light")
        #clothing.add_table("Shirts", "SHIRT", "Long Sleeve", "Black", "Cool")
        #clothing.add_table("Shirts", "SHIRT", "Sweater", "Red", "Cold")

        #clothing.add_table("Pants", "PANT", "Shorts", "White", "Hot")
        #clothing.add_table("Pants", "PANT", "Sweat Pants", "Grey", "Warm")
        #clothing.add_table("Pants", "PANT", "Jeans", "Blue", "Light")
        #clothing.add_table("Pants", "PANT", "khaki", "Brown", "Cool")
        #clothing.add_table("Pants", "PANT", "Snow Pants", "Black", "Cold")

        #clothing.add_table("Jackets", "JACKET", "Bomber Jacket", "White", "Warm")
        #clothing.add_table("Jackets", "JACKET", "Summer Jacket", "Blue", "Light")
        #clothing.add_table("Jackets", "JACKET", "Wind breaker", "Black", "Cool")
        #clothing.add_table("Jackets", "JACKET", "Winter Jacket", "Black", "Cold")

if __name__ == "__main__":
    Clothing.main()
        