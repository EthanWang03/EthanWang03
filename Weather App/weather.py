import requests
#d9d94b6807846f7c9dae85931da43d6d

def get_weather_data(api_key, city):
    url = f"http://api.openweathermap.org/data/2.5/weather?q={city}&appid={api_key}"
    response = requests.get(url)
    data = response.json()
    return data

def display_weather_data(data):
    if data["cod"] == "404":
        print("City not found.")
    else:
        print(f"Weather in {data['name']}:")
        kelvin = data['main']['temp']
        celsius = round(kelvin - 273.15,2)
        print(f"Temperature: {celsius} C")
        print(f"Humidity: {data['main']['humidity']}%")
        print(f"Wind Speed: {data['wind']['speed']} m/s")
        print(f"Weather Conditions: {data['weather'][0]['description']}")

def main():
    api_key = "d9d94b6807846f7c9dae85931da43d6d" #API key
    city = input("Enter a city name: ")
    weather_data = get_weather_data(api_key, city)
    display_weather_data(weather_data)

if __name__ == "__main__":
    main()
