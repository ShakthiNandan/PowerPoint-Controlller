import requests
import time
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
from ctypes import cast, POINTER
from comtypes import CLSCTX_ALL
import pyautogui

# Volume control setup
devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = cast(interface, POINTER(IAudioEndpointVolume))

ESP_IP = "http://192.168.4.1"  # Default IP for ESP8266 in AP mode
VOLUME_STEP = 0.2 # Step to increase/decrease volume

def get_volume_action():
    try:
        response = requests.get(f"{ESP_IP}/getVolumeAction")
        if response.status_code == 200:
            return response.text
    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
    return None

def adjust_volume(action):
    current_volume = volume.GetMasterVolumeLevelScalar()
    if action == "increase":
        volume.SetMasterVolumeLevelScalar(min(current_volume + VOLUME_STEP, 1.0), None)
        print("Volume increased")
        pyautogui.press('right') 
    elif action == "decrease":
        volume.SetMasterVolumeLevelScalar(max(current_volume - VOLUME_STEP, 0.0), None)
        print("Volume decreased")
        pyautogui.press('left') 

while True:
    action = get_volume_action()
    if action == "increase" or action == "decrease":
        adjust_volume(action)
    # Poll every second
