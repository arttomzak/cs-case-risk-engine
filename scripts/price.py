import requests
import os 
from dotenv import load_dotenv

load_dotenv()

API_KEY = os.getenv("CSFLOAT_API_KEY")

item_name = "AK-47 | Redline (Field-Tested)"
sort = "lowest_price"
limit = 1


response = requests.get(
    "https://csfloat.com/api/v1/listings",
    headers={"Authorization": API_KEY},
    params={"market_hash_name": item_name, "sort_by": sort, "limit": limit}
)

print(response.json())
