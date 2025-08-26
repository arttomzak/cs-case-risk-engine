import requests
import os 
import json


from dotenv import load_dotenv
load_dotenv()

API_KEY = os.getenv("STEAMWEBAPI_KEY")

base_url = "https://www.steamwebapi.com/steam/api/cs/collection"

# hardcoded for now, gonna want to pull from user input down the line
slug = "the-revolver-case-collection"


final_url = f"{base_url}/{slug}"

response = requests.get(final_url, params={"key": API_KEY})

if response.ok:
    data = response.json()

    filepath = f"data/{slug}.json"

    with open(filepath, "w") as file:
        json.dump(data, file, indent=2)

    print(f"Data saved to {filepath}")

else:
    print(f"Request failed! {response.status_code}")
