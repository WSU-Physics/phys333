import spotipy
from spotipy.oauth2 import SpotifyOAuth
import os
import serial
import time
import pyfirmata
from pyfirmata import Arduino

CLIENT_ID = os.environ.get('CLIENT_ID')
CLIENT_SECRET = os.environ.get('CLIENT_SECRET')
REDIRECT_URI = 'https://www.youtube.com/watch?v=dQw4w9WgXcQ'

sp = spotipy.Spotify(
    auth_manager = SpotifyOAuth(
        client_id = CLIENT_ID,
        client_secret = CLIENT_SECRET,
        redirect_uri = REDIRECT_URI,
        scope = 'user-read-currently-playing'
    )
)

#make this the port arduino is attached to
serialcomm = serial.Serial('COM11', 9600)
serialcomm.timeout = 1

board = serial.Serial('COM11') # Replace with your actual port

while True:
    current_track = sp.current_user_playing_track()

    if current_track is not None:
        current_track = sp.current_user_playing_track()
        song_name = current_track['item']['name']
        artist_name = current_track['item']['artists'][0]['name']
        divider = ' by '
        
        # print(song_name)
        # print(artist_name)   

    else: 
        print("UH OH! we it's broken - Not playing any music!")

    serialcomm.write(song_name.encode())
    serialcomm.write(divider.encode())
    serialcomm.write(artist_name.encode())
    #board.digital[3].write(0) # Sets pin 3 to LOW pin 2 and 3 are attached the the attackInterupt()


        #this is very much needed or no response from the uno
    time.sleep(0.5)
    print(serialcomm.readline().decode('ascii'))
 

serialcomm.close()

