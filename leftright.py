import requests
import time
import pyautogui

# Replace with the IP address of your ESP8266 (printed in the serial monitor)
ESP8266_IP = "http://192.168.175.243"

def get_action():
    try:
        response = requests.get(f"{ESP8266_IP}/getAction")
        if response.status_code == 200:
            return response.text
    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
    return None

def press(action):
    if action == "right":
        pyautogui.press('right') 
    elif action == "left":
        pyautogui.press('left') 

while True:
    action = get_action()
    if action == "right" or action == "left":
        press(action)
